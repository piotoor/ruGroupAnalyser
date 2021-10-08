set(CMAKE_TOOLCHAIN_FILE "toolchain-win32.cmake")
set(CMAKE_SYSTEM_NAME Windows)

# TODO download / apt-get + auto find paths?
set(CMAKE_C_COMPILER /usr/bin/i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/i686-w64-mingw32-g++)

SET(CMAKE_WIN32_COMPILATION 1)
