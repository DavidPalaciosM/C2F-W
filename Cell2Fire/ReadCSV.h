#ifndef READCSV
#define READCSV

#include "Cells.h"
#include "DataGenerator.h"
#include "ReadArgs.h"

#include "tiffio.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*
 *   Forest structure
 */
typedef struct
{
    int cellside, rows, cols;
    double xllcorner, yllcorner;
    // std::vector<std::unordered_map<std::string, int>> adjCells;
    std::vector<std::vector<int>> coordCells;
} forestDF;

/*
 * A class to read data from a csv file.
 */
class CSVReader
{
  public:
    // inmutable
    std::string fileName;
    std::string delimeter;

    // Constructor
    CSVReader(std::string filename, std::string delm = ",");

    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string>> getData();
    std::unordered_map<int, int> getDataIg();

    // Print data to console (Debug)
    void printData(std::vector<std::vector<std::string>>& DF);

    // Populate DF (Spanish version)
    void parseDF(inputs* df_ptr, std::vector<std::vector<std::string>>& DF, arguments* args_ptr, int NCells);

    // Populate NFtypes (Spanish version)
    void parseNDF(std::vector<int>& NFTypes, std::vector<std::vector<std::string>>& DF, int NCells);

    // Populate Probabilities
    void parsePROB(std::vector<float>& probabilities, std::vector<std::vector<std::string>>& DF, int NCells);

    // Populate Weather DF (Spanish version)
    void
    parseWeatherDF(weatherDF* wt_ptr, arguments* args_ptr, std::vector<std::vector<std::string>>& DF, int WPeriods);

    // Populate Ignition Points
    void parseIgnitionDF(std::vector<int>& ig, std::vector<std::vector<std::string>>& DF, int IgPeriods);

    // Populates ForestDF
    void parseForestDF(forestDF* frt_ptr, std::vector<std::vector<std::string>>& DF);

    // Populate Harvested Cells
    void parseHarvestedDF(std::unordered_map<int, std::vector<int>>& hc,
                          std::vector<std::vector<std::string>>& DF,
                          int HPeriods);

    // Populate BBO Factors
    void parseBBODF(std::unordered_map<int, std::vector<float>>& bbo,
                    std::vector<std::vector<std::string>>& DF,
                    int NFTypes);

    // Prints individual cell info
    void printDF(inputs df);

    // Prints individual weather row info
    void printWeatherDF(weatherDF wdf);
};

#endif
