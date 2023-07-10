#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordSkillData : public ESMSubrecordCommon // SKDT
{
public:
	ESMSubrecordSkillData(void) : m_AttributeID(0), m_Specialization(0) {}
	ESMSubrecordSkillData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordSkillData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual size_t GetDataSize(void) const;
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "SKDT"; }

protected:
	int m_AttributeID;
	int m_Specialization; // 0 - combat, 1 - magic, 2 - stealth
	std::vector<float> m_UseValue; // what's this?
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordSkillData>(void) { return "SKDT"; }

