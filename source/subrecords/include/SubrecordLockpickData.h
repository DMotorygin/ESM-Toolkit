#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordLockpickData : public ESMSubrecordCommon // LKDT    
{
public:
	ESMSubrecordLockpickData(void) : m_Weight(0.0f), m_Value(0), m_Quality(0.0f), m_Uses(0) {}
	ESMSubrecordLockpickData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLockpickData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Lockpick Data"; }
	virtual const char* GetShortName(void) const { return "LKDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_Weight;
	int m_Value;
	float m_Quality;
	int m_Uses;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLockpickData>(void) { return "LKDT"; }


class ESMSubrecordProbeData : public ESMSubrecordLockpickData // PBDT   
{
public:
	ESMSubrecordProbeData(void) {}
	ESMSubrecordProbeData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordLockpickData(subrecordHeader) {};
	virtual ~ESMSubrecordProbeData(void) {}

	virtual const char* GetClassName(void) const { return "Probe Data"; }
	virtual const char* GetShortName(void) const { return "PBDT"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordProbeData>(void) { return "PBDT"; }

