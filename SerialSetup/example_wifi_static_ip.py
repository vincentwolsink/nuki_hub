import serial

ser = serial.Serial('/dev/ttyUSB0', 115200)
print(ser.portstr)

ser.write(b'nwhw 1 -1\r')
ser.write(b'wifi <ssid> <psk>\r')
ser.write(b'mqttbroker 192.168.0.10 1883\r')
ser.write(b'nukipath nukitstx nukioptstx\r')
ser.write(b'dhcp 0\r')
ser.write(b'ip 192.168.0.46 255.255.255.0\r')
ser.write(b'gw 192.168.0.1\r')
ser.write(b'dns 192.168.0.1\r')
ser.write(b'restart\r')

ser.close()