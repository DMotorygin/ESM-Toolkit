#include "pch.h"

#include "SubrecordIngridientData.h"

#include "xmlUtils.h"
#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordIngrediantData::ESMSubrecordIngrediantData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_Weight(0.0f)
	, m_Value(0)
{}

void ESMSubrecordIngrediantData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordIngrediantData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_Weight);
	READ_VAR(m_Value);

	m_effectID.resize(4); // always 4
	for (size_t idx = 0; idx < m_effectID.size(); ++idx)
	{
		input.read(reinterpret_cast<char*>(&m_effectID[idx]), sizeof(m_effectID[idx]));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;
	}

	m_skillID.resize(4); // always 4
	for (size_t idx = 0; idx < m_skillID.size(); ++idx)
	{
		input.read(reinterpret_cast<char*>(&m_skillID[idx]), sizeof(m_skillID[idx]));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;
	}

	m_attributeID.resize(4); // always 4
	for (size_t idx = 0; idx < m_attributeID.size(); ++idx)
	{
		input.read(reinterpret_cast<char*>(&m_attributeID[idx]), sizeof(m_attributeID[idx]));
		if ((input.rdstate() & std::ifstream::failbit) != 0)
			return false;
	}

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Weight", m_Weight);
	LOG_VAR_AS_STR("Value", m_Value);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Effects"); assert(res != -1);
	assert(res != -1);
	for (size_t idx = 0; idx < m_effectID.size(); ++idx)
	{
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "EffectID", BAD_CAST std::to_string(m_effectID[idx]).c_str());		assert(res != -1);
	}
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Skill IDs"); assert(res != -1);
	assert(res != -1);
	for (size_t idx = 0; idx < m_skillID.size(); ++idx)
	{
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "skill ID", BAD_CAST std::to_string(m_skillID[idx]).c_str());		assert(res != -1);
	}
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterStartElement(writer, BAD_CAST "Attributes ID"); assert(res != -1);
	assert(res != -1);
	for (size_t idx = 0; idx < m_attributeID.size(); ++idx)
	{
		res = xmlTextWriterWriteAttribute(writer, BAD_CAST "attribute ID", BAD_CAST std::to_string(m_attributeID[idx]).c_str());		assert(res != -1);
	}
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordIngrediantData::GetDataSize(void) const
{
	return TotalSum(m_Weight, m_Value) + m_effectID.size() * sizeof(int) + m_skillID.size() * sizeof(int) + m_attributeID.size() * sizeof(int);
}
