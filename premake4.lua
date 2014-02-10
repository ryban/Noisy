solution "Noise Solution"
    configurations {"Release"}
    project "Noise"
        kind "StaticLib"
        language "C++"
        files {"src/*.cpp"}
        includedirs {"include"}
        location "build"
        targetdir "lib"
        targetname "noisy"

    project "Example"
        kind "ConsoleApp"
        language "C++"
        files {"examples/example.cpp"}
        includedirs {"include"}
        links {"noisy", "png"}
        libdirs "lib"
        location "build"
        targetname "example"
        targetdir "bin"

    project "SelectExample"
        kind "ConsoleApp"
        language "C++"
        files {"examples/select.cpp"}
        includedirs {"include"}
        links {"noisy", "png"}
        libdirs "lib"
        location "build"
        targetname "select"
        targetdir "bin"