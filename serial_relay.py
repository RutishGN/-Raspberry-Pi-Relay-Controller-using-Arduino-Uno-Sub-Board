import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
time.sleep(2)

def send_command(command):
    ser.write((command + '\n').encode())
    response = ser.readline().decode().strip()
    print(f"Sent: {command} | Received: {response}")

try:
    while True:
        print("Activating relays in a pattern...")

        for i in range(1, 17):
            for j in range(1, 17):
                send_command(f"OFF {j}")

            send_command(f"ON {i}")
            time.sleep(0.3)

except KeyboardInterrupt:
    print("Exiting program...")

finally:
    for i in range(1, 17):
        send_command(f"OFF {i}")
    ser.close()
    print("All relays turned off and serial connection closed.")