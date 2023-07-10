#include "pch.h"

#include "SubrecordWeatherData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>
#include <algorithm>


ESMSubrecordWeatherData::ESMSubrecordWeatherData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_clear(0)
	, m_cloudy(0)
	, m_foggy(0)
	, m_overcast(0)
	, m_rain(0)
	, m_thunder(0)
	, m_ash(0)
	, m_blight(0)
{}

void ESMSubrecordWeatherData::Write(std::ostream & output)
{
	// NIY
}

bool ESMSubrecordWeatherData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_clear), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//input.read(reinterpret_cast<char*>(&m_clear), sizeof(m_clear));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_cloudy), sizeof(m_cloudy));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_foggy), sizeof(m_foggy));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_overcast), sizeof(m_overcast));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_rain), sizeof(m_rain));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_thunder), sizeof(m_thunder));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_ash), sizeof(m_ash));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_blight), sizeof(m_blight));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");											assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "clear", BAD_CAST std::to_string(m_clear).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "cloudy", BAD_CAST std::to_string(m_cloudy).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "foggy", BAD_CAST std::to_string(m_foggy).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "overcast", BAD_CAST std::to_string(m_overcast).c_str());	assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "rain", BAD_CAST std::to_string(m_rain).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "thunder", BAD_CAST std::to_string(m_thunder).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "ash", BAD_CAST std::to_string(m_ash).c_str());				assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "blight", BAD_CAST std::to_string(m_blight).c_str());		assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordWeatherData::GetDataSize(void) const
{
	return 8;
}

ESMSubrecordRegionColorData::ESMSubrecordRegionColorData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_red(0)
	, m_green(0)
	, m_blue(0)
	, m_unknown(0)
{}

void ESMSubrecordRegionColorData::Write(std::ostream & output)
{
	// NIY
}

bool ESMSubrecordRegionColorData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_red), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//input.read(reinterpret_cast<char*>(&m_red), sizeof(m_red));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_green), sizeof(m_green));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_blue), sizeof(m_blue));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_unknown), sizeof(m_unknown));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");												assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "red", BAD_CAST std::to_string((int) m_red).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "green", BAD_CAST std::to_string((int) m_green).c_str());		assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "blue", BAD_CAST std::to_string((int) m_blue).c_str());			assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "unknown", BAD_CAST std::to_string((int) m_unknown).c_str());	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordRegionColorData::GetDataSize(void) const
{
	return 4;
}

ESMSubrecordRegionSoundData::ESMSubrecordRegionSoundData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_chance(0)
{}

size_t ESMSubrecordRegionSoundData::GetDataSize(void) const
{
	return 1 + m_soundName.size();
}

void ESMSubrecordRegionSoundData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordRegionSoundData::Read(std::ifstream& input)
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
	char* buffer = new char[stringLength];
	input.read(buffer, stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	m_soundName.resize(stringLength);
	m_soundName.assign(buffer, stringLength);
	delete[] buffer;

	// looks like data after '\0' in this string is garbage, unlike some other similar strings
	//std::replace(m_soundName.begin(), m_soundName.end(), '\0', ';');

	input.read(reinterpret_cast<char*>(&m_chance), sizeof(m_chance));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");												assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "soundName", BAD_CAST m_soundName.c_str());						assert(res != -1);
	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "chance", BAD_CAST std::to_string((int)m_chance).c_str());		assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}


