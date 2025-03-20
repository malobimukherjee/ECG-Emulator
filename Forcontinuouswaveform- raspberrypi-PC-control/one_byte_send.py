import socket

def udp_sender():
    # Replace with your Raspberry Pi's IP address
    rpi_ip = "172.16.101.22"
    rpi_port = 12345

    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    data = b'\x00'  # data to be send one byte

    try:
        # Send data to the Raspberry Pi
        print(f"Sending data: {data} to {rpi_ip}:{rpi_port}")
        sock.sendto(data, (rpi_ip, rpi_port))
    finally:
        sock.close()

if __name__ == "__main__":
    udp_sender()
