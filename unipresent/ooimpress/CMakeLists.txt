project(unipresentooimpress)

set(unipresentooimpress_SRCS
    UpOoimpBackend.cpp
)

set(unipresentooimpress_TYPE STATIC)
add_library(unipresentooimpress ${unipresentooimpress_TYPE} ${unipresentooimpress_SRCS})

