#pragma once

#include "pch.h"
#include "SubrecordHeader.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>

// interface of subrecord class
class ESMSubrecordIface;
using ESMSubrecordCreator = std::function<ESMSubrecordIface* (std::shared_ptr<ESMSubrecordHeader>& header)>;

struct KeyHasher {
	unsigned short operator()(const std::string_view& key) const {
		unsigned short res =
			( *(reinterpret_cast<const unsigned short*>(&key.data()[0]))
			+ *(reinterpret_cast<const unsigned short*>(&key.data()[2]))
			+ *(reinterpret_cast<const unsigned short*>(&key.data()[1]))
			) & 0x03FF; // % 1024;
		return res;
	}
};

struct IsEqual {
	bool operator() (const std::string_view& a, const std::string_view& b) const {
		return (strncmp(a.data(), b.data(), b.size()) == 0);
	};
};

template <typename T>
using CreatorsMap = std::unordered_map<std::string_view, T, KeyHasher, IsEqual>;

#define DECLARE_SUBRECORD_PAIR(name, subrecordType) std::string_view(name, 4), ESMSubrecordIface::creator<subrecordType>() 

// interface class
class ESMSubrecordIface
{
public:
	// c/d
	ESMSubrecordIface(void) {}
	virtual ~ESMSubrecordIface(void) {}

	// interface
	// - mutators
	virtual bool Read(std::ifstream& input) = 0;
	virtual void Write(std::ostream& output) = 0; // this is for the future when we will want to save modifed data

	// - accessors
	virtual size_t GetDataSize(void) const = 0;
	virtual bool IsValid(void) const = 0; // compares size of data in the header with supposed size of subrecord of this type
	virtual const char* GetShortName(void) const = 0;
	virtual const char* GetClassName(void) const = 0; 

	// to be used it subrecord factory
	template <typename T>
	static ESMSubrecordCreator creator(void)
	{
		return [](std::shared_ptr<ESMSubrecordHeader>& header) { return (ESMSubrecordIface*) new T(header); };
	}
};

// common functions of subrecord
class ESMSubrecordCommon : public ESMSubrecordIface
{
public:
	ESMSubrecordCommon(void);
	ESMSubrecordCommon(std::shared_ptr<ESMSubrecordHeader>& subrecordHeader);
	virtual ~ESMSubrecordCommon(void);

	// should be overriden; is not abstract because this was not in interface from the start
	virtual const char* GetClassName(void) const;

	// part of read/write function that is the same for all subrecords
	virtual bool Read(std::ifstream& input);
	virtual void Write(std::ostream& output);

	// same for most of subrecords
	virtual bool IsValid(void) const;

protected:
	bool ReadSubrecordHeader(std::ifstream& input);

protected:
	// subrecord header
	std::shared_ptr<ESMSubrecordHeader> m_subrecordHeader;
};

template <typename T>
inline const char* GetSubrecordShortName(void)
{
	static_assert(false, "subrecord not declared!");
	return nullptr;
}

//**************************************************************************
// utility
//**************************************************************************

// to summate size of data fields in the record relevant to record size in file (not the same as sizeof(subrecord_class))
template <typename T>
size_t TotalSum(T input)
{
	return sizeof(decltype(input));
}

template <typename T, typename... Args>
size_t TotalSum(T input, Args... args)
{
	return sizeof(decltype(input)) + TotalSum(args...);
}

// macro to read data
#define READ_VAR(var)	input.read(reinterpret_cast<char*>(&var), sizeof(var)); \
						if ((input.rdstate() & std::ifstream::failbit) != 0)	\
							return false;

// misc
#define THIS_TYPE std::remove_pointer<decltype(this)>::type



