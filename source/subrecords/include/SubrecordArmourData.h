#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordArmourData : public ESMSubrecordCommon // AODT   
{
public:
	ESMSubrecordArmourData(void) : m_Type(0), m_Weight(0.0f), m_Value(0), m_Health(0), m_EnchantPoints(0), m_Armour(0) {}
	ESMSubrecordArmourData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordArmourData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Armour Data"; }
	virtual const char* GetShortName(void) const { return "AODT"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_Type; //0 = Helmet, 1 = Cuirass, 2 = L.Pauldron, 3 = R.Pauldron, 4 = Greaves, 5 = Boots, 6 = L.Gauntlet, 7 = R.Gauntlet, 8 = Shield, 9 = L.Bracer, 10 = R.Bracer
	float m_Weight;
	int m_Value;
	int m_Health;
	int m_EnchantPoints;
	int m_Armour;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordArmourData>(void) { return "AODT"; }

