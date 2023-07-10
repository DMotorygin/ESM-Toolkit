#include "pch.h"

#include "SubrecordAlchemyData.h"

#include "xmlUtils.h"
#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordAlchemyData::ESMSubrecordAlchemyData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Weight(0.0f)
	, m_Value(0)
	, m_auto(0)
{}

void ESMSubrecordAlchemyData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordAlchemyData::Read(std::ifstream& input)
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
	//READ_VAR(m_auto);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Weight", m_Weight);
	LOG_VAR_AS_STR("Value", m_Value);
	LOG_VAR_AS_STR("auto", m_auto);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordAlchemyData::GetDataSize(void) const
{
	return TotalSum(m_Weight, m_Value, m_auto);
}
