#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

// record ID
class ESMSubrecordContainerData : public ESMSubrecordCommon // CNDT  
{
public:
	ESMSubrecordContainerData(void) : m_Weight(0.0f) {}
	ESMSubrecordContainerData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordContainerData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Container Data"; }
	virtual const char* GetShortName(void) const { return "CNDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_Weight; 
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordContainerData>(void) { return "CNDT"; }

class ESMSubrecordFlags : public ESMSubrecordCommon // FLAG  
{
public:
	ESMSubrecordFlags(void) : m_Flags(0) {}
	ESMSubrecordFlags(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordFlags(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Flags"; }
	virtual const char* GetShortName(void) const { return "FLAG"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_Flags; //0x0001  = Organic; 0x0002 = Respawns, organic only; 0x0008 = Default, unknown
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordFlags>(void) { return "FLAG"; }

