
target_include_directories(esmToolkit PUBLIC include)

target_sources(esmToolkit 
PRIVATE 
RecordCommon.cpp
Record.cpp
RecordHeader.cpp
RecordGeneral.cpp
PUBLIC
include/Record.h
include/RecordHeader.h
)
