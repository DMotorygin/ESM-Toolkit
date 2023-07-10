#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

// string value
class ESMSubrecordFactionStringValue : public ESMSubrecordStringValue // ANAM
{
public:
	ESMSubrecordFactionStringValue(void) {}
	ESMSubrecordFactionStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordFactionStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Faction name"; }
	virtual const char* GetShortName(void) const { return "ANAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordFactionStringValue>(void) { return "ANAM"; }

