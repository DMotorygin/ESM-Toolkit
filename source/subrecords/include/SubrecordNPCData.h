#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

// record ID
class ESMSubrecordNPCData : public ESMSubrecordCommon // NPDT 
	// NOTICE: it has the same name tag as SubrecordCreatureData!
{
public:
	ESMSubrecordNPCData(void);
	ESMSubrecordNPCData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordNPCData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "NPC Data"; }
	virtual const char* GetShortName(void) const { return "NPDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	short m_Level;
	char  m_Strength;
	char  m_Intelligence;
	char  m_Willpower;
	char  m_Agility;
	char  m_Speed;
	char  m_Endurance;
	char  m_Personality;
	char  m_Luck;
	char m_Skills[27]; // According to the skillID(0 - 26)
	char  m_Reputation;
	short m_Health;
	short m_SpellPts;
	short m_Fatigue;
	char  m_Disposition;
	char  m_FactionID;
	char  m_Rank;
	char  m_Unknown;
	int	  m_gold;

	// these are for autocalculated NPCs
	char  m_Unknown2;
	char  m_Unknown3;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordNPCData>(void) { return "NPDT"; }

class ESMSubrecordNPCAIData : public ESMSubrecordCommon // AIDT
{
public:
	ESMSubrecordNPCAIData(void) : m_greetingDistance(0), m_Unknown(0), m_Fight(0), m_Flee(0), m_Alarm(0), m_Unknown1(0), m_Unknown2(0), m_Unknown3(0), m_services(0) {}
	ESMSubrecordNPCAIData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordNPCAIData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "AI data"; }
	virtual const char* GetShortName(void) const { return "AIDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	char m_greetingDistance; //???
	char m_Unknown;
	char m_Fight;
	char m_Flee;
	char m_Alarm;
	char m_Unknown1;
	char m_Unknown2;
	char m_Unknown3;
	int m_services;
		// 0x00001 = Weapon
		// 0x00002 = Armor
		// 0x00004 = Clothing
		// 0x00008 = Books
		// 0x00010 = Ingrediant
		// 0x00020 = Picks
		// 0x00040 = Probes
		// 0x00080 = Lights
		// 0x00100 = Apparatus
		// 0x00200 = Repair
		// 0x00400 = Misc
		// 0x00800 = Spells
		// 0x01000 = Magic Items
		// 0x02000 = Potions
		// 0x04000 = Training
		// 0x08000 = Spellmaking
		// 0x10000 = Enchanting
		// 0x20000 = Repair Item
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordNPCAIData>(void) { return "AIDT"; }

//*******************************************************************
// strings for NPC
//*******************************************************************
// string value
class ESMSubrecordHairModel : public ESMSubrecordStringValue // KNAM
{
public:
	ESMSubrecordHairModel(void) {}
	ESMSubrecordHairModel(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordHairModel(void) {}

	virtual const char* GetClassName(void) const { return "Hair model"; }
	virtual const char* GetShortName(void) const { return "KNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordHairModel>(void) { return "KNAM"; }


class ESMSubrecordHeadModel : public ESMSubrecordStringValue // BNAM
{
public:
	ESMSubrecordHeadModel(void) {}
	ESMSubrecordHeadModel(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordHeadModel(void) {}

	virtual const char* GetClassName(void) const { return "Head Model"; }
	virtual const char* GetShortName(void) const { return "BNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordHeadModel>(void) { return "BNAM"; }


class ESMSubrecordCellEscortString : public ESMSubrecordStringValue // CNDT
{
public:
	ESMSubrecordCellEscortString(void) {}
	ESMSubrecordCellEscortString(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellEscortString(void) {}

	virtual const char* GetClassName(void) const { return "Cell escort/follow to string"; }
	virtual const char* GetShortName(void) const { return "CNDT"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellEscortString>(void) { return "CNDT"; }


class ESMSubrecordDestinationCellString : public ESMSubrecordStringValue // DNAM
{
public:
	ESMSubrecordDestinationCellString(void) {}
	ESMSubrecordDestinationCellString(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordDestinationCellString(void) {}

	virtual const char* GetClassName(void) const { return "Another cell related string?"; }
	virtual const char* GetShortName(void) const { return "DNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordDestinationCellString>(void) { return "DNAM"; }


class ESMSubrecordAIFollow : public ESMSubrecordCommon // AI_F 
{
public:
	ESMSubrecordAIFollow(void) : m_X(0.0f), m_Y(0.0f), m_Z(0.0f), m_Duration(0), m_shouldRepeat(0), m_padding(0) {}
	ESMSubrecordAIFollow(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordAIFollow(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "AI Follow"; }
	virtual const char* GetShortName(void) const { return "AI_F"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_X;
	float m_Y;
	float m_Z;
	short m_Duration;
	std::string m_ID; // 32 byte
	unsigned char m_shouldRepeat;
	unsigned char m_padding;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAIFollow>(void) { return "AI_F"; }


class ESMSubrecordAIEscort : public ESMSubrecordAIFollow // AI_E
{
public:
	ESMSubrecordAIEscort(void) {}
	ESMSubrecordAIEscort(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordAIFollow(subrecordHeader) {};
	virtual ~ESMSubrecordAIEscort(void) {}

	virtual const char* GetClassName(void) const { return "AI Escort"; }
	virtual const char* GetShortName(void) const { return "AI_E"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAIEscort>(void) { return "AI_E"; }


class ESMSubrecordAIActivate : public ESMSubrecordCommon // AI_A 
{
public:
	ESMSubrecordAIActivate(void) : m_shouldRepeat(0) {}
	ESMSubrecordAIActivate(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordAIActivate(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "AI Activate"; }
	virtual const char* GetShortName(void) const { return "AI_A"; }
	virtual size_t GetDataSize(void) const;

protected:
	std::string m_ID; // 32 byte
	unsigned char m_shouldRepeat;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAIActivate>(void) { return "AI_A"; }


class ESMSubrecordCellTravelDestination : public ESMSubrecordCommon // DODT 
{
public:
	ESMSubrecordCellTravelDestination(void);
	ESMSubrecordCellTravelDestination(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCellTravelDestination(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "Cell Travel Destination"; }
	virtual const char* GetShortName(void) const { return "DODT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_XPos;
	float m_YPos;
	float m_ZPos;
	float m_XRot;
	float m_YRot;
	float m_ZRot;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellTravelDestination>(void) { return "DODT"; }

