
#include "pch.h"
#include "Record.h"
#include "xmlUtils.h"

#include <functional>
#include <map>
#include <assert.h>

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
