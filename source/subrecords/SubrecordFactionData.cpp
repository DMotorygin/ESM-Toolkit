#include "pch.h"

#include "SubrecordFactionData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordFactionData::ESMSubrecordFactionData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordFactionData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_AttributeID1), sizeof(m_AttributeID1));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_AttributeID2), sizeof(m_AttributeID2));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	m_RankData.resize(10); // always 10
	for (size_t idx = 0; idx < m_RankData.size(); ++idx)
	{
		input.read(reinterpret_cast<char*>(&m_RankData[idx].m_Attribute1), sizeof(m_RankData[idx].m_Attribute1));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;

		input.read(reinterpret_cast<char*>(&m_RankData[idx].m_Attribute2), sizeof(m_RankData[idx].m_Attribute2));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;

		input.read(reinterpret_cast<char*>(&m_RankData[idx].m_FirstSkill), sizeof(m_RankData[idx].m_FirstSkill));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;

		input.read(reinterpret_cast<char*>(&m_RankData[idx].m_SecondSkill), sizeof(m_RankData[idx].m_SecondSkill));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;

		input.read(reinterpret_cast<char*>(&m_RankData[idx].m_Faction), sizeof(m_RankData[idx].m_Faction));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;
	}

	m_SkillID.resize(6); // always 6
	for (size_t idx = 0; idx < m_SkillID.size(); ++idx)
	{
		input.read(reinterpret_cast<char*>(&m_SkillID[idx]), sizeof(m_SkillID[idx]));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;
	}

	input.read(reinterpret_cast<char*>(&m_unknown), sizeof(m_unknown));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_flags), sizeof(m_flags));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");													assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "AttributeID1", BAD_CAST std::to_string(m_AttributeID1).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "AttributeID2", BAD_CAST std::to_string(m_AttributeID2).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Unknown", BAD_CAST std::to_string(m_unknown).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Flags", BAD_CAST std::to_string(m_flags).c_str());					assert(res != -1);

	for (size_t idx = 0; idx < m_RankData.size(); ++idx)
	{
		res = xmlTextWriterStartElement(writer, BAD_CAST "Rank_Data");																				assert(res != -1);
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Attribute1", BAD_CAST std::to_string(m_RankData[idx].m_Attribute1).c_str());		assert(res != -1);
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Attribute2", BAD_CAST std::to_string(m_RankData[idx].m_Attribute2).c_str());		assert(res != -1);
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "FirstSkill", BAD_CAST std::to_string(m_RankData[idx].m_FirstSkill).c_str());			assert(res != -1);
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SecondSkill", BAD_CAST std::to_string(m_RankData[idx].m_SecondSkill).c_str());			assert(res != -1);
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Faction", BAD_CAST std::to_string(m_RankData[idx].m_Faction).c_str());					assert(res != -1);
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
	}

	res = xmlTextWriterStartElement(writer, BAD_CAST "SkillsID"); assert(res != -1);
	assert(res != -1);
	for (size_t idx = 0; idx < m_SkillID.size(); ++idx)
	{
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SkillID", BAD_CAST std::to_string(m_SkillID[idx]).c_str());		assert(res != -1);
	}
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordFactionData::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordFactionData::GetDataSize(void) const
{
	return sizeof(int) * 4 + sizeof(RankData) * m_RankData.size() + sizeof(int) * m_SkillID.size();
}

const char* ESMSubrecordFactionData::GetClassName(void) const
{
	return "Faction_Data";
}
