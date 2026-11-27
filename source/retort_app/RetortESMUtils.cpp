
#include "RetortESMUtils.h"
#include "Record.h"
#include "Reader.h"
#include "Utils.h"

#include <windows.h>
#include <objidl.h>
#include <shellapi.h>
#include <gdiplus.h>
#include <commctrl.h>

#include <map>
#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>
#include <cwctype>

using namespace Gdiplus;

#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Gdiplus.lib")

void BuildItems(const RecordsCollection& records_map, std::vector<MagicEffectItem>& items)
{
    using Map = std::map<unsigned int, std::unique_ptr<ESMRecordMagicEffect>>;
    auto& records = std::get<Map>(records_map);

    for (auto& record : records)
    {
        const ESMRecordMagicEffect* pMGEF = record.second.get();

        ESMSubrecordDescription* pDesc =
            (ESMSubrecordDescription*)pMGEF->Subrecords().back().get();
        std::string mgefDesc = pDesc->Get();
        std::wstring description(mgefDesc.begin(), mgefDesc.end());

        SubrecordIDValue* pID = (SubrecordIDValue*)pMGEF->Subrecords()[0].get();
        std::wstring id = std::to_wstring(pID->IntValue());

        ESMSubrecordEffectIconStringValue* pIconString =
            (ESMSubrecordEffectIconStringValue*)pMGEF->Subrecords()[2].get();
        std::string iconName = pIconString->Get();
        std::wstring icon(iconName.begin(), iconName.end());
        icon.erase(0, 7);
        icon.erase(icon.length() - 5);
        std::wstring name = icon;
        std::transform(name.begin(), name.end(), name.begin(),
            [](wchar_t c) { return std::towlower(c); });
        icon.insert(0, L"b_tx_s_");
        icon += L".png";
        std::filesystem::path iconPath =
            GetExecutableDirectory() / L"PNG" / icon;
        icon = iconPath;

        items.emplace_back(MagicEffectItem{ name, description, id, icon });
    }
}

int ReadESM(RecordsCollection& records_map)
{
    // parse input
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv == nullptr || argc < 2)
        return 1;

    std::wstring widePath(argv[1]);
    std::string filepath(widePath.begin(), widePath.end());

    LocalFree(argv);

    // read esm
    bool success = ReadBinESMToMap(filepath, records_map);
    assert(success);
    if (!success)
        return 1;

    return 0;
}

int GetImageIndex(const std::wstring& imagePath, 
    HIMAGELIST hImageList,
    std::unordered_map<std::wstring, int>& imageCache)
{
    // Already loaded?
    auto it = imageCache.find(imagePath);

    if (it != imageCache.end())
        return it->second;

    // Load image
    Bitmap bitmap(imagePath.c_str());

    if (bitmap.GetLastStatus() != Ok)
        return -1;

    HBITMAP hBitmap = nullptr;

    if (bitmap.GetHBITMAP(Color(0, 0, 0, 0), &hBitmap) != Ok)
        return -1;

    int imageIndex = ImageList_Add(
        hImageList,
        hBitmap,
        nullptr
    );

    DeleteObject(hBitmap);

    if (imageIndex >= 0)
        imageCache.emplace(imagePath, imageIndex);

    return imageIndex;
}

