# dcc027-galaxian
Implementation of the galaxian game using GLFW, Glew and GLM.

You need OpenGL 3.0 or higher to compile. Every other library is linked
statically.

To compile:

  * cd $GAME\_FOLDER
  * mkdir build
  * cd build
  * cmake ..
  * make

To run:
  * cd $GAME\_FOLDER
  * ./build/galaxian
  * Note that you can't move the binary or else the paths to the assets will be
  messed up. Create a link (e.g. ln -s .build/galaxian ~/Desktop/) if you want
  the binary elsewhere.

A few dependecies:
  * libudev for SFML
    * sudo apt-get install libudev-dev
    * Need to fix /etc/gai.conf
      #
      #    For sites which prefer IPv4 connections change the last line to
      #
      precedence ::ffff:0:0/96 100


  * OpenAL: sudo apt-get install libopenal0a libopenal-dev

  * sudo apt install autoconf autogen automake build-essential libasound2-dev \
      libflac-dev libogg-dev libtool libvorbis-dev pkg-config python
