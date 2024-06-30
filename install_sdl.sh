#!/bin/bash

# Check if SDL2 and related libraries are installed
dpkg -s libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-net-dev &> /dev/null

if [ $? -eq 0 ]; then
    echo "SDL2 and related libraries are installed."
else
    echo "SDL2 and related libraries are not installed. Installing..."
    sudo apt-get update
    sudo apt-get install -y libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-net-dev
fi