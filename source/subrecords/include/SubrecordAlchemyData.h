#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordAlchemyData : public ESMSubrecordCommon // ALDT    
{
public:
	ESMSubrecordAlchemyData(void) : m_Weight(0.0f), m_Value(0), m_auto(0) {}
	ESMSubrecordAlchemyData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordAlchemyData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Book Data"; }
	virtual const char* GetShortName(void) const { return "ALDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_Weight;
	int m_Value;
	int m_auto;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAlchemyData>(void) { return "ALDT"; }
