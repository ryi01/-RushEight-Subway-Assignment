#pragma once
#include <string>

struct StationEdge
{
    // 이어지는 역 이름
    std::string stationName;
    // 호선
    int line;
    // 걸리는 시간
    int timeToSec;
};