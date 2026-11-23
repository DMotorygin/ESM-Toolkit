
#include <string>
#include <fstream>
#include <functional>
#include <assert.h>
#include <deque>
#include <chrono>

#include "Reader.h"

// esm records wrappers factory
using ESMObjCreatorFunc = std::function<ESMRecordIface* (std::unique_ptr<ESMRecordHeader>& header)>;

static CreatorsMap<ESMObjCreatorFunc> ESMObjCreatorFuncs =
{
    { "TES3", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordMainHeader(header); }
    },
    { "GMST", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordGameSetting(header); }
    },
    { "GLOB", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordGlobalVariable(header); }
    },
    { "CLAS", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordClass(header); }
    },
    { "REGN", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordRegion(header); }
    },
    { "LTEX", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordLandTexture(header); }
    },
    { "NPC_", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordNPC(header); }
    },
    { "SPEL", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordSpell(header); }
    },
    { "ENCH", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordEnchantment(header); }
    },
    { "ALCH", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordAlchemyPotion(header); }
    },
    { "LEVI", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordLeveledItemsList(header); }
    },
    { "LEVC", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordLeveledCreaturesList(header); }
    },
    { "CELL", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordCell(header); }
    },
    { "LAND", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordLand(header); }
    },
    { "PGRD", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordPathGrid(header); }
    },
    { "INFO", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordDialogInfo(header); }
    },
    { "MGEF", [](std::unique_ptr<ESMRecordHeader>& header) {
        return (ESMRecordIface*) new ESMRecordMagicEffect(header); }
    },
};

std::unique_ptr<ESMRecordIface> ReadESMRecord(std::ifstream& input, bool& result)
{
    bool success = false;

    // read record header
    std::unique_ptr<ESMRecordHeader> header = std::make_unique<ESMRecordHeader>();
    result = header->Read(input);
    if (!result)
        return std::unique_ptr<ESMRecordIface>();

    // find correct record creator function
    ESMObjCreatorFunc pCreator = nullptr;
    auto it = ESMObjCreatorFuncs.find(header->GetRecordType().data());
    if (it == ESMObjCreatorFuncs.end())
    {
        pCreator = [](std::unique_ptr<ESMRecordHeader>& header)
            {
                return (ESMRecordIface*) new ESMRecordGeneral(header);
            };
    }
    else
    {
        pCreator = it->second;
    }

    // create record instance
    ESMRecordIface* pESMObj = pCreator(header);

    // read record
    success = pESMObj->Read(input);
    result = success;
    assert(success);

    //if (!success) // don't want to abort want app to process failure
        //std::abort();

    std::unique_ptr<ESMRecordIface> esmObjWrapper(pESMObj);
    return esmObjWrapper;
}

typedef std::chrono::high_resolution_clock chrono;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

const int count_records = 50000;

bool ReadBinESMToVector(std::string filepath)
{
    std::ifstream input(filepath, std::ios::binary);
    if (!input)
        return false;

    std::vector<std::unique_ptr<ESMRecordIface>> records;
    records.reserve(count_records);

    chrono::time_point t0 = chrono::now();

    // in one thread because reading from HDD
    do
    {
        bool success = false;
        records.push_back(ReadESMRecord(input, success));

        if (!success)
            return false;

    } while (input && !input.eof());
    input.close();

    // output time log
    chrono::time_point t1 = chrono::now();
    fsec fs = t1 - t0;
    ms d = std::chrono::duration_cast<ms>(fs);
    std::cout << "time spent reading: " << std::to_string(d.count()).c_str() << " ms\n";

    return true;
}


bool ReadBinESMToMap(std::string filepath,
    RecordsCollection& records_map)
{
    // ensure valid input
    std::ifstream input(filepath, std::ios::binary);
    if (!input)
        return false;

    // time logging
    chrono::time_point t0 = chrono::now();

    // Read in one thread because reading from HDD
    do {
        bool success = false;
        std::unique_ptr<ESMRecordIface> esmObjWrapper(ReadESMRecord(input, success));
        if (success)
            AssignRecord<RECORDS>(records_map, std::move(esmObjWrapper));
    } while (input && !input.eof());
    input.close();

    // output time log
    chrono::time_point t1 = chrono::now();
    fsec fs = t1 - t0;
    ms d = std::chrono::duration_cast<ms>(fs);
    std::cout << "time spent reading: " << std::to_string(d.count()).c_str() << " ms\n";

    return true;
}


