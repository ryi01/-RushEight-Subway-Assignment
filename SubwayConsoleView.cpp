#include "SubwayConsoleView.h"
#include <iostream>

void SubwayConsoleView::OutputSearchResult(const std::string& startStation, const std::string& endStation)
{
    // 출발역 -> 도착역 출력
    std::cout << "[탐색 결과] , " << startStation << " -> " << endStation << "\n";
}

void SubwayConsoleView::OutputRoute(const RouteResult& result)
{
    std::cout << "이동 경로 : ";
    for (int i = 0; i < result.route.size(); i++)
    {
        std::string text = result.route[i];
        std::cout << text;
        // result 내에 있는 환승역을 확인 
        if (std::find(result.transferStations.begin(), result.transferStations.end(), text) != result.transferStations.end()) std::cout << "(환승)";
        if (i < result.route.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}

void SubwayConsoleView::OutputTime(const RouteResult& result)
{
    std::cout << "총 소요 시간 : " << result.totalTime / 60 << "분 " << result.totalTime % 60 << "초" << std::endl;
}
