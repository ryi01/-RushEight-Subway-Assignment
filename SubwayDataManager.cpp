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
#pragma endregion

