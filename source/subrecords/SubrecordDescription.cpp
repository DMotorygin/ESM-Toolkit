#include "pch.h"

#include "SubrecordDescription.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordDescription::ESMSubrecordDescription(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordDescription::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	int nameLength = m_subrecordHeader->GetDataSize();
	m_description.resize(nameLength);
	input.read(m_description.data(), nameLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "value", BAD_CAST m_description.c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordDescription::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordDescription::GetDataSize(void) const
{
	return m_description.size();
}

const char* ESMSubrecordDescription::GetClassName(void) const
{
	return "Description";
}
