# Fractal Tree
A visualization of a recursive fractal tree algorithm using the SDL2 library.

![](https://i.imgur.com/p5udT3f.png)

## Usage
- Windows\
Download the archive in releases, unpack it and make sure SDL2.dll stays within the same folder as the .exe.
- Linux\
Run the .exe with Wine.

The algorithm's values can be controlled using the arrow keys on the keyboard.

## Dependencies
- SDL2 (Windows 32-bit version included with the project)
    - SDL.h
    - SDL2.lib
    - SDL2main.lib
    - __SDL2.dll__ in the same directory as the binary or in the environment variable


## Building
Compile for x86 including and linking the files specified in Dependencies.
- Windows 
You can use the provided Visual Studio solution.
- Linux
You will have to download the Linux version of SDL2 to be able to compile the project.
