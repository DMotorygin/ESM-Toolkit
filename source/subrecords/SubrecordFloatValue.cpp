#include "pch.h"

#include "SubrecordFloatValue.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordFloatValue::ESMSubrecordFloatValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordFloatValue::Read(std::ifstream& input)
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

	READ_VAR(m_floatValue);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Value", m_floatValue);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordFloatValue::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordFloatValue::GetDataSize(void) const
{
	return sizeof(m_floatValue);
}

const char* ESMSubrecordFloatValue::GetClassName(void) const
{
	return "Float_Value";
}
