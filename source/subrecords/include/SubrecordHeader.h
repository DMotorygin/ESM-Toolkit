#pragma once

#include "pch.h"
#include <string>
#include <iostream>
#include <string_view>

// wrapper for header of sub record
// always 8 bytes
class ESMSubrecordHeader
{
public:
	ESMSubrecordHeader(void);
	~ESMSubrecordHeader(void);

	bool Read(std::ifstream& input);
	void Write(std::ostream& output); // this is for the future when we will want to save modifed data

	void DumpToXML(void);

	int GetDataSize(void) const;
	const std::string_view& GetSubrecordType(void) const;

	static size_t HeaderSize(void);

protected:
	char m_subRecordType[4]; // always 4 bytes of data
	int m_dataSize;
	std::string_view m_str;
};

