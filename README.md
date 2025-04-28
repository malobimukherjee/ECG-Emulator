# ECG-Emulator

## Demonstration and PSOC/RPI Code Implementation

Folder - PSOC contains: 
1. Signal-Generator_1.zip - PSOC code to receive continuous chunk and plot.
2. Workspace02.zip - PSOC code to receive chunk and plot for signal quality evaluation.


Folder - Forcontinuouswaveform- raspberrypi-PC-control contains (This is for continuous plotting of the whole signal:
1. csv_code_final.py rpi code to transmit the whole waveform in chunks.
2. one_byte_send.py - for PC side control. 

Folder - Forsignalqualityevaluation-raspberrypi-PC-control (This is plotting only first two peaks of every signal - testing)
1. csv_code_final.py rpi code to transmit the first two peaks of the waveform in chunks continuously.
2. one_byte_send.py - for PC side control.

Folder - readinginV (Emulator output in Volts)
Normalization is used here to match both signals amplitude.
1. 1-peak-correlation.py - For single peak correlation
2. 2-peak-correlation.py - For two peaks correlation
3. readings - "scope_0-100.csv", etc.
4. Graph.pdf - output of the codes 

Folder - readinginmV (Emulator output in milliVolts)
Normalization is not used here to match both signals amplitude. Original signals are compared.
1. 1-peak-correlation.py - For single peak correlation
2. 2-peak-correlation.py - For two peaks correlation
3. readings - "scope_100.csv", etc.
4. Graph.pdf - output of the codes 

ECG- Emulator Project demonstration:
https://drive.google.com/file/d/1iLw46b3T_O6b1dZw4OgvF0SsyfaQwCDk/view?usp=sharing



