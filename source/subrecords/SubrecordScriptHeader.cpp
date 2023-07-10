#include "pch.h"

#include "SubrecordScriptHeader.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>
#include <algorithm>

ESMSubrecordScriptHeader::ESMSubrecordScriptHeader(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_NumShorts(0)
	, m_NumLongs(0)
	, m_NumFloats(0)
	, m_ScriptDataSize(0)
	, m_LocalVarSize(0)
{}

bool ESMSubrecordScriptHeader::Read(std::ifstream& input)
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
	m_Name.resize(stringLength);
	input.read(m_Name.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	input.read(reinterpret_cast<char*>(&m_NumShorts), (sizeof(int) * 5));
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	//input.read(reinterpret_cast<char*>(&m_NumShorts), sizeof(m_NumShorts));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_NumLongs), sizeof(m_NumLongs));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_NumFloats), sizeof(m_NumFloats));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_ScriptDataSize), sizeof(m_ScriptDataSize));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;
	//
	//input.read(reinterpret_cast<char*>(&m_LocalVarSize), sizeof(m_LocalVarSize));
	//if ((input.rdstate() & std::ifstream::failbit) != 0)
	//	return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Name", BAD_CAST m_Name.c_str());	assert(res != -1);
	LOG_VAR_AS_STR("NumShorts", m_NumShorts);
	LOG_VAR_AS_STR("NumLongs", m_NumLongs);
	LOG_VAR_AS_STR("NumFloats", m_NumFloats);
	LOG_VAR_AS_STR("ScriptDataSize", m_ScriptDataSize);
	LOG_VAR_AS_STR("LocalVarSize", m_LocalVarSize);
	//res = xmlTextWriterWriteAttribute(writer, BAD_CAST "NumShorts", BAD_CAST std::to_string(m_NumShorts).c_str());				assert(res != -1);
	//res = xmlTextWriterWriteAttribute(writer, BAD_CAST "NumLongs", BAD_CAST int_to_hex(m_NumLongs).c_str());					assert(res != -1);
	//res = xmlTextWriterWriteAttribute(writer, BAD_CAST "NumFloats", BAD_CAST std::to_string(m_NumFloats).c_str());				assert(res != -1);
	//res = xmlTextWriterWriteAttribute(writer, BAD_CAST "ScriptDataSize", BAD_CAST std::to_string(m_ScriptDataSize).c_str());	assert(res != -1);
	//res = xmlTextWriterWriteAttribute(writer, BAD_CAST "LocalVarSize", BAD_CAST std::to_string(m_LocalVarSize).c_str());		assert(res != -1);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordScriptHeader::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordScriptHeader::GetDataSize(void) const
{
	return m_Name.size() + sizeof(int) * 5;
}

bool ESMSubrecordScriptVariables::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	size_t stringLength = m_subrecordHeader->GetDataSize();
	m_stringValue.resize(stringLength);
	input.read(m_stringValue.data(), stringLength);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;

	std::replace(m_stringValue.begin(), m_stringValue.end(), '\0', ';');

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");
	assert(res != -1);

	res = xmlTextWriterWriteAttribute(writer, BAD_CAST "Value", BAD_CAST m_stringValue.c_str());
	assert(res != -1);

	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}


