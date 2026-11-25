
target_include_directories(esmToolkit PRIVATE include)
target_include_directories(esmRetort PRIVATE include)

set(SOURCES
    RecordCommon.cpp
    Record.cpp
    RecordHeader.cpp
    RecordGeneral.cpp
)

target_sources(esmToolkit PRIVATE ${SOURCES})
target_sources(esmRetort PRIVATE ${SOURCES})
