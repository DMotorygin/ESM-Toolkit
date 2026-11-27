#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <filesystem>


inline std::filesystem::path GetExecutableDirectory()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);

    return std::filesystem::path(buffer).parent_path();
}


inline bool ContainsIgnoreCase(
    const std::wstring& text,
    const std::wstring& filter)
{
    std::wstring a = text;
    std::wstring b = filter;

    std::transform(a.begin(), a.end(), a.begin(), towlower);
    std::transform(b.begin(), b.end(), b.begin(), towlower);

    return a.find(b) != std::wstring::npos;
}

