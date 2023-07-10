#include "pch.h"

#include "SubrecordIDValue.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>


bool SubrecordIDValue::Read(std::ifstream& input)
{
	// read subrecord data
	if (m_subrecordHeader->GetDataSize() == 4)
	{
		return ESMSubrecordIntValue::Read(input);
	}

	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	char value;
	input.read(reinterpret_cast<char*>(&value), sizeof(value));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	m_intValue = value;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Value ", m_intValue);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void SubrecordIDValue::Write(std::ostream& output)
{
	// NIY
}

size_t SubrecordIDValue::GetDataSize(void) const
{
	return (m_subrecordHeader->GetDataSize() == 4) ? sizeof(m_intValue) : 1;
}

const char* SubrecordIDValue::GetClassName(void) const
{
	if (m_subrecordHeader->GetDataSize() == 4)
	{
		return "ID Value";
	}
	else
	{
		return "Body Part Index";
	}
}

