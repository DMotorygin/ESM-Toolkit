#include "pch.h"

#include "SubrecordMagicEffectData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordMagicEffectData::ESMSubrecordMagicEffectData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_SpellSchool(0)
	, m_BaseCost(0.0f)
	, m_flags(0)
	, m_red(0)
	, m_blue(0)
	, m_green(0)
	, m_speedX(0.0f)
	, m_sizeX(0.0f)
	, m_sizeCap(0.0f)
{}

bool ESMSubrecordMagicEffectData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_SpellSchool), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//input.read(reinterpret_cast<char*>(&m_SpellSchool), sizeof(m_SpellSchool));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_BaseCost), sizeof(m_BaseCost));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_flags), sizeof(m_flags));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_red), sizeof(m_red));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_blue), sizeof(m_blue));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_green), sizeof(m_green));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_speedX), sizeof(m_speedX));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_sizeX), sizeof(m_sizeX));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_sizeCap), sizeof(m_sizeCap));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SpellSchool", BAD_CAST std::to_string(m_SpellSchool).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "BaseCost", BAD_CAST std::to_string(m_BaseCost).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Flags", BAD_CAST int_to_hex(m_flags).c_str());					assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Red", BAD_CAST std::to_string(m_red).c_str());					assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Blue", BAD_CAST std::to_string(m_blue).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Green", BAD_CAST std::to_string(m_green).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SpeedX", BAD_CAST std::to_string(m_speedX).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SizeX", BAD_CAST std::to_string(m_sizeX).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SizeCap", BAD_CAST std::to_string(m_sizeCap).c_str());			assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordMagicEffectData::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordMagicEffectData::GetDataSize(void) const
{
	return TotalSum(m_SpellSchool, m_BaseCost, m_flags, m_red, m_blue, m_green, m_speedX, m_sizeX, m_sizeCap);
}

