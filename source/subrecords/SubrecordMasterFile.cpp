#include "pch.h"

#include "SubrecordMasterFile.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordMasterFile::ESMSubrecordMasterFile(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordMasterFile::Read(std::ifstream& input)
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

	// read subrecord data
	assert(strncmp(m_subrecordHeader->GetSubrecordType().data(), "MAST", 4) == 0);

	input.read(reinterpret_cast<char*>(&m_nameLength), sizeof(m_nameLength));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	m_fileName.resize(m_nameLength);
	input.read(m_fileName.data(), m_nameLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Name Length", BAD_CAST std::to_string(m_nameLength).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "File Name", BAD_CAST m_fileName.c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordMasterFile::Write(std::ostream& output)
{
	// NIY
}


size_t ESMSubrecordMasterFile::GetDataSize(void) const
{
	return m_fileName.size() + sizeof(m_nameLength);
}

bool ESMSubrecordMasterFile::IsValid(void) const
{
	if (!m_subrecordHeader)
		return false;

	size_t subrecordSize = GetDataSize();

	return subrecordSize == m_subrecordHeader->GetDataSize();
}

const char* ESMSubrecordMasterFile::GetClassName(void) const
{
	return "Master_File_Reference";
}
