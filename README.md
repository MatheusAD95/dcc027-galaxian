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
