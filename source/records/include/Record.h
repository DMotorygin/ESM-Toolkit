#pragma once

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>

#include "RecordHeader.h"
#include "SubrecordCommon.h"
#include "SubrecordUnknown.h"
#include "SubrecordMasterFile.h"
#include "SubrecordFileHeader.h"
#include "SubrecordDataFileInfo.h"
#include "SubrecordName.h"
#include "SubrecordStringValue.h"
#include "SubrecordIntValue.h"
#include "SubrecordFloatValue.h"
#include "SubrecordFriendlyName.h"
#include "SubrecordClassData.h"
#include "SubrecordDescription.h"
#include "SubrecordRankOrRaceName.h"
#include "SubrecordFactionData.h"
#include "SubrecordFactionStringValue.h"
#include "SubrecordSpecialAbilityName.h"
#include "SubrecordRaceData.h"
#include "SubrecordIDValue.h"
#include "SubrecordSkillData.h"
#include "SubrecordMagicEffectData.h"
#include "SubrecordScriptHeader.h"
#include "SubrecordWeatherData.h"
#include "SubrecordMiscWeaponData.h"
#include "SubrecordWeaponData.h"
#include "SubrecordContainerData.h"
#include "SubrecordSpellData.h"
#include "SubrecordCreatureData.h"
#include "SubrecordBodyPartData.h"
#include "SubrecordLightData.h"
#include "SubrecordEnchantmentData.h"
#include "SubrecordNPCData.h"
#include "SubrecordArmourData.h"
#include "SubrecordClothingData.h"
#include "SubrecordRepairItemData.h"
#include "SubrecordAlchemyApparatusData.h"
#include "SubrecordLockpickData.h"
#include "SubrecordIngridientData.h"
#include "SubrecordBookData.h"
#include "SubrecordAlchemyData.h"
#include "SubrecordLeveledList.h"
#include "SubrecordCellData.h"
#include "SubrecordLandscapeData.h"

class ESMRecordIface
{
public:
	// c/d
	ESMRecordIface(void) {}
	virtual ~ESMRecordIface(void) {}

	// interface
	// - mutators
	virtual bool Read(std::ifstream& input) = 0;
	virtual void Write(std::ostream& output) = 0;

	// - accessors
	virtual const std::string_view& GetRecordType(void) const = 0;
	virtual bool IsValid(void) const = 0;
};

class ESMRecordCommon : ESMRecordIface
{
public:
	ESMRecordCommon(std::unique_ptr<ESMRecordHeader>& recordHeader);
	virtual ~ESMRecordCommon(void);

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output); // this is for the future when we will want to save modifed data

	virtual const std::string_view& GetRecordType(void) const;
	virtual bool IsValid(void) const; // compares size of data in the header with supposed size of record of this type

protected:
	bool ReadSubrecords(std::ifstream& input);

protected:
	// record header
	std::unique_ptr<ESMRecordHeader> m_recordHeader;

	// collection of subrecords of this record
	// - NOTICE: I have to use shared_ptr here instead of unique_ptr because of GCC issue related to usage of make_unique in initialization list https://stackoverflow.com/questions/9618268/initializing-container-of-unique-ptrs-from-initializer-list-fails-with-gcc-4-7 
	std::vector<std::shared_ptr<ESMSubrecordIface>> m_subrecords;
};

// record for which no special class was created
// other record types are needed for 2 reasons:
// 1) some subrecords have non-unique names;
// 2) to ensure safe writing (or rather to be sure that other applications would be able to read esm file that we save): 
//    it is better to create different record types with hardcoded number and order of subrecords;
class ESMRecordGeneral : public ESMRecordCommon
{
public:
	// c/d
	ESMRecordGeneral(std::unique_ptr<ESMRecordHeader>& recordHeader);
	virtual ~ESMRecordGeneral(void);

	// interace
	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual bool IsValid(void) const;
};

class ESMRecordMainHeader : public ESMRecordCommon // TES3
{
public:
	ESMRecordMainHeader(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = { 
			std::make_shared<ESMSubrecordFileHeader>(), 
			std::make_shared<ESMSubrecordMasterFile>(), 
			std::make_shared<ESMSubrecordDataFileInfo>()
		};
	}

	virtual ~ESMRecordMainHeader(void) {}

	// depending on whether we are reading ESM or ESP files different subrecords should be read
	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const;
};

class ESMRecordGameSetting : public ESMRecordCommon // GMST
{
public:
	ESMRecordGameSetting(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>()
			// <= create dynamically because different types of subrecords are possible in this record
		};
	}

	virtual ~ESMRecordGameSetting(void) {}

	// game setting can have different subrecords
	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "GMST/0", 4); }
};

class ESMRecordGlobalVariable : public ESMRecordCommon // GLOB
{
public:
	ESMRecordGlobalVariable(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<ESMSubrecordFriendlyName>(),
			std::make_shared<ESMSubrecordFloatValue>()
		};
	}

	virtual ~ESMRecordGlobalVariable(void) {}

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "GLOB/0", 4); };
};

class ESMRecordClass : public ESMRecordCommon // CLAS
{
public:
	ESMRecordClass(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<ESMSubrecordFriendlyName>(),
			std::make_shared<ESMSubrecordClassData>(),
			std::make_shared<ESMSubrecordDescription>()
		};
	}

	virtual ~ESMRecordClass(void) {}

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "CLAS/0", 4); };
};

