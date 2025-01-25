import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import wfdb
from scipy.signal import resample, correlate, butter, filtfilt

# Oscilloscope Data Loading
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

# Resample the oscilloscope signal to 2.777 ms time interval
target_interval = 2.77 / 1000  # 2.777 ms in seconds
target_length = int((time2[-1] - time2[0]) / target_interval)  # Calculate the target number of samples
time_resampled = np.linspace(time2[0], time2[-1], target_length)
voltage_resampled = resample(voltage2, target_length)

# MIT-BIH Patient Data
patient_mit = "104"  # Patient number
record_path = f"mitdb/{patient_mit}"  # Path to the MIT-BIH record
record = wfdb.rdrecord(record_path, channels=[0])

# Extract ECG signal
ecg_signal = record.p_signal[:, 0]
sampling_rate = record.fs
time = np.array([i / sampling_rate for i in range(len(ecg_signal))])

# Match the time range for both signals
start_time = time_resampled[0]  # Start time for both signals
end_time = time_resampled[-1]   # End time for both signals

# Extract the indices for the MIT-BIH signal that match the oscilloscope signal's time range
mit_start_idx = np.where(time >= start_time)[0][0]
mit_end_idx = np.where(time <= end_time)[0][-1]

# Extract the MIT-BIH signal and time for the matching range
time_mit_matched = time[mit_start_idx:mit_end_idx + 1]
ecg_signal_matched = ecg_signal[mit_start_idx:mit_end_idx + 1]

# Equalize the number of samples by slicing
min_samples = min(len(voltage_resampled), len(ecg_signal_matched))
time_resampled = time_resampled[:min_samples]
voltage_resampled = voltage_resampled[:min_samples]
time_mit_matched = time_mit_matched[:min_samples]
ecg_signal_matched = ecg_signal_matched[:min_samples]

# Define the window for the oscilloscope signal (start and end points)
oscilloscope_window_start = 0  # Set your start point for the oscilloscope window (in sample index)
oscilloscope_window_end = 552   # Set your end point for the oscilloscope window (in sample index)

# Define the window for the ECG signal (start and end points)
ecg_window_start = 6         # Set your start point for the ECG window (in sample index)
ecg_window_end = 506         # Set your end point for the ECG window (in sample index)

# Extract the subset of the oscilloscope signal based on the window
oscilloscope_window = voltage_resampled[oscilloscope_window_start:oscilloscope_window_end]
time_oscilloscope_window = time_resampled[oscilloscope_window_start:oscilloscope_window_end]

# Extract the subset of the ECG signal based on the window
ecg_window = ecg_signal_matched[ecg_window_start:ecg_window_end]
time_ecg_window = time_mit_matched[ecg_window_start:ecg_window_end]

# Normalize the oscilloscope signal window
oscilloscope_window_normalized = (oscilloscope_window - np.min(oscilloscope_window)) / (np.max(oscilloscope_window) - np.min(oscilloscope_window))

# Bandpass filter design for oscilloscope signal
lowcut = 0.5  # Low cutoff frequency (Hz)
highcut = 125.0  # High cutoff frequency (Hz)
fs = 1 / (time_resampled[1] - time_resampled[0])  # Sampling frequency (Hz)

# Design the 4th-order Butterworth bandpass filter
b, a = butter(4, [lowcut / (0.5 * fs), highcut / (0.5 * fs)], btype='band')

# Apply the filter to the oscilloscope signal
oscilloscope_window_filtered = filtfilt(b, a, oscilloscope_window_normalized)

# Normalize the ECG signal window
ecg_window_normalized = (ecg_window - np.min(ecg_window)) / (np.max(ecg_window) - np.min(ecg_window))

# Ensure both signals have the same amplitude range for comparison
# Normalize the oscilloscope and ECG signals to have the same peak amplitude (0 to 1)
min_ecg = np.min(ecg_window_normalized)
max_ecg = np.max(ecg_window_normalized)
min_osc = np.min(oscilloscope_window_filtered)
max_osc = np.max(oscilloscope_window_filtered)

# Scale both signals to the same range (0 to 1)
oscilloscope_window_filtered_scaled = (oscilloscope_window_filtered - min_osc) / (max_osc - min_osc)
ecg_window_normalized_scaled = (ecg_window_normalized - min_ecg) / (max_ecg - min_ecg)

# Calculate the normalized cross-correlation
cross_corr = correlate(oscilloscope_window_filtered_scaled - np.mean(oscilloscope_window_filtered_scaled),
                       ecg_window_normalized_scaled - np.mean(ecg_window_normalized_scaled), mode='full')
normalized_cross_corr = cross_corr / (np.std(oscilloscope_window_filtered_scaled) * np.std(ecg_window_normalized_scaled) * len(oscilloscope_window_filtered_scaled))

# Print the maximum normalized cross-correlation value
print(f"Normalized cross-correlation value: {np.max(normalized_cross_corr):.6f}")

# Calculate the time shift between the oscilloscope and ECG signals
time_shift = time_oscilloscope_window[0] - time_ecg_window[0]

# Shift the time of the ECG window to align it with the oscilloscope signal
time_ecg_window_shifted = time_ecg_window + time_shift

# Plot the oscilloscope signal window (filtered and normalized)
plt.figure(figsize=(10, 5))
plt.plot(time_oscilloscope_window, oscilloscope_window_filtered_scaled, label='Oscilloscope Signal (Windowed, Filtered, Normalized)', color='red', linewidth=1.5)
plt.title("Oscilloscope Signal (Windowed, Filtered, Normalized)")
plt.xlabel("Time (seconds)")
plt.ylabel("Normalized Amplitude")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# Plot the matched MIT-BIH ECG signal window (shifted)
plt.figure(figsize=(10, 5))
plt.plot(time_ecg_window_shifted, ecg_window_normalized_scaled, label='MIT-BIH ECG Signal (Windowed, Normalized)', color='blue', linewidth=1.5)
plt.title("MIT-BIH ECG Signal (Windowed, Normalized, Shifted)")
plt.xlabel("Time (seconds)")
plt.ylabel("Normalized Amplitude")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# Plot the oscilloscope signal and MIT-BIH ECG signal together
plt.figure(figsize=(10, 5))
plt.plot(time_oscilloscope_window, oscilloscope_window_filtered_scaled, label='Oscilloscope Signal (Windowed, Filtered, Normalized)', color='red', linewidth=1.5)
plt.plot(time_ecg_window_shifted, ecg_window_normalized_scaled, label='MIT-BIH ECG Signal (Windowed, Normalized)', color='blue', linewidth=1.5)
plt.title("Comparison of Oscilloscope Signal and MIT-BIH ECG Signal")
plt.xlabel("Time (seconds)")
plt.ylabel("Normalized Amplitude")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()


