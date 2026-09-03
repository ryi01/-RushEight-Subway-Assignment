#include "SubwayDataManager.h"
#include "SubwayCSVLoader.h"

#pragma region 초기화
bool SubwayDataManager::InitializeSubwayData()
{   
    // CSVLoaer 객체 생성 및 CSV 읽어오기
    SubwayCSVLoader loader;
    subwayDataList = loader.LoadCSV("Data/SubwayData.csv");
    if(subwayDataList.empty()) return false;

    return true;
}
bool SubwayDataManager::HasStation(const std::string& station)
{
    for (const SubwayData& data : subwayDataList)
    {
        if(data.fromStationName == station || data.toStationName == station) return true;
    }
    return false;
}
#pragma endregion

