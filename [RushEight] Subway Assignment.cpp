#include <iostream>
#include <Windows.h>

#include "StringUtil.h"
#include "SubwayCSVLoader.h"

int main()
{
    // 콘솔 설정 -> UTF_8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SubwayCSVLoader loader;
    // CSV 파일을 읽고 데이터 목록 가져오기
    std::vector<SubwayData> subwayDataList = loader.LoadCSV("Data/SubwayData.csv");

    std::cout << "로드된 데이터 개수 : " << subwayDataList.size() << std::endl;
}


