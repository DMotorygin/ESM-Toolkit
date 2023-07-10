#pragma once

#include "SubrecordCommon.h"

// record ID
class ESMSubrecordClassData : public ESMSubrecordCommon // CLDT
{
public:
	ESMSubrecordClassData(void);
	ESMSubrecordClassData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordClassData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const; 
	virtual const char* GetShortName(void) const { return "CLDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_primaryAttribute1ID;
	int m_primaryAttribute2ID;
	int m_specialization; // 0 = combat; 1 = magic; 2 = stealth
	int m_minorSkill1ID;
	int m_majorSkill1ID;
	int m_minorSkill2ID;
	int m_majorSkill2ID;
	int m_minorSkill3ID;
	int m_majorSkill3ID;
	int m_minorSkill4ID;
	int m_majorSkill4ID;
	int m_minorSkill5ID;
	int m_majorSkill5ID;
	int m_isPlayable;
	int m_flags;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordClassData>(void) { return "CLDT"; }

