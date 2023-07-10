#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

// record ID
class ESMSubrecordBookData : public ESMSubrecordCommon // BKDT    
{
public:
	ESMSubrecordBookData(void) : m_Weight(0.0f), m_Value(0), m_Scroll(0), m_skillID(0), m_EnchantPoints(0) {}
	ESMSubrecordBookData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordBookData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Book Data"; }
	virtual const char* GetShortName(void) const { return "BKDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_Weight;
	int m_Value;
	int m_Scroll;
	int m_skillID;
	int m_EnchantPoints;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordBookData>(void) { return "BKDT"; }


class ESMSubrecordTextValue : public ESMSubrecordStringValue // TEXT
{
public:
	ESMSubrecordTextValue(void) {}
	ESMSubrecordTextValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordTextValue(void) {}

	virtual const char* GetClassName(void) const { return "Text Value"; }
	virtual const char* GetShortName(void) const { return "TEXT"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordTextValue>(void) { return "TEXT"; }

