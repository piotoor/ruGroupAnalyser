set(CMAKE_TOOLCHAIN_FILE "toolchain-win.cmake")
set(CMAKE_SYSTEM_NAME Windows)

# TODO download / apt-get + auto find paths?
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)

SET(CMAKE_WIN_COMPILATION 1)
