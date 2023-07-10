#include "pch.h"

#include "SubrecordLightData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordLightData::ESMSubrecordLightData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_weight(0.0f)
	, m_value(0)
	, m_time(0)
	, m_radius(0)
	, m_R(0)
	, m_G(0)
	, m_B(0)
	, m_Unknown(0)
	, m_Flags(0)
{}

void ESMSubrecordLightData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordLightData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_weight), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//READ_VAR(m_weight);
	//READ_VAR(m_value);
	//READ_VAR(m_time);
	//READ_VAR(m_radius);
	//READ_VAR(m_R);
	//READ_VAR(m_G);
	//READ_VAR(m_B);
	//READ_VAR(m_Unknown);
	//READ_VAR(m_Flags);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("weight", m_weight);
	LOG_VAR_AS_STR("value", m_value);
	LOG_VAR_AS_STR("time", m_time);
	LOG_VAR_AS_STR("radius", m_radius);
	int r = 0;
	int g = 0;
	int b = 0;
	((char*)&r)[0] = m_R;
	((char*)&g)[0] = m_G;
	((char*)&b)[0] = m_B;
	LOG_VAR_AS_STR("R", r);
	LOG_VAR_AS_STR("G", g);
	LOG_VAR_AS_STR("B", b);
	LOG_CHAR_AS_INT("Unknown", m_Unknown);
	LOG_VAR_AS_HEX("Flags", m_Flags);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordLightData::GetDataSize(void) const
{
	return TotalSum(m_weight, m_value, m_time, m_radius, m_R, m_G, m_B, m_Unknown, m_Flags);
}
