Dolori
=======

External dependencies
---------
* OpenGL
* DevIL
* SDL2_ttf

Build
-----
```shell
$ git clone https://gitlab.com/Linkz/Dolori
$ cd Dolori
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --config MinSizeRel
```

Current supported settings
--------------------------
* Packet version: 20080910
* Packet obfuscation: Disabled
* Client version: 23

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