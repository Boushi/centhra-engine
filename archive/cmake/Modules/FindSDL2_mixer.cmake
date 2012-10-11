# Locate SDL2_mixer library
# This module defines
# SDL2MIXER_LIBRARY, the name of the library to link against
# SDL2MIXER_FOUND, if false, do not try to link to SDL2
# SDL2MIXER_INCLUDE_DIR, where to find SDL2/SDL.h
#
# $SDL2DIR is an environment variable that would
# correspond to the ./configure --prefix=$SDL2DIR
# used in building SDL2.
#
# Created by Eric Wing. This was influenced by the FindSDL2.cmake 
# module, but with modifications to recognize OS X frameworks and 
# additional Unix paths (FreeBSD, etc).
#
# Ported by Johnny Patterson. This is a literal port for SDL2 of the FindSDL_mixer.cmake
# module with the minor edit of changing "SDL" to "SDL2" where necessary. This
# was not created for redistribution, and exists temporarily pending official
# SDL2 CMake modules.

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

FIND_PATH(SDL2MIXER_INCLUDE_DIR SDL_mixer.h
  HINTS
  $ENV{SDL2MIXERDIR}
  $ENV{SDL2DIR}
  PATH_SUFFIXES include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/SDL2
  /usr/include/SDL2
  /usr/local/include
  /usr/include
  /sw/include/SDL2 # Fink
  /sw/include
  /opt/local/include/SDL2 # DarwinPorts
  /opt/local/include
  /opt/csw/include/SDL2 # Blastwave
  /opt/csw/include 
  /opt/include/SDL2
  /opt/include
)

FIND_LIBRARY(SDL2MIXER_LIBRARY 
  NAMES SDL2_mixer
  HINTS
  $ENV{SDL2MIXERDIR}
  $ENV{SDL2DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

SET(SDL2MIXER_FOUND "NO")
IF(SDL2MIXER_LIBRARY AND SDL2MIXER_INCLUDE_DIR)
  SET(SDL2MIXER_FOUND "YES")
ENDIF(SDL2MIXER_LIBRARY AND SDL2MIXER_INCLUDE_DIR)

