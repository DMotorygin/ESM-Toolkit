#pragma once

#include "Retort.h"
#include "Record.h"

#include <windows.h>
#include <commctrl.h>

void BuildItems(const RecordsCollection& records_map, std::vector<MagicEffectItem>& items);

int ReadESM(RecordsCollection& records_map);

int GetImageIndex(const std::wstring& imagePath, HIMAGELIST hImageList, std::unordered_map<std::wstring, int>& imageCache);
