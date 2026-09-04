#include <iostream>
#include <Windows.h>

#include "StringUtil.h"
#include "SubwayDataManager.h"
#include "SubwayPathFinder.h"
#include "SubwayConsoleView.h"

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
int main()
{
    // 콘솔 설정 -> UTF_8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 데이터 매니저 생성
    SubwayDataManager dataManager;
    if(!dataManager.InitializeSubwayData()) return -1;
    // 경로 찾는 객체 생성
    SubwayPathFinder pathFinder(dataManager.GetStationGraph());

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

    // 이동 경로 출력
    RouteResult result = pathFinder.FindShortRoute(startStation, endStation);
    // 출력을 위한 객체 생성
    SubwayConsoleView view;
    // 탐색 결과 출력
    view.OutputSearchResult(startStation, endStation);
    // 경로 출력
    view.OutputRoute(result);
    // 총 소요시간 출력
    view.OutputTime(result);
#pragma endregion

    return 0;
}


