#include "SubwayPathFinder.h"


SubwayPathFinder::SubwayPathFinder(const std::map<std::string, std::vector<StationEdge>>& graph) : stationGraph(graph)
{
}

// 다익스트라 알고리즘을 통해 가중치에 따른 최소 경로 찾기
RouteResult SubwayPathFinder::FindShortRoute(const std::string& startStation, const std::string& endStation)
{
#pragma region 변수 선언
    // 최종 반환 구조체
    RouteResult result;
    // 역 별 최소 소요 시간을 담을 map
    std::map<std::string, int> subwayTimeData;
    // 방문 여부를 확인하기 위한 map
    std::map<std::string, bool> visitedStation;

    // 이전 위치 저장
    std::map<std::string, std::string> prevStations;
    // 이전 호선
    std::map<std::string, int> prevLine;
#pragma endregion

    InitData(subwayTimeData, visitedStation);

    // 출발지를 확인하고 소요시간을 0으로 변경
    subwayTimeData[startStation] = 0;

    // 현재 위치 및 최소 시간
    std::string currentStationName;
    int minTime;

    for (int i = 0; i < stationGraph.size(); i++)
    {
        currentStationName.clear();
        // 최소 시간
        minTime = std::numeric_limits<int>::max();

        FindMinTimeStation(subwayTimeData, visitedStation, minTime, currentStationName);

        // 탐색할 수 있는 역이 없는 경우
        if (currentStationName.empty()) break;
        // 방문 처리
        visitedStation[currentStationName] = true;
        // 목적지인 경우
        if (currentStationName == endStation) break;

        UpdateConnectedStations(currentStationName, startStation, subwayTimeData, prevStations, prevLine);
    }

    FindRouteStation(startStation, endStation, result, prevStations);
    FindTransformStation(result, prevLine);

    // 최종 시간 대입
    result.totalTime = subwayTimeData[endStation];
    return result;
}

// 데이터 초기화 함수

void SubwayPathFinder::InitData(std::map<std::string, int>& subwayTimeData, std::map<std::string, bool>& visitedStation)
{
    // 전체 map을 INF로 초기화
    for (const auto& data : stationGraph)
    {
        subwayTimeData[data.first] = std::numeric_limits<int>::max();
        visitedStation[data.first] = false;
    }
}
// 최소 시간 방문 갱신 함수
void SubwayPathFinder::FindMinTimeStation(std::map<std::string, int>& subwayTimeData, std::map<std::string, bool>& visitedStation, int& minTime, std::string& currentStationName)
{
    for (const auto& data : stationGraph)
    {
        // 방문했던 곳이라면 패스
        if (visitedStation[data.first]) continue;
        // 현재역의 시간이 저장된 시간 보다 작다면
        if (subwayTimeData[data.first] < minTime)
        {
            // 최소시간을 갱신
            minTime = subwayTimeData[data.first];
            currentStationName = data.first;
        }
    }
}
// 연결된 역들 갱신 함수
void SubwayPathFinder::UpdateConnectedStations(const std::string& currentStationName, const std::string& startStation, std::map<std::string, int>& subwayTimeData, std::map<std::string, std::string>& prevStations, std::map<std::string, int>& prevLine)
{
    // 연결된 역 시간 갱신
    for (const StationEdge& edge : stationGraph.at(currentStationName))
    {
        // 다음 역까지의 시간 계산
        int time = subwayTimeData[currentStationName] + edge.timeToSec;

        // 출발지가 아니고 기존 호선과 다음 호선이 다르면 환승시간 추가
        if (currentStationName != startStation && prevLine[currentStationName] != edge.line) time += (3 * 60);

        // 원래 시간과 계산된 시간 비교
        if (time < subwayTimeData[edge.stationName])
        {
            // 다음역의 최소시간 갱신
            subwayTimeData[edge.stationName] = time;

            // 현재 위치 저장
            prevStations[edge.stationName] = currentStationName;

            // 현재 호선 저장
            prevLine[edge.stationName] = edge.line;
        }
    }
}
// 경로 복원 함수
void SubwayPathFinder::FindRouteStation(const std::string& startStation, const std::string& endStation, RouteResult& result, std::map<std::string, std::string>& prevStations)
{
    // 경로 복원
    std::string routeStation = endStation;
    // 출발지가 아니라면 
    while (routeStation != startStation)
    {
        // 경로 추가
        result.route.push_back(routeStation);
        routeStation = prevStations[routeStation];
    }
    // 출발지 추가
    result.route.push_back(startStation);
    // 도착 -> 출발 경로를 반대로 
    std::reverse(result.route.begin(), result.route.end());
}
// 환승역 찾기
void SubwayPathFinder::FindTransformStation(RouteResult& result, std::map<std::string, int>& prevLine)
{
    // 환승역 찾기
    for (int i = 1; i < result.route.size() - 1; i++)
    {
        // 현재 역 이름
        std::string station = result.route[i];
        // 다음 역이름
        std::string nextStation = result.route[i + 1];
        // 현재역과 다음역의 호선을 비교
        if (prevLine[station] != prevLine[nextStation])result.transferStations.push_back(station);
    }

}
