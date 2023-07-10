#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

// string value
class ESMSubrecordSpecialAbilityStringValue : public ESMSubrecordStringValue // STRV
{
public:
	ESMSubrecordSpecialAbilityStringValue(void) {}
	ESMSubrecordSpecialAbilityStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordSpecialAbilityStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Special power/ability name"; }
	virtual const char* GetShortName(void) const { return "NPCS"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordSpecialAbilityStringValue>(void) { return "NPCS"; }

