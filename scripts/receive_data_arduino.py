#!/usr/bin/env python3
import serial
import subprocess

ser = serial.Serial('/dev/ttyS0',9600)
ser.reset_input_buffer()
while True:
	if ser.in_waiting > 0 :
		line = ser.readline().decode('utf-8').rstrip()
		print(line)
		subprocess.check_call(['/home/pi/scripts/write_log.sh', line])
