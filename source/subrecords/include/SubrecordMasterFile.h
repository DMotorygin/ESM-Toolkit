#pragma once
#include "SubrecordCommon.h"

// exists only in esp file
class ESMSubrecordMasterFile : public ESMSubrecordCommon //MAST
{
public:
	ESMSubrecordMasterFile(void) {}
	ESMSubrecordMasterFile(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordMasterFile(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "MAST"; }
	virtual size_t GetDataSize(void) const;
	virtual bool IsValid(void) const;

protected:
	int m_nameLength;
	std::string m_fileName;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordMasterFile>(void) { return "MAST"; }

