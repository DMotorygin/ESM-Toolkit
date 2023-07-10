#include "pch.h"

#include "SubrecordStringValue.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordStringValue::ESMSubrecordStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordStringValue::Read(std::ifstream& input)
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
	m_stringValue.resize(stringLength);
	input.read(m_stringValue.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Value", BAD_CAST m_stringValue.c_str()); assert(res != -1);

	res = xmlTextWriterEndElement(writer); assert(res != -1);
	res = xmlTextWriterEndElement(writer); assert(res != -1);
#endif

	return true;
}

void ESMSubrecordStringValue::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordStringValue::GetDataSize(void) const
{
	return m_stringValue.size();
}

const char* ESMSubrecordStringValue::GetClassName(void) const
{
	return "String_Value";
}

const char* ESMSubrecordStringValue::GetShortName(void) const 
{
	return "STRV";
}

