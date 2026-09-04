#pragma once
#include <string>
#include <map>

#include "RouteResult.h"
#include "StationEdge.h"

class SubwayPathFinder
{
private:
    // 실제 지하철 연결 정보
    std::map<std::string, std::vector<StationEdge>> stationGraph;
    // 환승 페널티
    // 초단위로 작성
    const int transferTimeSec = 180;

    //===============================================================================
    // 함수
    //===============================================================================
    // 경로 탐색에 필요한 최소시간과 데이터 초기화
    void InitPathSearchData(std::map<std::string, int>& subwayTimeData, std::map<std::string, bool>& visitedStation);
    // 최소 시간 방문 갱신 함수
    void FindMinTimeStation(std::map<std::string, int>& subwayTimeData, std::map<std::string, bool>& visitedStation, int& minTime, std::string& currentStationName);
    // 연결된 역들 갱신 함수
    void UpdateConnectedStations(const std::string& currentStationName, const std::string& startStation, std::map<std::string, int>& subwayTimeData, std::map<std::string, std::string>& prevStations, std::map<std::string, int>& prevLine);
    // 경로 복원 함수
    void FindRouteStation(const std::string& startStation, const std::string& endStation, RouteResult& result, std::map<std::string, std::string>& prevStations);
    // 환승역 찾기
    void FindTransformStation(RouteResult& result, std::map<std::string, int>& prevLine);
public:
    // 생성자
    SubwayPathFinder(const std::map<std::string, std::vector<StationEdge>>& graph);
    // 다익스트라 알고리즘 이용
    RouteResult FindShortRoute(const std::string& startStation, const std::string& endStation);
};

