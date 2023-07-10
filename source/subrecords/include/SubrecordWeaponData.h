#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordWeaponData : public ESMSubrecordCommon // WEAP
{
public:
	ESMSubrecordWeaponData(void) : m_weight(0.0f), m_Value(0), m_Type(0), m_Health(0), m_Speed(0.0f), m_Reach(0.0f), m_EnchantPts(0), m_ChopMin(0), m_ChopMax(0), m_SlashMin(0), m_SlashMax(0), m_ThrustMin(0), m_ThrustMax(0), m_flags(0) {}
	ESMSubrecordWeaponData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordWeaponData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual size_t GetDataSize(void) const;
	virtual const char* GetClassName(void) const { return "Weapon Data"; }
	virtual const char* GetShortName(void) const { return "WPDT"; }

protected:
	float m_weight;
	int m_Value;
	short m_Type;
	short m_Health;
	float m_Speed;
	float m_Reach;
	short m_EnchantPts;
	char m_ChopMin;
	char m_ChopMax;
	char m_SlashMin;
	char m_SlashMax;
	char m_ThrustMin;
	char m_ThrustMax;
	int m_flags; // ?
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordWeaponData>(void) { return "WPDT"; }

