#pragma once
#include "SubrecordCommon.h"

// record ID
class ESMSubrecordIngrediantData : public ESMSubrecordCommon // IRDT    
{
public:
	ESMSubrecordIngrediantData(void) : m_Weight(0.0f), m_Value(0) {}
	ESMSubrecordIngrediantData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordIngrediantData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Ingrediant Data"; }
	virtual const char* GetShortName(void) const { return "IRDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_Weight;
	int m_Value;

	// the size of following vectors is always 4
	std::vector<int> m_effectID;
	std::vector<int> m_skillID;
	std::vector<int> m_attributeID;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordIngrediantData>(void) { return "IRDT"; }

