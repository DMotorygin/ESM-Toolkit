#include "pch.h"

#include "SubrecordSkillData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordSkillData::ESMSubrecordSkillData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_AttributeID(0)
	, m_Specialization(0)
{}

bool ESMSubrecordSkillData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_AttributeID), sizeof(m_AttributeID));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_Specialization), sizeof(m_Specialization));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	m_UseValue.resize(4); // always 4
	for (size_t idx = 0; idx < m_UseValue.size(); ++idx)
	{
		input.read(reinterpret_cast<char*>(&m_UseValue[idx]), sizeof(m_UseValue[idx]));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;
	}

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "AttributeID", BAD_CAST std::to_string(m_AttributeID).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Specialization", BAD_CAST std::to_string(m_Specialization).c_str());	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Use_Value"); assert(res != -1);
	for (size_t idx = 0; idx < m_UseValue.size(); ++idx)
	{															
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST std::to_string(idx).c_str(), BAD_CAST std::to_string(m_UseValue[idx]).c_str());	assert(res != -1);
	}
	res = xmlTextWriterEndElement(writer); assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordSkillData::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordSkillData::GetDataSize(void) const
{
	return sizeof(int) * 2 + sizeof(float) * 4;
}

const char* ESMSubrecordSkillData::GetClassName(void) const
{
	return "Skill_Data";
}

