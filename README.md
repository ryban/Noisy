Noisy
=====

A small library for generating coherent noise

Building
=====

There are no dependecies for the library, so it should compile no problem.
You will need premake4 in for the build system though.
http://industriousone.com/premake
http://industriousone.com/what-premake

Just run 'premake4 gmake' to generate the makefiles (or which program you want to build with)
Once premake is done run 'make' to build the library and example program.

Alternatively you can just add the soruce to your project.

The example program will require libpng to create the image files.
Using gmake, running make will first build the static lib, then the example, so even if you don't have libpng installed, the library will still build
