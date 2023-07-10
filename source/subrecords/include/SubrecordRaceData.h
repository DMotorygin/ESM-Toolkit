#pragma once
#include "SubrecordCommon.h"
#include <array>

// record ID
class ESMSubrecordRaceData : public ESMSubrecordCommon // RADT
{
public:
	ESMSubrecordRaceData(void) {}
	ESMSubrecordRaceData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordRaceData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "RADT"; }
	virtual size_t GetDataSize(void) const;

protected:
	struct SkillBonuses
	{
		int m_SkillID;
		int m_Bonus;
	};
	std::vector<SkillBonuses> m_SkillBonuses;

	std::array<int, 2> m_Strength;
	std::array<int, 2> m_Intelligence;
	std::array<int, 2> m_Willpower;
	std::array<int, 2> m_Agility;
	std::array<int, 2> m_Speed;
	std::array<int, 2> m_Endurance;
	std::array<int, 2> m_Personality;
	std::array<int, 2> m_Luck;
	std::array<float, 2> m_Height;
	std::array<float, 2> m_Weight;
	int m_flags; // 1 - Playable, 2 - Beast Race
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordRaceData>(void) { return "RADT"; }

