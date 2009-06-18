# need to find out:
# OO_SDK_HOME (e.g. /usr/lib64/openoffice.org/sdk)
# oo.org program dir

# UNO_APPENDS(<output> {<suffix>} PATHS {<prefix>})
# Writes all combinations of <prefix>/<suffix> to <output>
MACRO (UNO_APPEND_PATHS output)
  SET(UNO_APPEND_PATHS_SUFFIXES "")
  SET(UNO_APPEND_PATHS_RESULTS "")
  SET(UNO_APPEND_PATHS_STEP 0)
  FOREACH (UNO_APPEND_PATHS_ARG ${ARGN})
    IF (UNO_APPEND_PATHS_STEP)
      # add to results this prefix with each suffix appended
      FOREACH (UNO_APPEND_PATHS_SUFFIX ${UNO_APPEND_PATHS_SUFFIXES})
        SET(UNO_APPEND_PATHS_RESULTS ${UNO_APPEND_PATHS_RESULTS} "${UNO_APPEND_PATHS_ARG}/${UNO_APPEND_PATHS_SUFFIX}")
      ENDFOREACH (UNO_APPEND_PATHS_SUFFIX)
    ELSEIF (UNO_APPEND_PATHS_ARG STREQUAL "PATHS")
      # If we have reached paths, switch processing step
      SET(UNO_APPEND_PATHS_STEP 1)
    ELSE (UNO_APPEND_PATHS_STEP)
      # Just suffixes, gather them together
      SET(UNO_APPEND_PATHS_SUFFIXES ${UNO_APPEND_PATHS_SUFFIXES} ${UNO_APPEND_PATHS_ARG})
    ENDIF (UNO_APPEND_PATHS_STEP)
  ENDFOREACH (UNO_APPEND_PATHS_ARG)
  SET(${output} ${UNO_APPEND_PATHS_RESULTS})
ENDMACRO (UNO_APPEND_PATHS)

# Find OO location
SET(UNO_OO_HOME_LIBS "/usr/lib64" "/usr/lib" "/opt")
UNO_APPEND_PATHS(UNO_OO_HOMES "openoffice.org3" "openoffice.org" PATHS ${UNO_OO_HOME_LIBS})
FIND_PATH(UNO_OO_HOME "program/versionrc" PATHS ${UNO_OO_HOMES})

# Find OO SDK location
UNO_APPEND_PATHS(UNO_OO_SDK_HOMES "basis-link/sdk" "sdk" PATHS ${UNO_OO_HOME})
FIND_PATH(UNO_OO_SDK_HOME "include/sal/types.h" PATHS ${UNO_OO_SDK_HOMES})

SET(UNO_OO_SDK_BINS "${UNO_OO_SDK_HOME}/linux/bin" "${UNO_OO_HOME}/basis-link/ure-link/bin" "${UNO_OO_SDK_HOME}/bin")
SET(UNO_IDL_PATH "${UNO_OO_SDK_HOME}/idl")
SET(UNO_INCLUDES "${UNO_OO_SDK_HOME}/include")
SET(UNO_OO_PROGRAM "${UNO_OO_HOME}/program")
SET(UNO_OO_PROGRAMS "${UNO_OO_HOME}/basis-link/program" "${UNO_OO_HOME}/program")

# Find registry databases
SET(UNO_OO_RDBS )
# offapi (OO.org 3) has the OpenOffice.org API
FIND_FILE(UNO_OO_OFFAPI_RDB "offapi.rdb" PATHS ${UNO_OO_PROGRAMS})
IF(UNO_OO_OFFAPI_RDB)
  SET(UNO_OO_RDBS ${UNO_OO_RDBS} ${UNO_OO_OFFAPI_RDB})
ENDIF(UNO_OO_OFFAPI_RDB)
# types has UNO types and (OO.org 2) OpenOffice.org API
FIND_FILE(UNO_OO_TYPES_RDB "types.rdb" PATHS ${UNO_OO_PROGRAMS} "${UNO_OO_HOME}/basis-link/ure-link/share/misc")
IF(UNO_OO_TYPES_RDB)
  SET(UNO_OO_RDBS ${UNO_OO_RDBS} ${UNO_OO_TYPES_RDB})
