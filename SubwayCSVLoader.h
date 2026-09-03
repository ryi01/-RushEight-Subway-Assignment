#pragma once
#include <string>
#include <vector>
#include "SubwayData.h"


// CSV 로드를 위한 클래스
class SubwayCSVLoader
{
private:
    // CSV에 있는 소요시간으로 초로 변환 함수
    int ParseTimeSec(const std::string& timeText);
public:
    // CSV파일을 로드해 SubwayData로 변환
    std::vector<SubwayData> LoadCSV(const std::string& filePath);
};

