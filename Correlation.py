import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import butter, filtfilt, correlate
from sklearn.metrics import mean_squared_error
from scipy.interpolate import interp1d
import wfdb

# --- Oscilloscope Data ---
oscilloscope_dir = "/home/"  # Update with your directory
patient_scope = "04"  # Replace with the oscilloscope patient identifier or file name
oscilloscope_file_path = f"{oscilloscope_dir}scope_0-{patient_scope}.csv"  # Updated file path

# Load oscilloscope data
oscilloscope_data = pd.read_csv(oscilloscope_file_path, skiprows=2, header=None)
oscilloscope_data = oscilloscope_data.iloc[:, :2]
oscilloscope_data.columns = ["second", "Volt"]
oscilloscope_data['second'] = pd.to_numeric(oscilloscope_data['second'], errors='coerce')
oscilloscope_data['Volt'] = pd.to_numeric(oscilloscope_data['Volt'], errors='coerce')
oscilloscope_data.dropna(inplace=True)
 
# Shift time to start at 0 seconds without removing any data
time2 = oscilloscope_data['second'].to_numpy()
time2 -= time2.min()  # Shift to start from 0 seconds
voltage2 = oscilloscope_data['Volt'].to_numpy()

# Resample oscilloscope data to 2.777 ms time interval
time_interval = 0.002777  # 2.777 ms
new_time2 = np.arange(time2[0], time2[-1], time_interval)  # New time array with 2.777 ms intervals

# Interpolate voltage data to match the new time array
interpolator = interp1d(time2, voltage2, kind='linear', fill_value="extrapolate")
voltage2_resampled = interpolator(new_time2)

# Remove samples up to 0.4 seconds and shift the signal
remove_time = 0.4  # Remove samples up to 0.35 seconds
valid_indices = new_time2 >= remove_time  # Find indices of time >= 0.35 seconds

# Keep only valid samples and shift the time array
new_time2 = new_time2[valid_indices] - remove_time
voltage2_resampled = voltage2_resampled[valid_indices]

# --- MIT-BIH Patient Data ---
patient_mit = "104"  # Patient number
record_path = f"mitdb/{patient_mit}"  # Path to the MIT-BIH record
record = wfdb.rdrecord(record_path, channels=[0])

# Extract ECG signal
ecg_signal = record.p_signal[:, 0]
sampling_rate = record.fs
time = np.array([i / sampling_rate for i in range(len(ecg_signal))])

# Limit both signals to 4 seconds
max_time = 4  # 4 seconds limit
ecg_limit_index = np.where(time >= max_time)[0][0]
oscilloscope_limit_index = np.where(new_time2 >= max_time)[0][0]

ecg_signal = ecg_signal[:ecg_limit_index]
time = time[:ecg_limit_index]
voltage2_resampled = voltage2_resampled[:oscilloscope_limit_index]
new_time2 = new_time2[:oscilloscope_limit_index]

# Normalize both signals
ecg_norm = (ecg_signal - np.mean(ecg_signal)) / np.std(ecg_signal)
voltage2_norm = (voltage2_resampled - np.mean(voltage2_resampled)) / np.std(voltage2_resampled)

# --- Bandpass Filter (0.5 Hz to 40 Hz) ---
low_cutoff = 0.5  # 0.5 Hz
high_cutoff = 40  # 40 Hz
nyquist_freq = 0.5 * sampling_rate
normalized_low_cutoff = low_cutoff / nyquist_freq
normalized_high_cutoff = high_cutoff / nyquist_freq

# Design the bandpass filter
b, a = butter(4, [normalized_low_cutoff, normalized_high_cutoff], btype='bandpass')
voltage2_filtered = filtfilt(b, a, voltage2_norm)

# --- Adjust Signal Lengths ---
min_length = min(len(ecg_norm), len(voltage2_filtered))
ecg_trimmed = ecg_norm[:min_length]
voltage2_trimmed = voltage2_filtered[:min_length]

# --- Correlation and Alignment ---
correlation = correlate(ecg_trimmed, voltage2_trimmed, mode="full")
lag = np.argmax(correlation) - (len(ecg_trimmed) - 1)

