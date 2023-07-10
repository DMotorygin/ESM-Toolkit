#include "pch.h"

#include "SubrecordClassData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordClassData::ESMSubrecordClassData()
	: m_primaryAttribute1ID(0)
	, m_primaryAttribute2ID(0)
	, m_specialization(0)
	, m_minorSkill1ID(0)
	, m_majorSkill1ID(0)
	, m_minorSkill2ID(0)
	, m_majorSkill2ID(0)
	, m_minorSkill3ID(0)
	, m_majorSkill3ID(0)
	, m_minorSkill4ID(0)
	, m_majorSkill4ID(0)
	, m_minorSkill5ID(0)
	, m_majorSkill5ID(0)
	, m_isPlayable(0)
	, m_flags(0)
{}

ESMSubrecordClassData::ESMSubrecordClassData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_primaryAttribute1ID(0)
	, m_primaryAttribute2ID(0)
	, m_specialization(0)
	, m_minorSkill1ID(0)
	, m_majorSkill1ID(0)
	, m_minorSkill2ID(0)
	, m_majorSkill2ID(0)
	, m_minorSkill3ID(0)
	, m_majorSkill3ID(0)
	, m_minorSkill4ID(0)
	, m_majorSkill4ID(0)
	, m_minorSkill5ID(0)
	, m_majorSkill5ID(0)
	, m_isPlayable(0)
	, m_flags(0)
{}

bool ESMSubrecordClassData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_primaryAttribute1ID), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	//input.read(reinterpret_cast<char*>(&m_primaryAttribute1ID), sizeof(m_primaryAttribute1ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_primaryAttribute2ID), sizeof(m_primaryAttribute2ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_specialization), sizeof(m_specialization));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_minorSkill1ID), sizeof(m_minorSkill1ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_majorSkill1ID), sizeof(m_majorSkill1ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_minorSkill2ID), sizeof(m_minorSkill2ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_majorSkill2ID), sizeof(m_majorSkill2ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_minorSkill3ID), sizeof(m_minorSkill3ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_majorSkill3ID), sizeof(m_majorSkill3ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_minorSkill4ID), sizeof(m_minorSkill4ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_majorSkill4ID), sizeof(m_majorSkill4ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_minorSkill5ID), sizeof(m_minorSkill5ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_majorSkill5ID), sizeof(m_majorSkill5ID));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_isPlayable), sizeof(m_isPlayable));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_flags), sizeof(m_flags));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "primary attr 1", BAD_CAST std::to_string(m_primaryAttribute1ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "primary attr 2", BAD_CAST std::to_string(m_primaryAttribute2ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "specialization", BAD_CAST std::to_string(m_specialization).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "minor skill 1", BAD_CAST std::to_string(m_minorSkill1ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Major skill 1", BAD_CAST std::to_string(m_majorSkill1ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "minor skill 2", BAD_CAST std::to_string(m_minorSkill2ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Major skill 2", BAD_CAST std::to_string(m_majorSkill2ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "minor skill 3", BAD_CAST std::to_string(m_minorSkill3ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Major skill 3", BAD_CAST std::to_string(m_majorSkill3ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "minor skill 4", BAD_CAST std::to_string(m_minorSkill4ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Major skill 4", BAD_CAST std::to_string(m_majorSkill4ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "minor skill 5", BAD_CAST std::to_string(m_minorSkill5ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Major skill 5", BAD_CAST std::to_string(m_majorSkill5ID).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "is playable", BAD_CAST std::to_string(m_isPlayable).c_str());
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "flags", BAD_CAST int_to_hex(m_flags).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordClassData::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordClassData::GetDataSize(void) const
{
	return TotalSum(m_primaryAttribute1ID
		, m_primaryAttribute2ID
		, m_specialization
		, m_minorSkill1ID
		, m_majorSkill1ID
		, m_minorSkill2ID
		, m_majorSkill2ID
		, m_minorSkill3ID
		, m_majorSkill3ID
		, m_minorSkill4ID
		, m_majorSkill4ID
		, m_minorSkill5ID
		, m_majorSkill5ID
		, m_isPlayable
		, m_flags);
}

const char* ESMSubrecordClassData::GetClassName(void) const
{
	return "Class_Data";
}
