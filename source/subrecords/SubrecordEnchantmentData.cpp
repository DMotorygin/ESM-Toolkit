#include "pch.h"

#include "SubrecordEnchantmentData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordEnchantmentData::ESMSubrecordEnchantmentData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_type(0)
	, m_cost(0)
	, m_charge(0)
	, m_autoCalc(0)
{}

void ESMSubrecordEnchantmentData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordEnchantmentData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_type), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//READ_VAR(m_type);
	//READ_VAR(m_cost);
	//READ_VAR(m_charge);
	//READ_VAR(m_autoCalc);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("weight", m_type);
	LOG_VAR_AS_STR("value", m_cost);
	LOG_VAR_AS_STR("time", m_charge);
	LOG_VAR_AS_STR("radius", m_autoCalc);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordEnchantmentData::GetDataSize(void) const
{
	return TotalSum(m_type, m_cost, m_charge, m_autoCalc);
}