class ESMRecordRegion : public ESMRecordCommon // REGN
{
public:
	ESMRecordRegion(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<ESMSubrecordFriendlyName>(),
			std::make_shared<ESMSubrecordWeatherData>(),
			std::make_shared<ESMSubrecordRegionStringValue>(),
			std::make_shared<ESMSubrecordRegionColorData>(),
			//std::make_shared<ESMSubrecordRegionSoundData>(), // <= create dynamically because different records have different number of this subrecord
		};
	}

	virtual ~ESMRecordRegion(void) {}

	// game setting can have different subrecords
	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "REGN/0", 4); }
};

class ESMRecordSpell : public ESMRecordCommon // SPEL
{
public:
	ESMRecordSpell(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<ESMSubrecordFriendlyName>(),
			std::make_shared<ESMSubrecordSpellData>(),
			//std::make_shared<ESMSubrecordSpellEffectData>() //  <= can have multiple subrecords of this type
		};
	}

	virtual ~ESMRecordSpell(void) {}

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "SPEL/0", 4); };

	// can have different number of ESMSubrecordSpellEffectData subrecords
	virtual bool Read(std::ifstream& input);
};

class ESMRecordEnchantment : public ESMRecordCommon // ENCH
{
public:
	ESMRecordEnchantment(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<ESMSubrecordEnchantmentData>(),
			//std::make_shared<ESMSubrecordSpellEffectData>() //  <= can have multiple subrecords of this type
		};
	}

	virtual ~ESMRecordEnchantment(void) {}

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "ENCH/0", 4); };

	// can have different number of ESMSubrecordSpellEffectData subrecords
	virtual bool Read(std::ifstream& input);
};

class ESMRecordLandTexture : public ESMRecordCommon // LTEX
{
public:
	ESMRecordLandTexture(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<ESMSubrecordIntValue>(),
			std::make_shared<ESMSubrecordDataString>(),
		};
	}

	virtual ~ESMRecordLandTexture(void) {}

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "LTEX/0", 4); }
};

class ESMRecordNPC : public ESMRecordCommon // NPC_
{
public:
	ESMRecordNPC(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			// <= create dynamically because different types of subrecords are possible in this record
		};
	}

	virtual ~ESMRecordNPC(void) {}

	// can have different subrecords
	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "NPC_/0", 4); }
};

class ESMRecordAlchemyPotion : public ESMRecordCommon // ALCH
{
public:
	ESMRecordAlchemyPotion(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			// *** create dynamically because different types of subrecords are possible in this record ***
			//std::make_shared<ESMSubrecordModelFilename>(),
			//std::make_shared<ESMSubrecordFriendlyName>(),
			//std::make_shared<ESMSubrecordAlchemyData>(),
			//std::make_shared<ESMSubrecordSpellEffectData>() //  <= can have multiple (1 to 8) subrecords of this type
			//std::make_shared<ESMSubrecordTextValue>(),
			//std::make_shared<ESMSubrecordCreatureScript>(),
		};
	}

	virtual ~ESMRecordAlchemyPotion(void) {}

	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "ALCH/0", 4); }
};


class ESMRecordLeveledItemsList : public ESMRecordCommon // LEVI
{
public:
	ESMRecordLeveledItemsList(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<SubrecordLeveledListData>(),
			std::make_shared<ESMSubrecordLeveledListChance>(),
			std::make_shared<SubrecordLeveledListIntValue>(),
			// *** create dynamically because different number of following subrecords are possible in this record ***
			//std::make_shared<ESMSubrecordItemLeveledListId>(),
			//std::make_shared<ESMSubrecordLeveledListPCLevel>(),
		};
	}

	virtual ~ESMRecordLeveledItemsList(void) {}

	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "LEVI/0", 4); }
};


class ESMRecordLeveledCreaturesList : public ESMRecordCommon // LEVC
{
public:
	ESMRecordLeveledCreaturesList(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<SubrecordLeveledListData>(),
			std::make_shared<ESMSubrecordLeveledListChance>(),
			std::make_shared<SubrecordLeveledListIntValue>(),
			// *** create dynamically because different number of following subrecords are possible in this record ***
			//std::make_shared<ESMSubrecordCreatureLeveledListId>(),
			//std::make_shared<ESMSubrecordLeveledListPCLevel>(),
		};
	}

	virtual ~ESMRecordLeveledCreaturesList(void) {}

	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "LEVC/0", 4); }
};


class ESMRecordCell : public ESMRecordCommon // CELL
{
public:
	ESMRecordCell(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordName>(),
			std::make_shared<ESMSubrecordCellData>(),
			// *** create dynamically because different types of subrecords are possible in this record ***
			// ******
		};
	}

	virtual ~ESMRecordCell(void) {}

	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "CELL/0", 4); }
};

class ESMRecordLand : public ESMRecordCommon // LAND
{
public:
	ESMRecordLand(std::unique_ptr<ESMRecordHeader>& recordHeader)
		: ESMRecordCommon(recordHeader)
	{
		m_subrecords = {
			std::make_shared<ESMSubrecordLandCellXY>(),
			std::make_shared<ESMSubrecordLandFlags>(),
			// *** create dynamically because different types of subrecords are possible in this record ***
			// ******
		};
	}

	virtual ~ESMRecordLand(void) {}

	virtual bool Read(std::ifstream& input);

	virtual bool IsValid(void) const { return ESMRecordCommon::IsValid() && strncmp(GetRecordType().data(), "LAND/0", 4); }

};


