
#include "pch.h"
#include "Record.h"
#include "xmlUtils.h"

#include <functional>
#include <map>
#include <assert.h>

unsigned int hashString(const std::string& str)
{
    uint32_t hash = 2166136261u;

    for (unsigned char c : str)
    {
        hash ^= c;
        hash *= 16777619u;
    }

    return hash;
}

unsigned int hashGridKey(int x, int y)
{
    return (uint32_t)(x + 999) * 1999u
        + (uint32_t)(y + 999);
}

unsigned int OrderedHash(unsigned int a, unsigned int b)
{
    constexpr uint64_t offset = 14695981039346656037ULL;
    constexpr uint64_t prime = 1099511628211ULL;

    uint64_t hash = offset;

    for (int i = 0; i < 8; ++i)
    {
        hash ^= (a & 0xFF);
        hash *= prime;
        a >>= 8;
    }

    for (int i = 0; i < 8; ++i)
    {
        hash ^= (b & 0xFF);
        hash *= prime;
        b >>= 8;
    }

    return hash;
}

bool ESMRecordMainHeader::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	bool success = false;

	// depending on whether we are reading ESM or ESP files different subrecords should be read
	success = m_subrecords[0]->Read(input);
	if (!success || !m_subrecords[0]->IsValid())
		return false;

	size_t sizeOfRecord = m_recordHeader->GetDataSize();
	size_t sizeOfSubrecord = m_subrecords[0]->GetDataSize() + ESMSubrecordHeader::HeaderSize();

	if (sizeOfRecord != sizeOfSubrecord)
	{
		success = m_subrecords[1]->Read(input);
		if (!success || !m_subrecords[1]->IsValid())
			return false;

		success = m_subrecords[2]->Read(input);
		if (!success || !m_subrecords[2]->IsValid())
			return false;
	}

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

bool ESMRecordMainHeader::IsValid(void) const 
{ 
	bool isClassValid = strncmp(GetRecordType().data(), "TES3/0", 4);
	bool areSubrecordsValid = ESMRecordCommon::IsValid();
	return  isClassValid && areSubrecordsValid;
}

unsigned int ESMRecordMainHeader::UUID(void) const
{
    ESMSubrecordFileHeader* pHdr = (ESMSubrecordFileHeader*)m_subrecords[0].get();
    assert(pHdr != nullptr);
    return hashString(pHdr->FileDesc());
}

bool ESMRecordGameSetting::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecord NAME
	m_subrecords[0]->Read(input);
	if (!m_subrecords[0]->IsValid())
		return false;

	// record of this type can have only subrecord NAME and no data 
	// this make no sense... maybe value not set for such names because the are unused?
	if (m_recordHeader->GetDataSize() == m_subrecords[0]->GetDataSize() + ESMSubrecordHeader::HeaderSize())
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return true; // valid case
	}

	std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
	bool success = subrecordHeader->Read(input);
	if (!success)
		return false;

	if (strncmp(subrecordHeader->GetSubrecordType().data(), "STRV", 4) == 0)
		m_subrecords.emplace_back(std::make_shared<ESMSubrecordStringValue>(subrecordHeader));
	else
	if (strncmp(subrecordHeader->GetSubrecordType().data(), "INTV", 4) == 0)
		m_subrecords.emplace_back(std::make_shared<ESMSubrecordIntValue>(subrecordHeader));
	else
	if (strncmp(subrecordHeader->GetSubrecordType().data(), "FLTV", 4) == 0)
		m_subrecords.emplace_back(std::make_shared<ESMSubrecordFloatValue>(subrecordHeader));
	else
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return false; // should not be here!
	}

	success = m_subrecords.back()->Read(input);
	if (!success || !m_subrecords.back()->IsValid())
		return false;

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

