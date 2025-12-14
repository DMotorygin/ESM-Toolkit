
#include "pch.h"
#include "Record.h"
#include "xmlUtils.h"

#include <functional>
#include <map>
#include <assert.h>
#include <string>

ESMRecordGeneral::ESMRecordGeneral(std::unique_ptr<ESMRecordHeader>& recordHeader)
	: ESMRecordCommon(recordHeader)
{}

ESMRecordGeneral::~ESMRecordGeneral()
{}

// subrecords factory
#define DECLARE_SUBRECORD(subrecordType) std::string_view(GetSubrecordShortName<subrecordType>(), 4), ESMSubrecordIface::creator<subrecordType>() 

static CreatorsMap<ESMSubrecordCreator> ESMSubrecordCreators =
{
	{ DECLARE_SUBRECORD(ESMSubrecordClassData)					},
	{ DECLARE_SUBRECORD(ESMSubrecordDataFileInfo)				},
	{ DECLARE_SUBRECORD(ESMSubrecordDescription)				},
	{ DECLARE_SUBRECORD(ESMSubrecordFileHeader)					},
	{ DECLARE_SUBRECORD(ESMSubrecordFloatValue)					},
	{ DECLARE_SUBRECORD(ESMSubrecordFriendlyName)				},
	{ DECLARE_SUBRECORD(ESMSubrecordIntValue)					},
	{ DECLARE_SUBRECORD(ESMSubrecordMasterFile)					},
	{ DECLARE_SUBRECORD(ESMSubrecordName)						},
	{ DECLARE_SUBRECORD(ESMSubrecordStringValue)				},
	{ DECLARE_SUBRECORD(ESMSubrecordRankOrRaceName)				},
	{ DECLARE_SUBRECORD(ESMSubrecordFactionData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordFactionStringValue)			},
	{ DECLARE_SUBRECORD(ESMSubrecordSpecialAbilityStringValue)	},
	{ DECLARE_SUBRECORD(ESMSubrecordRaceData)					},
	{ DECLARE_SUBRECORD(SubrecordIDValue)						},
	{ DECLARE_SUBRECORD(ESMSubrecordSkillData)					},
	{ DECLARE_SUBRECORD(ESMSubrecordMagicEffectData)			},
	{ DECLARE_SUBRECORD(ESMSubrecordEffectIconStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordParticleTextureStringValue) },
	{ DECLARE_SUBRECORD(ESMSubrecordCastEffectStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordBoltEffectStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordHitEffectStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordAreaEffectStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordCastSoundStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordBoltSoundStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordHitSoundStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordAreaSoundStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordScriptHeader)				},
	{ DECLARE_SUBRECORD(ESMSubrecordScriptVariables)			},
	{ DECLARE_SUBRECORD(ESMSubrecordScriptTextValue)			},
	{ DECLARE_SUBRECORD(ESMSubrecordCompiledScript)				},
	{ DECLARE_SUBRECORD(ESMSubrecordWeatherData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordRegionStringValue)			},
	{ DECLARE_SUBRECORD(ESMSubrecordTextureFilename)			},
	{ DECLARE_SUBRECORD(ESMSubrecordModelFilename)				},
	{ DECLARE_SUBRECORD(ESMSubrecordSoundName)					},
	{ DECLARE_SUBRECORD(ESMSubrecordMiscWeaponData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordWeaponData)					},
	{ DECLARE_SUBRECORD(ESMSubrecordContainerData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordFlags)						},
	{ DECLARE_SUBRECORD(ESMSubrecordSpellData)					},
	{ DECLARE_SUBRECORD(ESMSubrecordEnchantmentStringValue)		},
	{ DECLARE_SUBRECORD(ESMSubrecordCreatureData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordCreatureScript)				},
	{ DECLARE_SUBRECORD(ESMSubrecordItemRecord)					},
	{ DECLARE_SUBRECORD(ESMSubrecordCreatureAIData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordAIWander)					},
	{ DECLARE_SUBRECORD(ESMSubrecordAITravel)					},
	{ DECLARE_SUBRECORD(ESMSubrecordCreatureScale)				},
	{ DECLARE_SUBRECORD(ESMSubrecordBodyPartData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordLightData)					},
	{ DECLARE_SUBRECORD(ESMSubrecordScriptName)					},
	{ DECLARE_SUBRECORD(ESMSubrecordEnchantmentData)			},
	{ DECLARE_SUBRECORD(ESMSubrecordCName)						},
	{ DECLARE_SUBRECORD(ESMSubrecordAIFollow)					},
	{ DECLARE_SUBRECORD(ESMSubrecordAIActivate)					},
	{ DECLARE_SUBRECORD(ESMSubrecordAIEscort)					},
	{ DECLARE_SUBRECORD(ESMSubrecordCellTravelDestination)		},
	{ DECLARE_SUBRECORD(ESMSubrecordArmourData)					},
	{ DECLARE_SUBRECORD(ESMSubrecordClothingData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordRepairItemData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordAlchemyApparatusData)		},
	{ DECLARE_SUBRECORD(ESMSubrecordLockpickData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordProbeData)					},
	{ DECLARE_SUBRECORD(ESMSubrecordIngrediantData)				},
	{ DECLARE_SUBRECORD(ESMSubrecordBookData)					},
	{ DECLARE_SUBRECORD(ESMSubrecordTextValue)					},
};

