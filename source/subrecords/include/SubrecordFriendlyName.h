#pragma once
#include "SubrecordCommon.h"

// string value
class ESMSubrecordFriendlyName : public ESMSubrecordCommon // FNAM
{
public:
	ESMSubrecordFriendlyName(void) {}
	ESMSubrecordFriendlyName(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordFriendlyName(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "FNAM"; }
	virtual size_t GetDataSize(void) const;

protected:
	std::string m_name;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordFriendlyName>(void) { return "FNAM"; }