bool ESMRecordRegion::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// record of this type can have several SNAM records
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return true; // valid case
	}

	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		if (strncmp(subrecordHeader->GetSubrecordType().data(), "SNAM", 4) != 0)
		{
#ifdef DUMP_ESM_TO_XML
			res = xmlTextWriterEndElement(writer);
#endif
			return false;
		}

		m_subrecords.emplace_back(std::make_shared<ESMSubrecordRegionSoundData>(subrecordHeader));
		success = m_subrecords.back()->Read(input);
		if (!success || !m_subrecords.back()->IsValid())
			return false;

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}
	while(totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

static CreatorsMap<ESMSubrecordCreator> NPCSubrecordCreators =
{
	{ DECLARE_SUBRECORD_PAIR("FNAM", ESMSubrecordFriendlyName)				},
	{ DECLARE_SUBRECORD_PAIR("MODL", ESMSubrecordModelFilename)				},
	{ DECLARE_SUBRECORD_PAIR("RNAM", ESMSubrecordRankOrRaceName)			},
	{ DECLARE_SUBRECORD_PAIR("ANAM", ESMSubrecordFactionStringValue)		},
	{ DECLARE_SUBRECORD_PAIR("BNAM", ESMSubrecordHeadModel)					},
	{ DECLARE_SUBRECORD_PAIR("CNAM", ESMSubrecordCName)						},
	{ DECLARE_SUBRECORD_PAIR("KNAM", ESMSubrecordHairModel)					},
	{ DECLARE_SUBRECORD_PAIR("NPDT", ESMSubrecordNPCData)					},
	{ DECLARE_SUBRECORD_PAIR("FLAG", ESMSubrecordFlags)						},
	{ DECLARE_SUBRECORD_PAIR("NPCO", ESMSubrecordItemRecord)				},
	{ DECLARE_SUBRECORD_PAIR("NPCS", ESMSubrecordSpecialAbilityStringValue)	},
	{ DECLARE_SUBRECORD_PAIR("AIDT", ESMSubrecordNPCAIData)					},
	{ DECLARE_SUBRECORD_PAIR("AI_W", ESMSubrecordAIWander)					},
	{ DECLARE_SUBRECORD_PAIR("AI_T", ESMSubrecordAITravel)					},
	{ DECLARE_SUBRECORD_PAIR("XSCL", ESMSubrecordCreatureScale)				},
	{ DECLARE_SUBRECORD_PAIR("CNDT", ESMSubrecordCellEscortString)			},
	{ DECLARE_SUBRECORD_PAIR("DNAM", ESMSubrecordDestinationCellString)		},
	{ DECLARE_SUBRECORD_PAIR("AI_F", ESMSubrecordAIFollow)					},
	{ DECLARE_SUBRECORD_PAIR("AI_A", ESMSubrecordAIActivate)				},
	{ DECLARE_SUBRECORD_PAIR("AI_E", ESMSubrecordAIEscort)					},
	{ DECLARE_SUBRECORD_PAIR("DODT", ESMSubrecordCellTravelDestination)		},
	{ DECLARE_SUBRECORD_PAIR("SCRI", ESMSubrecordCreatureScript)			},
};

bool ESMRecordNPC::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// to be sure that data is correct
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return false; // invalid case
	}

	// record of this type can have several different records
	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		// find correct record creator function
		ESMSubrecordCreator pCreator = nullptr;
		auto it = NPCSubrecordCreators.find(subrecordHeader->GetSubrecordType().data());
		if (it == NPCSubrecordCreators.end())
		{
			pCreator = [](std::shared_ptr<ESMSubrecordHeader>& header) { return (ESMSubrecordIface*) new ESMSubrecordUnknown(header); };
		}
		else
		{
			pCreator = it->second;
		}

		// create subrecord instance
		ESMSubrecordIface* pSubrecord = pCreator(subrecordHeader);

		// read subrecord
		success = pSubrecord->Read(input);
		if (!success)
			return false;

		success = pSubrecord->IsValid();
		assert(success);
		if (!success)
			return false;

		m_subrecords.push_back(std::shared_ptr<ESMSubrecordIface>(pSubrecord));

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	} while (totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

bool ESMRecordEnchantment::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// record of this type can have only subrecord NAME and no data 
	// this make no sense?..
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return true; // somehow valid case
	}

	// record of this type can have several different records
	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		if (strncmp(subrecordHeader->GetSubrecordType().data(), "ENAM", 4) != 0)
		{
#ifdef DUMP_ESM_TO_XML
			res = xmlTextWriterEndElement(writer);
#endif
			return false;
		}

		m_subrecords.emplace_back(std::make_shared<ESMSubrecordSpellEffectData>(subrecordHeader));
		success = m_subrecords.back()->Read(input);
		if (!success || !m_subrecords.back()->IsValid())
			return false;

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	} while (totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

bool ESMRecordSpell::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// to be sure that data is correct
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return false; // invalid case
	}

	// record of this type can have several different records
	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		if (strncmp(subrecordHeader->GetSubrecordType().data(), "ENAM", 4) != 0)
		{
#ifdef DUMP_ESM_TO_XML
			res = xmlTextWriterEndElement(writer);
#endif
			return false;
		}

		m_subrecords.emplace_back(std::make_shared<ESMSubrecordSpellEffectData>(subrecordHeader));
		success = m_subrecords.back()->Read(input);
		if (!success || !m_subrecords.back()->IsValid())
			return false;

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	} while (totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

static CreatorsMap<ESMSubrecordCreator> PotionSubrecordCreators =
{
	{ DECLARE_SUBRECORD_PAIR("MODL", ESMSubrecordModelFilename)				},
	{ DECLARE_SUBRECORD_PAIR("FNAM", ESMSubrecordFriendlyName)				},
	{ DECLARE_SUBRECORD_PAIR("ALDT", ESMSubrecordAlchemyData)				},
	{ DECLARE_SUBRECORD_PAIR("ENAM", ESMSubrecordSpellEffectData)			},
	{ DECLARE_SUBRECORD_PAIR("TEXT", ESMSubrecordTextValue)					},
	{ DECLARE_SUBRECORD_PAIR("SCRI", ESMSubrecordCreatureScript)			},
};

bool ESMRecordAlchemyPotion::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// to be sure that data is correct
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return false; // invalid case
	}

	// record of this type can have several different records
	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		// find correct record creator function
		ESMSubrecordCreator pCreator = nullptr;
		auto it = PotionSubrecordCreators.find(subrecordHeader->GetSubrecordType().data());
		if (it == PotionSubrecordCreators.end())
		{
			pCreator = [](std::shared_ptr<ESMSubrecordHeader>& header) { return (ESMSubrecordIface*) new ESMSubrecordUnknown(header); };
		}
		else
		{
			pCreator = it->second;
		}

		// create subrecord instance
		ESMSubrecordIface* pSubrecord = pCreator(subrecordHeader);

		// read subrecord
		success = pSubrecord->Read(input);
		if (!success)
			return false;

		success = pSubrecord->IsValid();
		assert(success);
		if (!success)
			return false;

		m_subrecords.push_back(std::shared_ptr<ESMSubrecordIface>(pSubrecord));

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	} while (totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}


