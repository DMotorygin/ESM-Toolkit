#include "pch.h"

#include "SubrecordDataFileInfo.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordDataFileInfo::ESMSubrecordDataFileInfo(void)
	: m_dataLength(0)
	, m_data()
{}

ESMSubrecordDataFileInfo::ESMSubrecordDataFileInfo(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_dataLength(0)
	, m_data()
{}

bool ESMSubrecordDataFileInfo::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	m_dataLength = m_subrecordHeader->GetDataSize();
	m_data.resize(m_dataLength);
	input.read(reinterpret_cast<char*>(m_data.data()), m_dataLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Data Length", BAD_CAST std::to_string(m_dataLength).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordDataFileInfo::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordDataFileInfo::GetDataSize(void) const
{
	return m_data.size();
}

bool ESMSubrecordDataFileInfo::IsValid(void) const
{
	if (!m_subrecordHeader)
		return false;

	size_t subrecordSize = GetDataSize();

	return subrecordSize == m_subrecordHeader->GetDataSize();
}

const char* ESMSubrecordDataFileInfo::GetClassName(void) const
{
	return "Data_File_Info";
}
