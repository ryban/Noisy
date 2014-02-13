Noisy
=====

A small C++ library for generating coherent noise such as Simplex noise, Fractal Brownian Motion, Ridged Multi fractals, Voronoi. Provides functionality to combine the noise functions in numerous ways.

Building
=====

As long as you have a C++11 compiler, the project should have no trouble building.
You will need premake4 in for generating the build files though.

http://industriousone.com/premake

http://industriousone.com/what-premake

Just run 'premake4 gmake' to generate the makefiles (or which environment you want to build in)
Once premake is done run 'make' to build the library and example programs.

Alternatively you can just add the soruce to your project and compile it there.

The example programs will require libpng to create the image files.
Using gmake, running make will first build the static lib, then the examples, so even if you don't have libpng installed, the library will still build.