bool ESMRecordLeveledItemsList::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// to be sure that data is correct
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return false; // invalid case
	}

	// different number of following subrecords are possible
	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		if (strncmp(subrecordHeader->GetSubrecordType().data(), "INAM", 4) == 0)
		{ 
			m_subrecords.emplace_back(std::make_shared<ESMSubrecordItemLeveledListId>(subrecordHeader));
			success = m_subrecords.back()->Read(input);
			if (!success || !m_subrecords.back()->IsValid())
				return false;
		}
		else if (strncmp(subrecordHeader->GetSubrecordType().data(), "INTV", 4) == 0)
		{
			m_subrecords.emplace_back(std::make_shared<ESMSubrecordLeveledListPCLevel>(subrecordHeader));
			success = m_subrecords.back()->Read(input);
			if (!success || !m_subrecords.back()->IsValid())
				return false;
		}
		else
		{
#ifdef DUMP_ESM_TO_XML
			res = xmlTextWriterEndElement(writer);
#endif
			return false;
		}

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	} while (totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}


bool ESMRecordLeveledCreaturesList::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// to be sure that data is correct
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return false; // invalid case
	}

	// different number of following subrecords are possible
	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		if (strncmp(subrecordHeader->GetSubrecordType().data(), "CNAM", 4) == 0)
		{
			m_subrecords.emplace_back(std::make_shared<ESMSubrecordCreatureLeveledListId>(subrecordHeader));
			success = m_subrecords.back()->Read(input);
			if (!success || !m_subrecords.back()->IsValid())
				return false;
		}
		else if (strncmp(subrecordHeader->GetSubrecordType().data(), "INTV", 4) == 0)
		{
			m_subrecords.emplace_back(std::make_shared<ESMSubrecordLeveledListPCLevel>(subrecordHeader));
			success = m_subrecords.back()->Read(input);
			if (!success || !m_subrecords.back()->IsValid())
				return false;
		}
		else
		{
#ifdef DUMP_ESM_TO_XML
			res = xmlTextWriterEndElement(writer);
#endif
			return false;
		}

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	} while (totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

static CreatorsMap<ESMSubrecordCreator> CellSubrecordCreators =
{
	{ DECLARE_SUBRECORD_PAIR("RGNN", ESMSubrecordCellRegionNameValue)		},
	{ DECLARE_SUBRECORD_PAIR("NAM0", SubrecordCellObjectsCount)				},
	{ DECLARE_SUBRECORD_PAIR("NAM5", SubrecordCellMapColor)					},
	{ DECLARE_SUBRECORD_PAIR("WHGT", SubrecordCellWaterHeight)				},
	{ DECLARE_SUBRECORD_PAIR("AMBI", ESMSubrecordCellAmbientLight)			},
	{ DECLARE_SUBRECORD_PAIR("FRMR", ESMSubrecordCellObjectIdx)				},
	{ DECLARE_SUBRECORD_PAIR("NAME", ESMSubrecordCellObjectID)				},
	{ DECLARE_SUBRECORD_PAIR("XSCL", SubrecordCellObjectScale)				},
	{ DECLARE_SUBRECORD_PAIR("DODT", ESMSubrecordCellDoorObject)			},
	{ DECLARE_SUBRECORD_PAIR("DNAM", ESMSubrecordCellDoorName)				},
	{ DECLARE_SUBRECORD_PAIR("KNAM", ESMSubrecordCellDoorKey)				},
	{ DECLARE_SUBRECORD_PAIR("TNAM", ESMSubrecordCellDoorTrap)				},
	{ DECLARE_SUBRECORD_PAIR("UNAM", ESMSubrecordCellUnknownFlag)			},
	{ DECLARE_SUBRECORD_PAIR("ANAM", ESMSubrecordCellOwnerID)				},
	{ DECLARE_SUBRECORD_PAIR("BNAM", ESMSubrecordCellGlobalID)				},
	{ DECLARE_SUBRECORD_PAIR("NAM9", SubrecordCellNam9)						},
	{ DECLARE_SUBRECORD_PAIR("XSOL", ESMSubrecordCellSoul)					},
	{ DECLARE_SUBRECORD_PAIR("DATA", ESMSubrecordCellReferencedObjectData)	},
};

bool ESMRecordCell::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// to be sure that data is correct
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return true; // valid case
	}

	// record of this type can have several different records
	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		// find correct record creator function
		ESMSubrecordCreator pCreator = nullptr;
		auto it = CellSubrecordCreators.find(subrecordHeader->GetSubrecordType().data());
		if (it == CellSubrecordCreators.end())
		{
			pCreator = [](std::shared_ptr<ESMSubrecordHeader>& header) { return (ESMSubrecordIface*) new ESMSubrecordUnknown(header); };
		}
		else
		{
			pCreator = it->second;
		}

		// create subrecord instance
		ESMSubrecordIface* pSubrecord = pCreator(subrecordHeader);

		// read subrecord
		success = pSubrecord->Read(input);
		if (!success)
			return false;

		success = pSubrecord->IsValid();
		assert(success);
		if (!success)
			return false;

		m_subrecords.push_back(std::shared_ptr<ESMSubrecordIface>(pSubrecord));

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	} while (totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

unsigned int ESMRecordCell::UUID(void) const
{
    unsigned int hash = 0;

    ESMSubrecordName* pName = dynamic_cast<ESMSubrecordName*>(m_subrecords[0].get());
    assert(pName != nullptr);
    if (pName->Name().size() > 1)
        hash = hashString(pName->Name());

    ESMSubrecordCellData* pCellData = (ESMSubrecordCellData*)m_subrecords[1].get();
    assert(pCellData != nullptr);
    hash ^= hashGridKey(pCellData->X(), pCellData->Y());

    return hash;
}


static CreatorsMap<ESMSubrecordCreator> CellLandCreators =
{
	{ DECLARE_SUBRECORD_PAIR("VNML", ESMSubrecordLandVertexNormals)	},
	{ DECLARE_SUBRECORD_PAIR("VHGT", ESMSubrecordLandHeightmap)		},
	{ DECLARE_SUBRECORD_PAIR("WNAM", ESMSubrecordLandWNAM)			},
	{ DECLARE_SUBRECORD_PAIR("VCLR", ESMSubrecordLandVertexColor)	},
	{ DECLARE_SUBRECORD_PAIR("VTEX", ESMSubrecordLandTexture)		},
};

bool ESMRecordLand::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input
	if (!input)
		return false;

	// read subrecords that are the same all the time
	size_t totalSize = 0;
	for (auto& subrecord : m_subrecords)
	{
		subrecord->Read(input);

		if (!subrecord->IsValid())
			return false;

		totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	}

	// to be sure that data is correct
	if (m_recordHeader->GetDataSize() == totalSize)
	{
#ifdef DUMP_ESM_TO_XML
		res = xmlTextWriterEndElement(writer);
		assert(res != -1);
#endif
		return true; // valid case
	}

	// record of this type can have several different records
	do
	{
		std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
		bool success = subrecordHeader->Read(input);
		if (!success)
			return false;

		// find correct record creator function
		ESMSubrecordCreator pCreator = nullptr;
		auto it = CellLandCreators.find(subrecordHeader->GetSubrecordType().data());
		if (it == CellLandCreators.end())
		{
			pCreator = [](std::shared_ptr<ESMSubrecordHeader>& header) { return (ESMSubrecordIface*) new ESMSubrecordUnknown(header); };
		}
		else
		{
			pCreator = it->second;
		}

		// create subrecord instance
		ESMSubrecordIface* pSubrecord = pCreator(subrecordHeader);

		// read subrecord
		success = pSubrecord->Read(input);
		if (!success)
			return false;

		success = pSubrecord->IsValid();
		assert(success);
		if (!success)
			return false;

		m_subrecords.push_back(std::shared_ptr<ESMSubrecordIface>(pSubrecord));

		totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
	} while (totalSize < m_recordHeader->GetDataSize());
	assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
	res = xmlTextWriterEndElement(writer);
	assert(res != -1);
#endif

	return true;
}

