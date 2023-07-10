#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"
#include "SubrecordDataFileInfo.h"

// record ID
class ESMSubrecordScriptHeader : public ESMSubrecordCommon // SCHD 
{
public:
	ESMSubrecordScriptHeader(void) : m_NumShorts(0), m_NumLongs(0), m_NumFloats(0), m_ScriptDataSize(0), m_LocalVarSize(0) {}
	ESMSubrecordScriptHeader(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordScriptHeader(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Script Header"; }
	virtual const char* GetShortName(void) const { return "SCHD"; }
	virtual size_t GetDataSize(void) const;

protected:
	std::string m_Name;
	int m_NumShorts;
	int m_NumLongs;
	int m_NumFloats;
	int m_ScriptDataSize;
	int m_LocalVarSize;
}; 

template <> inline const char* GetSubrecordShortName<ESMSubrecordScriptHeader>(void) { return "SCHD"; }

//*******************************************************************
// strings for scripts
//*******************************************************************
// string value
class ESMSubrecordScriptVariables : public ESMSubrecordStringValue // SCVR
{
public:
	ESMSubrecordScriptVariables(void) {}
	ESMSubrecordScriptVariables(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordScriptVariables(void) {}

	virtual bool Read(std::ifstream& input);

	virtual const char* GetClassName(void) const { return "List of all the local script variables"; }
	virtual const char* GetShortName(void) const { return "SCVR"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordScriptVariables>(void) { return "SCVR"; }

// string value
class ESMSubrecordScriptTextValue : public ESMSubrecordStringValue // SCTX
{
public:
	ESMSubrecordScriptTextValue(void) {}
	ESMSubrecordScriptTextValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordScriptTextValue(void) {}

	virtual const char* GetClassName(void) const { return "Script text"; }
	virtual const char* GetShortName(void) const { return "SCTX"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordScriptTextValue>(void) { return "SCTX"; }

//*******************************************************************
// data for scripts
//*******************************************************************
// data block
class ESMSubrecordCompiledScript : public ESMSubrecordDataFileInfo // SCDT
{
public:
	ESMSubrecordCompiledScript(void) {}
	ESMSubrecordCompiledScript(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordDataFileInfo(subrecordHeader) {};
	virtual ~ESMSubrecordCompiledScript(void) {}

	virtual const char* GetClassName(void) const { return "The compiled script data"; }
	virtual const char* GetShortName(void) const { return "SCDT"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCompiledScript>(void) { return "SCDT"; }

