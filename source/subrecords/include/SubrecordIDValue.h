#pragma once
#include "SubrecordCommon.h"
#include "SubrecordIntValue.h"

// int or char value
// 2 types of INDX subrecords exist; one is 4 bytes other is 1 byte
class SubrecordIDValue : public ESMSubrecordIntValue // INDX 
{
public:
	SubrecordIDValue(void) {}
	SubrecordIDValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordIntValue(subrecordHeader) {};
	virtual ~SubrecordIDValue(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual size_t GetDataSize(void) const;

	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "INDX"; }
};

template <> inline const char* GetSubrecordShortName<SubrecordIDValue>(void) { return "INDX"; }


