# Install script for directory: /home/piotr/Piotr/IGF/libcloudphxx/tests

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/pzmij/biblioteki/local_folder/master")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/piotr/Piotr/IGF/libcloudphxx/build/tests/theta/cmake_install.cmake")
  include("/home/piotr/Piotr/IGF/libcloudphxx/build/tests/particles/cmake_install.cmake")
  include("/home/piotr/Piotr/IGF/libcloudphxx/build/tests/fake_units/cmake_install.cmake")
  include("/home/piotr/Piotr/IGF/libcloudphxx/build/tests/zip/cmake_install.cmake")
  include("/home/piotr/Piotr/IGF/libcloudphxx/build/tests/python/cmake_install.cmake")
  include("/home/piotr/Piotr/IGF/libcloudphxx/build/tests/common/cmake_install.cmake")
  include("/home/piotr/Piotr/IGF/libcloudphxx/build/tests/blk2m_hello_world/cmake_install.cmake")
  include("/home/piotr/Piotr/IGF/libcloudphxx/build/tests/toms748/cmake_install.cmake")

endif()

