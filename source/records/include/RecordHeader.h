
#pragma once
#include "pch.h"
#include <string>
#include <iostream>

// wrapper of header of esm records; is the same for every record
// always 16 bytes

class ESMRecordHeader 
{
public:
	ESMRecordHeader(void);
	~ESMRecordHeader(void);

	bool Read(std::ifstream& input);
	void Write(std::ostream& output); // this is for the future when we will want to save modifed data

	void DumpToXML(void);

	int GetDataSize(void) const;
	const std::string_view& GetRecordType(void) const;

protected:
	char m_recordType[4]; // always 4 bytes of data
	int m_dataSize;
	int m_unknown;
	int m_flags;
	std::string_view m_str;
};
