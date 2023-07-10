#include "pch.h"

#include "SubrecordIntValue.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordIntValue::ESMSubrecordIntValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_intValue(0)
{}

bool ESMSubrecordIntValue::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	assert(strncmp(m_subrecordHeader->GetSubrecordType().data(), GetShortName(), 4) == 0);

	input.read(reinterpret_cast<char*>(&m_intValue), sizeof(m_intValue));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Value", BAD_CAST std::to_string(m_intValue).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordIntValue::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordIntValue::GetDataSize(void) const
{
	return sizeof(m_intValue);
}

const char* ESMSubrecordIntValue::GetClassName(void) const
{
	return "Integer_Value";
}
