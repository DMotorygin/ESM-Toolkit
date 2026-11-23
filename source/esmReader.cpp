// esmReader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <assert.h>

#include "Reader.h"
#include "Record.h"
#include "xmlUtils.h"

#include <stdio.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>


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
    // TODO: rewrite ConvertInput. Current implementation uses old libxml API that don't work anymore
	//xmlChar* tmp = ConvertInput(pFile, MY_ENCODING);
    xmlChar* tmp = reinterpret_cast<xmlChar*>(pFile);
	res = xmlTextWriterWriteComment(writer, tmp);
	assert(res != -1);
	//if (tmp != NULL) 
	//	xmlFree(tmp);
#endif

	// begin reading
	std::string filepath(pFile);
	//bool success = ReadBinESMToVector(filepath);
    RecordsCollection records_map;
	bool success = ReadBinESMToMap(filepath, records_map);

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

