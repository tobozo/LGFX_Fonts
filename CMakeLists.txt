set(COMPONENT_ADD_INCLUDEDIRS src )

#file(GLOB_RECURSE SRCS src *.cpp *.hpp *.h *.c)
file(GLOB_RECURSE SRCS "src/*.cpp" "src/*.c" "src/*.hpp" "src/*.h")
set(COMPONENT_SRCS ${SRCS})

### If you use arduino-esp32 components, please activate next comment line.
# list(APPEND COMPONENT_REQUIRES arduino-esp32)

### Activate either LovyanGFX or M5GFX
list(APPEND COMPONENT_REQUIRES LovyanGFX)
# list(APPEND COMPONENT_REQUIRES M5GFX)

message(STATUS "LGFX_Fonts use components = ${COMPONENT_REQUIRES}")

register_component()
