#include "StringUtil.h"

std::string StringUtil::RemoveSpace(const std::string& text)
{
    // 원본 복사해서 담음
    std::string result = text;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}
