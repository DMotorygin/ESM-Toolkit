#pragma once

#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordDescription : public ESMSubrecordCommon // DESC
{
public:
	ESMSubrecordDescription(void) {}
	ESMSubrecordDescription(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordDescription(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "DESC"; }
	virtual size_t GetDataSize(void) const;

protected:
	std::string m_description; // variable length?
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordDescription>(void) { return "DESC"; }

