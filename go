#!/bin/sh

amixer sset PCM 95%

cd /home/pi/doomclock

cd ds1302
./ds1302 r
cd ..

cd linux
./doomclock >/dev/null 2>&1 &
cd ..

