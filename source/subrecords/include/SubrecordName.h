#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordName : public ESMSubrecordCommon //NAME
{
public:
	ESMSubrecordName(void) {}
	ESMSubrecordName(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordName(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "NAME"; }
	virtual size_t GetDataSize(void) const;

protected:
	std::string m_name; // variable length?
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordName>(void) { return "NAME"; }


