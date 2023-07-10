#include "pch.h"

#include "SubrecordSpellData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordSpellData::ESMSubrecordSpellData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Type(0)
	, m_SpellCost(0)
	, m_Flags(0)
{}

void ESMSubrecordSpellData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordSpellData::Read(std::ifstream& input)
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

	//input.read(reinterpret_cast<char*>(&m_Type), sizeof(m_Type));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_SpellCost), sizeof(m_SpellCost));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_Flags), sizeof(m_Flags));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");											assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Type", BAD_CAST std::to_string(m_Type).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SpellCost", BAD_CAST std::to_string(m_SpellCost).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Flags", BAD_CAST int_to_hex(m_Flags).c_str());				assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordSpellData::GetDataSize(void) const
{
	return TotalSum(m_Type, m_SpellCost, m_Flags);
}

ESMSubrecordSpellEffectData::ESMSubrecordSpellEffectData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_effectID(0)
	, m_skillID(0)
	, m_attributeID(0)
	, m_rangeType(0)
	, m_area(0)
	, m_duration(0)
	, m_min(0)
	, m_max(0)
{}

void ESMSubrecordSpellEffectData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordSpellEffectData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	//READ_VAR(m_effectID);
	//READ_VAR(m_skillID);
	//READ_VAR(m_attributeID);
	//READ_VAR(m_rangeType);
	//READ_VAR(m_area);
	//READ_VAR(m_duration);
	//READ_VAR(m_min);
	//READ_VAR(m_max);
	input.read(reinterpret_cast<char*>(&m_effectID), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");											assert(res != -1);

	LOG_VAR_AS_STR("Effect ID", m_effectID);
	LOG_CHAR_AS_INT("Skill ID", m_skillID);
	LOG_CHAR_AS_INT("Attribute ID", m_attributeID);
	LOG_VAR_AS_STR("Range Type", m_rangeType);
	LOG_VAR_AS_STR("Area", m_area);
	LOG_VAR_AS_STR("Duration", m_duration);
	LOG_VAR_AS_STR("Min", m_min);
	LOG_VAR_AS_STR("Max", m_max);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordSpellEffectData::GetDataSize(void) const
{
	return TotalSum(m_effectID, m_skillID, m_attributeID, m_rangeType, m_area, m_duration, m_min, m_max);
}


