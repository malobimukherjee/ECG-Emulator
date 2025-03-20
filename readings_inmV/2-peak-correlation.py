import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import wfdb
from scipy.signal import resample, correlate

# List of patient records to plot
patients = ["100", "102", "103", "104"]
record_path_base = "mitdb/"  # Path to the MIT-BIH database
oscilloscope_dir = "/home/"  # Update with your directory

plt.figure(figsize=(12, 8))

for i, patient in enumerate(patients, 1):
    # Load MIT-BIH ECG Data
    record_path = f"{record_path_base}{patient}"
    record = wfdb.rdrecord(record_path, channels=[0])
    ecg_signal = record.p_signal[:, 0] / 1000
    sampling_rate = record.fs
    time_mit = np.array([j / sampling_rate for j in range(len(ecg_signal))])
    max_index = np.where(time_mit <= 1.5)[0][-1]
    time_mit = time_mit[:max_index + 1]
    ecg_signal = ecg_signal[:max_index + 1]
    
    # Load Oscilloscope Data
    oscilloscope_file_path = f"{oscilloscope_dir}scope_{patient}.csv"
    oscilloscope_data = pd.read_csv(oscilloscope_file_path, skiprows=2, header=None)
    oscilloscope_data = oscilloscope_data.iloc[:, :2]
    oscilloscope_data.columns = ["second", "Volt"]
    oscilloscope_data['second'] = pd.to_numeric(oscilloscope_data['second'], errors='coerce')
    oscilloscope_data['Volt'] = pd.to_numeric(oscilloscope_data['Volt'], errors='coerce')
    oscilloscope_data.dropna(inplace=True)
    
    time2 = oscilloscope_data['second'].to_numpy()
    time2 -= time2.min()
    voltage2 = oscilloscope_data['Volt'].to_numpy()
    
    target_interval = 2.778 / 1000
    target_length = int((time2[-1] - time2[0]) / target_interval)
    time_resampled = np.linspace(time2[0], time2[-1], target_length)
    voltage_resampled = resample(voltage2, target_length)
    
    if patient == '100':
        min_index = np.where(time_resampled >= 0.37)[0][0]
        max_index = np.where(time_resampled <= 1.87)[0][-1]
    elif patient == '102':
        min_index = np.where(time_resampled >= 0.35)[0][0]
        max_index = np.where(time_resampled <= 1.85)[0][-1]
    elif patient == '103':
        min_index = np.where(time_resampled >= 0)[0][0]
        max_index = np.where(time_resampled <= 1.5)[0][-1]
    elif patient == '104':
        min_index = np.where(time_resampled >= 1.25)[0][0]
        max_index = np.where(time_resampled <= 2.75)[0][-1]
    
    time_resampled = time_resampled[min_index:max_index + 1]
    voltage_resampled = voltage_resampled[min_index:max_index + 1]
    
    # Align signals to start at the same time
    time_shift = time_resampled[0] - time_mit[0] if patient == '100' else time_resampled[np.argmax(voltage_resampled)] - time_mit[np.argmax(ecg_signal)]
    time_mit_shifted = time_mit + time_shift
    
    # Align MIT-BIH ECG to oscilloscope offset level
    ecg_offset = np.mean(voltage_resampled) - np.mean(ecg_signal)
    ecg_signal_aligned = ecg_signal + ecg_offset
    
    # Calculate normalized cross-correlation
    cross_corr = correlate(voltage_resampled - np.mean(voltage_resampled), ecg_signal_aligned - np.mean(ecg_signal_aligned), mode='full')
    normalized_cross_corr = cross_corr / (np.std(voltage_resampled) * np.std(ecg_signal_aligned) * len(voltage_resampled))
    
    print(f"Normalized cross-correlation value for patient {patient}: {np.max(normalized_cross_corr):.6f}")
    
    # Plot comparison of MIT-BIH ECG and Oscilloscope signal
    plt.subplot(2, 2, i)
    plt.plot(time_mit_shifted, ecg_signal_aligned, label=f'MIT-BIH ECG - Patient {patient}', color='blue', linewidth=1.2)
    plt.plot(time_resampled, voltage_resampled, label=f'Oscilloscope - Patient {patient}', color='red', linestyle='dashed', linewidth=1.2)
    plt.title(f'Comparison of MIT-BIH and Oscilloscope - Patient {patient}')
    plt.xlabel("Time (seconds)")
    plt.ylabel("Voltage (V)")
    plt.legend()
    plt.grid(True)

plt.tight_layout()
plt.show()
