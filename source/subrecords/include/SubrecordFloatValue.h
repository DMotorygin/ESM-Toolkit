#pragma once
#pragma once
#include "SubrecordCommon.h"

// integer value
class ESMSubrecordFloatValue : public ESMSubrecordCommon // FLTV
{
public:
	ESMSubrecordFloatValue(void) : m_floatValue(0.0f) {}
	ESMSubrecordFloatValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordFloatValue(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "FLTV"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_floatValue; // 4 bytes
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordFloatValue>(void) { return "FLTV"; }

