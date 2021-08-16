# About this project

This is the C-implementation code of vulkan triangle based on [**vulkan-tutorial.com**][VK_TUT].

**NOTE**

An old, archived single-C-source-file version can be found [**here**][VK_OLD].

# Why use C instead of C++?

Because some newcomers don't know C++ or STL. Implement the code with C will help them have a better understanding with the tutorial.

# How many chapters this code had actually implemented?

From [**chapter 1**][TUT_START] to [**chapter 16**][TUT_END], you can view comments from the source code to see how they're implemented.

# How to build it?

**FOR WINDOWS USERS**

You need to install [**VulkanSDK**][WIN_VKSDK], [**mingw-w64(Optional but Recommended)**][WIN_GCC](GNU C/C++ Compiler for Windows), [**CMake**][WIN_CMAKE]. Then download and extract [**GLFW prebuild library for windows**][WIN_GLFW_LIB] (and move it under C:/ if possible).

Now fetch this source code through [**Git**][GIT] or Direct-Download.

Then you should read carefully through [**CMakeLists.txt**][BUILD_FILE] and modify everything that suit your needs.

Then open the project folder press **Shift + Right Click** and select **open in terminal**, Type the following command(change argument with <> to what you want):

```

# using mingw-w64(Recommended)

cmake -G "MinGW Makefiles" -B <your-build-dir>

# using visual C++

cmake -G "Visual Studio 16 2019" -A x64 -B <your-build-dir>

cmake --build <your-build-dir> --target all -j<numbers-of-threads>

```

If you don't like typing command line, **Double Click 'Windows_Build.bat'** and it will automatically build inside a subdirectory named **'build'**.

**FOR LINUX USERS**

You need to install a **Desktop Environment**, **vulkan driver for your GPU**, **gcc**, **glslang**, **cmake** and **glfw**, they should be included inside your package manager if you're using popular distro. If not, fetch their source code, build and install them manually.

Now fetch this source code through [**Git**][GIT] or Direct-Download.

Then read carefully through [**CMakeLists.txt**][BUILD_FILE], confirm that the path was absolutely correct.

Then open the terminal by pressing **Ctrl + Alt + T** to open the terminal(If your Desktop Environment doesn't support this shortcut, open it manually through application launcher), Type the following command:

```

cd <project-path>

cmake -B <your-build-dir>

cmake --build <your-build-dir> --target all -j<numbers-of-threads>

```

# Where is the program after the build steps?

Open file manager(or use **cd** if you like typing command) and open your build folder, double click the program named 'vulkan-triangle', a colorful triangle with purple background will pop up.

**NOTE FOR WINDOWS USERS**

Everything is placed under ```<your-build-dir>/Debug``` if you build it with Visual C++.

# How to change the color of The Background or The Triangle ?

**BACKGROUND COLOR**:

Search "VkClearValue" in [**Sources/vk_command.c**][CODE_MAIN], the four-floating-number-array after clear_val is the background color, represents "R", "G", "B" and "A", curretly only RGB value has effect.

**TRIANGLE COLOR**:

Search "vec3 colors" in [**Shaders/triangle.vert**][CODE_VERT], there are three three-floating-number-array after that. It's the RGB value of three vertex colors of the triangle.


[VK_OLD]: https://github.com/lonelydevil/vulkan-tutorial-C-implementation
[VK_TUT]: https://vulkan-tutorial.com/
[TUT_START]: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Base_code
[TUT_END]: https://vulkan-tutorial.com/Drawing_a_triangle/Drawing/Rendering_and_presentation
[WIN_VKSDK]: https://vulkan.lunarg.com/sdk/home#windows
[WIN_GCC]: http://mingw-w64.org/doku.php/download/mingw-builds
[WIN_CMAKE]: https://cmake.org/download/
[WIN_GLFW_LIB]: https://www.glfw.org/download.html
[GIT]: https://git-scm.com/downloads
[BUILD_FILE]: https://github.com/lonelydevil/Vulkan-Triangle/blob/main/CMakeLists.txt
[CODE_MAIN]: https://github.com/lonelydevil/Vulkan-Triangle/blob/main/Sources/vk_command.c
[CODE_VERT]: https://github.com/lonelydevil/Vulkan-Triangle/blob/main/Shaders/triangle.vert
