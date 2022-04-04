#!/bin/bash

echo 20 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio20/direction
./sensor
