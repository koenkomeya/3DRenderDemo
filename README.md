About
=====

This is a simple program written in C++ to render stuff, presently only to a web target via Emscripten
but designed so that it can be ported easily to different targets.


Targets
=======

Implemented targets:
TARGET_WEB_EM_GLES3_0 = Web - Emscripten + OpenGL ES 3.0

Planned targets:
TARGET_WEB_EM_WEBGL2_0 = Web - Emscripten + WebGL 2.0?  
TARGET_WIN_VUL1_1 = Executable - Windows 7+ + Vulkan 1.1
TARGET_UNIX_VUL1_1 = Executable - Unix + Vulkan 1.1
TARGET_MACOS_VUL1_1 = Executable - Mac OS + Vulkan 1.1 using Metal
TARGET_IOS_VUL1_1 = Executable - iOS + Vulkan 1.1 using Metal
//TARGET_SERVER = (Server Implementation)

Planned abstract targets:
TARGET_ANDROID_VUL1_1 = App - Android + Vulkan 1.1
TARGET_ANDROID_GLES3_0 = App - Android + OpenGL ES 3.0

Important defines
TARGET_ATTR_BIGENV_WEB - Web-based
TARGET_ATTR_BIGENV_APP - App-based
TARGET_ATTR_APP_MOBILE - App Executable
TARGET_ATTR_APP_DESK - Desktop Executable

Tools
TARGET_ATTR_TOOL_EM - Emscripten

Windowing/Input
TARGET_ATTR_WIND_GLFW - GLFW

Networking
TARGET_ATTR_NET_EM - Use Emscripten Sockets

Render target
TARGET_ATTR_REND_GLES_3_0 - Use OpenGL ES 3.0
TARGET_ATTR_REND_WEBGL2_0 - Use WebGL 2.0
TARGET_ATTR_REND_VUL_1_1  - Use Vulkan 1.1


Building
========

This is a CMake project and thus can be built using different generators. These commands are listed mainly for convenience.

Building for Emscripten
-----------------------

Replace {TARGET} with the target to build for, {emconfigure} and {emmake} with your preferred means of calling emconfigure and emmake respectively.
(Starting at project root directory)

Debug:  
```
cmake -E chdir build/Debug/ {emconfigure} cmake -G "Unix Makefiles" ../../ -DCMAKE_BUILD_TYPE:STRING=Debug -D{TARGET}=1 
{emmake} make -f build/Debug/Makefile -C build/Debug all
```

Release: 
```
cmake -E chdir build/Release/ {emconfigure} cmake -G "Unix Makefiles" ../../ -DCMAKE_BUILD_TYPE:STRING=Release -D{TARGET}=1 
{emmake} make -f build/Debug/Makefile -C build/Debug all
```


Building for everything else
----------------------------

Replace {TARGET} with the target to build for 
(Starting at project root directory) 

Debug:  
```
cmake -E chdir build/Debug/ cmake -G "Unix Makefiles" ../../ -DCMAKE_BUILD_TYPE:STRING=Debug -D{TARGET}=1 
make -f build/Debug/Makefile
```

Release: 
```
cmake -E chdir build/Release/ cmake -G "Unix Makefiles" ../../ -DCMAKE_BUILD_TYPE:STRING=Release -D{TARGET}=1 
make -f build/Debug/Makefile
```

