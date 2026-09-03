#pragma once
#include <string>

// CSV 파일에서 파싱할 구조체
struct SubwayData
{
    // 라인
    int line;

    // 출발지
    std::string toStationName;

    // 도착지
    std::string fromStationName;

    // 시간 => 초로 저장
    int timeToSec;
};