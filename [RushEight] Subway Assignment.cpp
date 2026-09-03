#include <iostream>
#include <Windows.h>

#include "StringUtil.h"
#include "SubwayDataManager.h"

#pragma region 입력 관련
std::string InputStation(SubwayDataManager& manager, const std::string& message)
{
    // 공백 제거용 객체
    StringUtil util;
    // 반환할 문자열
    std::string result;

    while (true)
    {
        std::cout << message;
        std::getline(std::cin, result);

        result = util.RemoveSpace(result);
        if (!manager.HasStation(result))
        {
            std::cout << "존재하지 않는 역입니다. 다시 입력해주세요." << std::endl;
            continue;
        }
        break;
    }

    return result;
}
#pragma endregion

#pragma region 출력 관련

#pragma endregion

int main()
{
    // 콘솔 설정 -> UTF_8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 데이터 매니저 생성
    SubwayDataManager dataManager;
    if(!dataManager.InitializeSubwayData()) return -1;

#pragma region 입력 관련
    std::string startStation;
    std::string endStation;

    while (true)
    {
        startStation = InputStation(dataManager, "출발 역 : ");
        endStation = InputStation(dataManager, "도착 역 : ");

        if (startStation == endStation)
        {
            std::cout << "출발역과 도착역이 같습니다. 다시 입력해주세요." << std::endl;
            continue;
        }
        break;
    }
#pragma endregion

#pragma region 출력 관련
    // 출발역 -> 도착역 출력
    std::cout << "[탐색 결과] , " << startStation << " -> " << endStation << "\n";
    // 이동 경로 출력
#pragma endregion


    return 0;
}


