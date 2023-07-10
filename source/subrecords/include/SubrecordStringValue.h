#pragma once
#include "SubrecordCommon.h"

// string value
class ESMSubrecordStringValue : public ESMSubrecordCommon // STRV
{
public:
	ESMSubrecordStringValue(void) {}
	ESMSubrecordStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordStringValue(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const;
	virtual size_t GetDataSize(void) const;

protected:
	std::string m_stringValue; // variable number of bytes
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordStringValue>(void) { return "STRV"; }

//*******************************************************************
// string subrecords
//*******************************************************************
// string value
class ESMSubrecordTextureFilename : public ESMSubrecordStringValue // TNAM
{
public:
	ESMSubrecordTextureFilename(void) {}
	ESMSubrecordTextureFilename(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordTextureFilename(void) {}

	virtual const char* GetClassName(void) const { return "Texture filename"; }
	virtual const char* GetShortName(void) const { return "TNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordTextureFilename>(void) { return "TNAM"; }

class ESMSubrecordModelFilename : public ESMSubrecordStringValue // MODL 
{
public:
	ESMSubrecordModelFilename(void) {}
	ESMSubrecordModelFilename(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordModelFilename(void) {}

	virtual const char* GetClassName(void) const { return "Nif model"; }
	virtual const char* GetShortName(void) const { return "MODL"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordModelFilename>(void) { return "MODL"; }

// SNAM stands for 2 different subrecords types
class ESMSubrecordSoundName : public ESMSubrecordStringValue // SNAM 
{
public:
	ESMSubrecordSoundName(void) {}
	ESMSubrecordSoundName(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordSoundName(void) {}

	virtual const char* GetClassName(void) const { return "Sound name"; }
	virtual const char* GetShortName(void) const { return "SNAM"; }
};
 
template <> inline const char* GetSubrecordShortName<ESMSubrecordSoundName>(void) { return "SNAM"; }

// DATA stands for 2 different subrecord types
class ESMSubrecordDataString : public ESMSubrecordStringValue // DATA 
{
public:
	ESMSubrecordDataString(void) {}
	ESMSubrecordDataString(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordDataString(void) {}

	virtual const char* GetClassName(void) const { return "Data string value"; }
	virtual const char* GetShortName(void) const { return "DATA"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordDataString>(void) { return "DATA"; }


class ESMSubrecordCName : public ESMSubrecordStringValue // CNAM 
{
public:
	ESMSubrecordCName(void) {}
	ESMSubrecordCName(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCName(void) {}

	virtual const char* GetClassName(void) const { return "String data value"; }
	virtual const char* GetShortName(void) const { return "CNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCName>(void) { return "CNAM"; }


