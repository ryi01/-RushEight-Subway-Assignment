#include "SubwayDataManager.h"
#include "SubwayCSVLoader.h"
#include <queue>

#pragma region 초기화
bool SubwayDataManager::InitializeSubwayData()
{   
    // CSVLoaer 객체 생성 및 CSV 읽어오기
    SubwayCSVLoader loader;
    subwayDataList = loader.LoadCSV("Data/SubwayData.csv");
    if(subwayDataList.empty()) return false;

    BuildBFSData();

    return true;
}
void SubwayDataManager::BuildBFSData()
{
    for (const SubwayData& data : subwayDataList)
    {
        // BFS용 데이터 생성
        // from → to 등록
        StationConnectionData fromConnect;
        fromConnect.stationName = data.toStationName;
        fromConnect.line = data.line;
        fromConnect.timeToSec = data.timeToSec;

        // 벡터 등록
        stationConnectionDataMap[data.fromStationName].push_back(fromConnect);

        // to → from 등록
        StationConnectionData toConnect;
        toConnect.stationName = data.fromStationName;
        toConnect.line = data.line;
        toConnect.timeToSec = data.timeToSec;

        // 벡터 등록
        stationConnectionDataMap[data.toStationName].push_back(toConnect);
    }
}
#pragma endregion
// 데이터 조회
bool SubwayDataManager::HasStation(const std::string& station)
{
    for (const SubwayData& data : subwayDataList)
    {
        if (data.fromStationName == station || data.toStationName == station) return true;
    }
    return false;
}

PathResult SubwayDataManager::FindPathBFS(const std::string& startStation, const std::string& endStation)
{
    // 반환 결과
    PathResult bfsResult;
    bfsResult.totalTime = 0;
    bfsResult.route.clear();

    // 탐색할 역 모음
    std::queue<std::string> stationQueue;
    // 출발지부터 얼마나 걸리는지
    std::map<std::string, int> travelTimes;
    // 이전 루트
    std::map<std::string, std::string> prevStations;
    // 호선 확인
    std::map<std::string, int> prevLines;

    // 출발지를 큐에 넣기
    stationQueue.push(startStation);
    // 거리 설정
    travelTimes[startStation] = 0;
    // 큐가 빌때까지 반복 
    while (!stationQueue.empty())
    {
        std::string currentStation = stationQueue.front();
        stationQueue.pop();
        // 목적지 확인
        if (currentStation == endStation)
        {
            // 결과를 저장해서 반환
            bfsResult.totalTime = travelTimes[currentStation];
            // 경로 복원
            std::string routeStation = endStation;
            // 출발지가 아닐때
            while (routeStation != startStation)
            {
                // 루트를 거슬러가며 추가
                bfsResult.route.push_back(routeStation);
                routeStation = prevStations[routeStation];
            }
            bfsResult.route.push_back(startStation);
            // 역순으로 저장되어있기에 복구
            std::reverse(bfsResult.route.begin(), bfsResult.route.end());
            // 호선 확인
            for (int i = 1; i < bfsResult.route.size() - 1; i++)
            {
                // 현재 역과 다음역 호선 비교
                std::string station = bfsResult.route[i];
                std::string nextStation = bfsResult.route[i + 1];
                // 호선이 다르면 현재역이 환승지역
                if(prevLines[station] != prevLines[nextStation])bfsResult.transferStations.push_back(station);
            }
            return bfsResult;
        }
        // map을 순회하며 다음 역을 확인
        for (const StationConnectionData& nextStation : stationConnectionDataMap[currentStation])
        {
            // 이미 있는 역이라면 제외
            if(travelTimes.find(nextStation.stationName) != travelTimes.end()) continue;
            // 새로 등록하고 시간을 업데이트
            travelTimes[nextStation.stationName] = travelTimes[currentStation] + nextStation.timeToSec;
           
            stationQueue.push(nextStation.stationName);
            // 이전 역 저장
            prevStations[nextStation.stationName] = currentStation;
            prevLines[nextStation.stationName] = nextStation.line;
        }
    }

    return bfsResult;
}


