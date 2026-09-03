#pragma once
#include <vector>
#include <string>

// 최종 결과를 메인에 넘기는 구조체
struct RouteResult
{
    // 최종 시간
    int totalTime;
    // 최종 이동 경로
    std::vector<std::string> route;
    // 환승 구역
    std::vector<std::string> transferStations;
};