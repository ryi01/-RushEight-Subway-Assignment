#include <iostream>
#include <Windows.h>

#include "StringUtil.h"
#include "SubwayDataManager.h"

int main()
{
    // 콘솔 설정 -> UTF_8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 데이터 매니저 생성
    SubwayDataManager dataManager;
    if(!dataManager.InitializeSubwayData()) return -1;

    return 0;
}


