#include "pch.h"

#include "SubrecordMiscWeaponData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordMiscWeaponData::ESMSubrecordMiscWeaponData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_weight(0.0f)
	, m_Value(0)
	, m_Unknown(0)
{}

void ESMSubrecordMiscWeaponData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordMiscWeaponData::Read(std::ifstream& input)
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
	//input.read(reinterpret_cast<char*>(&m_Unknown), sizeof(m_Unknown));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");										assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Weight", BAD_CAST std::to_string(m_weight).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Value", BAD_CAST std::to_string(m_Value).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Unknown", BAD_CAST std::to_string(m_Unknown).c_str());	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordMiscWeaponData::GetDataSize(void) const
{
	return TotalSum(m_weight, m_Value, m_Unknown);
}

