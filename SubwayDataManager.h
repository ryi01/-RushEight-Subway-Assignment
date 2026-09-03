#pragma once
#include <vector>
#include <map>

#include "SubwayData.h"
#include "StationEdge.h"
#include "RouteResult.h"

// CSV 파일에 있는 데이터 관리
class SubwayDataManager
{
private:
    // 전체 데이터 보관
    std::vector<SubwayData> subwayDataList;
    // CSV 기반 그래프
    std::map<std::string, std::vector<StationEdge>> stationGraph;

    void BuildGraph();
public:
    // CSV 데이터 초기화 및 전체데이터 보관
    bool InitializeSubwayData();
    // 특정 역 데이터 조회
    bool HasStation(const std::string& station);
    // 그래프 getter
    const std::map<std::string, std::vector<StationEdge>>& GetStationGraph() const;


};

