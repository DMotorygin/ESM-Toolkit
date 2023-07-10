#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"
#include "SubrecordFloatValue.h"

// record ID
class ESMSubrecordCreatureData : public ESMSubrecordCommon // NPDT  
{
public:
	ESMSubrecordCreatureData(void)
		: m_Type(0)
		, m_Level(0)
		, m_Strength(0)
		, m_Intelligence(0)
		, m_Willpower(0)
		, m_Agility(0)
		, m_Speed(0)
		, m_Endurance(0)
		, m_Personality(0)
		, m_Luck(0)
		, m_Health(0)
		, m_SpellPts(0)
		, m_Fatigue(0)
		, m_Soul(0)
		, m_Combat(0)
		, m_Magic(0)
		, m_Stealth(0)
		, m_AttackMin1(0)
		, m_AttackMax1(0)
		, m_AttackMin2(0)
		, m_AttackMax2(0)
		, m_AttackMin3(0)
		, m_AttackMax3(0)
		, m_Gold(0)
	{}
	ESMSubrecordCreatureData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCreatureData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Creature Data"; }
	virtual const char* GetShortName(void) const { return "NPDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_Type; // 0 = Creature, 1 = Daedra, 2 = Undead, 3 = Humanoid
	int m_Level;
	int m_Strength;
	int m_Intelligence;
	int m_Willpower;
	int m_Agility;
	int m_Speed;
	int m_Endurance;
	int m_Personality;
	int m_Luck;
	int m_Health;
	int m_SpellPts;
	int m_Fatigue;
	int m_Soul;
	int m_Combat;
	int m_Magic;
	int m_Stealth;
	int m_AttackMin1;
	int m_AttackMax1;
	int m_AttackMin2;
	int m_AttackMax2;
	int m_AttackMin3;
	int m_AttackMax3;
	int m_Gold;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCreatureData>(void) { return "NPDT"; }

class ESMSubrecordItemRecord : public ESMSubrecordCommon // NPCO
{
public:
	ESMSubrecordItemRecord(void) : m_count(0) {}
	ESMSubrecordItemRecord(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordItemRecord(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Item record"; }
	virtual const char* GetShortName(void) const { return "NPCO"; }
	virtual size_t GetDataSize(void) const;

protected:
	long m_count;
	std::string m_itemID; // always 32 bytes
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordItemRecord>(void) { return "NPCO"; }

// string value
class ESMSubrecordCreatureScript : public ESMSubrecordStringValue // SCRI
{
public:
	ESMSubrecordCreatureScript(void) {}
	ESMSubrecordCreatureScript(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCreatureScript(void) {}

	virtual const char* GetClassName(void) const { return "Script"; }
	virtual const char* GetShortName(void) const { return "SCRI"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCreatureScript>(void) { return "SCRI"; }

// not sure what this is...
class ESMSubrecordCreatureAIData : public ESMSubrecordCommon // AIDT
{
public:
	ESMSubrecordCreatureAIData(void) : m_greetingDistance(0), m_Fight(0), m_Flee(0), m_Alarm(0), m_Unknown1(0), m_Unknown2(0), m_Unknown3(0), m_services(0) {}
	ESMSubrecordCreatureAIData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCreatureAIData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "AI data"; }
	virtual const char* GetShortName(void) const { return "AIDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	short m_greetingDistance;
	char m_Fight;
	char m_Flee;
	char m_Alarm;
	char m_Unknown1;
	char m_Unknown2;
	char m_Unknown3;
	int m_services;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCreatureAIData>(void) { return "AIDT"; }

class ESMSubrecordAIWander : public ESMSubrecordCommon // AI_W
{
public:
	ESMSubrecordAIWander(void) : m_Distance(0), m_Duration(0), m_TimeOfDay(0), m_shouldRepeat(0) {}
	ESMSubrecordAIWander(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordAIWander(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "AI Wander"; }
	virtual const char* GetShortName(void) const { return "AI_W"; }
	virtual size_t GetDataSize(void) const;

protected:
	short m_Distance;
	short m_Duration;
	char m_TimeOfDay;
	std::string m_idle; // 8
	char m_shouldRepeat;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAIWander>(void) { return "AI_W"; }


class ESMSubrecordAITravel : public ESMSubrecordCommon // AI_T 
{
public:
	ESMSubrecordAITravel(void) : m_X(0.0f), m_Y(0.0f), m_Z(0.0f), m_shouldRepeat(0) {}
	ESMSubrecordAITravel(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordAITravel(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "AI Travel?"; }
	virtual const char* GetShortName(void) const { return "AI_T"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_X;
	float m_Y;
	float m_Z;
	char m_shouldRepeat;
	std::string m_padding; // 3
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAITravel>(void) { return "AI_T"; }


// string value
class ESMSubrecordCreatureScale : public ESMSubrecordFloatValue // XSCL
{
public:
	ESMSubrecordCreatureScale(void) {}
	ESMSubrecordCreatureScale(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordFloatValue(subrecordHeader) {};
	virtual ~ESMSubrecordCreatureScale(void) {}

	virtual const char* GetClassName(void) const { return "Scale"; }
	virtual const char* GetShortName(void) const { return "XSCL"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCreatureScale>(void) { return "XSCL"; }

