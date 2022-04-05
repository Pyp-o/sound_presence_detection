#!/bin/bash

bash /home/pi/Documents/presenceDetectorGit/sound_presence_detection/scripts/send.sh &
python3 /home/pi/Documents/presenceDetectorGit/sound_presence_detection/scripts/receive_data_arduino.py &
