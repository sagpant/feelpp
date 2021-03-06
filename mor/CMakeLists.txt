###  CMakeLists.txt ---

#  Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
#       Date: 2009-11-12
#
#  Copyright (C) 2009-2017 Université Joseph Fourier (Grenoble I)
#
# Distributed under the GPL(GNU Public License):
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#
cmake_minimum_required(VERSION 3.7.2)
project(mor)

set(FEELPP_MOR_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(FEELPP_MOR_BINARY_DIR ${PROJECT_BINARY_DIR})

# with this it is possible to compile applications/MOR from an installed
# version of feel++. This is useful also for staged compilation for docker
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} )
  find_package(Feel++ COMPONENTS Toolboxes PATHS $ENV{FEELPP_DIR}/share/feelpp/feel/cmake/modules /usr/share/feelpp/feel/cmake/modules /usr/local/share/feelpp/feel/cmake/modules )
  if(NOT FEELPP_FOUND)
    message(FATAL_ERROR "Feel++ was not found on your system. Make sure to install it and specify the FEELPP_DIR to reference the installation directory.")
  endif()
  if (NOT FEELPP_TOOLBOXES_FOUND)
    message(WARNING "Feel++ was not installed with toolboxes")
  endif()
else()
  include_directories(${FEELPP_MOR_SOURCE_DIR})
  include_directories(${FEELPP_MOR_BINARY_DIR})  
endif()






OPTION(FEELPP_ENABLE_MOR_ALL "enable all MOR testcase" OFF)

OPTION(FEELPP_ENABLE_MOR_EADS "enable EADS testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_HEAT1D "enable HEAT1D testcase" ON )
OPTION(FEELPP_ENABLE_MOR_HEAT2D "enable HEAT2D testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_HEAT3D "enable HEAT3D testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_LINEARELASTICITY "enable LINEARELASTICITY testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_RBHEAT "enable RBHEAT testcases" OFF)
OPTION(FEELPP_ENABLE_MOR_CABINEHEAT "enable CABINEHEAT testcases" OFF)
OPTION(FEELPP_ENABLE_MOR_FINALCABINEHEAT "enable FINALCABINEHEAT testcases" OFF)
OPTION(FEELPP_ENABLE_MOR_AD1 "enable AD1(Advection-Diffusion) testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_THERMALBLOCK "enable THERMALBLOCK(many parameters) testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_HELMHOLTZ "enable Helmholtz testcases" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_HEATSINK "enable Heatsink testcases" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_HEATSHIELD "enable Heatshield testcases" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_BENCHMARKGREPL "enable BenchmarkGrepl testcases" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_GEOHEATDIFFUSION "enable GeoHeatDiffusion testcases" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_THERMALFIN "enable ThermalFin testcases" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_EEG "enable EEG testcase" OFF)
OPTION(FEELPP_ENABLE_MOR_CONVECTION "enable Convection testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_STOKESDEIM "enable stokes with deim testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_THERMOELECTRIC "enable thermoelectric testcase" ${FEELPP_ENABLE_MOR_ALL})
OPTION(FEELPP_ENABLE_MOR_GREPLDEIM "enable grepldeim testcase" ${FEELPP_ENABLE_MOR_ALL})


if ( NOT FEELPP_TOOLBOXES_FOUND )
  set( FEELPP_ENABLE_MOR_THERMOELECTRIC OFF )
endif()

set(FEELPP_MOR_LIBRARIES)

INCLUDE(CTest)
ENABLE_TESTING()

add_subdirectory(onlinerun)


IF ( FEELPP_ENABLE_MOR_EADS )
  #add_subdirectory(eads)
ENDIF()

IF ( FEELPP_ENABLE_MOR_HEAT2D )
  add_subdirectory(heat2d)
ENDIF()

IF ( FEELPP_ENABLE_MOR_HEAT3D )
  add_subdirectory(heat3d)
ENDIF()

IF ( FEELPP_ENABLE_MOR_HEAT1D )
  add_subdirectory(heat1d)
  add_subdirectory(unsteady_heat1d)
ENDIF()

if ( FEELPP_ENABLE_MOR_LINEARELASTICITY )
  add_subdirectory(linearelasticity3d)
endif()

if ( FEELPP_ENABLE_MOR_THERMALBUILDING )
  add_subdirectory(thermalbuilding)
endif()
if ( FEELPP_ENABLE_MOR_OPUSHEAT )
  add_subdirectory(opusheat)
endif()

IF ( FEELPP_ENABLE_MOR_RBHEAT )
  #add_subdirectory(Rbheat)
ENDIF()

IF ( FEELPP_ENABLE_MOR_CABINEHEAT )
  #add_subdirectory(Cabineheat)
ENDIF()

IF ( FEELPP_ENABLE_MOR_FINALCABINEHEAT )
  #add_subdirectory(Finalcabineheat)
ENDIF()

IF ( FEELPP_ENABLE_MOR_AD1 )
  add_subdirectory(advection-diffusion-2d-1)
ENDIF()


IF ( FEELPP_ENABLE_MOR_THERMALBLOCK )
  add_subdirectory(thermalblock)
ENDIF()


IF ( FEELPP_ENABLE_MOR_HELMHOLTZ )
add_subdirectory(helmholtz)
ENDIF()


if ( FEELPP_ENABLE_MOR_HEATSINK )
  add_subdirectory(heatsink-2d)
ENDIF()

if ( FEELPP_ENABLE_MOR_HEATSHIELD )
  add_subdirectory(heatshield)
ENDIF()

if ( FEELPP_ENABLE_MOR_BENCHMARKGREPL )
  add_subdirectory(BenchmarkGrepl)
ENDIF()

if ( FEELPP_ENABLE_MOR_GEOHEATDIFFUSION )
  add_subdirectory(GeoHeatDiffusion)
ENDIF()

if ( FEELPP_ENABLE_MOR_THERMALFIN )
  add_subdirectory(thermalfin)
ENDIF()

IF ( FEELPP_ENABLE_MOR_EEG )
  add_subdirectory(eeg)
ENDIF()

IF ( FEELPP_ENABLE_MOR_CONVECTION )
  add_subdirectory(convection)
ENDIF()

IF ( FEELPP_ENABLE_MOR_STOKESDEIM )
  add_subdirectory(stokesdeim)
ENDIF()



if ( FEELPP_ENABLE_MOR_MINIMAL )
  add_subdirectory(minimal)
endif()
if ( FEELPP_ENABLE_MOR_THERMOELECTRIC )
  add_subdirectory(thermoelectric)
endif()
if ( FEELPP_ENABLE_MOR_GREPLDEIM )
  add_subdirectory(grepldeim)
endif()

add_subdirectory(pyfeelpp-mor)

include(${FEELPP_MOR_SOURCE_DIR}/cmake/feelpp.mor.cmake)
install(EXPORT feelpp-mor-export-targets
  FILE feelpp-mor-export-targets.cmake
  NAMESPACE Feelpp::
  DESTINATION share/feelpp/mor/cmake/
  )
