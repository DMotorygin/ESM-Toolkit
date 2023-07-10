
#include "pch.h"
#include "SubrecordHeader.h"
#include "xmlUtils.h"

#include <fstream>
#include <assert.h>

const int subrecordHeaderSize = 8;

ESMSubrecordHeader::ESMSubrecordHeader()
	: m_str(m_subRecordType, 4)
	, m_dataSize(0)
{
}

ESMSubrecordHeader::~ESMSubrecordHeader()
{}

int ESMSubrecordHeader::GetDataSize(void) const
{ 
	return m_dataSize; 
}

const std::string_view& ESMSubrecordHeader::GetSubrecordType(void) const
{ 
	return m_str;
}

// always 8 bytes
size_t ESMSubrecordHeader::HeaderSize(void)
{
	return sizeof(int) + 4; // m_subRecordType is always 4 bytes
}

void ESMSubrecordHeader::Write(std::ostream& output)
{
	// NIY
}

void ESMSubrecordHeader::DumpToXML(void)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Header");
	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Type", BAD_CAST std::string(m_subRecordType, 4).c_str()/*m_str.data()*/);
	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Size", BAD_CAST std::to_string(m_dataSize).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif
}

bool ESMSubrecordHeader::Read(std::ifstream& input)
{
	// ensure valid input stream
	if (!input)
		return false;

	// read subrecord header
	input.read(reinterpret_cast<char*>(this), subrecordHeaderSize);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	// read subrecord type
	/*char data[subrecordHeaderSize];
	input.read(data, subrecordHeaderSize);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;*/

	/*
	m_subRecordType.assign(data, 4); // m_subRecordType always have length 4
	assert(m_subRecordType != "");

	// read subrecord data size (this value excludes size of the header)
	memcpy((char*)&m_dataSize, data+4, 4);*/

	return true;
}

