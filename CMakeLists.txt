# STM32 Minimal CMake project for C/C++ projects
cmake_minimum_required(VERSION 3.10)

### System settings - not important for MCUs.
set(CMAKE_SYSTEM_NAME Generic)  # Linux/Windows/Darwin - compiler is forced by project, so this is set to generic.
set(CMAKE_SYSTEM_VERSION 1)     # target 'uname -r' output - meaningless for embedded
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
###############################################################################
# Set project name and source code folder location
project(STM32F01XX_CPP_TEST)

# Set firmware version
set(FW_VER "xx-xx-xx")




### Skips compiler checking by cmake.
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

### Toolchain settings
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_FLAGS_INIT
    "-fdata-sections -ffunction-sections --specs=nano.specs -Wl,--gc-sections")
set(CMAKE_CXX_FLAGS_INIT
    "${CMAKE_C_FLAGS_INIT} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)

    
set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")


#Set microcontroller settings/information
set(MCU_FAMILY STM32F1xx)
set(MCU_MODEL STM32F103xb)
set(CPU_PARAMETERS
    -mcpu=cortex-m3
    -mthumb
    )
add_definitions(-DSTM32F103xB)
add_definitions(-DCMAKE_SYSTEM_NAME=Generic)

set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/CubeMX/STM32F103C8Tx_FLASH.ld)
set(STARTUP_SCRIPT ${PROJECT_SOURCE_DIR}/CubeMX/startup_stm32f103xb.s)
set_property(SOURCE ${PROJECT_SOURCE_DIR}/startup_stm32f103xb.s PROPERTY LANGUAGE C)
###############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

enable_language(ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
set(CMAKE_CXX_EXTENSIONS ON)
###############################################################################
set(STM32CUBEMX_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include)

set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/Project)



file(GLOB_RECURSE STM32CUBEMX_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/*.c)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Project)
set(BSP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bsp)
set(BSP_INCLUDE_DIRECTORIES ${BSP_DIR}/inc)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
 ${PROJECT_DIR}/*.cpp
${PROJECT_DIR}/*.c)

file(GLOB_RECURSE BSP_SOURCES CONFIGURE_DEPENDS
 ${BSP_DIR}/src/*.cpp
${BSP_DIR}/src/*.c)

add_executable(${EXECUTABLE}
    ${STM32CUBEMX_SOURCES} 
    ${PROJECT_SOURCES}
    ${BSP_SOURCES}
    ${STARTUP_SCRIPT})

target_compile_definitions(${EXECUTABLE} PRIVATE
    #$<$<CONFIG:Debug>:DEBUG>
    ${MCU_MODEL}
    USE_HAL_DRIVER)

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
    ${STM32CUBEMX_INCLUDE_DIRECTORIES})

target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES}
    ${BSP_INCLUDE_DIRECTORIES})
###############################################################################
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -lc 
    -specs=nosys.specs
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wformat=2 
    -Wformat-truncation
    -Wundef
    -fno-common
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wconversion
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)
###############################################################################

# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)

option(DUMP_ASM "Create full assembly of final executable" OFF)
if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D -C $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s)
endif()

