#pragma once
#include "SubrecordCommon.h"
#include "SubrecordIntValue.h"


// record ID
class ESMSubrecordLandCellXY : public ESMSubrecordCommon // INTV
{
public:
	ESMSubrecordLandCellXY(void) : m_X(0), m_Y(0) {}
	ESMSubrecordLandCellXY(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLandCellXY(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Cell XY"; }
	virtual const char* GetShortName(void) const { return "INTV"; }
	virtual size_t GetDataSize(void) const;

protected:
	unsigned int m_X;
	unsigned int m_Y;
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLandCellXY>(void) { return "INTV"; }


// record ID
class ESMSubrecordLandFlags : public ESMSubrecordIntValue // DATA
{
public:
	ESMSubrecordLandFlags(void) {}
	ESMSubrecordLandFlags(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader) : ESMSubrecordIntValue(subrecordHeader) {};
	virtual ~ESMSubrecordLandFlags(void) {}

	virtual const char* GetClassName(void) const { return "Unknown Land Flags"; }
	virtual const char* GetShortName(void) const { return "DATA"; }
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLandFlags>(void) { return "DATA"; }


// values of constants shamelessly stolen from https://gist.github.com/timurgen/c9ed3f8aff29ae01cd5ab10e413f64f8 and OpenMW :)
// - the following records are 65*65 color images plus some occasional data
// - colors here represent vectors
// - Blue is vertical(Z), Red the X directionand Green the Y direction.Note that the y - direction of the data is from the bottom up
// - number of vertices per side?
static const int VERTS_PER_SIDE = 65;

// - total number of vertices
static const int LAND_NUM_VERTS = VERTS_PER_SIDE * VERTS_PER_SIDE;

// - cell terrain size in world coords
static const int REAL_SIZE = 4096; //not sure!


// - default height to use in case there is no Land record
static const int DEFAULT_HEIGHT = -2048;

static const int HEIGHT_SCALE = 8;


// - number of textures per side of land
static const int LAND_TEXTURE_SIZE = 16;

// - total number of textures per land
static const int LAND_NUM_TEXTURES = LAND_TEXTURE_SIZE * LAND_TEXTURE_SIZE;

static const int LAND_GLOBAL_MAP_LOD_SIZE = 81;

static const int LAND_GLOBAL_MAP_LOD_SIZE_SQRT = 9;


struct ESM_byteVec3
{
	signed char m_X;
	signed char m_Y;
	signed char m_Z;

	ESM_byteVec3() : m_X (0), m_Y(0), m_Z(0) {}
};


// record ID
class ESMSubrecordLandVertexNormals : public ESMSubrecordCommon // VNML
{
public:
	ESMSubrecordLandVertexNormals(void) {}
	ESMSubrecordLandVertexNormals(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLandVertexNormals(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Cell Land Vertex Normals"; }
	virtual const char* GetShortName(void) const { return "VNML"; }
	virtual size_t GetDataSize(void) const;

protected:
	ESM_byteVec3 m_Normals[LAND_NUM_VERTS];
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLandVertexNormals>(void) { return "VNML"; }


// record ID
class ESMSubrecordLandHeightmap : public ESMSubrecordCommon // VHGT
{
public:
	ESMSubrecordLandHeightmap(void) : m_heightOffset(0.0f), m_flags(0), m_flags2(0) {}
	ESMSubrecordLandHeightmap(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLandHeightmap(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Cell Heightmap"; }
	virtual const char* GetShortName(void) const { return "VHGT"; }
	virtual size_t GetDataSize(void) const;

protected:
	float m_heightOffset;
	unsigned char m_flags; // unknown flags
	unsigned char m_heights[LAND_NUM_VERTS];
	short m_flags2; // unknown flags
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLandHeightmap>(void) { return "VHGT"; }


// record ID
class ESMSubrecordLandWNAM : public ESMSubrecordCommon // WNAM 
													   // - from OpenMW: low-LOD heightmap (used for rendering the global map)
{
public:
	ESMSubrecordLandWNAM(void) {}
	ESMSubrecordLandWNAM(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLandWNAM(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Cell low-LOD heightmap"; }
	virtual const char* GetShortName(void) const { return "WNAM"; }
	virtual size_t GetDataSize(void) const;

protected:
	unsigned char m_heights[LAND_GLOBAL_MAP_LOD_SIZE];
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLandWNAM>(void) { return "WNAM"; }


// record ID
class ESMSubrecordLandVertexColor : public ESMSubrecordCommon // VCLR
{
public:
	ESMSubrecordLandVertexColor(void) {}
	ESMSubrecordLandVertexColor(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLandVertexColor(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Cell Land vertex color"; }
	virtual const char* GetShortName(void) const { return "VCLR"; }
	virtual size_t GetDataSize(void) const;

protected:
	ESM_byteVec3 m_vertexColors[LAND_NUM_VERTS];
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLandVertexColor>(void) { return "VCLR"; }


// From OpenMW:
// 2D array of texture indices. An index can be used to look up an LandTexture,
// but to do so you must subtract 1 from the index first!
// An index of 0 indicates the default texture.
class ESMSubrecordLandTexture : public ESMSubrecordCommon // VTEX
{
public:
	ESMSubrecordLandTexture(void) {}
	ESMSubrecordLandTexture(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordLandTexture(void) {}

	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);
	virtual const char* GetClassName(void) const { return "Cell Land Textures"; }
	virtual const char* GetShortName(void) const { return "VTEX"; }
	virtual size_t GetDataSize(void) const;

protected:
	unsigned short m_textureIndices[LAND_NUM_TEXTURES];
};

template <> inline const char* GetSubrecordShortName<ESMSubrecordLandTexture>(void) { return "VTEX"; }


