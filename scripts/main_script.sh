#!/bin/bash

bash /home/pi/scripts/send.sh &
python3 /home/pi/scripts/receive_data_arduino.py &
