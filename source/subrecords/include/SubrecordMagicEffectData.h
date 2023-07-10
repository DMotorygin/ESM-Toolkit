#pragma once
#include "SubrecordCommon.h"
#include "SubrecordStringValue.h"

// record ID
class ESMSubrecordMagicEffectData : public ESMSubrecordCommon // MEDT 
{
public:
	ESMSubrecordMagicEffectData(void) : m_SpellSchool(0), m_BaseCost(0.0f), m_flags(0), m_red(0), m_blue(0), m_green(0), m_speedX(0.0f), m_sizeX(0.0f), m_sizeCap(0.0f) {}
	ESMSubrecordMagicEffectData(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordMagicEffectData(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Magic Effect Data"; }
	virtual const char* GetShortName(void) const { return "MEDT"; }
	virtual size_t GetDataSize(void) const;

protected:
	int m_SpellSchool; // 0 = Alteration, 1 = Conjuration, 2 = Destruction,	3 = Illusion, 4 = Mysticism, 5 = Restoration
	float m_BaseCost;
	int m_flags; // 0x0200 = Spellmaking, 0x0400 = Enchanting, 0x0800 = Negative
	int m_red;
	int m_blue;
	int m_green;
	float m_speedX;
	float m_sizeX;
	float m_sizeCap;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordMagicEffectData>(void) { return "MEDT"; }


//*******************************************************************
// strings for magic effects
//*******************************************************************
// string value
class ESMSubrecordEffectIconStringValue : public ESMSubrecordStringValue // ITEX
{
public:
	ESMSubrecordEffectIconStringValue(void) {}
	ESMSubrecordEffectIconStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordEffectIconStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Effect Icon string"; }
	virtual const char* GetShortName(void) const { return "ITEX"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordEffectIconStringValue>(void) { return "ITEX"; }


// string value
class ESMSubrecordParticleTextureStringValue : public ESMSubrecordStringValue // PTEX 
{
public:
	ESMSubrecordParticleTextureStringValue(void) {}
	ESMSubrecordParticleTextureStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordParticleTextureStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Particle texture string"; }
	virtual const char* GetShortName(void) const { return "PTEX"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordParticleTextureStringValue>(void) { return "PTEX"; }


// string value
class ESMSubrecordCastEffectStringValue : public ESMSubrecordStringValue // CVFX 
{
public:
	ESMSubrecordCastEffectStringValue(void) {}
	ESMSubrecordCastEffectStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCastEffectStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Casting visual effect string"; }
	virtual const char* GetShortName(void) const { return "CVFX"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCastEffectStringValue>(void) { return "CVFX"; }


// string value
class ESMSubrecordBoltEffectStringValue : public ESMSubrecordStringValue // BVFX 
{
public:
	ESMSubrecordBoltEffectStringValue(void) {}
	ESMSubrecordBoltEffectStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordBoltEffectStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Bolt visual effect string"; }
	virtual const char* GetShortName(void) const { return "BVFX"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordBoltEffectStringValue>(void) { return "BVFX"; }

// string value
class ESMSubrecordHitEffectStringValue : public ESMSubrecordStringValue // HVFX 
{
public:
	ESMSubrecordHitEffectStringValue(void) {}
	ESMSubrecordHitEffectStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordHitEffectStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Hit visual effect string"; }
	virtual const char* GetShortName(void) const { return "HVFX"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordHitEffectStringValue>(void) { return "HVFX"; }

// string value
class ESMSubrecordAreaEffectStringValue : public ESMSubrecordStringValue // AVFX 
{
public:
	ESMSubrecordAreaEffectStringValue(void) {}
	ESMSubrecordAreaEffectStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordAreaEffectStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Area visual effect string"; }
	virtual const char* GetShortName(void) const { return "AVFX"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAreaEffectStringValue>(void) { return "AVFX"; }

// string value
class ESMSubrecordCastSoundStringValue : public ESMSubrecordStringValue // CSND  
{
public:
	ESMSubrecordCastSoundStringValue(void) {}
	ESMSubrecordCastSoundStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordCastSoundStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Cast sound"; }
	virtual const char* GetShortName(void) const { return "CSND"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordCastSoundStringValue>(void) { return "CSND"; }

// string value
class ESMSubrecordBoltSoundStringValue : public ESMSubrecordStringValue // BSND  
{
public:
	ESMSubrecordBoltSoundStringValue(void) {}
	ESMSubrecordBoltSoundStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordBoltSoundStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Bolt sound"; }
	virtual const char* GetShortName(void) const { return "BSND"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordBoltSoundStringValue>(void) { return "BSND"; }

// string value
class ESMSubrecordHitSoundStringValue : public ESMSubrecordStringValue // HSND  
{
public:
	ESMSubrecordHitSoundStringValue(void) {}
	ESMSubrecordHitSoundStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordHitSoundStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Hit sound"; }
	virtual const char* GetShortName(void) const { return "HSND"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordHitSoundStringValue>(void) { return "HSND"; }

// string value
class ESMSubrecordAreaSoundStringValue : public ESMSubrecordStringValue // ASND  
{
public:
	ESMSubrecordAreaSoundStringValue(void) {}
	ESMSubrecordAreaSoundStringValue(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordStringValue(subrecordHeader) {};
	virtual ~ESMSubrecordAreaSoundStringValue(void) {}

	virtual const char* GetClassName(void) const { return "Area sound"; }
	virtual const char* GetShortName(void) const { return "ASND"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordAreaSoundStringValue>(void) { return "ASND"; }


