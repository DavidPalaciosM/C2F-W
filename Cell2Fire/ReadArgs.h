#ifndef READARGS
#define READARGS

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
/*
 *   Args structure
 */
typedef struct
{
    std::string InFolder, OutFolder, WeatherOpt, HarvestPlan, Simulator;
    bool OutMessages, OutFl, OutIntensity, OutRos, OutCrown, OutCrownConsumption, OutSurfConsumption, Trajectories,
        NoOutput, verbose, IgnitionsLog, Ignitions, OutputGrids, FinalGrid, PromTuned, Stats, BBOTuning, AllowCROS, Co2eq;;
    float ROSCV, ROSThreshold, CROSThreshold, HFIThreshold, HFactor, FFactor, BFactor, EFactor, FirePeriodLen;
    float CBDFactor, CCFFactor, ROS10Factor, CROSActThreshold;
    int MinutesPerWP, MaxFirePeriods, TotalYears, TotalSims, NWeatherFiles, IgnitionRadius, seed, nthreads, FMC,
        scenario;
    std::unordered_set<int> HCells, BCells;
} arguments;

char* getCmdOption(char** begin, char** end, const std::string& option);

bool cmdOptionExists(char** begin, char** end, const std::string& option);

void parseArgs(int argc, char* argv[], arguments* args_ptr);

void printArgs(arguments args);

int countWeathers(std::string directory_path);

#endif
