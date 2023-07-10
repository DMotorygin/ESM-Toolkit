// esmReader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>
#include <assert.h>
#include <deque>
#include <chrono>

#include "Record.h"
#include "xmlUtils.h"

#include <stdio.h>
#include <string.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

// esm records wrappers factory
using ESMObjCreatorFunc = std::function<ESMRecordIface*(std::unique_ptr<ESMRecordHeader>& header)>;

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
}; 

std::unique_ptr<ESMRecordIface> ReadESMRecord(std::ifstream& input, bool& result)
{
	bool success = false;

	// read record header
	std::unique_ptr<ESMRecordHeader> header = std::make_unique<ESMRecordHeader>();
	success = header->Read(input);
	assert(success);

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

	//if (!success)
		//std::abort();

	std::unique_ptr<ESMRecordIface> esmObjWrapper(pESMObj);
	return esmObjWrapper;
}

bool ReadBinESM(std::string filepath)
{
	std::ifstream input(filepath, std::ios::binary);
	if (!input)
		return false;

	std::vector<std::unique_ptr<ESMRecordIface>> records;
	records.reserve(48500);
	//std::deque<std::unique_ptr<ESMRecordIface>> records;

	typedef std::chrono::high_resolution_clock chrono;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;
	chrono::time_point t0 = chrono::now();

	size_t count = 0;
	while (!input.eof())
	{
		bool success = false;
		records.push_back(ReadESMRecord(input, success));

		if (!success)
			return false;

		if (count++ > 22000)
			break;
	}
	input.close();

	chrono::time_point t1 = chrono::now();
	fsec fs = t1 - t0;
	ms d = std::chrono::duration_cast<ms>(fs);
	std::cout << "time spent reading: " << std::to_string(d.count()).c_str() << " ms\n";

	return true;
}

bool ReadESM(char* pFile, char* pOut)
{
#ifdef DUMP_ESM_TO_XML
	XMLWriterWrapper::SetXMLWriterOutputFile(pOut);
	int res = 0;
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);
	res = xmlTextWriterStartElement(writer, BAD_CAST "File");
	assert(res != -1);
#endif

	// ensure file found
	if (pFile == nullptr)
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlChar* tmp = ConvertInput(pFile, MY_ENCODING);
	res = xmlTextWriterWriteComment(writer, tmp);
	assert(res != -1);
	if (tmp != NULL) 
		xmlFree(tmp);
#endif

	// begin reading
	std::string filepath(pFile);
	bool success = ReadBinESM(filepath);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);

	res = xmlTextWriterEndDocument(writer);
	assert(res != -1);

	xmlFreeTextWriter(writer);

	assert(res != -1);
#endif

	return success;
}

// Args example:
// "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Morrowind\\Data Files\\Morrowind.esm" "C:\\debug\\esm\\Morr.xml"
// 
int main(int argc, char* argv[])
{
	if (argc < 3)
		return 1;

	bool res = ReadESM(argv[1], argv[2]);

	if (!res)
	{
		std::cout << "Run Failed!\n";
		return 1;
	}

	std::cout << "Run Completed!\n";
	return 0;
}

