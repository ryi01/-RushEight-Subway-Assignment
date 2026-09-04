#pragma once
#include "RouteResult.h"

// MVC
class SubwayConsoleView
{
public:
    void OutputSearchResult(const std::string& startStation, const std::string& endStation);
    void OutputRoute(const RouteResult& result);
    void OutputTime(const RouteResult& result);
};

