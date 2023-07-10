#include "pch.h"

#include "SubrecordWeaponData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordWeaponData::ESMSubrecordWeaponData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_weight(0.0f)
	, m_Value(0)
	, m_Type(0)
	, m_Health(0)
	, m_Speed(0.0f)
	, m_Reach(0.0f)
	, m_EnchantPts(0)
	, m_ChopMin(0)
	, m_ChopMax(0)
	, m_SlashMin(0)
	, m_SlashMax(0)
	, m_ThrustMin(0)
	, m_ThrustMax(0)
	, m_flags(0)
{}

void ESMSubrecordWeaponData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordWeaponData::Read(std::ifstream& input)
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

	//input.read(reinterpret_cast<char*>(&m_weight), sizeof(m_weight));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_Value), sizeof(m_Value));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_Type), sizeof(m_Type));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_Health), sizeof(m_Health));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_Speed), sizeof(m_Speed));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_Reach), sizeof(m_Reach));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_EnchantPts), sizeof(m_EnchantPts));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_ChopMin), sizeof(m_ChopMin));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_ChopMax), sizeof(m_ChopMax));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_SlashMin), sizeof(m_SlashMin));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_SlashMax), sizeof(m_SlashMax));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_ThrustMin), sizeof(m_ThrustMin));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_ThrustMax), sizeof(m_ThrustMax));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_flags), sizeof(m_flags));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");												assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "weight", BAD_CAST std::to_string(m_weight).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Value", BAD_CAST std::to_string(m_Value).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Type", BAD_CAST std::to_string(m_Type).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Health", BAD_CAST std::to_string(m_Health).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Speed", BAD_CAST std::to_string(m_Speed).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Reach", BAD_CAST std::to_string(m_Reach).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "EnchantPts", BAD_CAST std::to_string(m_EnchantPts).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "ChopMin", BAD_CAST std::to_string((int)m_ChopMin).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "ChopMax", BAD_CAST std::to_string((int)m_ChopMax).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SlashMin", BAD_CAST std::to_string((int)m_SlashMin).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "SlashMax", BAD_CAST std::to_string((int)m_SlashMax).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "ThrustMin", BAD_CAST std::to_string((int)m_ThrustMin).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "ThrustMax", BAD_CAST std::to_string((int)m_ThrustMax).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "flags", BAD_CAST int_to_hex(m_flags).c_str());					assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordWeaponData::GetDataSize(void) const
{
	return TotalSum(m_weight, m_Value, m_Type, m_Health, m_Speed, m_Reach, m_EnchantPts, m_ChopMin, m_ChopMax, m_SlashMin, m_SlashMax, m_ThrustMin, m_ThrustMax, m_flags);
}

