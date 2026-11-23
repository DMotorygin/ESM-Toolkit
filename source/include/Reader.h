#pragma once

#include <string.h>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>

#include "pch.h"
#include "Record.h"

bool ReadBinESMToVector(std::string filepath);

bool ReadBinESMToMap(std::string filepath,
    RecordsCollection& records_map);

template<typename T, typename... Args>
void AssignRecord(RecordsCollection& records_map,
    std::unique_ptr<ESMRecordIface> ptr)
{
    if (dynamic_cast<T*>(ptr.get()) != nullptr) {
        unsigned int uuid = ptr->UUID();
        using Map = std::map<unsigned int, std::unique_ptr<T>>;
        auto& records = std::get<Map>(records_map);
        auto it = records.find(uuid);
        //        if (it != records.end())
        //            int debugj = 0;
        records[uuid] = std::unique_ptr<T>(static_cast<T*>(ptr.release()));
    }
    else if constexpr (sizeof...(Args) > 0)
    {
        AssignRecord<Args...>(records_map, std::move(ptr));
    }
}

