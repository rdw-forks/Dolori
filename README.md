Dolori
=======

[![Build status](https://ci.appveyor.com/api/projects/status/ye0d4xcsm6kbx2h7?svg=true)](https://ci.appveyor.com/project/L1nkZ/dolori) [![pipeline status](https://gitlab.com/Dolori/Dolori/badges/master/pipeline.svg)](https://gitlab.com/Dolori/Dolori/commits/master)

External dependencies
---------------------
* OpenGL
* DevIL
* SDL2_ttf

Build
-----
```shell
$ git clone https://gitlab.com/Linkz/Dolori --recurse-submodules
$ cd Dolori
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --config MinSizeRel
```

Current supported settings
--------------------------
* Packet version: 20130807
* Packet obfuscation: Disabled
* Client version: 45

Configuration file
------------------
Dolori uses a JSON file to store its configuration (graphics, sound, fonts, etc.).  
Here's what its content might look like:

```json
{
  "graphics": {
    "fullscreen": false,
    "window_width": 800,
    "window_height": 600,
    "vsync": false,
    "msaa": 4
  },
  "fonts": {
    "font_folder": "/usr/share/fonts/truetype/msttcorefonts/"
  }
}
```