unsigned int ESMRecordLand::UUID(void) const
{
    ESMSubrecordLandCellXY* pCell = (ESMSubrecordLandCellXY*)m_subrecords[0].get();
    assert(pCell != nullptr);
    return hashGridKey(pCell->X(), pCell->Y());
}

unsigned int ESMRecordPathGrid::UUID(void) const
{
    unsigned int hash = 0;

    ESMSubrecordName* pName = dynamic_cast<ESMSubrecordName*>(m_subrecords[1].get());
    assert(pName != nullptr);
    if (pName->Name().size() > 1)
        hash = hashString(pName->Name());

    ESMSubrecordPathGridData* pData = dynamic_cast<ESMSubrecordPathGridData*>(m_subrecords[0].get());
    assert(pData != nullptr);
    hash ^= hashGridKey(pData->X(), pData->Y());

    return hash;
}

bool ESMRecordPathGrid::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
    xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
    assert(writer);

    int res = 0;

    res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
    assert(res != -1);
#endif

    m_recordHeader->DumpToXML();

    // ensure valid input
    if (!input)
        return false;

    // read subrecords that are the same all the time
    size_t totalSize = 0;
    for (auto& subrecord : m_subrecords)
    {
        subrecord->Read(input);

        if (!subrecord->IsValid())
            return false;

        totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
    }

    // to be sure that data is correct
    if (m_recordHeader->GetDataSize() == totalSize)
    {
#ifdef DUMP_ESM_TO_XML
        res = xmlTextWriterEndElement(writer);
        assert(res != -1);
#endif
        return true; // valid case
    }

    // record of this type has several subrecords that I have not implemented yet
    do
    {
        std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
        bool success = subrecordHeader->Read(input);
        if (!success)
            return false;

        // find correct record creator function
        ESMSubrecordCreator pCreator = nullptr;
        pCreator = [](std::shared_ptr<ESMSubrecordHeader>& header) { return (ESMSubrecordIface*) new ESMSubrecordUnknown(header); };

        // create subrecord instance
        ESMSubrecordIface* pSubrecord = pCreator(subrecordHeader);

        // read subrecord
        success = pSubrecord->Read(input);
        if (!success)
            return false;

        success = pSubrecord->IsValid();
        assert(success);
        if (!success)
            return false;

        m_subrecords.push_back(std::shared_ptr<ESMSubrecordIface>(pSubrecord));

        totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
    } while (totalSize < m_recordHeader->GetDataSize());
    assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
    res = xmlTextWriterEndElement(writer);
    assert(res != -1);
