# ECG-Emulator

## Demonstration and PSOC/RPI Code Implementation

Folder - PSOC (Receiver) contains: 
1. Signal-Generator_1.zip - PSOC code to receive continuous packets and generate corresponding analog voltage signal.
2. Workspace02.zip - PSOC code to receive packet and test for signal quality evaluation.


Folder - Forcontinuouswaveform- raspberrypi (transmitter) -PC-control contains (This is for continuous generation of the whole signal):
1. csv_code_final.py rpi code to transmit the whole waveform in packets.
2. one_byte_send.py - for PC side control. 

Folder - Forsignalqualityevaluation-raspberrypi (transmitter)-PC-control (This is for generating only first two peaks of every signal - testing)
1. csv_code_final.py rpi code to transmit the first two-peak data of the waveform in a single packet continuously.
2. one_byte_send.py - for PC side control.

Folder - readinginV (Emulator output in Volts)  -- Correlation Code.
Normalization is used here to match both signals amplitude.
1. 1-peak-correlation.py - For single peak correlation
2. 2-peak-correlation.py - For two peaks correlation
3. readings - "scope_0-100.csv", etc.
4. Graph.pdf - output of the codes 

Folder - readinginmV (Emulator output in milliVolts) -- Correlation Code.
Normalization is not used here to match both signals amplitude. Original signals are compared.
1. 1-peak-correlation.py - For single peak correlation
2. 2-peak-correlation.py - For two peaks correlation
3. readings - "scope_100.csv", etc.
4. Graph.pdf - output of the codes 

ECG- Emulator Project demonstration (This video shows how the system works):
https://drive.google.com/file/d/1iLw46b3T_O6b1dZw4OgvF0SsyfaQwCDk/view?usp=sharing




