#pragma once

#include "resource.h"

#include <string>

struct MagicEffectItem
{
    const std::wstring name;
    const std::wstring description;
    const std::wstring id;
    const std::wstring icon;
};

struct IngedientsItem
{
    const std::wstring name;
    const std::wstring id;
    const std::wstring icon;
    int effectId[4];
    int attrId[4]; 
    // technically need another one for skill ID, 
    // but there are no alchemical ingredients that affect skills
};
