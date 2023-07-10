#include "pch.h"

#include "SubrecordLeveledList.h"

#include "xmlUtils.h"
#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordLeveledListChance::ESMSubrecordLeveledListChance(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_val(0)
{}

void ESMSubrecordLeveledListChance::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordLeveledListChance::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_val);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_CHAR_AS_INT("Value", m_val);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}


ESMSubrecordLeveledListPCLevel::ESMSubrecordLeveledListPCLevel(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_lvl(0)
{}

void ESMSubrecordLeveledListPCLevel::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordLeveledListPCLevel::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	READ_VAR(m_lvl);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_VAR_AS_STR("Level", m_lvl);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordLeveledListPCLevel::GetDataSize(void) const
{
	return TotalSum(m_lvl);
}

