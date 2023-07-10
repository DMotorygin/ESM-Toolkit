#pragma once

#include "SubrecordCommon.h"

// placeholder for subrecord types that aren't supported yet
// simply dumps data block into memory buffer
class ESMSubrecordUnknown : public ESMSubrecordCommon
{
public:
	ESMSubrecordUnknown(void);
	ESMSubrecordUnknown(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordUnknown(void);

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return ""; }
	virtual size_t GetDataSize(void) const;
	virtual bool IsValid(void) const;

protected:
	// unknown data is dumped here
	int m_dataSize;
	std::vector<char> m_data;
};
