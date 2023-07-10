#include "pch.h"

#include "SubrecordCreatureData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>


ESMSubrecordCreatureData::ESMSubrecordCreatureData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Type(0)
	, m_Level(0)
	, m_Strength(0)
	, m_Intelligence(0)
	, m_Willpower(0)
	, m_Agility(0)
	, m_Speed(0)
	, m_Endurance(0)
	, m_Personality(0)
	, m_Luck(0)
	, m_Health(0)
	, m_SpellPts(0)
	, m_Fatigue(0)
	, m_Soul(0)
	, m_Combat(0)
	, m_Magic(0)
	, m_Stealth(0)
	, m_AttackMin1(0)
	, m_AttackMax1(0)
	, m_AttackMin2(0)
	, m_AttackMax2(0)
	, m_AttackMin3(0)
	, m_AttackMax3(0)
	, m_Gold(0)
{}

void ESMSubrecordCreatureData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordCreatureData::Read(std::ifstream& input)
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
	//READ_VAR(m_Level);
	//READ_VAR(m_Strength);
	//READ_VAR(m_Intelligence);
	//READ_VAR(m_Willpower);
	//READ_VAR(m_Agility);
	//READ_VAR(m_Speed);
	//READ_VAR(m_Endurance);
	//READ_VAR(m_Personality);
	//READ_VAR(m_Luck);
	//READ_VAR(m_Health);
	//READ_VAR(m_SpellPts);
	//READ_VAR(m_Fatigue);
	//READ_VAR(m_Soul);
	//READ_VAR(m_Combat);
	//READ_VAR(m_Magic);
	//READ_VAR(m_Stealth);
	//READ_VAR(m_AttackMin1);
	//READ_VAR(m_AttackMax1);
	//READ_VAR(m_AttackMin2);
	//READ_VAR(m_AttackMax2);
	//READ_VAR(m_AttackMin3);
	//READ_VAR(m_AttackMax3);
	//READ_VAR(m_Gold);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Type", m_Type);
	LOG_VAR_AS_STR("Level", m_Level);
	LOG_VAR_AS_STR("Strength", m_Strength);
	LOG_VAR_AS_STR("Intelligence", m_Intelligence);
	LOG_VAR_AS_STR("Willpower", m_Willpower);
	LOG_VAR_AS_STR("Agility", m_Agility);
	LOG_VAR_AS_STR("Speed", m_Speed);
	LOG_VAR_AS_STR("Endurance", m_Endurance);
	LOG_VAR_AS_STR("Personality", m_Personality);
	LOG_VAR_AS_STR("Luck", m_Luck);
	LOG_VAR_AS_STR("Health", m_Health);
	LOG_VAR_AS_STR("SpellPts", m_SpellPts);
	LOG_VAR_AS_STR("Fatigue", m_Fatigue);
	LOG_VAR_AS_STR("Soul", m_Soul);
	LOG_VAR_AS_STR("Combat", m_Combat);
	LOG_VAR_AS_STR("Magic", m_Magic);
	LOG_VAR_AS_STR("Stealth", m_Stealth);
	LOG_VAR_AS_STR("AttackMin1", m_AttackMin1);
	LOG_VAR_AS_STR("AttackMax1", m_AttackMax1);
	LOG_VAR_AS_STR("AttackMin2", m_AttackMin2);
	LOG_VAR_AS_STR("AttackMax2", m_AttackMax2);
	LOG_VAR_AS_STR("AttackMax2", m_AttackMax2);
	LOG_VAR_AS_STR("AttackMax3", m_AttackMax3);
	LOG_VAR_AS_STR("Gold", m_Gold);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordCreatureData::GetDataSize(void) const
{
	return TotalSum(
		m_Type, 
		m_Level, 
		m_Strength,
		m_Intelligence,
		m_Willpower,
		m_Agility,
		m_Speed,
		m_Endurance,
		m_Personality,
		m_Luck,
		m_Health,
		m_SpellPts,
		m_Fatigue,
		m_Soul,
		m_Combat,
		m_Magic,
		m_Stealth,
		m_AttackMin1,
		m_AttackMax1,
		m_AttackMin2,
		m_AttackMax2,
		m_AttackMin3,
		m_AttackMax3,
		m_Gold
	);
}

