
#include "pch.h"
#include "SubrecordCommon.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordCommon::ESMSubrecordCommon()
{}

ESMSubrecordCommon::ESMSubrecordCommon(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: m_subrecordHeader(subrecordHeader)
{}

ESMSubrecordCommon::~ESMSubrecordCommon()
{}

const char* ESMSubrecordCommon::GetClassName(void) const
{
	return m_subrecordHeader->GetSubrecordType().data();
}

bool ESMSubrecordCommon::ReadSubrecordHeader(std::ifstream& input)
{
	m_subrecordHeader = std::make_unique<ESMSubrecordHeader>();
	bool res = m_subrecordHeader->Read(input);

	return res;
}

bool ESMSubrecordCommon::IsValid(void) const
{
	size_t subrecordSize = GetDataSize();

	return subrecordSize == m_subrecordHeader->GetDataSize();
}

bool ESMSubrecordCommon::Read(std::ifstream& input)
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

	assert(strncmp(m_subrecordHeader->GetSubrecordType().data(), GetShortName(), 4) == 0);

	// log in xml
	m_subrecordHeader->DumpToXML();

	return true;
}

void ESMSubrecordCommon::Write(std::ostream& output)
{
	// NIY
}


