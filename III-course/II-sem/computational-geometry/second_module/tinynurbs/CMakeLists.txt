add_library(tinynurbs
        include/core/basis.h
        include/core/check.h
        include/core/curve.h
        include/core/evaluate.h
        include/core/modify.h
        include/core/surface.h
        include/io/obj.h
        include/util/array2.h
        include/util/util.h
        include/tinynurbs.h)

target_include_directories(tinynurbs PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE source)

set_target_properties(tinynurbs PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF
        LINKER_LANGUAGE CXX)
