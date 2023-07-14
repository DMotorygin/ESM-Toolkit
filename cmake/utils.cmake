macro(set_if_undefined variable)
    if (NOT DEFINED "${variable}")
        set("${variable}" ${ARGN})
    endif()
endmacro()

macro(win32_copy_runtime_deps target component)
    if(WIN32)
        # such a task should be solved with
        # $<TARGET_PDB_FILE:tgt> and $<TARGET_RUNTIME_DLLS:tgt>
        # but some 3rd_party CMake cmake libraries do work correctly with с $<TARGET_RUNTIME_DLLS:tgt>
        # for example, zlib - does not work, and zlib does not install with $<TARGET_RUNTIME_DLLS:tgt> (at the moment I write this comment)
        # so reinventing the wheel here
        install(CODE "
            file(GLOB _found_files \"$<TARGET_FILE_DIR:${target}>/*.[dp][ld][lb]\")
            file(INSTALL \${_found_files} DESTINATION \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}\")
        " COMPONENT ${component})
    endif()
endmacro()
