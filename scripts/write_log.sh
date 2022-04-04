#!/bin/bash

now=$(date +'%Y-%m-%d %H:%M:%S')

echo "$now;$1." >> /home/pi/logs/logs.txt

