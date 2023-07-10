
#include "pch.h"
#include "Record.h"
#include "xmlUtils.h"

#include <functional>
#include <map>
#include <assert.h>

ESMRecordCommon::ESMRecordCommon(std::unique_ptr<ESMRecordHeader>& recordHeader)
	: m_recordHeader(std::move(recordHeader))
{}

ESMRecordCommon::~ESMRecordCommon()
{}

const std::string_view& ESMRecordCommon::GetRecordType(void) const
{
	return m_recordHeader->GetRecordType();
}

bool ESMRecordCommon::IsValid(void) const
{
	size_t totalSize = 0;

	for (auto& subrecord : m_subrecords)
	{
		if (!subrecord)
			continue;

		if (!subrecord->IsValid())
			continue;

		totalSize += subrecord->GetDataSize();
		totalSize += ESMSubrecordHeader::HeaderSize();
	}

	if (totalSize != m_recordHeader->GetDataSize())
		return false;

	return true;
}

void ESMRecordCommon::Write(std::ostream& output)
{
	// NIY
}

bool ESMRecordCommon::Read(std::ifstream& input)
{
	// xml log begin element
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords
	bool success = false;

	success = ReadSubrecords(input);
	if (!success)
		return false;

	// xml log end element
#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	// report success
	return true;
}

bool ESMRecordCommon::ReadSubrecords(std::ifstream& input)
{
	size_t totalSize = 0;

	// read each record
	for (auto& subrecord : m_subrecords)
	{
		if (!subrecord->Read(input))
			return false;

		if (!subrecord->IsValid())
			return false;

		// not all subrecords might be present in some of the records
		totalSize += subrecord->GetDataSize();
		totalSize += ESMSubrecordHeader::HeaderSize();
		if (totalSize == m_recordHeader->GetDataSize())
			break;
	}

	return true;
}


