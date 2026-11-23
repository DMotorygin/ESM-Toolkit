#include "pch.h"

#include "SubrecordPathGrid.h"
#include "xmlUtils.h"

#include <fstream>
#include <istream>
#include <assert.h>

ESMSubrecordPathGridData::ESMSubrecordPathGridData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader)
	: ESMSubrecordCommon(subrecordHeader)
{}

bool ESMSubrecordPathGridData::Read(std::ifstream& input)
{
	if (!ESMSubrecordCommon::Read(input))
		return false;

#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;
#endif

    // read subrecord data
    input.read(reinterpret_cast<char*>(&m_gridX), GetDataSize());
    if ((input.rdstate() & std::ifstream::failbit) != 0)
        return false;

#ifdef DUMP_ESM_TO_XML
    res = xmlTextWriterStartElement(writer, BAD_CAST "Subrecord_Contents");	assert(res != -1);

    LOG_VAR_AS_STR("GridX", m_gridX);
    LOG_VAR_AS_STR("GridY", m_gridY);
    LOG_VAR_AS_HEX("Flags", m_flags);
    LOG_VAR_AS_STR("Point Counts", m_countPoints);

    res = xmlTextWriterEndElement(writer);	assert(res != -1);
    res = xmlTextWriterEndElement(writer);	assert(res != -1);
#endif

	return true;
}

void ESMSubrecordPathGridData::Write(std::ostream& output)
{
	// NIY
}

size_t ESMSubrecordPathGridData::GetDataSize(void) const
{
	return TotalSum(m_gridX, m_gridY, m_flags, m_countPoints);
}

bool ESMSubrecordPathGridData::IsValid(void) const
{
	size_t subrecordSize = GetDataSize();

	return subrecordSize == m_subrecordHeader->GetDataSize();
}

const char* ESMSubrecordPathGridData::GetClassName(void) const
{
	return "Path_Grid_Metadata";
}
