#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordClothingData : public ESMSubrecordCommon // CTDT   
{
public:
	ESMSubrecordClothingData(void) : m_Type(0), m_Weight(0.0f), m_Value(0), m_EnchantPoints(0) {}
	ESMSubrecordClothingData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordClothingData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Clothing Data"; }
	virtual const char* GetShortName(void) const { return "CTDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_Type; 
	float m_Weight;
	short m_Value;
	short m_EnchantPoints;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordClothingData>(void) { return "CTDT"; }
