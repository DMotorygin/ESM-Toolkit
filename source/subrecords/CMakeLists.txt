
target_include_directories(esmToolkit PRIVATE include)
target_include_directories(esmRetort PRIVATE include)

set(SOURCES
    SubrecordClassData.cpp
    SubrecordCommon.cpp
    SubrecordUnknown.cpp
    SubrecordDataFileInfo.cpp
    SubrecordDescription.cpp
    SubrecordFileHeader.cpp
    SubrecordFloatValue.cpp
    SubrecordFriendlyName.cpp
    SubrecordHeader.cpp
    SubrecordIntValue.cpp
    SubrecordMasterFile.cpp
    SubrecordName.cpp
    SubrecordStringValue.cpp
    SubrecordRankOrRaceName.cpp
    SubrecordFactionData.cpp
    SubrecordRaceData.cpp
    SubrecordSkillData.cpp
    SubrecordMagicEffectData.cpp
    SubrecordScriptHeader.cpp
    SubrecordWeatherData.cpp
    SubrecordMiscWeaponData.cpp
    SubrecordWeaponData.cpp
    SubrecordContainerData.cpp
    SubrecordSpellData.cpp
    SubrecordCreatureData.cpp
    SubrecordBodyPartData.cpp
    SubrecordLightData.cpp
    SubrecordEnchantmentData.cpp
    SubrecordNPCData.cpp
    SubrecordIDValue.cpp
    SubrecordArmourData.cpp
    SubrecordClothingData.cpp
    SubrecordRepairItemData.cpp
    SubrecordAlchemyApparatusData.cpp
    SubrecordLockpickData.cpp
    SubrecordIngridientData.cpp
    SubrecordBookData.cpp
    SubrecordAlchemyData.cpp
    SubrecordLeveledList.cpp
    SubrecordCellData.cpp
    SubrecordLandscapeData.cpp
	SubrecordPathGrid.cpp
)

target_sources(esmToolkit PRIVATE ${SOURCES})
target_sources(esmRetort PRIVATE ${SOURCES})
