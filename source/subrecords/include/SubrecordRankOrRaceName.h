#pragma once
#include "SubrecordCommon.h"

// exists only in esp file
class ESMSubrecordRankOrRaceName : public ESMSubrecordCommon // RNAM
{
public:
	ESMSubrecordRankOrRaceName(void);
	ESMSubrecordRankOrRaceName(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordRankOrRaceName(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "RNAM"; }
	virtual size_t GetDataSize(void) const;

protected:
	// should be constant size, but not sure
	std::string m_stringValue;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordRankOrRaceName>(void) { return "RNAM"; }

