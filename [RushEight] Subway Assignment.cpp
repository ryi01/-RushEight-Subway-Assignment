#include <iostream>
#include <Windows.h>

#include "StringUtil.h"
#include "SubwayDataManager.h"
#include "SubwayPathFinder.h"

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
void OutputRoute(const RouteResult& result)
{
    std::cout << "이동 경로 : ";
    for (int i = 0; i < result.route.size(); i++)
    {
        std::string text = result.route[i];
        std::cout << text;
        // result 내에 있는 환승역을 확인 
        if(std::find(result.transferStations.begin(), result.transferStations.end(), text) != result.transferStations.end()) std::cout << "(환승)";
        if(i < result.route.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}
void OutputTime(const RouteResult& result)
{
    std::cout << "총 소요 시간 : " << result.totalTime / 60 << "분 " << result.totalTime % 60 << "초" << std::endl;
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
    // 출발역 -> 도착역 출력
    std::cout << "[탐색 결과] , " << startStation << " -> " << endStation << "\n";
    // 이동 경로 출력
    RouteResult result = pathFinder.FindShortRoute(startStation, endStation);
    OutputRoute(result);
    OutputTime(result);
#pragma endregion

    return 0;
}


