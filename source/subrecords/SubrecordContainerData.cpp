#include "pch.h"

#include "SubrecordContainerData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>


ESMSubrecordContainerData::ESMSubrecordContainerData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Weight(0)
{}

void ESMSubrecordContainerData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordContainerData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_Weight);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");											assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Weight", BAD_CAST std::to_string(m_Weight).c_str());			assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordContainerData::GetDataSize(void) const
{
	return sizeof(float);
}

ESMSubrecordFlags::ESMSubrecordFlags(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Flags(0)
{}

void ESMSubrecordFlags::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordFlags::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_Flags);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");										assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Flags", BAD_CAST int_to_hex(m_Flags).c_str());			assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordFlags::GetDataSize(void) const
{
	return sizeof(int);
}
