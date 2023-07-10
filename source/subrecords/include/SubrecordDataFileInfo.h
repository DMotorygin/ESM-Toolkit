#pragma once
#include "SubrecordCommon.h"

// exists only in esp file
class ESMSubrecordDataFileInfo : public ESMSubrecordCommon 
{
public:
	ESMSubrecordDataFileInfo(void);
	ESMSubrecordDataFileInfo(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordDataFileInfo(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "DATA"; }
	virtual size_t GetDataSize(void) const;
	virtual bool IsValid(void) const;

protected:
	// variable size
	int m_dataLength;
	std::vector<char> m_data;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordDataFileInfo>(void) { return "DATA"; }

