#include "pch.h"

#include "SubrecordUnknown.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordUnknown::ESMSubrecordUnknown(void)
	: m_dataSize(0)
	, m_data()
{}

ESMSubrecordUnknown::~ESMSubrecordUnknown()
{}

ESMSubrecordUnknown::ESMSubrecordUnknown(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordUnknown::Read(std::ifstream& input)
{
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

	// read subrecord as raw data
	m_dataSize = m_subrecordHeader->GetDataSize();
	m_data.resize(m_dataSize);
	input.read(m_data.data(), m_dataSize);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Data Size", BAD_CAST std::to_string(m_dataSize).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordUnknown::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordUnknown::GetDataSize(void) const
{
	return m_dataSize;
}

const char* ESMSubrecordUnknown::GetClassName(void) const
{
	return "Unknow Data Block";
}

bool ESMSubrecordUnknown::IsValid(void) const
{
	return (GetDataSize() == m_subrecordHeader->GetDataSize()) && (m_dataSize == m_data.size());
}

