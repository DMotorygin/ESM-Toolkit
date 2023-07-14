
target_include_directories(esmToolkit PRIVATE include)
target_sources(esmToolkit PRIVATE
    RecordCommon.cpp
    Record.cpp
    RecordHeader.cpp
    RecordGeneral.cpp
)
