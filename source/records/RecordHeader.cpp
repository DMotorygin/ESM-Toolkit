
#include "pch.h"
#include "RecordHeader.h"
#include "xmlUtils.h"
#include <fstream>
#include <assert.h>

const int recordHeaderSize = 16;

ESMRecordHeader::ESMRecordHeader()
	: m_str(m_recordType, 4)
	, m_dataSize(0)
	, m_unknown(0)
	, m_flags(0)
{}

ESMRecordHeader::~ESMRecordHeader()
{}

int ESMRecordHeader::GetDataSize(void) const
{
	return m_dataSize;
}

const std::string_view& ESMRecordHeader::GetRecordType(void) const
{
	return m_str;
}

void ESMRecordHeader::Write(std::ostream& output)
{
	// NIY
}

void ESMRecordHeader::DumpToXML(void)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record_Header");														assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Type", BAD_CAST std::string(m_recordType, 4).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Size", BAD_CAST std::to_string(m_dataSize).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Header Unknown Value", BAD_CAST std::to_string(m_unknown).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Flags", BAD_CAST int_to_hex(m_flags).c_str());						assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
}

bool ESMRecordHeader::Read(std::ifstream& input)
{
	// ensure valid input stream
	if (!input)
		return false;

	// read data from file
	input.read(reinterpret_cast<char*>(this), recordHeaderSize);

	/*char data[recordHeaderSize];
	input.read(data, recordHeaderSize);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	// read record type
	m_recordType.assign(data, 4); // record type always have length 4

	// read subrecord data size (this value excludes size of the header)
	memcpy((char*)&m_dataSize, data+4, 4);

	// read header's unknown flags
	memcpy((char*)&m_unknown, data+8, 4);

	// read header known flags
	// TODO: write meaning of this flags
	memcpy((char*)&m_flags, data+12, 4);*/

	/*
	// read record type
	char recordType[recordHeaderSize];
	input.read(recordType, recordHeaderSize);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	m_recordType.assign(recordType, recordHeaderSize);

	// read subrecord data size (this value excludes size of the header)
	input.read(reinterpret_cast<char*>(&m_dataSize), sizeof(m_dataSize));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	// read header's unknown flags 
	input.read(reinterpret_cast<char*>(&m_unknown), sizeof(m_unknown));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	// read header known flags
	// TODO: write meaning of this flags
	input.read(reinterpret_cast<char*>(&m_flags), sizeof(m_flags));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	*/

	return true;
}

