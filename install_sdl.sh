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


# Local installation
#mkdir -p ~/libs
#cd ~/libs
#  Download SDL2 source code
#wget https://www.libsdl.org/release/SDL2-2.26.5.tar.gz
#tar -xzvf SDL2-2.26.5.tar.gz
#cd SDL2-2.26.5
#./configure --prefix=$HOME/libs/SDL2_local
#make
#make install
#cd ..
# Download SDL2_image source code
#wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.6.3.tar.gz
#tar -xzvf SDL2_image-2.6.3.tar.gz
#cd SDL2_image-2.6.3
#./configure --prefix=$HOME/libs/SDL2_image_local --with-sdl-prefix=$HOME/libs/SDL2_local
#make
#make install
#cd ..
# Download SDL2_mixer source code
#wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz
#tar -xzvf SDL2_mixer-2.0.4.tar.gz
#cd SDL2_mixer-2.0.4
#./configure --prefix=$HOME/libs/SDL2_mixer_local --with-sdl-prefix=$HOME/libs/SDL2_local
#make
#make install
#cd ..
# Download SDL2_ttf source code
#wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz
#tar -xzvf SDL2_ttf-2.0.15.tar.gz
#cd SDL2_ttf-2.0.15
#./configure --prefix=$HOME/libs/SDL2_ttf_local --with-sdl-prefix=$HOME/libs/SDL2_local
#make
#make install
#cd ..
# Download SDL2_net source code
#wget https://www.libsdl.org/projects/SDL_net/release/SDL2_net-2.0.1.tar.gz
#tar -xzvf SDL2_net-2.0.1.tar.gz
#cd SDL2_net-2.0.1
#./configure --prefix=$HOME/libs/SDL2_net_local --with-sdl-prefix=$HOME/libs/SDL2_local
#make
#make install
#cd ..