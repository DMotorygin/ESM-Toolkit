#include "pch.h"

#include "SubrecordLandscapeData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>


ESMSubrecordLandCellXY::ESMSubrecordLandCellXY(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_X(0)
	, m_Y(0)
{}

void ESMSubrecordLandCellXY::Write(std::ostream & output)
{
	// NIY
}

bool ESMSubrecordLandCellXY::Read(std::ifstream & input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_X), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Cell X", m_X);
	LOG_VAR_AS_STR("Cell Y", m_Y);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordLandCellXY::GetDataSize(void) const
{
	return TotalSum(m_X, m_Y);
}


ESMSubrecordLandVertexNormals::ESMSubrecordLandVertexNormals(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

void ESMSubrecordLandVertexNormals::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordLandVertexNormals::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_Normals[0]), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Data Field of Size", BAD_CAST std::to_string(GetDataSize()).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordLandVertexNormals::GetDataSize(void) const
{
	return sizeof(ESM_byteVec3) * LAND_NUM_VERTS;
}


ESMSubrecordLandHeightmap::ESMSubrecordLandHeightmap(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_heightOffset(0.0f)
	, m_flags(0)
	, m_flags2(0)
{}

void ESMSubrecordLandHeightmap::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordLandHeightmap::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_heightOffset), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Height Offset", m_heightOffset);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Data Field of Size", BAD_CAST std::to_string(LAND_NUM_VERTS).c_str());
	assert(res != -1);

	LOG_VAR_AS_STR("unknown flags 1", m_flags);
	LOG_VAR_AS_STR("unknown flags 2", m_flags2);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordLandHeightmap::GetDataSize(void) const
{
	return  TotalSum(m_heightOffset, m_flags, m_flags2) + LAND_NUM_VERTS;
}


ESMSubrecordLandWNAM::ESMSubrecordLandWNAM(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

void ESMSubrecordLandWNAM::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordLandWNAM::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_heights[0]), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Data Field of Size", BAD_CAST std::to_string(GetDataSize()).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordLandWNAM::GetDataSize(void) const
{
	return LAND_GLOBAL_MAP_LOD_SIZE;
}


ESMSubrecordLandVertexColor::ESMSubrecordLandVertexColor(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

void ESMSubrecordLandVertexColor::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordLandVertexColor::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_vertexColors[0]), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Data Field of Size", BAD_CAST std::to_string(GetDataSize()).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordLandVertexColor::GetDataSize(void) const
{
	return sizeof(ESM_byteVec3) * LAND_NUM_VERTS;
}


ESMSubrecordLandTexture::ESMSubrecordLandTexture(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

void ESMSubrecordLandTexture::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordLandTexture::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_textureIndices[0]), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Data Field of Size", BAD_CAST std::to_string(GetDataSize()).c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordLandTexture::GetDataSize(void) const
{
	return sizeof(unsigned short) * LAND_NUM_TEXTURES;
}
