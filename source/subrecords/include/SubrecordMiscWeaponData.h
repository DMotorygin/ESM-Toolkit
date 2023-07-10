#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordMiscWeaponData : public ESMSubrecordCommon // MCDT
{
public:
	ESMSubrecordMiscWeaponData(void) : m_weight(0), m_Value(0), m_Unknown(0) {}
	ESMSubrecordMiscWeaponData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordMiscWeaponData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual size_t GetDataSize(void) const;
	virtual const char* GetClassName(void) const { return "Misc Weapon Data"; }
	virtual const char* GetShortName(void) const { return "MCDT"; }

protected:
	float m_weight;
	int m_Value;
	int m_Unknown;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordMiscWeaponData>(void) { return "MCDT"; }


