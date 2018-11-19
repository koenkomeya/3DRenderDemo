About
=====

This is a simple program written in C++ using the CMake build system to render stuff.
While it presently only supports a web target via Emscripten and using OpenGL ES 3.0 (converted to
WebGL 2.0 handily by Emscripten), it is designed to be ported easily to 
different targets.


Targets
=======

Implemented targets:  
TARGET\_WEB\_EM\_GLES3\_0 = Web - Emscripten + OpenGL ES 3.0 (w/ 2.0 as a fallback)

Planned targets:  
TARGET\_WIN\_VUL1\_1 = Executable - Windows 7+ + Vulkan 1.1  
TARGET\_UNIX\_VUL1\_1 = Executable - Unix + Vulkan 1.1   
TARGET\_MACOS\_VUL1\_1 = Executable - Mac OS + Vulkan 1.1 using Metal  
TARGET\_IOS\_VUL1\_1 = Executable - iOS + Vulkan 1.1 using Metal  
//TARGET\_SERVER = (Server Implementation)

Planned abstract targets:  
TARGET\_ANDROID\_VUL1\_1 = App - Android + Vulkan 1.1  
TARGET\_ANDROID\_GLES3\_0 = App - Android + OpenGL ES 3.0 

Important defines  
TARGET\_ATTR\_BIGENV\_WEB - Web-based  
TARGET\_ATTR\_BIGENV\_APP - App-based  
TARGET\_ATTR\_APP\_MOBILE - App Executable  
TARGET\_ATTR\_APP\_DESK - Desktop Executable  

Tools  
TARGET\_ATTR\_TOOL\_EM - Emscripten  

Windowing/Input  
TARGET\_ATTR\_WIND\_GLFW - GLFW  

Networking  
TARGET\_ATTR\_NET\_EM - Use Emscripten Sockets  

Render target  
TARGET\_ATTR\_REND\_GLES\_3\_0 - Use OpenGL ES 3.0  
TARGET\_ATTR\_REND\_VUL\_1\_1  - Use Vulkan 1.1  

TARGET\_ATTR\_RENDFB\_GLES\_2\_0 - Use OpenGL ES 2.0 as a fallback  


Building
========

This is a CMake project and thus can be built using different generators. These commands are listed mainly for convenience.

Building for Emscripten
-----------------------

Replace {TARGET} with the target to build for, {emconfigure} and {emmake} with your preferred means of calling emconfigure and emmake respectively.  
(Starting at project root directory)

Debug:  
```
cmake -E chdir build/Debug/ {emconfigure} cmake -G "Unix Makefiles" ../../ -DCMAKE\_BUILD\_TYPE:STRING=Debug -DBTARGET={TARGET}   
{emmake} make -f build/Debug/Makefile -C build/Debug all  
```

Release: 
```
cmake -E chdir build/Release/ {emconfigure} cmake -G "Unix Makefiles" ../../ -DCMAKE\_BUILD\_TYPE:STRING=Release -DBTARGET={TARGET}  
{emmake} make -f build/Debug/Makefile -C build/Debug all  
```


Building for everything else
----------------------------

Replace {TARGET} with the target to build for  
(Starting at project root directory)  

Debug:  
```
cmake -E chdir build/Debug/ cmake -G "Unix Makefiles" ../../ -DCMAKE\_BUILD\_TYPE:STRING=Debug -D{TARGET}=1   
make -f build/Debug/Makefile  
```

Release: 
```
cmake -E chdir build/Release/ cmake -G "Unix Makefiles" ../../ -DCMAKE\_BUILD\_TYPE:STRING=Release -D{TARGET}=1  
make -f build/Debug/Makefile  
```