# Align the oscilloscope signal
if lag > 0:
    aligned_ecg = ecg_trimmed[lag:]
    aligned_voltage = voltage2_trimmed[:len(aligned_ecg)]
else:
    aligned_voltage = voltage2_trimmed[-lag:]
    aligned_ecg = ecg_trimmed[:len(aligned_voltage)]

# --- RMSE and Percentage Errors ---
rmse_before = np.sqrt(mean_squared_error(ecg_trimmed, voltage2_trimmed))
rmse_after = np.sqrt(mean_squared_error(aligned_ecg, aligned_voltage))

range_ecg = np.max(ecg_trimmed) - np.min(ecg_trimmed)
error_before = (rmse_before / range_ecg) * 100
error_after = (rmse_after / range_ecg) * 100
percentage_reduction = error_before - error_after

# --- Plotting ---
plt.figure(figsize=(19, 5))

# Plot correlation
plt.subplot(1, 3, 1)
plt.plot(correlation, label="Correlation", color="purple")
plt.title("Cross-Correlation", fontsize=12)
plt.xlabel("Lag", fontsize=10)
plt.ylabel("Correlation Coefficient", fontsize=10)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(fontsize=9)

# Plot original and aligned signals
plt.subplot(1, 3, 2)
plt.plot(ecg_trimmed, label="MIT-BIH ECG (Trimmed)", color="blue", linewidth=1)
plt.plot(voltage2_trimmed, label="Oscilloscope (Trimmed)", color="red", linestyle="--", linewidth=1)
plt.title("Signals Before Alignment", fontsize=12)
plt.legend(fontsize=9)
plt.grid(True, linestyle='--', alpha=0.6)

plt.subplot(1, 3, 3)
plt.plot(aligned_ecg, label="MIT-BIH ECG (Aligned)", color="blue", linewidth=1)
plt.plot(aligned_voltage, label="Oscilloscope (Aligned)", color="green", linestyle="--", linewidth=1)
plt.title("Signals After Alignment", fontsize=12)
plt.legend(fontsize=9)
plt.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.show()

# Print RMSE and percentage errors
print(f"RMSE Before Alignment: {rmse_before:.4f}")
print(f"RMSE After Alignment: {rmse_after:.4f}")
print(f"Percentage Error Before Alignment: {error_before:.2f}%")
print(f"Percentage Error After Alignment: {error_after:.2f}%")
print(f"Percentage Reduction in Error: {percentage_reduction:.2f}%")

# --- Truncate Aligned Signals to First 550 Samples ---
max_samples = 550
aligned_ecg_550 = aligned_ecg[:max_samples]
aligned_voltage_550 = aligned_voltage[:max_samples]

# --- Recalculate RMSE and Percentage Errors ---
rmse_after_550 = np.sqrt(mean_squared_error(aligned_ecg_550, aligned_voltage_550))

# Range of the original ECG signal for percentage error calculation
range_ecg = np.max(ecg_trimmed) - np.min(ecg_trimmed)

# Percentage errors
error_before = (rmse_before / range_ecg) * 100
error_after_550 = (rmse_after_550 / range_ecg) * 100
percentage_reduction_550 = error_before - error_after_550

# --- Print Metrics ---
print(f"RMSE Before Alignment: {rmse_before:.4f}")
print(f"RMSE After Alignment (First 550 Samples): {rmse_after_550:.4f}")
print(f"Percentage Error Before Alignment: {error_before:.2f}%")
print(f"Percentage Error After Alignment (First 550 Samples): {error_after_550:.2f}%")
print(f"Percentage Reduction in Error (First 550 Samples): {percentage_reduction_550:.2f}%")

# --- Plot First 550 Samples of Aligned Signals ---
plt.figure(figsize=(12, 6))
plt.plot(np.arange(max_samples), aligned_ecg_550, label="ECG Signal (First 550 Samples)", color="blue")
plt.plot(np.arange(max_samples), aligned_voltage_550, label="Aligned Oscilloscope Signal (First 550 Samples)", color="green")
plt.title("First 550 Samples of Aligned Signals")
plt.xlabel("Sample Number")
plt.ylabel("Amplitude")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
