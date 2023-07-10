#include "pch.h"

#include "SubrecordArmourData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordArmourData::ESMSubrecordArmourData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Type(0)
	, m_Weight(0.0f)
	, m_Value(0)
	, m_Health(0)
	, m_EnchantPoints(0)
	, m_Armour(0)
{}

void ESMSubrecordArmourData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordArmourData::Read(std::ifstream& input)
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
	//READ_VAR(m_Health);
	//READ_VAR(m_EnchantPoints);
	//READ_VAR(m_Armour);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Type", m_Type);
	LOG_VAR_AS_STR("Weight", m_Weight);
	LOG_VAR_AS_STR("Value", m_Value);
	LOG_VAR_AS_STR("Health", m_Health);
	LOG_VAR_AS_STR("EnchantPoints", m_EnchantPoints);
	LOG_VAR_AS_STR("Armour", m_Armour);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordArmourData::GetDataSize(void) const
{
	return TotalSum(m_Type, m_Weight, m_Value, m_Health, m_EnchantPoints, m_Armour);
}
