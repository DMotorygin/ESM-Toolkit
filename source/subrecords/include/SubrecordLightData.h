#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

class ESMSubrecordLightData : public ESMSubrecordCommon // LHDT
{
public:
	ESMSubrecordLightData(void) : m_weight(0.0f), m_value(0), m_time(0), m_radius(0), m_R(0), m_G(0), m_B(0), m_Unknown(0), m_Flags(0) {}
	ESMSubrecordLightData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLightData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "Light data"; }
	virtual const char* GetShortName(void) const { return "LHDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_weight;
	int m_value;
	int m_time;
	int m_radius;
	char m_R;
	char m_G;
	char m_B;
	char m_Unknown;
	int m_Flags; // 0x0001 = Dynamic; 0x0002 = Can Carry; 0x0004 = Negative; 0x0008 = Flicker; 0x0010 = Fire; 0x0020 = Off Default; 0x0040 = Flicker Slow; 0x0080 = Pulse; 0x0100 = Pulse Slow
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLightData>(void) { return "LHDT"; }


// string value
class ESMSubrecordScriptName : public ESMSubrecordStringValue // SCPT
{
public:
	ESMSubrecordScriptName(void) {}
	ESMSubrecordScriptName(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordScriptName(void) {}

	virtual const char* GetClassName(void) const { return "Script name"; }
	virtual const char* GetShortName(void) const { return "SCPT"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordScriptName>(void) { return "SCPT"; }