ENDIF(UNO_OO_TYPES_RDB)

# Programs
FIND_PROGRAM(UNO_IDLC      "idlc"      PATHS ${UNO_OO_SDK_BINS})
FIND_PROGRAM(UNO_REGMERGE  "regmerge"  PATHS ${UNO_OO_SDK_BINS})
FIND_PROGRAM(UNO_CPPUMAKER "cppumaker" PATHS ${UNO_OO_SDK_BINS})
FIND_PROGRAM(UNO_REGCOMP   "regcomp"   PATHS ${UNO_OO_SDK_BINS})

# OS dependent preprocessor definitions
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  SET(UNO_CPPU_ENV gcc3)
  SET(UNO_SHLIB_EXT so)
  ADD_DEFINITIONS(-DUNX -DGCC -DLINUX)
  SET(UNO_TOOL_ENV env LD_LIBRARY_PATH=${UNO_OO_SDK_HOME}/linux/lib:${UNO_OO_HOME}/basis-link/ure-link/lib)
ELSE (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  MESSAGE("warning: unrecognised system ${CMAKE_SYSTEM_NAME} - you may need to add UNO preprocessor definitions to ${CMAKE_CURRENT_LIST_FILE}")
ENDIF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

# Libraries
SET(UNO_LIB_PATHS ${UNO_OO_PROGRAMS} "${UNO_OO_HOME}/basis-link/ure-link/lib")
MACRO(FIND_UNO_LIB output name)
  FIND_LIBRARY(${output} NAMES ${name} PATHS ${UNO_LIB_PATHS})
  IF(NOT ${output})
    FIND_FILE(${output} NAMES lib${name}.so.3 PATHS ${UNO_LIB_PATHS})
  ENDIF(NOT ${output})
ENDMACRO(FIND_UNO_LIB)

FIND_UNO_LIB(UNO_SAL_LIB        uno_sal) 
FIND_UNO_LIB(UNO_CPPU_LIB       uno_cppu) 
FIND_UNO_LIB(UNO_CPPUHELPER_LIB uno_cppuhelper${UNO_CPPU_ENV}) 
FIND_UNO_LIB(UNO_SALHELPER_LIB  uno_salhelper${UNO_CPPU_ENV}) 
FIND_UNO_LIB(UNO_REG_LIB        reg) 
FIND_UNO_LIB(UNO_STORE_LIB      store) 

# We need these programs to continue
IF (    UNO_OO_HOME
    AND UNO_OO_SDK_HOME
    AND UNO_OO_TYPES_RDB
    AND UNO_IDLC
    AND UNO_REGMERGE
    AND UNO_REGCOMP
    AND UNO_CPPUMAKER
    AND UNO_CPPUHELPER_LIB
    AND UNO_CPPU_LIB
    AND UNO_SALHELPER_LIB
    AND UNO_SAL_LIB
    )
  # SUCCESS
  SET(UNO_FOUND TRUE)

  SET(UNO_LIBS
      ${UNO_CPPUHELPER_LIB}
      ${UNO_CPPU_LIB}
      ${UNO_SALHELPER_LIB}
      ${UNO_SAL_LIB}
  )

  ADD_DEFINITIONS(-DCPPU_ENV=${UNO_CPPU_ENV})

  FIND_PATH(UNO_INCLUDE_DIR uno.h /usr/include/uno /usr/local/include/uno)

  # Macros

  # UNO_ADD_TYPES(sourcevar {types} )
  MACRO (UNO_ADD_TYPES sourcevar)
    SET(UNO_COMPONENT_INC "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/uno_include")
    SET(UNO_RDB "${CMAKE_CURRENT_BINARY_DIR}/types.rdb")
    # Add include directory
    INCLUDE_DIRECTORIES(${UNO_COMPONENT_INC})

    # rdb -> [cppumaker] -> hpp
    SET(UNO_HPPFILES )
    SET(UNO_URDFILES )
    SET(UNO_TYPELIST )
    # prefix each type with -T
    FOREACH(type ${ARGN})
      SET(UNO_TYPELIST ${UNO_TYPELIST} -T${type})
      STRING(REPLACE "." "/" UNO_HPPFILE "${type}")
      SET(UNO_IDLFILE "${UNO_IDL_PATH}/${UNO_HPPFILE}.idl")
      SET(UNO_URDFILE "${UNO_COMPONENT_INC}/${UNO_HPPFILE}.urd")
      GET_FILENAME_COMPONENT(UNO_URDDIR "${UNO_COMPONENT_INC}/${UNO_HPPFILE}.urd" PATH)
      SET(UNO_HPPFILE "${UNO_COMPONENT_INC}/${UNO_HPPFILE}.hpp")
      SET(UNO_URDFILES ${UNO_URDFILES} ${UNO_URDFILE})
      SET(UNO_HPPFILES ${UNO_HPPFILES} ${UNO_HPPFILE})
      # idl file is compiled into urd file
      #ADD_CUSTOM_COMMAND(
      #  OUTPUT ${UNO_URDFILE}
      #  COMMAND ${UNO_TOOL_ENV} ${UNO_IDLC} -C -I${UNO_IDL_PATH} ${UNO_IDLFILE} -O${UNO_URDDIR}
      #  MAIN_DEPENDENCY ${UNO_IDLFILE}
      #)
    ENDFOREACH(type)

    # Combined into a single command because regcomp alters the rdb
    ADD_CUSTOM_COMMAND(
      OUTPUT ${UNO_RDB} ${UNO_HPPFILES}
      COMMAND ${UNO_TOOL_ENV} ${UNO_REGMERGE} ${UNO_RDB} / ${UNO_OO_RDBS} #${UNO_URDFILES}
      COMMAND ${UNO_TOOL_ENV} ${UNO_CPPUMAKER} -Gc -BUCR -O${UNO_COMPONENT_INC} ${UNO_TYPELIST} ${UNO_RDB}
      COMMAND ${UNO_TOOL_ENV} ${UNO_REGCOMP} -register -r ${UNO_RDB} -c connector.uno.${UNO_SHLIB_EXT}
      COMMAND ${UNO_TOOL_ENV} ${UNO_REGCOMP} -register -r ${UNO_RDB} -c remotebridge.uno.${UNO_SHLIB_EXT}
      COMMAND ${UNO_TOOL_ENV} ${UNO_REGCOMP} -register -r ${UNO_RDB} -c bridgefac.uno.${UNO_SHLIB_EXT}
      COMMAND ${UNO_TOOL_ENV} ${UNO_REGCOMP} -register -r ${UNO_RDB} -c uuresolver.uno.${UNO_SHLIB_EXT}
      DEPENDS ${UNO_OO_RDBS}
    )

    # Make each source file depend on the header files
    SET_SOURCE_FILES_PROPERTIES(${${sourcevar}} PROPERTIES OBJECT_DEPENDS "${UNO_HPPFILES}")
  ENDMACRO (UNO_ADD_TYPES)

ENDIF (UNO_OO_HOME     AND UNO_OO_SDK_HOME AND UNO_OO_TYPES_RDB
       AND UNO_IDLC    AND UNO_REGMERGE
       AND UNO_REGCOMP AND UNO_CPPUMAKER
       AND UNO_CPPUHELPER_LIB AND UNO_CPPU_LIB
       AND UNO_SALHELPER_LIB  AND UNO_SAL_LIB
    )

IF (UNO_FOUND)
  IF (NOT UNO_FIND_QUIETLY)
    MESSAGE(STATUS "Found UNO: ${UNO_OO_SDK_HOME}")
  ENDIF (NOT UNO_FIND_QUIETLY)
ELSE (UNO_FOUND)
  IF (UNO_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find UNO")
  ENDIF (UNO_FIND_REQUIRED)
ENDIF (UNO_FOUND)

