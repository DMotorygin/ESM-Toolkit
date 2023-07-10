#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

// record ID
class ESMSubrecordSpellData : public ESMSubrecordCommon // SPDT   
{
public:
	ESMSubrecordSpellData(void) : m_Type(0), m_SpellCost(0), m_Flags(0) {}
	ESMSubrecordSpellData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordSpellData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Spell Data"; }
	virtual const char* GetShortName(void) const { return "SPDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_Type; //0 = Spell, 1 = Ability, 2 = Blight, 3 = Disease, 4 = Curse, 5 = Power
	int m_SpellCost;
	int m_Flags; //0x0001 = AutoCalc, 0x0002 = PC Start, 0x0004 = Always Succeeds
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordSpellData>(void) { return "SPDT"; }


// string value
class ESMSubrecordSpellEffectData : public ESMSubrecordCommon // ENAM
{
public:
	ESMSubrecordSpellEffectData(void) : m_effectID(0), m_skillID(0), m_attributeID(0), m_rangeType(0), m_area(0), m_duration(0), m_min(0), m_max(0) {}
	ESMSubrecordSpellEffectData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordSpellEffectData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "spell params data"; }
	virtual const char* GetShortName(void) const { return "ENAM"; }
	virtual size_t GetDataSize(void) const;

protected:
	short m_effectID;
	char m_skillID;
	char m_attributeID;
	int m_rangeType; // 0 - self; 1 - touch; 2 - ranged
	int m_area;
	int m_duration;
	int m_min;
	int m_max;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordSpellEffectData>(void) { return "ENAM"; }


class ESMSubrecordEnchantmentStringValue : public ESMSubrecordStringValue // ENAM
{
public:
	ESMSubrecordEnchantmentStringValue(void) {}
	ESMSubrecordEnchantmentStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordEnchantmentStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Enchantment String (ID?)"; }
	virtual const char* GetShortName(void) const { return "ENAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordEnchantmentStringValue>(void) { return "ENAM"; }

