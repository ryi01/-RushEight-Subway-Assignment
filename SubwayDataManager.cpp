#include "SubwayDataManager.h"
#include "SubwayCSVLoader.h"

#include <queue>

#pragma region 초기화
bool SubwayDataManager::InitializeSubwayData()
{
    // CSVLoaer 객체 생성 및 CSV 읽어오기
    SubwayCSVLoader loader;
    subwayDataList = loader.LoadCSV("Data/SubwayData.csv");
    if (subwayDataList.empty()) return false;

    // 그래프 생성
    BuildGraph();

    return true;
}
void SubwayDataManager::BuildGraph()
{
    stationGraph.clear();
    for (const SubwayData& data : subwayDataList)
    {
        // from → to 등록
        StationEdge fromConnect;
        fromConnect.stationName = data.toStationName;
        fromConnect.line = data.line;
        fromConnect.timeToSec = data.timeToSec;

        // 벡터 등록
        stationGraph[data.fromStationName].push_back(fromConnect);

        // to → from 등록
        StationEdge toConnect;
        toConnect.stationName = data.fromStationName;
        toConnect.line = data.line;
        toConnect.timeToSec = data.timeToSec;

        // 벡터 등록
        stationGraph[data.toStationName].push_back(toConnect);
    }
}
#pragma endregion

// 데이터 조회
bool SubwayDataManager::HasStation(const std::string& station)
{
    return stationGraph.find(station) != stationGraph.end();
}
// 그래프 getter함수
const std::map<std::string, std::vector<StationEdge>>& SubwayDataManager::GetStationGraph() const
{
    return stationGraph;
}






