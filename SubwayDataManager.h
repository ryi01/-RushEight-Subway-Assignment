#pragma once
#include <vector>
#include <map>

#include "SubwayData.h"
#include "BFSData.h"

// CSV 파일에 있는 데이터 관리
class SubwayDataManager
{
private:
    // 전체 데이터 보관
    std::vector<SubwayData> subwayDataList;

    // BFS용 연결 데이터
    std::map<std::string, std::vector<StationConnectionData>> stationConnectionDataMap;

    // BFS 데이터 셋팅
    void BuildBFSData();

public:
    // CSV 데이터 초기화 및 전체데이터 보관
    bool InitializeSubwayData();
    // 특정 역 데이터 조회
    bool HasStation(const std::string& station);
    // BFS 확인
    PathResult FindPathBFS(const std::string& startStation, const std::string& endStation);
    
};

