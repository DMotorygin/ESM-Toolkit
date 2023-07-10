#pragma once
#include "SubrecordCommon.h"

class ESMSubrecordBodyPartData : public ESMSubrecordCommon // BYDT
{
public:
	ESMSubrecordBodyPartData(void) : m_BodyPart(0), m_IsVampire(0), m_Flags(0), m_PartType(0) {}
	ESMSubrecordBodyPartData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordBodyPartData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "Body part data"; }
	virtual const char* GetShortName(void) const { return "BYDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	char m_BodyPart; // 0 = Head; 1 = Hair; 2 = Neck; 3 = Chest; 4 = Groin; 5 = Hand; 6 = Wrist; 7 = Forearm; 8 = Upperarm; 9 = Foot; 10 = Ankle; 11 = Knee; 12 = Upperleg; 13 = Clavicle; 14 = Tail
	char m_IsVampire;
	char m_Flags; // ??
	char m_PartType; //0 - skin; 1 - clothing; 2 - armor
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordBodyPartData>(void) { return "BYDT"; }
