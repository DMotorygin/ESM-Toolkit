#include "pch.h"

#include "SubrecordNPCData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

const int countSkills = 27;

ESMSubrecordNPCData::ESMSubrecordNPCData()
	: m_Level(0)
	, m_Strength(0)
	, m_Intelligence(0)
	, m_Willpower(0)
	, m_Agility(0)
	, m_Speed(0)
	, m_Endurance(0)
	, m_Personality(0)
	, m_Luck(0)
	, m_Reputation(0)
	, m_Health(0)
	, m_SpellPts(0)
	, m_Fatigue(0)
	, m_Disposition(0)
	, m_FactionID(0)
	, m_Rank(0)
	, m_Unknown(0)
{}

ESMSubrecordNPCData::ESMSubrecordNPCData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Level(0)
	, m_Strength(0)
	, m_Intelligence(0)
	, m_Willpower(0)
	, m_Agility(0)
	, m_Speed(0)
	, m_Endurance(0)
	, m_Personality(0)
	, m_Luck(0)
	, m_Reputation(0)
	, m_Health(0)
	, m_SpellPts(0)
	, m_Fatigue(0)
	, m_Disposition(0)
	, m_FactionID(0)
	, m_Rank(0)
	, m_Unknown(0)
{}

bool ESMSubrecordNPCData::Read(std::ifstream & input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	const size_t subrecordSize = m_subrecordHeader->GetDataSize();
	if (subrecordSize == 52)
	{
		input.read(reinterpret_cast<char*>(&m_Level), subrecordSize);
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;

		/*READ_VAR(m_Level);
		READ_VAR(m_Strength);
		READ_VAR(m_Intelligence);
		READ_VAR(m_Willpower);
		READ_VAR(m_Agility);
		READ_VAR(m_Speed);
		READ_VAR(m_Endurance);
		READ_VAR(m_Personality);
		READ_VAR(m_Luck);
		for (size_t idx = 0; idx < m_Skills.size(); ++idx)
		{
			READ_VAR(m_Skills[idx]);
		}
		READ_VAR(m_Reputation);
		READ_VAR(m_Health);
		READ_VAR(m_SpellPts);
		READ_VAR(m_Fatigue);
		READ_VAR(m_Disposition);
		READ_VAR(m_FactionID);
		READ_VAR(m_Rank);
		READ_VAR(m_Unknown);
		READ_VAR(m_gold);*/

#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);
		LOG_VAR_AS_STR("Level", m_Level);
		LOG_CHAR_AS_INT("Strength", m_Strength);
		LOG_CHAR_AS_INT("Intelligence", m_Intelligence);
		LOG_CHAR_AS_INT("Willpower", m_Willpower);
		LOG_CHAR_AS_INT("Agility", m_Agility);
		LOG_CHAR_AS_INT("Speed", m_Speed);
		LOG_CHAR_AS_INT("Endurance", m_Endurance);
		LOG_CHAR_AS_INT("Personality", m_Personality);
		LOG_CHAR_AS_INT("Luck", m_Luck);

		LOG_CHAR_AS_INT("Reputation", m_Reputation);
		LOG_VAR_AS_STR("Health", m_Health);
		LOG_VAR_AS_STR("SpellPts", m_SpellPts);
		LOG_VAR_AS_STR("Fatigue", m_Fatigue);
		LOG_CHAR_AS_INT("Disposition", m_Disposition);
		LOG_CHAR_AS_INT("FactionID", m_FactionID);
		LOG_CHAR_AS_INT("Rank", m_Rank);
		LOG_CHAR_AS_INT("Unknown", m_Unknown);
		LOG_VAR_AS_STR("gold", m_gold);

		res = xmlTextWriterStartElement(writer, BAD_CAST "Skills");
		for (size_t idx = 0; idx < countSkills; ++idx)
		{
			LOG_CHAR_AS_INT(std::to_string(idx).c_str(), m_Skills[idx]);
		}					
		res = xmlTextWriterEndElement(writer);	assert(res != -1);

		res = xmlTextWriterEndElement(writer);	assert(res != -1);
		res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
	}
	else if (subrecordSize == 12)
	{
		// this is NPC with autocalculated stats!
		READ_VAR(m_Level);
		READ_VAR(m_Disposition);
		READ_VAR(m_Reputation); // maybe faction ID???
		READ_VAR(m_Rank);
		READ_VAR(m_Unknown);
		READ_VAR(m_Unknown2);
		READ_VAR(m_Unknown3);
		READ_VAR(m_gold);

#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);
		LOG_VAR_AS_STR("Level", m_Level);
		LOG_CHAR_AS_INT("Disposition", m_Disposition);
		LOG_CHAR_AS_INT("Reputation", m_Reputation);
		LOG_CHAR_AS_INT("Rank", m_Rank);
		LOG_CHAR_AS_INT("Unknown", m_Unknown);
		LOG_CHAR_AS_INT("Unknown2", m_Unknown2);
		LOG_CHAR_AS_INT("Unknown3", m_Unknown3);
		LOG_VAR_AS_STR("gold", m_gold);

		res = xmlTextWriterEndElement(writer);	assert(res != -1);
		res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
	}
	else
	{
		assert(false); // should not be here!
		return false;
	}

	return true;
}

