#include "pch.h"

#include "SubrecordBodyPartData.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordBodyPartData::ESMSubrecordBodyPartData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
	, m_BodyPart(0)
	, m_IsVampire(0)
	, m_Flags(0)
	, m_PartType(0)
{}

void ESMSubrecordBodyPartData::Write(std::ostream& output)
{
	// NIY
}

bool ESMSubrecordBodyPartData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

	// read subrecord data
	input.read(reinterpret_cast<char*>(&m_BodyPart), GetDataSize());
	if ((input.rdstate() & std::ifstream::failbit) != 0)
		return false;
	//READ_VAR(m_BodyPart);
	//READ_VAR(m_IsVampire);
	//READ_VAR(m_Flags);
	//READ_VAR(m_PartType);

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

	LOG_CHAR_AS_INT("BodyPart", m_BodyPart);
	LOG_CHAR_AS_INT("IsVampire", m_IsVampire);
	LOG_CHAR_AS_INT("Flags", m_Flags);
	LOG_CHAR_AS_INT("PartType", m_PartType);

	res = xmlTextWriterEndElement(writer);	assert(res != -1);
	res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

size_t ESMSubrecordBodyPartData::GetDataSize(void) const
{
	return TotalSum(m_BodyPart, m_IsVampire, m_Flags, m_PartType);
}
