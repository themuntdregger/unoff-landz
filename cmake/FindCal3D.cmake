# - Find CAL3D
# Find the CAL3D includes and library
#
#  CAL3D_INCLUDE_DIR - Where to find CAL3D includes
#  CAL3D_LIBRARIES   - List of libraries when using CAL3D
#  CAL3D_FOUND       - True if CAL3D was found

IF(CAL3D_INCLUDE_DIR)
  SET(CAL3D_FIND_QUIETLY TRUE)
ENDIF(CAL3D_INCLUDE_DIR)

FIND_PATH(CAL3D_INCLUDE_DIR "cal3d/cal3d.h"
  PATHS
  $ENV{CAL3D_HOME}/include
  $ENV{EXTERNLIBS}/cal3d/include
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  DOC "CAL3D - Headers"
)

SET(CAL3D_NAMES cal3d)
SET(CAL3D_DBG_NAMES cal3d_d)

FIND_LIBRARY(CAL3D_LIBRARY NAMES ${CAL3D_NAMES}
  PATHS
  $ENV{CAL3D_HOME}
  $ENV{EXTERNLIBS}/cal3d
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  PATH_SUFFIXES lib lib64
  DOC "CAL3D - Library"
)

INCLUDE(FindPackageHandleStandardArgs)

IF(MSVC)
  # VisualStudio needs a debug version
  FIND_LIBRARY(CAL3D_LIBRARY_DEBUG NAMES ${CAL3D_DBG_NAMES}
    PATHS
    $ENV{CAL3D_HOME}
    $ENV{EXTERNLIBS}/CAL3D
    PATH_SUFFIXES lib lib64
    DOC "CAL3D - Library (Debug)"
  )
  
  IF(CAL3D_LIBRARY_DEBUG AND CAL3D_LIBRARY)
    SET(CAL3D_LIBRARIES optimized ${CAL3D_LIBRARY} debug ${CAL3D_LIBRARY_DEBUG})
  ENDIF(CAL3D_LIBRARY_DEBUG AND CAL3D_LIBRARY)

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(CAL3D DEFAULT_MSG CAL3D_LIBRARY CAL3D_LIBRARY_DEBUG CAL3D_INCLUDE_DIR)

  MARK_AS_ADVANCED(CAL3D_LIBRARY CAL3D_LIBRARY_DEBUG CAL3D_INCLUDE_DIR)
  
ELSE(MSVC)
  # rest of the world
  SET(CAL3D_LIBRARIES ${CAL3D_LIBRARY})

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(CAL3D DEFAULT_MSG CAL3D_LIBRARY CAL3D_INCLUDE_DIR)
  
  MARK_AS_ADVANCED(CAL3D_LIBRARY CAL3D_INCLUDE_DIR)
  
ENDIF(MSVC)

IF(CAL3D_FOUND)
  SET(CAL3D_INCLUDE_DIRS ${CAL3D_INCLUDE_DIR})
ENDIF(CAL3D_FOUND)
