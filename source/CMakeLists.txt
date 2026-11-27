# --------------------------------------------
# 3rd Parties
# --------------------------------------------

find_package(LibXml2 CONFIG REQUIRED)

# --------------------------------------------
# Targets Definition
# --------------------------------------------

add_executable(esmToolkit)
add_executable(esmRetort WIN32)

# --------------------------------------------
# Target Configuration
# --------------------------------------------

add_subdirectory(subrecords)
add_subdirectory(records)

set(ESM_SOURCES 
    xmlUtils.cpp
    pch.cpp 
	Reader.cpp
    esmReader.cpp)

target_sources(esmToolkit PRIVATE ${ESM_SOURCES})
target_include_directories(esmToolkit PRIVATE include)
target_link_libraries(esmToolkit PRIVATE LibXml2::LibXml2)

if (DUMP_ESM_TO_XML)
    target_compile_definitions(esmToolkit PRIVATE
        DUMP_ESM_TO_XML
    )
endif()

set(RETORT_SOURCES 
    xmlUtils.cpp
    pch.cpp 
	Reader.cpp
    Retort.cpp
	retort_app/Retort.rc)
	
target_sources(esmRetort PRIVATE ${RETORT_SOURCES})

target_include_directories(esmRetort PRIVATE 
	include 
	retort_app/include)
	
target_link_libraries(esmRetort PRIVATE LibXml2::LibXml2)

# Enable Unicode Windows APIs
target_compile_definitions(esmRetort PRIVATE
    UNICODE
    _UNICODE
)

add_custom_command(TARGET esmRetort POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/retort_app/PNG"
        "$<TARGET_FILE_DIR:esmRetort>/PNG"
)

# --------------------------------------------
# Target Installation
# --------------------------------------------

if (ESMTOOLKIT_INSTALL_TARGETS AND NOT CMAKE_SKIP_INSTALL_RULES)
    install(TARGETS esmToolkit
            EXPORT esmToolkit-export
            RUNTIME COMPONENT esmToolkit-exe
            )

    win32_copy_runtime_deps(esmToolkit esmToolkit-export)
endif ()
