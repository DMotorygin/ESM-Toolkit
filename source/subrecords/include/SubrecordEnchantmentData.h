#pragma once
#include "SubrecordCommon.h"

class ESMSubrecordEnchantmentData : public ESMSubrecordCommon // ENDT
{
public:
	ESMSubrecordEnchantmentData(void) : m_type(0), m_cost(0), m_charge(0), m_autoCalc(0) {}
	ESMSubrecordEnchantmentData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordEnchantmentData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	virtual const char* GetClassName(void) const { return "Light data"; }
	virtual const char* GetShortName(void) const { return "ENDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_type; // 0 - single use; 1 - cast on strike; 2 - cast on use; 3 - permanent effect
	int m_cost;
	int m_charge;
	int m_autoCalc; // what's this?
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordEnchantmentData>(void) { return "ENDT"; }
