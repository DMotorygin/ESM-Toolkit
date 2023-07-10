#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordAlchemyApparatusData : public ESMSubrecordCommon // AADT    
{
public:
	ESMSubrecordAlchemyApparatusData(void) : m_Type(0), m_Quality(0.0f), m_Weight(0.0f), m_Value(0) {}
	ESMSubrecordAlchemyApparatusData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordAlchemyApparatusData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Alchemy Apparatus Data"; }
	virtual const char* GetShortName(void) const { return "AADT"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_Type; // 0 = Mortar and Pestle, 1 = Albemic, 2 = Calcinator, 3 = Retort
	float m_Quality;
	float m_Weight;
	int m_Value;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAlchemyApparatusData>(void) { return "AADT"; }
