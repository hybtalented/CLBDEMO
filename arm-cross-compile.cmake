# 目标系统环境
set(CMAKE_SYSTEM_NAME raspberrypi)
set(CMAKE_SYSTEM_VERSION 4.19.97-v7l+)
set(CMAKE_COMPILER_ARCH $ENV{ARM_COMPILER_ARCH} CACHE STRING "交叉编译器架构")
# 交叉编译器设置
set(CMAKE_CXX_COMPILER ${CMAKE_COMPILER_ARCH}-g++)
set(CMAKE_C_COMPILER ${CMAKE_COMPILER_ARCH}-gcc)
# 交叉编译器目标环境
set(CMAKE_FIND_ROOT_PATH $ENV{ARM_COMPILER_PATH}/${ARM_COMPILER_ARCH})

# 在宿主机和目标环境内寻找应用程序
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)

# 只在目标环境内寻找包含文件和库文件
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
