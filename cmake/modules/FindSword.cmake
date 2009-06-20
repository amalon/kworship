SET (REQUIRED_SWORD_VERSION 1.6.0)

# This module looks for installed sword
# It is copied from the bibletime cmake/modules directory
#
# It will define the following values
# SWORD_INCLUDE_DIR
# SWORD_LIBS
# SWORD_FOUND         If false, don't try to use sword.

EXECUTE_PROCESS(COMMAND pkg-config --atleast-version=${REQUIRED_SWORD_VERSION} sword
	RESULT_VARIABLE SWORD_VERSION_OK
)
EXECUTE_PROCESS(COMMAND pkg-config --modversion sword
	OUTPUT_VARIABLE SWORD_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

IF (SWORD_VERSION_OK EQUAL 0)

	EXECUTE_PROCESS(COMMAND pkg-config --variable=includedir sword
		OUTPUT_VARIABLE SWORD_INCLUDE_DIR
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	EXECUTE_PROCESS(COMMAND pkg-config --libs sword
		OUTPUT_VARIABLE SWORD_LIBS
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	SET(SWORD_INCLUDE_DIR "${SWORD_INCLUDE_DIR}/sword")

	IF (NOT SWORD_FIND_QUIETLY)
		MESSAGE(STATUS "Sword version ${SWORD_VERSION} is ok")

		MESSAGE(STATUS "Sword lib linker flags to be used: ${SWORD_LIBS}")

		MESSAGE(STATUS "Sword include directory is ${SWORD_INCLUDE_DIR}")
	ENDIF (NOT SWORD_FIND_QUIETLY)

	MARK_AS_ADVANCED(
		SWORD_INCLUDE_DIR
		SWORD_LIBS
	)
	
	SET(SWORD_FOUND TRUE)

ELSE (SWORD_VERSION_OK EQUAL 0)
	IF (SWORD_FIND_REQUIRED)
		SET (SWORD_MESSAGE_TYPE FATAL_ERROR)
	ELSE (SWORD_FIND_REQUIRED)
		SET (SWORD_MESSAGE_TYPE STATUS)
	ENDIF (SWORD_FIND_REQUIRED)

	IF (SWORD_VERSION)
		MESSAGE(${SWORD_MESSAGE_TYPE} "Sword version ${SWORD_VERSION} does not match the required ${REQUIRED_SWORD_VERSION}")
	ELSE (SWORD_VERSION)
		MESSAGE(${SWORD_MESSAGE_TYPE} "Sword not found")
	ENDIF (SWORD_VERSION)
ENDIF (SWORD_VERSION_OK EQUAL 0)
