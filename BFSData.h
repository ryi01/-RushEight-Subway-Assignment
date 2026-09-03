#pragma once
#include <string>
#include <vector>

struct StationConnectionData
{
    // 연결되는 역
    std::string stationName;
    // 호선
    int line;
    // 시간
    int timeToSec;
};

// BFS 결과값
struct PathResult
{
    // 총 소요시간
    int totalTime;
    // 루트
    std::vector<std::string> route;
    // 환승역
    std::vector<std::string> transferStations;
};