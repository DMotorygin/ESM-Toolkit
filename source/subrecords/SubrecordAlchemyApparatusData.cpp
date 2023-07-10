#include "pch.h"

#include "SubrecordAlchemyApparatusData.h"

#include "xmlUtils.h"
#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordAlchemyApparatusData::ESMSubrecordAlchemyApparatusData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Type(0)
	, m_Quality(0.0f)
	, m_Weight(0.0f)
	, m_Value(0)
{}

void ESMSubrecordAlchemyApparatusData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordAlchemyApparatusData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_Type), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//READ_VAR(m_Type);
	//READ_VAR(m_Quality);
	//READ_VAR(m_Weight);
	//READ_VAR(m_Value);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Type", m_Type);
	LOG_VAR_AS_STR("Quality", m_Quality);
	LOG_VAR_AS_STR("Weight", m_Weight);
	LOG_VAR_AS_STR("Value", m_Value);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordAlchemyApparatusData::GetDataSize(void) const
{
	return TotalSum(m_Type, m_Quality, m_Weight, m_Value);
}
