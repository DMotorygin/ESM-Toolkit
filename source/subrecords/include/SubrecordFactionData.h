#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordFactionData : public ESMSubrecordCommon // FADT
{
public:
	ESMSubrecordFactionData(void) {}
	ESMSubrecordFactionData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordFactionData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual size_t GetDataSize(void) const;
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "FADT"; }

protected:
	int m_AttributeID1;
	int m_AttributeID2;
	struct RankData
	{
		int m_Attribute1;
		int m_Attribute2;
		int m_FirstSkill;
		int m_SecondSkill;
		int m_Faction;
	};
	std::vector<RankData> m_RankData;
	std::vector<int> m_SkillID;
	int m_unknown;
	int m_flags; // 1- hidden from the player
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordFactionData>(void) { return "FADT"; }

