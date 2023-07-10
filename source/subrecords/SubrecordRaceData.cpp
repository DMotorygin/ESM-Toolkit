#include "pch.h"

#include "SubrecordRaceData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordRaceData::ESMSubrecordRaceData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordRaceData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	assert(strncmp(m_subrecordHeader->GetSubrecordType().data(), GetShortName(), 4) == 0);

	m_SkillBonuses.resize(7); // always 7
	for (size_t idx = 0; idx < m_SkillBonuses.size(); ++idx)
	{
		input.read(reinterpret_cast<char*>(&m_SkillBonuses[idx].m_SkillID), sizeof(m_SkillBonuses[idx].m_SkillID));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;

		input.read(reinterpret_cast<char*>(&m_SkillBonuses[idx].m_Bonus), sizeof(m_SkillBonuses[idx].m_Bonus));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;
	}

	input.read(reinterpret_cast<char*>(&m_Strength[0]), sizeof(m_Strength[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Strength[1]), sizeof(m_Strength[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Intelligence[0]), sizeof(m_Intelligence[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Intelligence[1]), sizeof(m_Intelligence[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Willpower[0]), sizeof(m_Willpower[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Willpower[1]), sizeof(m_Willpower[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Agility[0]), sizeof(m_Agility[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Agility[1]), sizeof(m_Agility[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Speed[0]), sizeof(m_Speed[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Speed[1]), sizeof(m_Speed[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Endurance[0]), sizeof(m_Endurance[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Endurance[1]), sizeof(m_Endurance[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Personality[0]), sizeof(m_Personality[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Personality[1]), sizeof(m_Personality[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Luck[0]), sizeof(m_Luck[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Luck[1]), sizeof(m_Luck[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Height[0]), sizeof(m_Height[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Height[1]), sizeof(m_Height[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Weight[0]), sizeof(m_Weight[0]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	input.read(reinterpret_cast<char*>(&m_Weight[1]), sizeof(m_Weight[1]));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_flags), sizeof(m_flags));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Flags", BAD_CAST int_to_hex(m_flags).c_str());	assert(res != -1);

	for (size_t idx = 0; idx < m_SkillBonuses.size(); ++idx)
	{
		res = xmlTextWriterStartElement(writer, BAD_CAST "Skill_Bonuses");																assert(res != -1);
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SkillID", BAD_CAST std::to_string(m_SkillBonuses[idx].m_SkillID).c_str());	assert(res != -1);
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Bonus", BAD_CAST std::to_string(m_SkillBonuses[idx].m_Bonus).c_str());		assert(res != -1);
		res = xmlTextWriterEndElement(writer);																							assert(res != -1);
	}

	res = xmlTextWriterStartElement(writer, BAD_CAST "Strength"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Strength[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Strength[1]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Intelligence"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Intelligence[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Intelligence[1]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Willpower"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Willpower[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Willpower[1]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Agility"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Agility[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Agility[1]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Speed"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Speed[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Speed[1]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Endurance"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Endurance[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Endurance[1]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Personality"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Personality[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Personality[1]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Luck"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Luck[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Luck[1]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Height"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Height[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Height[1]).c_str());		assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Weight"); assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Male", BAD_CAST std::to_string(m_Weight[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Female", BAD_CAST std::to_string(m_Weight[1]).c_str());		assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordRaceData::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordRaceData::GetDataSize(void) const
{
	return sizeof(int) * 16 + sizeof(SkillBonuses) * m_SkillBonuses.size() + sizeof(float) * 4 + sizeof(m_flags);
}

const char* ESMSubrecordRaceData::GetClassName(void) const
{
	return "Race_Description";
}

