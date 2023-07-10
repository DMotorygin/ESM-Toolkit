#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

// record ID
class ESMSubrecordWeatherData : public ESMSubrecordCommon // WEAT 
{
public:
	ESMSubrecordWeatherData(void) : m_clear(0), m_cloudy(0), m_foggy(0), m_overcast(0), m_rain(0), m_thunder(0), m_ash(0), m_blight(0) {}
	ESMSubrecordWeatherData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordWeatherData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Weather Data"; }
	virtual const char* GetShortName(void) const { return "WEAT"; }
	virtual size_t GetDataSize(void) const;

protected:
	char m_clear;
	char m_cloudy;
	char m_foggy;
	char m_overcast;
	char m_rain;
	char m_thunder;
	char m_ash;
	char m_blight;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordWeatherData>(void) { return "WEAT"; }


class ESMSubrecordRegionColorData : public ESMSubrecordCommon // CNAM 
{
public:
	ESMSubrecordRegionColorData(void) : m_red(0), m_green(0), m_blue(0), m_unknown(0) {}
	ESMSubrecordRegionColorData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordRegionColorData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Region (map?) color"; }
	virtual const char* GetShortName(void) const { return "CNAM"; }
	virtual size_t GetDataSize(void) const;

protected:
	char m_red;
	char m_green;
	char m_blue;
	char m_unknown;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordRegionColorData>(void) { return "CNAM"; }


class ESMSubrecordRegionSoundData : public ESMSubrecordCommon // SNAM 
{
public:
	ESMSubrecordRegionSoundData(void) : m_chance(0) {}
	ESMSubrecordRegionSoundData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordRegionSoundData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Region sound"; }
	virtual const char* GetShortName(void) const { return "SNAM"; }
	virtual size_t GetDataSize(void) const;

protected:
	std::string m_soundName;
	char m_chance;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordRegionSoundData>(void) { return "SNAM"; }

//*******************************************************************
// strings for region
//*******************************************************************
// string value
class ESMSubrecordRegionStringValue : public ESMSubrecordStringValue // BNAM
{
public:
	ESMSubrecordRegionStringValue(void) {}
	ESMSubrecordRegionStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordRegionStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Sleep attack monsters list name"; }
	virtual const char* GetShortName(void) const { return "BNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordRegionStringValue>(void) { return "BNAM"; }
