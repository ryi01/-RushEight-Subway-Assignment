#pragma once
#include <vector>
#include "SubwayData.h"

// CSV 파일에 있는 데이터 관리
class SubwayDataManager
{
private:
    // 전체 데이터 보관
    std::vector<SubwayData> subwayDataList;

public:
    // CSV 데이터 초기화 및 전체데이터 보관
    bool InitializeSubwayData();
    // 특정 역 데이터 조회
    bool HasStation(const std::string& station);
    
};

