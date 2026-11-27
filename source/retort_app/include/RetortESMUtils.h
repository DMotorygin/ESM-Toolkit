#pragma once

#include "Retort.h"
#include "Record.h"

void BuildItems(const RecordsCollection& records_map, std::vector<MagicEffectItem>& items);

int ReadESM(RecordsCollection& records_map);