#endif

    return true;
}

// to be expanded for proper dialog editing tool
// - most dialoginfo related subrecords not existing atm
static CreatorsMap<ESMSubrecordCreator> DialogInfoCreators =
{
    { DECLARE_SUBRECORD_PAIR("DATA", ESMSubrecordDataFileInfo)	},
    { DECLARE_SUBRECORD_PAIR("NAME", ESMSubrecordName)		    },
    { DECLARE_SUBRECORD_PAIR("INTV", ESMSubrecordIntValue)		},
    { DECLARE_SUBRECORD_PAIR("FLTV", ESMSubrecordFloatValue)	},
};

bool ESMRecordDialogInfo::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
    xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
    assert(writer);

    int res = 0;

    res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
    assert(res != -1);
#endif

    m_recordHeader->DumpToXML();

    // ensure valid input
    if (!input)
        return false;

    // read subrecords that are the same all the time
    size_t totalSize = 0;
    for (auto& subrecord : m_subrecords)
    {
        subrecord->Read(input);

        if (!subrecord->IsValid())
            return false;

        totalSize += subrecord->GetDataSize() + ESMSubrecordHeader::HeaderSize();
    }

    // to be sure that data is correct
    if (m_recordHeader->GetDataSize() == totalSize)
    {
#ifdef DUMP_ESM_TO_XML
        res = xmlTextWriterEndElement(writer);
        assert(res != -1);
#endif
        return false; // invalid case
    }

    // record of this type can have several different records
    do
    {
        std::shared_ptr<ESMSubrecordHeader> subrecordHeader = std::make_unique<ESMSubrecordHeader>();
        bool success = subrecordHeader->Read(input);
        if (!success)
            return false;

        // find correct record creator function
        ESMSubrecordCreator pCreator = nullptr;
        auto it = DialogInfoCreators.find(subrecordHeader->GetSubrecordType().data());
        if (it == DialogInfoCreators.end())
        {
            pCreator = [](std::shared_ptr<ESMSubrecordHeader>& header) { return (ESMSubrecordIface*) new ESMSubrecordUnknown(header); };
        }
        else
        {
            pCreator = it->second;
        }

        // create subrecord instance
        ESMSubrecordIface* pSubrecord = pCreator(subrecordHeader);

        // read subrecord
        success = pSubrecord->Read(input);
        if (!success)
            return false;

        success = pSubrecord->IsValid();
        assert(success);
        if (!success)
            return false;

        m_subrecords.push_back(std::shared_ptr<ESMSubrecordIface>(pSubrecord));

        totalSize += m_subrecords.back()->GetDataSize() + ESMSubrecordHeader::HeaderSize();
    } while (totalSize < m_recordHeader->GetDataSize());
    assert(totalSize == m_recordHeader->GetDataSize());

