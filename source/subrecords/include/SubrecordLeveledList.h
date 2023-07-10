#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"
#include "SubrecordIntValue.h"

class SubrecordLeveledListData : public ESMSubrecordIntValue // DATA  
{
public:
	SubrecordLeveledListData(void) {}
	SubrecordLeveledListData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordIntValue(subrecordHeader) {};
	virtual ~SubrecordLeveledListData(void) {}

	virtual const char* GetClassName(void) const { return "Leveled List Flags?"; }
	virtual const char* GetShortName(void) const { return "DATA"; }
};

template <> inline const char* GetSubrecordShortName<SubrecordLeveledListData>(void) { return "DATA"; }


class ESMSubrecordLeveledListChance : public ESMSubrecordCommon // NNAM     
{
public:
	ESMSubrecordLeveledListChance(void) : m_val(0) {}
	ESMSubrecordLeveledListChance(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLeveledListChance(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Chance?"; }
	virtual const char* GetShortName(void) const { return "NNAM"; }
	virtual size_t GetDataSize(void) const { return 1; }

protected:
	unsigned char m_val;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLeveledListChance>(void) { return "NNAM"; }


class ESMSubrecordItemLeveledListId : public ESMSubrecordStringValue // INAM
{
public:
	ESMSubrecordItemLeveledListId(void) {}
	ESMSubrecordItemLeveledListId(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordItemLeveledListId(void) {}

	virtual const char* GetClassName(void) const { return "Item Leveled List Id"; }
	virtual const char* GetShortName(void) const { return "INAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordItemLeveledListId>(void) { return "INAM"; }


class ESMSubrecordCreatureLeveledListId : public ESMSubrecordStringValue // CNAM
{
public:
	ESMSubrecordCreatureLeveledListId(void) {}
	ESMSubrecordCreatureLeveledListId(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCreatureLeveledListId(void) {}

	virtual const char* GetClassName(void) const { return "Creature Leveled List Id"; }
	virtual const char* GetShortName(void) const { return "CNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCreatureLeveledListId>(void) { return "CNAM"; }


class ESMSubrecordLeveledListPCLevel : public ESMSubrecordCommon // INTV     
{
public:
	ESMSubrecordLeveledListPCLevel(void) : m_lvl(0) {}
	ESMSubrecordLeveledListPCLevel(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLeveledListPCLevel(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Player Character level for item/creature"; }
	virtual const char* GetShortName(void) const { return "INTV"; }
	virtual size_t GetDataSize(void) const;

protected:
	short m_lvl;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLeveledListPCLevel>(void) { return "INTV"; }


class SubrecordLeveledListIntValue : public ESMSubrecordIntValue // INDX 
{
public:
	SubrecordLeveledListIntValue(void) {}
	SubrecordLeveledListIntValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordIntValue(subrecordHeader) {};
	virtual ~SubrecordLeveledListIntValue(void) {}

	virtual const char* GetClassName(void) const { return "Value"; }
	virtual const char* GetShortName(void) const { return "INDX"; }
};

template <> inline const char* GetSubrecordShortName<SubrecordLeveledListIntValue>(void) { return "INDX"; }

