#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"
#include "SubrecordIntValue.h"
#include "SubrecordFloatValue.h"


// record ID
class ESMSubrecordCellData : public ESMSubrecordCommon // DATA    
{
public:
	ESMSubrecordCellData(void) : m_flags(0), m_gridX(0), m_gridY(0) {}
	ESMSubrecordCellData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCellData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Cell Data"; }
	virtual const char* GetShortName(void) const { return "DATA"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_flags;	// 0x01 = Interior?
					// 0x02 = Has Water
					// 0x04 = Illegal to Sleep here
					// 0x80 = Behave like exterior(Tribunal)

	int m_gridX;
	int m_gridY;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellData>(void) { return "DATA"; }



class ESMSubrecordCellRegionNameValue : public ESMSubrecordStringValue // RGNN
{
public:
	ESMSubrecordCellRegionNameValue(void) {}
	ESMSubrecordCellRegionNameValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellRegionNameValue(void) {}

	virtual const char* GetClassName(void) const { return "Region name"; }
	virtual const char* GetShortName(void) const { return "RGNN"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellRegionNameValue>(void) { return "RGNN"; }



class SubrecordCellObjectsCount : public ESMSubrecordIntValue // NAM0  
{
public:
	SubrecordCellObjectsCount(void) {}
	SubrecordCellObjectsCount(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordIntValue(subrecordHeader) {};
	virtual ~SubrecordCellObjectsCount(void) {}

	virtual const char* GetClassName(void) const { return "Count of objects in cell in current record"; }
	virtual const char* GetShortName(void) const { return "NAM0"; }
};

template <> inline const char* GetSubrecordShortName<SubrecordCellObjectsCount>(void) { return "NAM0"; }



// Exterior Cell Sub-Records
class SubrecordCellMapColor : public ESMSubrecordCommon // NAM5  
{
public:
	SubrecordCellMapColor(void) : m_colorValue(0) {}
	SubrecordCellMapColor(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~SubrecordCellMapColor(void) {}

	virtual bool Read(std::ifstream& input);
	virtual const char* GetClassName(void) const { return "Exterior Cell Map Color"; }
	virtual const char* GetShortName(void) const { return "NAM5"; }
	virtual size_t GetDataSize(void) const;

	// byte Red
	// byte Green
	// byte Blue
	// byte Null
protected:
	union cellMapColor
	{
		cellMapColor(int _integer) : m_integer(_integer) {}
		unsigned int m_integer;
		unsigned char m_byte[4];
	} m_colorValue;
};

template <> inline const char* GetSubrecordShortName<SubrecordCellMapColor>(void) { return "NAM5"; }



// Interior Cell Sub-Records
class SubrecordCellWaterHeight : public ESMSubrecordFloatValue // WHGT  
{
public:
	SubrecordCellWaterHeight(void) {}
	SubrecordCellWaterHeight(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordFloatValue(subrecordHeader) {};
	virtual ~SubrecordCellWaterHeight(void) {}

	virtual const char* GetClassName(void) const { return "Water height in the cell"; }
	virtual const char* GetShortName(void) const { return "WHGT"; }
};

template <> inline const char* GetSubrecordShortName<SubrecordCellWaterHeight>(void) { return "WHGT"; }



class ESMSubrecordCellAmbientLight : public ESMSubrecordCommon // AMBI    
{
public:
	ESMSubrecordCellAmbientLight(void) : m_ambientColor(0), m_sunlightColor(0), m_fogColor(0), m_fogDensity(0.0f) {}
	ESMSubrecordCellAmbientLight(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCellAmbientLight(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Ambient Light"; }
	virtual const char* GetShortName(void) const { return "AMBI"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_ambientColor;
	int m_sunlightColor;
	int m_fogColor;
	float m_fogDensity;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellAmbientLight>(void) { return "AMBI"; }



// Referenced Object Data Grouping
class ESMSubrecordCellObjectIdx : public ESMSubrecordIntValue // FRMR  
{
public:
	ESMSubrecordCellObjectIdx(void) {}
	ESMSubrecordCellObjectIdx(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordIntValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellObjectIdx(void) {}

	virtual const char* GetClassName(void) const { return "Object Index"; }
	virtual const char* GetShortName(void) const { return "FRMR"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellObjectIdx>(void) { return "FRMR"; }



class ESMSubrecordCellObjectID : public ESMSubrecordStringValue // NAME
{
public:
	ESMSubrecordCellObjectID(void) {}
	ESMSubrecordCellObjectID(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellObjectID(void) {}

	virtual const char* GetClassName(void) const { return "Object ID string"; }
	virtual const char* GetShortName(void) const { return "NAME"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellObjectID>(void) { return "NAME"; }



class SubrecordCellObjectScale : public ESMSubrecordFloatValue // XSCL  
{
public:
	SubrecordCellObjectScale(void) {}
	SubrecordCellObjectScale(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordFloatValue(subrecordHeader) {};
	virtual ~SubrecordCellObjectScale(void) {}

	virtual const char* GetClassName(void) const { return "Water height in the cell"; }
	virtual const char* GetShortName(void) const { return "XSCL"; }
};

template <> inline const char* GetSubrecordShortName<SubrecordCellObjectScale>(void) { return "XSCL"; }



class ESMSubrecordCellDoorObject : public ESMSubrecordCommon // DODT    
{
public:
	ESMSubrecordCellDoorObject(void) : m_XPos(0.0f), m_YPos(0.0f), m_ZPos(0.0f), m_XRot(0.0f), m_YRot(0.0f), m_ZRot(0.0f) {}
	ESMSubrecordCellDoorObject(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCellDoorObject(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Door transform"; }
	virtual const char* GetShortName(void) const { return "DODT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_XPos;
	float m_YPos;
	float m_ZPos;
	float m_XRot;
	float m_YRot;
	float m_ZRot;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellDoorObject>(void) { return "DODT"; }



class ESMSubrecordCellDoorName : public ESMSubrecordStringValue // DNAM
{
public:
	ESMSubrecordCellDoorName(void) {}
	ESMSubrecordCellDoorName(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellDoorName(void) {}

	virtual const char* GetClassName(void) const { return "Door Name"; }
	virtual const char* GetShortName(void) const { return "DNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellDoorName>(void) { return "DNAM"; }



class ESMSubrecordCellDoorKey : public ESMSubrecordStringValue // KNAM
{
public:
	ESMSubrecordCellDoorKey(void) {}
	ESMSubrecordCellDoorKey(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellDoorKey(void) {}

	virtual const char* GetClassName(void) const { return "Key Name"; }
	virtual const char* GetShortName(void) const { return "KNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellDoorKey>(void) { return "KNAM"; }



class ESMSubrecordCellDoorTrap : public ESMSubrecordStringValue // TNAM
{
public:
	ESMSubrecordCellDoorTrap(void) {}
	ESMSubrecordCellDoorTrap(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellDoorTrap(void) {}

	virtual const char* GetClassName(void) const { return "Trap Name"; }
	virtual const char* GetShortName(void) const { return "TNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellDoorTrap>(void) { return "TNAM"; }



class ESMSubrecordCellUnknownFlag : public ESMSubrecordCommon // UNAM  
{
public:
	ESMSubrecordCellUnknownFlag(void) : m_value('\0') {}
	ESMSubrecordCellUnknownFlag(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCellUnknownFlag(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual size_t GetDataSize(void) const { return 1; } //sizeof char always 1

	virtual const char* GetClassName(void) const { return "Unknown Cell Flag"; }
	virtual const char* GetShortName(void) const { return "UNAM"; }

protected:
	char m_value; // 1 bytes
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellUnknownFlag>(void) { return "UNAM"; }


class ESMSubrecordCellOwnerID : public ESMSubrecordStringValue // ANAM
{
public:
	ESMSubrecordCellOwnerID(void) {}
	ESMSubrecordCellOwnerID(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellOwnerID(void) {}

	virtual const char* GetClassName(void) const { return "Owner ID string?"; }
	virtual const char* GetShortName(void) const { return "ANAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellOwnerID>(void) { return "ANAM"; }



class ESMSubrecordCellGlobalID : public ESMSubrecordStringValue // BNAM
{
public:
	ESMSubrecordCellGlobalID(void) {}
	ESMSubrecordCellGlobalID(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellGlobalID(void) {}

	virtual const char* GetClassName(void) const { return "Global ID string?"; }
	virtual const char* GetShortName(void) const { return "BNAM"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellGlobalID>(void) { return "BNAM"; }

// I have no idea what this is (
class SubrecordCellNam9 : public ESMSubrecordIntValue // NAM9  
{
public:
	SubrecordCellNam9(void) {}
	SubrecordCellNam9(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordIntValue(subrecordHeader) {};
	virtual ~SubrecordCellNam9(void) {}

	virtual const char* GetClassName(void) const { return "???"; }
	virtual const char* GetShortName(void) const { return "NAM9"; }

	// byte Red
	// byte Green
	// byte Blue
	// byte Null
};

template <> inline const char* GetSubrecordShortName<SubrecordCellNam9>(void) { return "NAM9"; }



class ESMSubrecordCellSoul : public ESMSubrecordStringValue // XSOL
{
public:
	ESMSubrecordCellSoul(void) {}
	ESMSubrecordCellSoul(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCellSoul(void) {}

	virtual const char* GetClassName(void) const { return "Global ID string?"; }
	virtual const char* GetShortName(void) const { return "XSOL"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellSoul>(void) { return "XSOL"; }


// - NOTE! "DATA" tag already exist for this Record for another subrecord! Read subrecord carefully!
class ESMSubrecordCellReferencedObjectData : public ESMSubrecordCommon // DATA    
{
public:
	ESMSubrecordCellReferencedObjectData(void) : m_XPos(0.0f), m_YPos(0.0f), m_ZPos(0.0f), m_XRot(0.0f), m_YRot(0.0f), m_ZRot(0.0f) {}
	ESMSubrecordCellReferencedObjectData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCellReferencedObjectData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Cell Referenced Object Data"; }
	virtual const char* GetShortName(void) const { return "DATA"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_XPos;
	float m_YPos;
	float m_ZPos;
	float m_XRot;
	float m_YRot;
	float m_ZRot;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCellReferencedObjectData>(void) { return "DATA"; }

