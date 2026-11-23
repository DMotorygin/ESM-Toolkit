# --------------------------------------------
# 3rd Parties
# --------------------------------------------

find_package(LibXml2 CONFIG REQUIRED)

# --------------------------------------------
# Targets Definition
# --------------------------------------------

add_executable(esmToolkit)
#add_executable(esmRetort)

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

#set(RETORT_SOURCES 
#    pch.cpp 
#    main.cpp)
#target_sources(esmRetort PRIVATE ${RETORT_SOURCES})
#target_include_directories(esmRetort PRIVATE include)

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
