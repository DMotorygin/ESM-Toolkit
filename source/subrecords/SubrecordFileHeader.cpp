#include "pch.h"

#include "SubrecordFileHeader.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordFileHeader::ESMSubrecordFileHeader(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordFileHeader::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_version);
	READ_VAR(m_fileType);

	m_companyName.resize(32);
	input.read(m_companyName.data(), 32);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	m_fileDesc.resize(256);
	input.read(m_fileDesc.data(), 256);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	READ_VAR(m_numRecords);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Version", m_version);
	LOG_VAR_AS_STR("File Type", m_fileType);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Company Name", BAD_CAST m_companyName.c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "File Description", BAD_CAST m_fileDesc.c_str()); assert(res != -1);
	LOG_VAR_AS_STR("Count of Records", m_numRecords);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordFileHeader::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordFileHeader::GetDataSize(void) const
{
	return TotalSum(m_version, m_fileType, m_numRecords) + m_companyName.size() + m_fileDesc.size();
}

bool ESMSubrecordFileHeader::IsValid(void) const
{
	size_t subrecordSize = GetDataSize();

	return subrecordSize == m_subrecordHeader->GetDataSize();
}

const char* ESMSubrecordFileHeader::GetClassName(void) const
{
	return "Main_Header_Subrecord";
}
