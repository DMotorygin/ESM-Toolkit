#include "pch.h"

#include "SubrecordFriendlyName.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordFriendlyName::ESMSubrecordFriendlyName(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordFriendlyName::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	size_t stringLength = m_subrecordHeader->GetDataSize();
	m_name.resize(stringLength);
	input.read(m_name.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	/*
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST std::string("Subrecord " + std::string(GetClassName())).c_str());
	assert(res != -1);
#endif

	// ensure valid input stream
	if (!input)
		return false;

	// read subrecord header
	bool needReadHeader = !m_subrecordHeader;
	if (needReadHeader)
		if (!ReadSubrecordHeader(input))
			return false;

	// log in xml
	m_subrecordHeader->DumpToXML();

	// read subrecord data
	assert(strncmp(m_subrecordHeader->GetSubrecordType().data(), "FNAM", 4) == 0);

	size_t stringLength = m_subrecordHeader->GetDataSize();
	char* buffer = new char[stringLength];
	input.read(buffer, stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	m_name.resize(stringLength);
	m_name.assign(buffer, stringLength);
	delete[] buffer;*/

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Value", BAD_CAST m_name.c_str()); assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordFriendlyName::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordFriendlyName::GetDataSize(void) const
{
	return m_name.size();
}

const char* ESMSubrecordFriendlyName::GetClassName(void) const
{
	return "Friendly_Name";
}
