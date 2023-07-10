#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordRepairItemData : public ESMSubrecordCommon // RIDT    
{
public:
	ESMSubrecordRepairItemData(void) : m_Weight(0.0f), m_Value(0), m_Uses(0), m_Quality(0.0f) {}
	ESMSubrecordRepairItemData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordRepairItemData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Clothing Data"; }
	virtual const char* GetShortName(void) const { return "RIDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_Weight;
	int m_Value;
	int m_Uses;
	float m_Quality;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordRepairItemData>(void) { return "RIDT"; }
