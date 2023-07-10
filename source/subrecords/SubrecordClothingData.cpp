#include "pch.h"

#include "SubrecordClothingData.h"

#include "xmlUtils.h"
#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordClothingData::ESMSubrecordClothingData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Type(0)
	, m_Weight(0.0f)
	, m_Value(0)
	, m_EnchantPoints(0)
{}

void ESMSubrecordClothingData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordClothingData::Read(std::ifstream& input)
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
	//READ_VAR(m_Weight);
	//READ_VAR(m_Value);
	//READ_VAR(m_EnchantPoints);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Type", m_Type);
	LOG_VAR_AS_STR("Weight", m_Weight);
	LOG_VAR_AS_STR("Value", m_Value);
	LOG_VAR_AS_STR("EnchantPoints", m_EnchantPoints);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordClothingData::GetDataSize(void) const
{
	return TotalSum(m_Type, m_Weight, m_Value, m_EnchantPoints);
}