ESMSubrecordItemRecord::ESMSubrecordItemRecord(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_count(0)
{}

void ESMSubrecordItemRecord::Write(std::ostream & output)
{
	// NIY
}

size_t ESMSubrecordItemRecord::GetDataSize(void) const
{
	return TotalSum(m_count) + m_itemID.size();
}

bool ESMSubrecordItemRecord::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_count);

	size_t stringLength = 32; // always 32
	m_itemID.resize(stringLength);
	input.read(m_itemID.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("count", m_count);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "File Description", BAD_CAST m_itemID.c_str()); assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

ESMSubrecordCreatureAIData::ESMSubrecordCreatureAIData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_greetingDistance(0)
	, m_Fight(0)
	, m_Flee(0)
	, m_Alarm(0)
	, m_Unknown1(0)
	, m_Unknown2(0)
	, m_Unknown3(0)
	, m_services(0)
{}

void ESMSubrecordCreatureAIData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordCreatureAIData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_greetingDistance), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//READ_VAR(m_greetingDistance);
	//READ_VAR(m_Fight);
	//READ_VAR(m_Flee);
	//READ_VAR(m_Alarm);
	//READ_VAR(m_Unknown1);
	//READ_VAR(m_Unknown2);
	//READ_VAR(m_Unknown3);
	//READ_VAR(m_services);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("greeting distance", m_greetingDistance);
	LOG_CHAR_AS_INT("Fight", m_Fight);
	LOG_CHAR_AS_INT("Flee", m_Flee);
	LOG_CHAR_AS_INT("Alarm", m_Alarm);
	LOG_CHAR_AS_INT("Unknown1", m_Unknown1);
	LOG_CHAR_AS_INT("Unknown2", m_Unknown2);
	LOG_CHAR_AS_INT("Unknown3", m_Unknown3);
	LOG_VAR_AS_HEX("services", m_services);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordCreatureAIData::GetDataSize(void) const
{
	return TotalSum(m_greetingDistance, m_Fight, m_Flee, m_Alarm, m_Unknown1, m_Unknown2, m_Unknown3, m_services);
}

ESMSubrecordAIWander::ESMSubrecordAIWander(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Distance(0)
	, m_Duration(0)
	, m_TimeOfDay(0)
	, m_shouldRepeat(0)
{}

void ESMSubrecordAIWander::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordAIWander::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_Distance);
	READ_VAR(m_Duration);
	READ_VAR(m_TimeOfDay);

	size_t stringLength = 8; // always 8
	m_idle.resize(stringLength);
	input.read(m_idle.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	READ_VAR(m_shouldRepeat);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");											assert(res != -1);

	LOG_VAR_AS_STR("Distance", m_Distance);
	LOG_VAR_AS_STR("Duration", m_Duration);
	LOG_CHAR_AS_INT("TimeOfDay", m_TimeOfDay);
	LOG_CHAR_AS_INT("shouldRepeat", m_shouldRepeat);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Idle"); assert(res != -1);
	for (size_t idx = 0; idx < m_idle.size(); ++idx)
	{
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST std::to_string(idx).c_str(), BAD_CAST std::to_string((int)m_idle[idx]).c_str());	assert(res != -1);
	}
	res = xmlTextWriterEndElement(writer); assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordAIWander::GetDataSize(void) const
{
	return TotalSum(m_Distance, m_Duration, m_TimeOfDay, m_shouldRepeat) + m_idle.size();
}


ESMSubrecordAITravel::ESMSubrecordAITravel(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_X(0.0f)
	, m_Y(0.0f)
	, m_Z(0.0f)
	, m_shouldRepeat(0)
{}

void ESMSubrecordAITravel::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordAITravel::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_X), TotalSum(m_X, m_Y, m_Z, m_shouldRepeat));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//READ_VAR(m_X);
	//READ_VAR(m_Y);
	//READ_VAR(m_Z);
	//READ_VAR(m_shouldRepeat);

	size_t stringLength = 3; // always 3
	m_padding.resize(stringLength);
	input.read(m_padding.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("X", m_X);
	LOG_VAR_AS_STR("Y", m_Y);
	LOG_VAR_AS_STR("Z", m_Z);
	LOG_CHAR_AS_INT("shouldRepeat", m_shouldRepeat);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "padding", BAD_CAST m_padding.c_str());	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordAITravel::GetDataSize(void) const
{
	return TotalSum(m_X, m_Y, m_Z, m_shouldRepeat) + m_padding.size();
}

