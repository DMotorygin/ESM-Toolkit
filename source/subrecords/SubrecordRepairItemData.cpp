#include "pch.h"

#include "SubrecordRepairItemData.h"

#include "xmlUtils.h"
#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordRepairItemData::ESMSubrecordRepairItemData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Weight(0.0f)
	, m_Value(0)
	, m_Uses(0)
	, m_Quality(0.0f)
{}

void ESMSubrecordRepairItemData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordRepairItemData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_Weight), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//READ_VAR(m_Weight);
	//READ_VAR(m_Value);
	//READ_VAR(m_Uses);
	//READ_VAR(m_Quality);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Weight", m_Weight);
	LOG_VAR_AS_STR("Value", m_Value);
	LOG_VAR_AS_STR("Uses", m_Uses);
	LOG_VAR_AS_STR("Quality", m_Quality);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordRepairItemData::GetDataSize(void) const
{
	return TotalSum(m_Weight, m_Value, m_Uses, m_Quality);
}
