#pragma once
#include "SubrecordCommon.h"

// integer value
class ESMSubrecordIntValue : public ESMSubrecordCommon // INTV
{
public:
	ESMSubrecordIntValue(void) : m_intValue(0) {}
	ESMSubrecordIntValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordIntValue(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual size_t GetDataSize(void) const;
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "INTV"; }

protected:
	int m_intValue; // 4 bytes
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordIntValue>(void) { return "INTV"; }