bool ESMRecordGeneral::Read(std::ifstream& input)
{
#ifdef DUMP_ESM_TO_XML
	xmlTextWriterPtr writer = XMLWriterWrapper::GetXMLWriter();
	assert(writer);

	int res = 0;

	res = xmlTextWriterStartElement(writer, BAD_CAST "Record");
	assert(res != -1);
#endif

	m_recordHeader->DumpToXML();

	// ensure valid input stream
    // - somehow, with the last record it has header with invalid code and file ends after it
    // - so we need to handle the case when header is read but then file ends
    if (!input.eof()) 
    {

        // read record data
#ifdef READ_RAW_DATA
        m_dataSize = m_recordHeader->GetDataSize();
        m_data.resize(m_dataSize);
        input.read(m_data.data(), m_dataSize);
        if ((input.rdstate() & std::ifstream::failbit) != 0)
            return false;
#else
    // read subrecords
        size_t totalRead = 0;
        size_t sizeFromHeader = m_recordHeader->GetDataSize();
        while (totalRead < sizeFromHeader)
        {
            bool success = false;

            // read subrecord header
            std::shared_ptr<ESMSubrecordHeader> header = std::make_shared<ESMSubrecordHeader>();
            success = header->Read(input);
            assert(success);
            if (!success)
                return false;

            // find correct record creator function
            ESMSubrecordCreator pCreator = nullptr;
            auto it = ESMSubrecordCreators.find(header->GetSubrecordType().data());
            if (it == ESMSubrecordCreators.end())
            {
                pCreator = [](std::shared_ptr<ESMSubrecordHeader>& header) { return (ESMSubrecordIface*) new ESMSubrecordUnknown(header); };
            }
            else
            {
                pCreator = it->second;
            }

            // create subrecord instance
            ESMSubrecordIface* pSubrecord = pCreator(header);

            // read subrecord
            success = pSubrecord->Read(input);
            assert(success);
            if (!success)
                return false;

            success = pSubrecord->IsValid();
            if (!success)
            {
                return false;
            }

            m_subrecords.push_back(std::shared_ptr<ESMSubrecordIface>(pSubrecord));

            totalRead += pSubrecord->GetDataSize();
            totalRead += ESMSubrecordHeader::HeaderSize();
        }
        assert(totalRead == sizeFromHeader);
#endif

#ifdef DUMP_ESM_TO_XML
        res = xmlTextWriterEndElement(writer);
        assert(res != -1);
#endif
    }

	return true;
}

void ESMRecordGeneral::Write(std::ostream& input)
{
	// NIY
}

bool ESMRecordGeneral::IsValid(void) const
{
	bool areSubrecordsValid = ESMRecordCommon::IsValid();
	return areSubrecordsValid;
}