#ifdef DUMP_ESM_TO_XML
    res = xmlTextWriterEndElement(writer);
    assert(res != -1);
#endif

    return true;
}

unsigned int ESMRecordDialogInfo::UUID(void) const
{
    // it's really weird, but we have completely identical dialog info records. Not sure what to do with them...
    ESMSubrecordDialogResponseId* pId = (ESMSubrecordDialogResponseId*)m_subrecords[0].get();
    assert(pId != nullptr);

    ESMSubrecordDialogResponseIdPrev* pPrevId = (ESMSubrecordDialogResponseIdPrev*)m_subrecords[1].get();
    assert(pPrevId != nullptr);

    ESMSubrecordDialogResponseIdNext* pNextId = (ESMSubrecordDialogResponseIdNext*)m_subrecords[2].get();
    assert(pNextId != nullptr);

    std::string res = pId->Get();
    if (!res.empty() && res.back() == '\0')
        res.pop_back();

    std::string prev = pPrevId->Get();
    if (!prev.empty() && prev.back() == '\0')
        prev.pop_back();
    if (!prev.empty())
        res.append(prev);
    else
        res.append("0");

    std::string next = pNextId->Get();
    if (!next.empty() && next.back() == '\0')
        next.pop_back();
    if (!next.empty())
        res.append(next);
    else
        res.append("0");

    return hashString(res);
   
    /*ESMSubrecordName* pName = nullptr;
    auto it = m_subrecords.begin(); it += 4;
    do {
        pName = dynamic_cast<ESMSubrecordName*>(it->get());
        it++;
    } while ((pName == nullptr) && (it != m_subrecords.end()));

    if (pName != nullptr)
        hash = hashString(pName->Name());

    // kind of sily, but there are different records with identical strings, and Id's that produce the same hash
    unsigned int hash2 = 0;
    ESMSubrecordDialogResponseId* pId = (ESMSubrecordDialogResponseId*)m_subrecords[0].get();
    assert(pId != nullptr);

    ESMSubrecordDialogResponseIdPrev* pPrevId = (ESMSubrecordDialogResponseIdPrev*)m_subrecords[1].get();
    assert(pPrevId != nullptr);
    hash2 = OrderedHash(std::stoull(pId->Get()),
        pPrevId->Get().length() > 1 ? std::stoull(pPrevId->Get()) : 0);

    ESMSubrecordDialogResponseIdNext* pNextId = (ESMSubrecordDialogResponseIdNext*)m_subrecords[2].get();
    assert(pNextId != nullptr);
    hash2 = OrderedHash(hash2, 
        pNextId->Get().length() > 1 ? std::stoull(pNextId->Get()) : 0);

    hash ^= hash2;*/

    //return hash;
}

unsigned int ESMRecordMagicEffect::UUID(void) const
{
    SubrecordIDValue* pIdx = dynamic_cast<SubrecordIDValue*>(m_subrecords[0].get());
    assert(pIdx != nullptr);
    return pIdx->IntValue();
}

