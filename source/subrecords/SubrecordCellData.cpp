#include "pch.h"

#include "SubrecordCellData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordCellData::ESMSubrecordCellData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_flags(0)
	, m_gridX(0)
	, m_gridY(0)
{}

void ESMSubrecordCellData::Write(std::ostream & output)
{
	// NIY
}

bool ESMSubrecordCellData::Read(std::ifstream & input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_flags), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
#ifdef DUMP_CELL_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_HEX("Flags", m_flags);
	LOG_VAR_AS_STR("GridX", m_gridX);
	LOG_VAR_AS_STR("GridY", m_gridY);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordCellData::GetDataSize(void) const
{
	return TotalSum(m_flags, m_gridX, m_gridY);
}

SubrecordCellMapColor::SubrecordCellMapColor(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_colorValue(0)
{}

bool SubrecordCellMapColor::Read(std::ifstream& input)
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

	input.read(reinterpret_cast<char*>(&m_colorValue), sizeof(m_colorValue));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
#ifdef DUMP_CELL_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Red", BAD_CAST std::to_string((unsigned)m_colorValue.m_byte[0]).c_str());
	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Green", BAD_CAST std::to_string((unsigned)m_colorValue.m_byte[1]).c_str());
	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Blue", BAD_CAST std::to_string((unsigned)m_colorValue.m_byte[2]).c_str());
	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Null", BAD_CAST std::to_string((unsigned)m_colorValue.m_byte[3]).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t SubrecordCellMapColor::GetDataSize(void) const
{
	return sizeof(m_colorValue);
}

ESMSubrecordCellAmbientLight::ESMSubrecordCellAmbientLight(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_ambientColor(0)
	, m_sunlightColor(0)
	, m_fogColor(0)
	, m_fogDensity(0.0f)
{}

void ESMSubrecordCellAmbientLight::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordCellAmbientLight::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_ambientColor), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
#ifdef DUMP_CELL_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	unsigned char* pByte = (unsigned char*)&m_ambientColor;
	res = xmlTextWriterStartElement(writer, BAD_CAST "Ambient Color");	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Red", BAD_CAST std::to_string((unsigned)pByte[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Green", BAD_CAST std::to_string((unsigned)pByte[1]).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Blue", BAD_CAST std::to_string((unsigned)pByte[2]).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Null", BAD_CAST std::to_string((unsigned)pByte[3]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	pByte = (unsigned char*)&m_sunlightColor;
	res = xmlTextWriterStartElement(writer, BAD_CAST "Sunlight Color");	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Red", BAD_CAST std::to_string((unsigned)pByte[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Green", BAD_CAST std::to_string((unsigned)pByte[1]).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Blue", BAD_CAST std::to_string((unsigned)pByte[2]).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Null", BAD_CAST std::to_string((unsigned)pByte[3]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	pByte = (unsigned char*)&m_fogColor;
	res = xmlTextWriterStartElement(writer, BAD_CAST "Fog Color");	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Red", BAD_CAST std::to_string((unsigned)pByte[0]).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Green", BAD_CAST std::to_string((unsigned)pByte[1]).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Blue", BAD_CAST std::to_string((unsigned)pByte[2]).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Null", BAD_CAST std::to_string((unsigned)pByte[3]).c_str());	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordCellAmbientLight::GetDataSize(void) const
{
	return TotalSum(m_ambientColor, m_sunlightColor, m_fogColor, m_fogDensity);
}


ESMSubrecordCellDoorObject::ESMSubrecordCellDoorObject(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_XPos(0.0f)
	, m_YPos(0.0f)
	, m_ZPos(0.0f)
	, m_XRot(0.0f)
	, m_YRot(0.0f)
	, m_ZRot(0.0f)
{}

void ESMSubrecordCellDoorObject::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordCellDoorObject::Read(std::ifstream& input)
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

#ifdef DUMP_ESM_TO_XML
#ifdef DUMP_CELL_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("XPos", m_XPos);
	LOG_VAR_AS_STR("YPos", m_YPos);
	LOG_VAR_AS_STR("ZPos", m_ZPos);
	LOG_VAR_AS_STR("XRot", m_XRot);
	LOG_VAR_AS_STR("YRot", m_YRot);
	LOG_VAR_AS_STR("ZRot", m_ZRot);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordCellDoorObject::GetDataSize(void) const
{
	return TotalSum(m_XPos, m_YPos, m_ZPos, m_XRot, m_YRot, m_ZRot);
}

ESMSubrecordCellUnknownFlag::ESMSubrecordCellUnknownFlag(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_value('\0')
{}

void ESMSubrecordCellUnknownFlag::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordCellUnknownFlag::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_value), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
#ifdef DUMP_CELL_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_CHAR_AS_INT("Value", m_value);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

ESMSubrecordCellReferencedObjectData::ESMSubrecordCellReferencedObjectData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_XPos(0.0f)
	, m_YPos(0.0f)
	, m_ZPos(0.0f)
	, m_XRot(0.0f)
	, m_YRot(0.0f)
	, m_ZRot(0.0f)
{}

void ESMSubrecordCellReferencedObjectData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordCellReferencedObjectData::Read(std::ifstream& input)
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

#ifdef DUMP_ESM_TO_XML
#ifdef DUMP_CELL_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("XPos", m_XPos);
	LOG_VAR_AS_STR("YPos", m_YPos);
	LOG_VAR_AS_STR("ZPos", m_ZPos);
	LOG_VAR_AS_STR("XRot", m_XRot);
	LOG_VAR_AS_STR("YRot", m_YRot);
	LOG_VAR_AS_STR("ZRot", m_ZRot);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordCellReferencedObjectData::GetDataSize(void) const
{
	return TotalSum(m_XPos, m_YPos, m_ZPos, m_XRot, m_YRot, m_ZRot);
}