size_t ESMSubrecordNPCData::GetDataSize(void) const
{
	// can't implement this method the way it is done in other classes because this subrecord can have 2 sizes 
	// and they have no indications which one should be used inside the subrecord :(
	return m_subrecordHeader->GetDataSize();
}

void ESMSubrecordNPCData::Write(std::ostream & output)
{
	// NIY
}


ESMSubrecordNPCAIData::ESMSubrecordNPCAIData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_greetingDistance(0)
	, m_Unknown(0)
	, m_Fight(0)
	, m_Flee(0)
	, m_Alarm(0)
	, m_Unknown1(0)
	, m_Unknown2(0)
	, m_Unknown3(0)
	, m_services(0)
{}

void ESMSubrecordNPCAIData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordNPCAIData::Read(std::ifstream& input)
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
	//READ_VAR(m_Unknown);
	//READ_VAR(m_Fight);
	//READ_VAR(m_Flee);
	//READ_VAR(m_Alarm);
	//READ_VAR(m_Unknown1);
	//READ_VAR(m_Unknown2);
	//READ_VAR(m_Unknown3);
	//READ_VAR(m_services);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_CHAR_AS_INT("greeting distance", m_greetingDistance);
	LOG_CHAR_AS_INT("Unknown", m_Unknown);
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

size_t ESMSubrecordNPCAIData::GetDataSize(void) const
{
	return TotalSum(m_greetingDistance, m_Unknown, m_Fight, m_Flee, m_Alarm, m_Unknown1, m_Unknown2, m_Unknown3, m_services);
}

ESMSubrecordAIFollow::ESMSubrecordAIFollow(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_X(0.0f)
	, m_Y(0.0f)
	, m_Z(0.0f)
	, m_Duration(0)
	, m_shouldRepeat(0)
	, m_padding(0)
{}

void ESMSubrecordAIFollow::Write(std::ostream & output)
{
	// NIY
}

bool ESMSubrecordAIFollow::Read(std::ifstream & input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_X);
	READ_VAR(m_Y);
	READ_VAR(m_Z);
	READ_VAR(m_Duration);

	size_t stringLength = 32; // always 32
	m_ID.resize(stringLength);
	input.read(m_ID.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	READ_VAR(m_shouldRepeat);
	READ_VAR(m_padding);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("X", m_X);
	LOG_VAR_AS_STR("Y", m_Y);
	LOG_VAR_AS_STR("Z", m_Z);
	LOG_VAR_AS_STR("Duration", m_Duration);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Idle", BAD_CAST m_ID.c_str());	assert(res != -1);
	LOG_CHAR_AS_INT("shouldRepeat", m_shouldRepeat);
	LOG_CHAR_AS_INT("padding", m_padding);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordAIFollow::GetDataSize(void) const
{
	return TotalSum(m_X, m_Y, m_Z, m_Duration, m_shouldRepeat, m_padding) + m_ID.size();
}


ESMSubrecordAIActivate::ESMSubrecordAIActivate(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_shouldRepeat(0)
{}

void ESMSubrecordAIActivate::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordAIActivate::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	size_t stringLength = 32; // always 32
	m_ID.resize(stringLength);
	input.read(m_ID.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	READ_VAR(m_shouldRepeat);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Idle", BAD_CAST m_ID.c_str());	assert(res != -1);
	LOG_CHAR_AS_INT("shouldRepeat", m_shouldRepeat);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordAIActivate::GetDataSize(void) const
{
	return TotalSum(m_shouldRepeat) + m_ID.size();
}

ESMSubrecordCellTravelDestination::ESMSubrecordCellTravelDestination(void)
	: m_XPos(0.0f)
	, m_YPos(0.0f)
	, m_ZPos(0.0f)
	, m_XRot(0.0f)
	, m_YRot(0.0f)
	, m_ZRot(0.0f)
{}

ESMSubrecordCellTravelDestination::ESMSubrecordCellTravelDestination(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_XPos(0.0f)
	, m_YPos(0.0f)
	, m_ZPos(0.0f)
	, m_XRot(0.0f)
	, m_YRot(0.0f)
	, m_ZRot(0.0f)
{}

void ESMSubrecordCellTravelDestination::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordCellTravelDestination::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_XPos), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//READ_VAR(m_XPos);
	//READ_VAR(m_YPos);
	//READ_VAR(m_ZPos);
	//READ_VAR(m_XRot);
	//READ_VAR(m_YRot);
	//READ_VAR(m_ZRot);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("XPos", m_XPos);
	LOG_VAR_AS_STR("YPos", m_YPos);
	LOG_VAR_AS_STR("ZPos", m_ZPos);
	LOG_VAR_AS_STR("XRot", m_XRot);
	LOG_VAR_AS_STR("YRot", m_YRot);
	LOG_VAR_AS_STR("ZRot", m_ZRot);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordCellTravelDestination::GetDataSize(void) const
{
	return TotalSum(m_XPos, m_YPos, m_ZPos, m_XRot, m_YRot, m_ZRot);
}

