#!/bin/bash

FILE=/sys/class/gpio/gpio20
if [  -d "$FILE" ]; then
echo 20 > /sys/class/gpio/unexport
fi
  
echo 20 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio20/direction

/home/pi/Documents/presenceDetectorGit/sound_presence_detection/scripts/send &
exit 0
