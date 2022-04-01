#!/bin/bash

git -C /home/pi/Documents/presenceDetectorGit/sound_presence_detection commit -m "logs update" -o ./logs.txt
git -C /home/pi/Documents/presenceDetectorGit/sound_presence_detection push origin main
