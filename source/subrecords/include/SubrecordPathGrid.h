#pragma once
#include "SubrecordCommon.h"

// exists only in esp file
class ESMSubrecordPathGridData : public ESMSubrecordCommon // DATA
{
public:
    ESMSubrecordPathGridData(void) {}
    ESMSubrecordPathGridData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordPathGridData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const;
	virtual const char* GetShortName(void) const { return "DATA"; }
	virtual size_t GetDataSize(void) const;
	virtual bool IsValid(void) const;

    unsigned int X(void) const { return m_gridX; }
    unsigned int Y(void) const { return m_gridY; }

protected:
    int m_gridX;
    int m_gridY;

    short m_flags;	// granularity
    short m_countPoints;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordPathGridData>(void) { return "DATA"; }

