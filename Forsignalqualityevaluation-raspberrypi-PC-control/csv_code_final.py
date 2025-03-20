import time
import socket
import serial
import numpy as np
import pandas as pd

CHUNK_SIZE = 1152

# Raspberry Pi IP and port
rpi_ip = "172.16.101.10"
rpi_port = 12345
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((rpi_ip, rpi_port))

print("Raspberry Pi is listening...")

# Receive initial data from Raspberry Pi
data, addr = sock.recvfrom(1024)
print(f"Received data: {data} from {addr}")

# Open the serial connection
ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
if ser.isOpen():
    print("Serial opened successfully")

# List of CSV file paths
csv_arr = ["/home/malobimukherjee/Documents/100.csv", 
           "/home/malobimukherjee/Documents/102.csv", 
           "/home/malobimukherjee/Documents/103.csv", 
           "/home/malobimukherjee/Documents/104.csv"]

# Determine which file to use based on received data
k = int.from_bytes(data, byteorder='big')
print(f"Patient No. {k}")
df = pd.read_csv(csv_arr[k], usecols=[0], dtype=str)
arr = np.array(df)
arr2 = arr[:, 0]

# Adjust the array values
arr2 = [float(x) + 5.0 for x in arr2]

# Normalize the values and convert to bytes
num = np.zeros((len(arr2), 1))
min_value = np.min(arr2)
max_value = np.max(arr2)
for i in range(len(arr2)):
    num[i] = int(((arr2[i] - min_value) * 255) / (max_value - min_value))

j = 0

# Send the first chunk without waiting for any request
start_index = CHUNK_SIZE * j
end_index = start_index + CHUNK_SIZE
#print(start_index)
#print(end_index)
if end_index > len(arr2):
    padding_length = end_index - len(arr2)
    num = np.pad(num, (0, padding_length), 'constant', constant_values=(0,))

for i in range(start_index, end_index):
    value = int(num[i])
    byte = bytes([value])
    #print(value)
    #print(f"No. of bytes: {ser.write(byte)}")
    ser.write(byte)
    time.sleep(0.001)

j = 0

# Continuously look for receiving one byte to send the next chunk
while True:
    # Wait to receive a single byte before sending the next chunk
    ack = ser.read(size=1)
    if ack:
        #ser.reset_input_buffer()
        print("Acknowledgment received, sending next chunk...")

        start_index = CHUNK_SIZE * j
        end_index = start_index + CHUNK_SIZE
        #print(start_index)
        #print(end_index)
        if start_index < len(arr2):
            if end_index > len(arr2):
                padding_length = end_index - len(arr2)
   		        num = np.pad(num, (0, padding_length), 'constant', constant_values=(0,))

            for i in range(start_index, end_index):
                value = int(num[i])
                byte = bytes([value])
                ser.write(byte)
                time.sleep(0.001)
                #print(value)
                #print(f"No. of bytes: {ser.write(byte)}")

            j = 0
        else:
            print("All data sent.")
            break
    else:
        print("No acknowledgement received, continuing to search.")
    
