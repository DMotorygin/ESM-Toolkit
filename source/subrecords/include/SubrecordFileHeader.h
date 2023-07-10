#pragma once
#include "SubrecordCommon.h"

// exists only in esp file
class ESMSubrecordFileHeader : public ESMSubrecordCommon // HEDR
{
public:
	ESMSubrecordFileHeader(void) {}
	ESMSubrecordFileHeader(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordFileHeader(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "HEDR"; }
	virtual size_t GetDataSize(void) const;
	virtual bool IsValid(void) const;

protected:
	float m_version;
	int m_fileType;
	std::string m_companyName; // 32 bytes
	std::string m_fileDesc; // 256 bytes
	int m_numRecords;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordFileHeader>(void) { return "HEDR"; }

