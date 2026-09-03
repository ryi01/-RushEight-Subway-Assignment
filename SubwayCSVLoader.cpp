#include "SubwayCSVLoader.h"

#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "StringUtil.h"

#pragma region public 함수
std::vector<SubwayData> SubwayCSVLoader::LoadCSV(const std::string& filePath)
{
    // 반환할 SubwayDataList
    std::vector<SubwayData> subwayDataList;
    // 파일 경로로 파일 읽기
    std::ifstream file(filePath);
    // 파일 읽기 실패
    if (!file.is_open())
    {
        std::cout << "CSV 파일을 찾을 수 없습니다." << std::endl;
        return subwayDataList;
    }

    std::string line;
    std::getline(file, line);
    // csv 내부 파일 읽기
    while (std::getline(file, line))
    {
        // 한 줄을 stringstream에 담음
        std::stringstream ss(line);

        // 한 줄을 분해해서 구조체에 담을 공간
        std::string lineText;
        std::string fromStationText;
        std::string toStationText;
        std::string timeText;
        // 한줄 분리
        std::getline(ss, lineText, ',');
        std::getline(ss, fromStationText, ',');
        std::getline(ss, toStationText, ',');
        std::getline(ss, timeText, ',');
        // 문자열 공백 제거를 위한 stringUtil 객체
        StringUtil util;
        // subway 구조체
        SubwayData data;
        data.line = std::stoi(lineText);
        data.fromStationName = util.RemoveSpace(fromStationText);
        data.toStationName = util.RemoveSpace(toStationText);
        data.timeToSec = ParseTimeSec(timeText);

        // 벡터에 추가
        subwayDataList.push_back(data);
    }
    return subwayDataList;
}
#pragma endregion

#pragma region 초로 변경 함수
int SubwayCSVLoader::ParseTimeSec(const std::string& timeText)
{
    // 분과 초를 찾아서 int로 변환
    // 계산해서 반환할 초
    int totalTime = 0;
    // 원본 문자열 복사 => 원본 훼손 X
    std::string result = timeText;
    // 분 위치  찾기
    size_t minPos = result.find("분");
    // 분을 찾으면
    if (minPos != std::string::npos)
    {
        // 분에 해당되는 수를 추출
        std::string minText = result.substr(0, minPos);
        // 분계산
        int min = std::stoi(minText) * 60;
        totalTime += min;
        // 문자열 제거
        result = result.erase(minPos + std::string("분").size());
    }
    // 초 위치 찾기
    size_t secPos = result.find("초");
    // 초를 찾으면
    if (secPos != std::string::npos)
    {
        // 초에 해당되는 수(텍스트) 추출
        std::string secText = result.substr(0, secPos);
        // int로 변환해서 넣기
        totalTime += std::stoi(secText);
    }
    
    return totalTime;
}
#pragma endregion


