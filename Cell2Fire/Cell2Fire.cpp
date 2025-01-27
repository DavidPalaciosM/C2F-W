/* coding: utf-8
__version__ = "3.0"
__author__ = "Cristobal Pais"
__maintainer__ = "Jaime Carrasco, Cristobal Pais, David Woodruff, David Palacios"
*/
// Unified version by David Palacios
//  Include classes
#include "Cell2Fire.h"
#include "Cells.h"
#include "DataGenerator.h"
#include "FuelModelKitral.h"
#include "FuelModelSpain.h"
#include "Lightning.h"
#include "ReadArgs.h"
#include "ReadCSV.h"
#include "Spotting.h"
#include "WriteCSV.h"

// Include libraries
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <random>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Global Variables (DFs with cells and weather info)
inputs* df_ptr;
weatherDF* wdf_ptr;
weatherDF wdf[100000];  // hard to dynamic allocate memory since it changes from
                        // file to file, better to keep constant size;
inputs* df;
int currentSim = 0;
std::unordered_map<int, std::vector<float>> BBOFactors;
std::unordered_map<int, std::vector<int>> HarvestedCells;
std::vector<int> NFTypesCells;
std::unordered_map<int, int> IgnitionHistory;

/******************************************************************************
                                                                                                                                Utils
*******************************************************************************/

/**
 *
 *
 */
void
printSets(std::unordered_set<int> availCells,
          std::unordered_set<int> nonBurnableCells,
          std::unordered_set<int> burningCells,
          std::unordered_set<int> burntCells,
          std::unordered_set<int> harvestCells)
{
    std::cout << "\nSet information period" << std::endl;
    std::cout << "Available Cells:";
    for (auto& ac : availCells)
    {
        std::cout << " " << ac;
    }
    std::cout << std::endl;

    std::cout << "nonBurnable Cells:";
    for (auto& nbc : nonBurnableCells)
    {
        std::cout << " " << nbc;
    }
    std::cout << std::endl;

    std::cout << "Burning Cells:";
    for (auto& bc : burningCells)
    {
        std::cout << " " << bc;
    }
    std::cout << std::endl;

    std::cout << "Burnt Cells:";
    for (auto& bc : burntCells)
    {
        std::cout << " " << bc;
    }
    std::cout << std::endl;

    std::cout << "Firebreak Cells:";
    for (auto& hc : harvestCells)
    {
        std::cout << " " << hc;
    }
    std::cout << std::endl;
}

// Output grids
void
CSVGrid(int rows, int cols, int gridNumber, std::string gridFolder, std::vector<int>& statusCellsCSV, bool verbose)
{
    std::string gridName;
    if (gridNumber < 10)
    {
        gridName = gridFolder + "ForestGrid0" + std::to_string(gridNumber) + ".csv";
    }

    else
    {
        gridName = gridFolder + "ForestGrid" + std::to_string(gridNumber) + ".csv";
    }

    if (verbose)
    {
        std::cout << "We are plotting the current forest to a csv file " << gridName << std::endl;
    }
    CSVWriter CSVPloter(gridName, ",");
    CSVPloter.printCSV_V2(rows, cols, statusCellsCSV);
}

inline char
separator()
{
#if defined _WIN32 || defined __CYGWIN__
    return '\\';
#else
    return '/';
#endif
}

/******************************************************************************
                                                                                                                        Constructor
*******************************************************************************/

/**
 * @brief Constructs and initializes the Cell2Fire object to run a simulation.
 *
 * This constructor initializes the `Cell2Fire` object by reading configuration
 * and data files required for simulating fire spread in a forested
 * environment. It populates various member variables, including fuel
 * coefficients, forest structure, weather data, ignition points, and other
 * simulation-related parameters. It also performs preprocessing steps to
 * categorize cells into burnable and non-burnable types and to establish fire
 * ignition sets.
 *
 * @param _args List of command line arguments containing configuration and
 * file paths needed for the simulation.
 *
 * @return A fully initialized `Cell2Fire` object ready for simulation.
 *
 * ### Notes:
 * - Initializes forest data from the `fuels` data and `Data.csv` files.
 * - Initializes weather data from `Weather.csv` and optionally
 * `WeatherDistribution.csv`.
 * - Processes ignition points from `Ignitions.csv` (if provided) and computes
 * adjacent cells based on the ignition radius.
 * - Categorizes cells as burnable, non-burnable, or harvested based on input
 * data.
 * - If BBO tuning is enabled, initializes tuning factors using `BBOFuels.csv`.
 * - Validates and adjusts simulation parameters based on the weather file
 * consistency.
 */
Cell2Fire::Cell2Fire(arguments _args)
    : CSVWeather(_args.InFolder + "Weather.csv", ","), CSVForest(_args.InFolder + "fuels", " ")
{
    // Aux
    int i;

    // Populate arguments from command line into the Cell2Fire object
    this->args = _args;
    this->args_ptr = &this->args;

    /********************************************************************
     *
     *															Initialization
     *steps
     *
     ********************************************************************/
    // DEBUGstd::cout << "------------------ Simulator C++ Beta version
    // ----------------------\n" << std::endl;
    /*
                  Command line arguments (all of them inside args structure)
    */
    // DEBUGstd::cout << "------ Command line values ------\n";
    // DEBUGprintArgs(this->args);

    /********************************************************************
                                                             Initialize fuel
    coefficients for Spread Model
    ********************************************************************/
    // fuel_coefs coefs[18];
    this->coef_ptr = &this->coefs[0];

    /********************************************************************
                                    Global Values (Forest) and Instance (in
    memory for the moment)
    ********************************************************************/
    // DEBUGstd::cout << "\n------ Instance from file initialization ------\n";
    this->sim = 1;
    /********************************************************************
                                                                                    Read Instance from csv files...
    ********************************************************************/
    // Create forest structure
    forestDF frdf;
    // DEBUG
    std::cout << "------------------Forest Data ----------------------\n" << std::endl;
    std::vector<std::vector<std::string>> FDF = this->CSVForest.getData();
    // DEBUGthis->CSVForest.printData(FDF);
    this->CSVForest.parseForestDF(&frdf, FDF);

    // DEBUGstd::cout << "------------------Detailed Data
    // ----------------------\n" << std::endl;
    this->rows = frdf.rows;
    this->cols = frdf.cols;
    this->widthSims = std::to_string(this->args.TotalSims).length();
    this->nCells = rows * cols;
    this->cellSide = frdf.cellside;
    this->areaCells = cellSide * cellSide;
    this->perimeterCells = 4 * cellSide;
    this->xllcorner = frdf.xllcorner;
    this->yllcorner = frdf.yllcorner;

    this->coordCells = frdf.coordCells;
    // this->adjCells = frdf.adjCells;

    /********************************************************************
                                                    Dataframes initialization:
    Forest and Weather
    ********************************************************************/
    // DEBUGstd::cout << "\n------ Read DataFrames: Forest and Weather ------\n";

    /* Forest DataFrame */
    std::string filename = this->args.InFolder + "Data.csv";
    std::string sep = ",";
    CSVReader CSVParser(filename, sep);

    // Populate DF
    std::vector<std::vector<std::string>> DF = CSVParser.getData();
    std::cout << "Forest DataFrame from instance " << filename << std::endl;
    // DEBUGCSVParser.printData(DF);
    std::cout << "Number of cells: " << this->nCells << std::endl;
    df = new inputs[this->nCells];

    // Create empty df with size of NCells
    df_ptr = &df[0];  // access reference for the first element of df

    // Populate the df [nCells] objects
    CSVParser.parseDF(df_ptr,
                      DF,
                      this->args_ptr,
                      this->nCells);  // iterates from the first element of df, using DF,
                                      // args_ptr and the number of cells

    // Initialize and populate relevant vectors
    this->fTypeCells = std::vector<int>(this->nCells, 1);
    this->fTypeCells2 = std::vector<string>(this->nCells, "Burnable");
    this->statusCells = std::vector<int>(this->nCells, 0);
    // Outputs
    this->crownState = std::vector<int>(this->nCells, 0);
    this->crownFraction = std::vector<float>(this->nCells, 0);
    this->surfFraction = std::vector<float>(this->nCells, 0);
    this->surfaceIntensities = std::vector<float>(this->nCells, 0);
    this->RateOfSpreads = std::vector<float>(this->nCells, 0);
    this->surfaceFlameLengths = std::vector<float>(this->nCells, 0);
    this->crownIntensities = std::vector<float>(this->nCells, 0);
    this->crownFlameLengths = std::vector<float>(this->nCells, 0);
    this->maxFlameLengths = std::vector<float>(this->nCells, 0);

    this->ignProb = std::vector<float>(this->nCells, 1);
    CSVParser.parsePROB(this->ignProb, DF, this->nCells);

    // Non burnable types: populate relevant fields such as status and ftype
    std::string NoFuel = "NF ";
    std::string NoData = "ND ";
    std::string Empty = "";
    const char* NF = NoFuel.c_str();
    const char* ND = NoData.c_str();
    const char* EM = Empty.c_str();

    for (int l = 0; l < this->nCells; l++)
    {
        if (strcmp(df[l].fueltype, NF) == 0 || strcmp(df[l].fueltype, ND) == 0)
        {
            this->fTypeCells[l] = 0;
            this->fTypeCells2[l] = "NonBurnable";
            this->statusCells[l] = 4;
        }
    }

    // Harvested cells
    if (strcmp(this->args.HarvestPlan.c_str(), EM) != 0)
    {
        std::string sep = ",";
        CSVReader CSVHPlan(this->args.HarvestPlan, sep);

        // Populate Ignitions vector
        std::vector<std::vector<std::string>> HarvestedDF = CSVHPlan.getData();
        // CSVHPlan.printData(HarvestedDF);

        // Cells
        int HCellsP = HarvestedDF.size() - 1;
        CSVHPlan.parseHarvestedDF(HarvestedCells, HarvestedDF, HCellsP);

        // Print-out
        std::cout << "\nFirebreak Cells :" << std::endl;
        for (auto it = HarvestedCells.begin(); it != HarvestedCells.end(); it++)
        {
            std::cout << " " << it->first << ": ";
            for (auto& it2 : it->second)
            {
                std::cout << it2 << " ";
                this->fTypeCells[it2 - 1] = 0;
                this->fTypeCells2[it2 - 1] = "NonBurnable";
                this->statusCells[it2 - 1] = 3;
            }
        }
        std::cout << std::endl;
    }

    // Relevant sets: Initialization
    this->availCells.clear();
    this->nonBurnableCells.clear();
    this->burningCells.clear();
    this->burntCells.clear();
    this->harvestCells.clear();
    for (i = 0; i < this->statusCells.size(); i++)
    {
        if (this->statusCells[i] < 3)
            this->availCells.insert(i + 1);
        else if (this->statusCells[i] == 4)
            this->nonBurnableCells.insert(i + 1);
        else if (this->statusCells[i] == 3)
            this->harvestCells.insert(i + 1);
    }

    /* Weather DataFrame */
    this->WeatherDF = this->CSVWeather.getData();
    std::cout << "\nWeather DataFrame from instance " << this->CSVWeather.fileName << std::endl;

    if (this->args.WeatherOpt.compare("distribution") == 0)
    {
        CSVReader CSVWeatherDistribution(_args.InFolder + "WeatherDistribution.csv", ",");
        this->WDist = CSVWeatherDistribution.getData();
        CSVWeatherDistribution.printData(WDist);
    }

    std::vector<string> WeatherHistory;
    this->counter_wt = 0;

    // Populate WDF
    int WPeriods = WeatherDF.size() - 1;  // -1 due to header
    wdf_ptr = &wdf[0];
    std::cout << "Weather Periods: " << WPeriods << std::endl;

    // Populate the wdf objects
    this->CSVWeather.parseWeatherDF(wdf_ptr, this->args_ptr, this->WeatherDF, WPeriods);
    // std::cout << "\nPass Debug " << std::endl;
    // DEBUGthis->CSVWeather.printData(this->WeatherDF);

    /*  Ignitions */
    int IgnitionYears;
    std::vector<int> IgnitionPoints;

    if (this->args.Ignitions)
    {
        // DEBUGstd::cout << "\nWe have specific ignition points:" << std::endl;

        /* Ignition points */
        std::string ignitionFile = args.InFolder + "Ignitions.csv";
        std::string sep = ",";
        CSVReader CSVIgnitions(ignitionFile, sep);

        // Populate Ignitions vector
        std::vector<std::vector<std::string>> IgnitionsDF = CSVIgnitions.getData();
        // DEBUGstd::cout << "Ignition points from file " << ignitionFile <<
        // std::endl; DEBUGCSVIgnitions.printData(IgnitionsDF);

        // Total Years
        IgnitionYears = IgnitionsDF.size() - 1;
        // DEBUGstd::cout << "Ignition Years: " << IgnitionYears  << std::endl;
        // DEBUGstd::cout << "Total Years: " << this->args.TotalYears  <<
        // std::endl;
        args.TotalYears = std::min(args.TotalYears, IgnitionYears);
        // DEBUGstd::cout << "Setting TotalYears to " << args.TotalYears << " for
        // consistency with Ignitions file" << std::endl;

        // Ignition points
        this->IgnitionPoints = std::vector<int>(IgnitionYears, 0);
        CSVIgnitions.parseIgnitionDF(this->IgnitionPoints, IgnitionsDF, IgnitionYears);
        // this->IgnitionSets =
        // std::vector<unordered_set<int>>(this->IgnitionPoints.size());
        this->IgnitionSets = std::vector<std::vector<int>>(this->args.TotalYears);

        // Ignition radius
        if (this->args.IgnitionRadius > 0)
        {
            // Aux
            int i, a, igVal;
            // std::unordered_set<int> auxSet;
            std::vector<int> auxSet;
            int auxIg = 0;

            // Debug
            // for (i=0; i<this->args.TotalYears; i++)
            //	std::cout << this->IgnitionPoints[i] <<	std::endl;

            // Loop
            for (i = 0; i < this->args.TotalYears; i++)
            {
                auxSet.clear();
                igVal = this->IgnitionPoints[i];
                std::vector<int> adjacentCellsVector = adjacentCells(igVal, this->rows, this->cols);
                if (this->args.IgnitionRadius == 1)
                {
                    for (auto& nb : adjacentCellsVector)
                    {
                        if (nb != -1)
                        {
                            // this->IgnitionSets[auxIg].insert(nb.second);
                            this->IgnitionSets[auxIg].push_back(nb);
                        }
                    }
                    // this->IgnitionSets[auxIg].insert(igVal);
                    this->IgnitionSets[auxIg].push_back(igVal);
                }

                if (this->args.IgnitionRadius > 1)
                {
                    // Initial ignition set (first year for 1 degree)
                    for (auto& nb : adjacentCellsVector)
                    {
                        if (nb != -1)
                        {
                            // this->IgnitionSets[auxIg].insert(nb.second);
                            this->IgnitionSets[auxIg].push_back(nb);
                        }
                    }
                    int auxR = 1;
                    // auxSet.insert(igVal);
                    auxSet.push_back(igVal);

                    // loop over radius of adjacents
                    while (auxR < args.IgnitionRadius)
                    {
                        // unordered_set<int> IgnitionSetsAux =
                        // this->IgnitionSets[auxIg];
                        std::vector<int> IgnitionSetsAux = this->IgnitionSets[auxIg];

                        for (auto& c : IgnitionSetsAux)
                        {
                            // Populate Aux Set
                            std::vector<int> adjacentCellsVector = adjacentCells(c, this->rows, this->cols);
                            for (auto& na : adjacentCellsVector)
                            {
                                if (na != -1)
                                {
                                    // auxSet.insert(na.second);
                                    auxSet.push_back(na);
                                }
                            }
                        }
                        // Save aux set as Ignition Set
                        this->IgnitionSets[auxIg] = auxSet;
                        auxR += 1;
                    }
                }
                // Next iteration (year)
                auxIg++;
            }
        }

        // Clean vectors
        for (auto& v : this->IgnitionSets)
        {
            std::sort(v.begin(), v.end());
            v.erase(std::unique(v.begin(), v.end()), v.end());
        }

        // IgRadius Information
        if (this->args.verbose)
        {
            for (auto& nb : this->IgnitionSets[0])
            {
                std::cout << "Ignition sets[0] example:" << nb << std::endl;
            }
        }
    }

    /* BBO Tuning factors (only the ones present in the instances*/
    if (this->args.BBOTuning)
    {
        // Get fuel types numbers
        CSVParser.parseNDF(NFTypesCells, DF, this->nCells);

        // BBO File
        std::string BBOFile = args.InFolder + "BBOFuels.csv";
        std::string sep = ",";
        CSVReader CSVBBO(BBOFile, sep);

        // Populate BBO vector
        std::vector<std::vector<std::string>> BBODF = CSVBBO.getData();
        int BBONTypes = BBODF.size() - 1;
        CSVBBO.parseBBODF(BBOFactors, BBODF, BBONTypes);

        // Print-out
        std::cout << "BBO Factors:" << std::endl;
        for (auto it = BBOFactors.begin(); it != BBOFactors.end(); it++)
        {
            std::cout << " " << it->first << ": ";
            for (auto& it2 : it->second)
            {
                std::cout << it2 << " ";
            }
        }
        std::cout << std::endl;
    }
    /********************************************************************
     *
     *											Global
     *Parameters for loop
     *
     *********************************************************************/
    // Global parameters for the loop
    this->year = 1;
    this->weatherPeriod = 0;
    this->noIgnition = true;  // None = -1
    this->activeCrown = false;
    this->gridNumber = 0;
    this->fire_period = vector<int>(this->args.TotalYears, 0);

    // Check maxFirePeriods and Weather File consistency
    if (this->args.WeatherOpt.compare("rows") == 0 || this->args.WeatherOpt.compare("random") == 0)
    {
        int maxFP = this->args.MinutesPerWP / this->args.FirePeriodLen * WPeriods;
        if (this->args.MaxFirePeriods > maxFP)
        {
            this->args.MaxFirePeriods = maxFP;
            if (this->args.verbose)
            {
                std::cout << "Maximum fire periods are set to: " << this->args.MaxFirePeriods
                          << " based on the weather file, Fire Period Length, "
                             "and Minutes per WP"
                          << std::endl;
            }
        }
    }
}

/******************************************************************************
                                                                                                                                Methods
*******************************************************************************/

/**
 * @brief Initializes a cell within the simulation and adds it to the cell
 * collection.
 *
 * This method creates a `Cells` object for the specified cell ID, populates it
 * with the necessary parameters, and stores it in the `Cells_Obj` unordered
 * map. It also initializes the fire-related fields for the cell and, if
 * verbose mode is enabled, prints debugging information about the cell.
 *
 * @param id The ID of the cell to initialize.
 *
 * ### Details:
 * - The `Cells` object is constructed using the cell's properties, including:
 *   - `areaCells`: The area of the cell.
 *   - `coordCells`: The coordinates of the cell.
 *   - `fTypeCells`: The fuel type of the cell.
 *   - `fTypeCells2`: A textual description of the fuel type.
 *   - `perimeterCells`: The perimeter of the cell.
 *   - `statusCells`: The status of the cell (e.g., burning, available).
 *   - `id`: The identifier for the cell.
 * - The newly created cell is added to the `Cells_Obj` unordered map.
 *
 */

void
Cell2Fire::InitCell(int id)
{
    // Declare an iterator to unordered_map
    std::unordered_map<int, Cells>::iterator it2;

    // Initialize cell, insert it inside the unordered map
    Cells Cell(id - 1,
               this->areaCells,
               this->coordCells[id - 1],
               this->fTypeCells[id - 1],
               this->fTypeCells2[id - 1],
               this->perimeterCells,
               this->statusCells[id - 1],
               id);
    this->Cells_Obj.insert(std::make_pair(id, Cell));

    // Get object from unordered map
    it2 = this->Cells_Obj.find(id);

    // Initialize the fire fields for the selected cel
    it2->second.initializeFireFields(this->coordCells, this->availCells, this->cols, this->rows);

    // Print info for debugging
    if (this->args.verbose)
        it2->second.print_info();
}

/**
 * @brief Resets the simulation environment for a new run.
 *
 * This method initializes and resets all relevant parameters, structures, and
 * files needed for the simulation. It handles:
 * - Global simulation parameters
 * - Output directories and files
 * - Weather configuration
 * - Randomized inputs for fire spread simulation
 * - Data structures related to cells and fire metrics
 *
 * @param rnumber Random seed or identifier for weather selection.
 * @param rnumber2 Random value for initializing ROS (Rate of Spread)
 * variations.
 * @param simExt Simulation extension identifier (default: 1).
 *
 */
void
Cell2Fire::reset(int rnumber, double rnumber2, int simExt = 1)
{
    // Reset info
    // DEBUGstd::cout  << "--------------------- Reseting environment
    // -----------------------" << std::endl;

    // Aux
    int i;

    // Reset global parameters for the simulation
    this->year = 1;
    this->weatherPeriod = 0;
    this->noIgnition = true;  // None = -1
    this->nIgnitions = 0;
    this->gridNumber = 0;
    this->activeCrown = false;
    this->done = false;
    this->fire_period = vector<int>(this->args.TotalYears, 0);
    this->sim = simExt;
    // Initial status grid folder
    if (this->args.OutputGrids || this->args.FinalGrid)
    {
        CSVWriter CSVFolder("", "");
        this->gridFolder = this->args.OutFolder + "Grids" + separator();
        CSVFolder.MakeDir(this->gridFolder);
        this->gridFolder
            = this->args.OutFolder + "Grids" + separator() + "Grids" + std::to_string(this->sim) + separator();
        CSVFolder.MakeDir(this->gridFolder);
        // DEBUGstd::cout << "\nInitial Grid folder was generated in " <<
        // this->gridFolder << std::endl;
    }

    // Messages Folder
    if (this->args.OutMessages)
    {
        CSVWriter CSVFolder("", "");
        this->messagesFolder = this->args.OutFolder + "Messages";
        CSVFolder.MakeDir(this->messagesFolder);
        this->messagesFolder = this->args.OutFolder + "Messages" + separator();
    }
    // ROS Folder
    if (this->args.OutRos)
    {
        CSVWriter CSVFolder("", "");
        this->rosFolder = this->args.OutFolder + "RateOfSpread";
        CSVFolder.MakeDir(this->rosFolder);
        this->rosFolder = this->args.OutFolder + "RateOfSpread" + separator();
    }
    // Surface Byram Intensity Folder
    if (this->args.OutIntensity)
    {
        CSVWriter CSVFolder("", "");
        this->surfaceIntensityFolder = this->args.OutFolder + "SurfaceIntensity";
        CSVFolder.MakeDir(this->surfaceIntensityFolder);
        this->surfaceIntensityFolder = this->args.OutFolder + "SurfaceIntensity" + separator();
    }
    // Crown Byram Intensity Folder
    if ((this->args.OutIntensity) && (this->args.AllowCROS) && (this->args.Simulator == "S"))
    {
        CSVWriter CSVFolder("", "");
        this->crownIntensityFolder = this->args.OutFolder + "CrownIntensity";
        CSVFolder.MakeDir(this->crownIntensityFolder);
        this->crownIntensityFolder = this->args.OutFolder + "CrownIntensity" + separator();
    }
    // Surface Flame Length Folder
    if (this->args.OutFl)
    {
        CSVWriter CSVFolder("", "");
        this->surfaceFlameLengthFolder = this->args.OutFolder + "SurfaceFlameLength";
        CSVFolder.MakeDir(this->surfaceFlameLengthFolder);
        this->surfaceFlameLengthFolder = this->args.OutFolder + "SurfaceFlameLength" + separator();
    }
    // Crown Flame Length Folder
    if ((this->args.OutFl) && (this->args.AllowCROS) && (this->args.Simulator == "S"))
    {
        CSVWriter CSVFolder("", "");
        this->crownFlameLengthFolder = this->args.OutFolder + "CrownFlameLength";
        CSVFolder.MakeDir(this->crownFlameLengthFolder);
        this->crownFlameLengthFolder = this->args.OutFolder + "CrownFlameLength" + separator();
    }
    // max Flame Length Folder
    if ((this->args.OutFl) && (this->args.AllowCROS) && (this->args.Simulator == "S"))
    {
        CSVWriter CSVFolder("", "");
        this->maxFlameLengthFolder = this->args.OutFolder + "MaxFlameLength";
        CSVFolder.MakeDir(this->maxFlameLengthFolder);
        this->maxFlameLengthFolder = this->args.OutFolder + "MaxFlameLength" + separator();
    }
    // Crown Folder
    if (this->args.OutCrown && this->args.AllowCROS)
    {
        CSVWriter CSVFolder("", "");
        this->crownFolder = this->args.OutFolder + "CrownFire";
        CSVFolder.MakeDir(this->crownFolder);
        this->crownFolder = this->args.OutFolder + "CrownFire" + separator();
    }
    // Crown Fraction Burn Folder
    if (this->args.OutCrownConsumption && this->args.AllowCROS)
    {
        CSVWriter CSVFolder("", "");
        this->cfbFolder = this->args.OutFolder + "CrownFractionBurn";
        CSVFolder.MakeDir(this->cfbFolder);
        this->cfbFolder = this->args.OutFolder + separator() + "CrownFractionBurn" + separator();
    }
    // Surf Fraction Burn Folder
    if (this->args.OutSurfConsumption && this->args.Simulator == "C")
    {
        CSVWriter CSVFolder("", "");
        this->sfbFolder = this->args.OutFolder + "SurfFractionBurn";
        CSVFolder.MakeDir(this->sfbFolder);
        this->sfbFolder = this->args.OutFolder + separator() + "SurfFractionBurn" + separator();
    }

    // Random Weather
    /*std::cout << "Weather Option:" << this->args.WeatherOpt << std::endl;
    std::cout << "Weather Option random check:" <<
    (this->args.WeatherOpt.compare("random") == 0) << std::endl; std::cout <<
    "Weather Option rows check:" << (this->args.WeatherOpt.compare("rows") == 0)
    << std::endl;
    */

    if (this->args.WeatherOpt.compare("random") == 0)
    {
        // Random Weather
        this->CSVWeather.fileName
            = this->args.InFolder + "Weathers" + separator() + "Weather" + std::to_string(rnumber) + ".csv";

        /* Weather DataFrame */
        try
        {
            this->WeatherDF = this->CSVWeather.getData();
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            std::abort();
        }
        std::cout << "\nWeather file selected: " << this->CSVWeather.fileName << std::endl;

        // Populate WDF
        int WPeriods = this->WeatherDF.size() - 1;  // -1 due to header
        wdf_ptr = &wdf[0];
        std::cout << "Weather Periods: " << WPeriods << std::endl;
        std::string weather_name = "";
        for (int i = this->CSVWeather.fileName.size() - 1; i >= 0; i--)
        {
            std::string bol = std::to_string(this->CSVWeather.fileName[i]);
            int bol2 = std::stoi(bol);
            char check = '\\';
            int intcheck = (int)check;
            if (bol2 == intcheck)
            {
                break;
            }
            else
            {
                weather_name.push_back(this->CSVWeather.fileName[i]);
            }
        }
        reverse(weather_name.begin(), weather_name.end());
        WeatherHistory.push_back(weather_name);

        // Populate the wdf objects
        this->CSVWeather.parseWeatherDF(wdf_ptr, this->args_ptr, this->WeatherDF, WPeriods);
        // DEBUGthis->CSVWeather.printData(this->WeatherDF);

        // Check maxFirePeriods and Weather File consistency (reset
        // MaxFirePeriods and recalculate)
        int maxFP = this->args.MinutesPerWP / this->args.FirePeriodLen * WPeriods;
        this->args.MaxFirePeriods = 10000000;
        // DEBUGstd::cout << "Int MaxFP: " << maxFP << std::endl;
        // DEBUGstd::cout << "MinutesPerWP: " << this->args.MinutesPerWP <<
        // std::endl; DEBUGstd::cout << "FirePeriodLen: " <<
        // this->args.FirePeriodLen << std::endl; DEBUGstd::cout <<
        // "MaxfirePeriods: " << this->args.MaxFirePeriods << std::endl;
        if (this->args.MaxFirePeriods > maxFP)
        {
            this->args.MaxFirePeriods = maxFP;
            if (this->args.verbose)
            {
                std::cout << "Maximum fire periods are set to: " << this->args.MaxFirePeriods
                          << " based on the weather file, Fire Period Length, "
                             "and Minutes per WP"
                          << std::endl;
            }
        }
    }

    if (this->args.WeatherOpt.compare("distribution") == 0)
    {
        bool selectWeather = false;
        int countCases = 0;
        std::string weather_name;
        while (!selectWeather)
        {
            std::default_random_engine generator3(args.seed * simExt
                                                  * time(NULL));  // creates a different generator solving cases when
                                                                  // parallel running creates simulations at same time
            std::uniform_int_distribution<int> distribution(1, this->WDist.size() - 1);
            int weather_idx = distribution(generator3);

            float rd_number = (float)rand() / ((float)(RAND_MAX / 0.999999999));
            float probability_weather = std::stof(this->WDist[weather_idx][1]);
            // DEBUGstd::cout<<"prob: "<<(probability_weather)<<std::endl;
            // DEBUGstd::cout<<"weather_idx: "<<(weather_idx)<<std::endl;
            // DEBUGstd::cout<<"rdnumber: "<<(rd_number)<<std::endl;
            if (probability_weather > rd_number)
            {  // rd_number cannot be 1, but can be 0. So if prob weather has
                // prob=0 it does not have a chance of being selected, and if it
                // is 1, it will always be selected
                weather_name = this->WDist[weather_idx][0];
                // DEBUGstd::cout << "Weather name selected: " << weather_name <<
                // std::endl;
                selectWeather = true;
            }
            countCases++;
            if (countCases > 1000)
            {
                weather_name = this->WDist[weather_idx][0];
                selectWeather = true;
            }
            selectWeather = true;
        }

        // Random Weather
        this->CSVWeather.fileName = this->args.InFolder + "Weathers" + separator() + weather_name + ".csv";
        WeatherHistory.push_back(weather_name);

        /* Weather DataFrame */
        try
        {
            this->WeatherDF = this->CSVWeather.getData();
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            std::abort();
        }
        std::cout << "\nWeather file selected: " << this->CSVWeather.fileName << std::endl;

        // Populate WDF
        int WPeriods = this->WeatherDF.size() - 1;  // -1 due to header
        wdf_ptr = &wdf[0];
        std::cout << "Weather Periods: " << WPeriods << std::endl;

        // Populate the wdf objects
        this->CSVWeather.parseWeatherDF(wdf_ptr, this->args_ptr, this->WeatherDF, WPeriods);
        // DEBUGthis->CSVWeather.printData(this->WeatherDF);

        // Check maxFirePeriods and Weather File consistency (reset
        // MaxFirePeriods and recalculate)
        int maxFP = this->args.MinutesPerWP / this->args.FirePeriodLen * WPeriods;
        this->args.MaxFirePeriods = 10000000;
        // DEBUGstd::cout << "Int MaxFP: " << maxFP << std::endl;
        // DEBUGstd::cout << "MinutesPerWP: " << this->args.MinutesPerWP <<
        // std::endl; DEBUGstd::cout << "FirePeriodLen: " <<
        // this->args.FirePeriodLen << std::endl; DEBUGstd::cout <<
        // "MaxfirePeriods: " << this->args.MaxFirePeriods << std::endl;

        if (this->args.MaxFirePeriods > maxFP)
        {
            this->args.MaxFirePeriods = maxFP;
            if (this->args.verbose)
            {
                std::cout << "Maximum fire periods are set to: " << this->args.MaxFirePeriods
                          << " based on the weather file, Fire Period Length, "
                             "and Minutes per WP"
                          << std::endl;
            }
        }
    }
    // Random ROS-CV
    this->ROSRV = std::abs(rnumber2);
    // std::cout << "ROSRV: " << this->ROSRV << std::endl;

    // Cells dictionary
    this->Cells_Obj.clear();

    // Declare an iterator to unordered_map
    std::unordered_map<int, Cells>::iterator it;

    // Reset status
    this->fTypeCells = std::vector<int>(this->nCells, 1);
    this->fTypeCells2 = std::vector<string>(this->nCells, "Burnable");
    this->statusCells = std::vector<int>(this->nCells, 0);
    this->crownState = std::vector<int>(this->nCells, 0);
    this->crownFraction = std::vector<float>(this->nCells, 0);
    this->surfFraction = std::vector<float>(this->nCells, 0);
    this->surfaceIntensities = std::vector<float>(this->nCells, 0);
    this->crownIntensities = std::vector<float>(this->nCells, 0);
    this->RateOfSpreads = std::vector<float>(this->nCells, 0);
    this->surfaceFlameLengths = std::vector<float>(this->nCells, 0);
    this->crownFlameLengths = std::vector<float>(this->nCells, 0);
    this->maxFlameLengths = std::vector<float>(this->nCells, 0);

    this->FSCell.clear();
    this->crownMetrics.clear();  // intensity and crown

    // Non burnable types: populate relevant fields such as status and ftype
    std::string NoFuel = "NF ";
    std::string NoData = "ND ";
    const char* NF = NoFuel.c_str();
    const char* ND = NoData.c_str();

    for (i = 0; i < this->nCells; i++)
    {
        if (strcmp(df[i].fueltype, NF) == 0 || strcmp(df[i].fueltype, ND) == 0)
        {
            this->fTypeCells[i] = 0;
            this->fTypeCells2[i] = "NonBurnable";
            this->statusCells[i] = 4;
        }
    }

    // Relevant sets: Initialization
    this->availCells.clear();
    this->nonBurnableCells.clear();
    this->burningCells.clear();
    this->burntCells.clear();
    this->harvestCells.clear();

    // Harvest Cells
    for (auto it = HarvestedCells.begin(); it != HarvestedCells.end(); it++)
    {
        for (auto& it2 : it->second)
        {
            this->fTypeCells[it2 - 1] = 0;
            this->fTypeCells2[it2 - 1] = "NonBurnable";
            this->statusCells[it2 - 1] = 3;
        }
    }

    for (i = 0; i < this->statusCells.size(); i++)
    {
        if (this->statusCells[i] < 3)
            this->availCells.insert(i + 1);
        else if (this->statusCells[i] == 4)
            this->nonBurnableCells.insert(i + 1);
        else if (this->statusCells[i] == 3)
            this->harvestCells.insert(i + 1);
    }

    // Print-out sets information
    if (this->args.verbose)
    {
        printSets(this->availCells, this->nonBurnableCells, this->burningCells, this->burntCells, this->harvestCells);
    }
}

/**
 * @brief Simulates the ignition phase of the fire spread model for a single
 * simulation year.
 *
 * This method is responsible for selecting ignition points, either randomly or
 * from predefined data (e.g., CSV files), and attempting to ignite those
 * points based on the conditions of the cells (availability, burnability,
 * etc.). The simulation state is updated accordingly, including tracking
 * ignited, burnt, and available cells, as well as the fire and weather
 * periods.
 *
 * @param generator A random engine used to generate random values for ignition
 * point selection.
 * @param ep The current simulation epoch, used to seed the secondary random
 * generator for parallel simulations.
 * @return true If no ignition occurs during the current simulation year.
 * @return false If at least one ignition occurs during the current simulation
 * year.
 *
 * ### Detailed Behavior:
 * - If no ignition points are provided (args.Ignitions == 0), a random point
 * is selected repeatedly until a valid ignition is found or a limit is
 * reached.
 * - If ignition points are provided, the algorithm selects a point directly or
 * samples from a specified radius around the predefined points.
 * - The ignition process updates the state of the forest, including burning
 * and burnt cells, and prepares for the next period or year if no ignition
 * occurs.
 *
 * ### Key Updates:
 * - Ignition history (IgnitionHistory)
 * - Forest cell states (statusCells, burningCells, burntCells, availCells)
 * - Fire and weather periods
 *
 * ### Verbose Mode:
 * When `args.verbose` is true, detailed logs of the ignition process,
 * including selected points, random values, and status updates, are printed to
 * the console.
 */

bool
Cell2Fire::RunIgnition(std::default_random_engine generator, int ep)
{
    if (this->args.verbose)
    {
        printf("\n----------------------------- Simulating Year %d "
               "-----------------------------\n",
               this->year);
        printf("---------------------- Step 1: Ignition ----------------------\n");
    }
    /*******************************************************************
     *
     *												Step
     *1: Ignition
     *
     *******************************************************************/
    // Ignitions
    int aux = 0;
    int selected = 0;
    int loops = 0;
    int microloops = 0;
    this->noIgnition = false;
    currentSim = currentSim + 1;
    std::default_random_engine generator2(args.seed * ep * this->nCells);  // * time(NULL)); //creates a different
                                                                           // generator solving cases when parallel
                                                                           // running creates simulations at same time
    std::unordered_map<int, Cells>::iterator it;
    std::uniform_int_distribution<int> distribution(1, this->nCells);

    // No Ignitions provided
    if (this->args.Ignitions == 0)
    {
        while (true)
        {
            microloops = 0;
            while (true)
            {
                selected = distribution(generator2);
                float rd_number = (float)rand() / ((float)(RAND_MAX / 0.999999999));
                // DEBUGstd::cout << "selectedPoint: " << selected << std::endl;
                // DEBUGstd::cout << "selectedProbability: " <<
                // ignProb[selected-1] << std::endl; DEBUGstd::cout <<
                // "randomNumber: " << rd_number << std::endl; if
                // (ignProb[selected - 1] / static_cast<float>(100) > rd_number)
                // {    //If probabilities enter as integers, e.g: 80 as 0.8
                if (this->ignProb[selected - 1] > rd_number)
                {
                    aux = selected;
                    // DEBUSstd::cout << "selected_point" << std::endl;
                    break;
                }
                microloops++;
                if (microloops > this->nCells * 100)
                {
                    this->noIgnition = true;
                    break;
                }
            }
            // Check information (Debugging)
            if (this->args.verbose)
            {
                std::cout << "aux: " << aux << std::endl;
            }

            // If cell is available and not initialized, initialize it
            if (this->statusCells[aux - 1] < 3 && this->burntCells.find(aux) == this->burntCells.end())
            {
                if (this->Cells_Obj.find(aux) == this->Cells_Obj.end())
                {
                    InitCell(aux);
                    it = this->Cells_Obj.find(aux);
                }

                if (it->second.getStatus() == "Available" && it->second.fType != 0)
                {
                    IgnitionHistory[sim] = aux;
                    std::cout << "\nSelected (Random) ignition point for Year " << this->year << ", sim " << this->sim
                              << ": " << aux;
                    std::vector<int> ignPts = { aux };
                    if (it->second.ignition(this->fire_period[year - 1],
                                            this->year,
                                            ignPts,
                                            &df[aux - 1],
                                            this->coef_ptr,
                                            this->args_ptr,
                                            &wdf[this->weatherPeriod],
                                            this->activeCrown,
                                            this->perimeterCells))
                    {
                        // Printing info about ignitions
                        if (this->args.verbose)
                        {
                            std::cout << "Cell " << it->second.realId << " Ignites" << std::endl;
                            std::cout << "Cell " << it->second.realId << " Status: " << it->second.getStatus()
                                      << std::endl;
                        }

                        // Status
                        this->statusCells[it->second.realId - 1] = 1;

                        // Plotter placeholder
                        if (this->args.OutputGrids)
                        {
                            this->outputGrid();
                        }

                        break;
                    }
                }
            }

            loops++;
            if (loops > this->nCells * 100)
            {
                this->noIgnition = true;
                break;
            }
        }
    }

    // Ignitions with provided points from CSV
    else
    {
        int temp = IgnitionPoints[this->year - 1];

        // If ignition Radius != 0, sample from the Radius set
        if (this->args.IgnitionRadius > 0)
        {
            // Pick any at random and set temp with that cell
            std::uniform_int_distribution<int> udistribution(0, this->IgnitionSets[this->year - 1].size() - 1);
            temp = this->IgnitionSets[this->year - 1][udistribution(generator)];
        }

        std::cout << "\nSelected ignition point for Year " << this->year << ", sim " << this->sim << ": " << temp;
        // this->
        IgnitionHistory[sim] = temp;

        // If cell is available
        if (this->burntCells.find(temp) == this->burntCells.end() && this->statusCells[temp - 1] < 3)
        {
            if (this->Cells_Obj.find(temp) == this->Cells_Obj.end())
            {
                // Initialize cell, insert it inside the unordered map
                InitCell(temp);
            }

            // Iterator
            it = this->Cells_Obj.find(temp);

            // Not available or non burnable: no ignition
            if (it->second.getStatus() != "Available" || it->second.fType == 0)
            {
                this->noIgnition = true;
            }

            // Available and Burnable: ignition
            if (it->second.getStatus() == "Available" && it->second.fType != 0)
            {
                std::vector<int> ignPts = { temp };
                if (it->second.ignition(this->fire_period[year - 1],
                                        this->year,
                                        ignPts,
                                        &df[temp - 1],
                                        this->coef_ptr,
                                        this->args_ptr,
                                        &wdf[this->weatherPeriod],
                                        this->activeCrown,
                                        this->perimeterCells))
                {

                    // Printing info about ignitions
                    if (this->args.verbose)
                    {
                        std::cout << "Cell " << it->second.realId << " Ignites" << std::endl;
                        std::cout << "Cell " << it->second.realId << " Status: " << it->second.getStatus() << std::endl;
                    }

                    // Status
                    this->statusCells[it->second.realId - 1] = 1;
                }
            }
        }
        else
        {
            this->noIgnition = true;
            std::cout << "Next year..." << std::endl;
            if (this->args.verbose)
            {
                std::cout << "No ignition during year " << this->year << ", Cell "
                          << this->IgnitionPoints[this->year - 1] << " is already burnt or non-burnable type"
                          << std::endl;
            }
            this->year++;
            this->weatherPeriod = 0;
        }
    }

    // If ignition occurs, we update the forest status
    if (!this->noIgnition)
    {
        int newId = it->second.realId;
        if (this->args.verbose)
        std:
            cout << "New ID for burning cell: " << newId << std::endl;

        this->nIgnitions++;
        this->burningCells.insert(newId);
        this->burntCells.insert(newId);
        this->availCells.erase(newId);

        // Print sets information
        if (this->args.verbose)
        {
            printSets(
                this->availCells, this->nonBurnableCells, this->burningCells, this->burntCells, this->harvestCells);
        }
    }

    // Plotter placeholder
    if (this->args.OutputGrids)
    {
        // DEBUGstd::cout << "Grid post ignition" << std::endl;
        this->outputGrid();
    }

    // Next period
    // this->fire_period[year - 1] += 1;   // DEBUGGING!!!
    if (this->args.verbose)
    {
        std::cout << "Fire period updated to " << this->fire_period[year - 1] << std::endl;
    }

    // Check weather period consistency
    updateWeather();

    // Print-out information regarding the weather and fire period
    if (this->args.verbose)
    {
        std::cout << "Fire Period Starts: " << this->fire_period[year - 1] << std::endl;
        std::cout << "\nCurrent weather conditions:" << std::endl;
        this->CSVWeather.printWeatherDF(wdf[this->weatherPeriod]);

        if (this->args.WeatherOpt.compare("constant") == 0)
            std::cout << "(NOTE: current weather is not used for ROS with "
                         "constant option)"
                      << std::endl;

        // End of the ignition step
        std::cout << "\nNext Fire Period: " << this->fire_period[year - 1] << std::endl;
    }

    // If no ignition occurs, go to next year (no multiple ignitions per year,
    // only one)
    if (this->noIgnition)
    {
        if (this->args.verbose)
        {
            std::cout << "No ignition in year " << this->year << std::endl;
            std::cout << "------------------------------------------------------"
                         "-------------------\n"
                      << std::endl;
            std::cout << "                           End of the fire year " << this->year << "               "
                      << std::endl;
            std::cout << "------------------------------------------------------"
                         "-------------------"
                      << std::endl;
        }

        // Next year
        this->year += 1;
    }

    // std::cout << endl << "el punto de ignicion es: " << aux << std::endl;

    return this->noIgnition;
}

/**
 * @brief  Message-sending phase of the fire spread model, where burning cells
 * propagate fire messages to neighboring cells.
 *
 * This method iterates through all burning cells, updates their fire progress,
 * and determines whether fire messages should be sent to neighboring cells. A
 * fire message is sent to a cell if fire reaches its center. Burnt-out cells
 * are also identified and removed from the burning set.
 *
 * @return A map of cell IDs to lists of neighboring cell IDs that received
 * fire messages. Each key is the ID of a burning cell, and the value is a list
 * of neighboring cell IDs affected by the fire.
 *
 * ### Detailed Behavior:
 * - Iterates over all currently burning cells to manage fire propagation using
 * either the `manageFire` or `manageFireBBO` methods, depending on tuning
 * options.
 * - Builds a list of neighboring cells (`sendMessageList`) that receive fire
 * messages for potential ignition.
 * - Tracks cells that burn out during this phase and removes them from the
 * active burning set.
 * - Handles special conditions where repeat fire propagation may occur.
 *
 * ### Key Updates:
 * - `burningCells`: Updated to exclude cells that have burnt out.
 * - `burnedOutList`: Contains cells that are no longer burning after this
 * phase.
 * - `messagesSent`: A flag indicating if any fire messages were sent during
 * this phase.
 *
 * ### Verbose Mode:
 * When `args.verbose` is enabled:
 * - Prints detailed logs of the fire progress and messages sent by each
 * burning cell.
 * - Outputs the current fire period, sets of cells (available, non-burnable,
 * burning, burnt, harvested), and fire message details.
 *
 * ### Warning:
 * - A warning is issued if the fire period approaches the maximum allowed
 * (`args.MaxFirePeriods`).
 */
std::unordered_map<int, std::vector<int>>
Cell2Fire::SendMessages()
{
    // Iterator
    std::unordered_map<int, Cells>::iterator it;

    // Clean list
    this->burnedOutList.clear();

    // Check ending
    if (fire_period[year - 1] == args.MaxFirePeriods - 1 && this->args.verbose)
    {
        std::cout << "*** WARNING!!! About to hit MaxFirePeriods: " << this->args.MaxFirePeriods << std::endl;
    }

    /// Send messages logic
    this->messagesSent = false;
    std::unordered_map<int, vector<int>> sendMessageList;

    // Repeat fire flag
    this->repeatFire = false;

    // Printing info before sending messages
    if (this->args.verbose)
    {
        std::cout << "\n---------------------- Step 2: Sending Messages from "
                     "Ignition ----------------------"
                  << std::endl;
        std::cout << "Current Fire Period:" << this->fire_period[this->year - 1] << std::endl;
        printSets(this->availCells, this->nonBurnableCells, this->burningCells, this->burntCells, this->harvestCells);
    }

    /*
                    Potential parallel zone: Send messages
                    Burning cells loop: sending messages (Embarrasingly
       parallel?: CP: should be) Each burning cell updates its fire progress and
       (if needed) populates their message
    */
    for (int cell : this->burningCells)
    {
        std::vector<int> aux_list;
        // Get object from unordered map
        it = this->Cells_Obj.find(cell);

        // Cell's info
        if (this->args.verbose)
        {
            it->second.print_info();
        }

        /*
                        Manage Fire method main step
        */
        if (it->second.ROSAngleDir.size() > 0)
        {
            // std::cout << "Entra a Manage Fire" << std::endl;
            if (!this->args.BBOTuning)
            {  //&df[cell-1] replaced by full df for getting the slopes
                aux_list = it->second.manageFire(this->fire_period[this->year - 1],
                                                 this->availCells,
                                                 df,
                                                 this->coef_ptr,
                                                 this->coordCells,
                                                 this->Cells_Obj,
                                                 this->args_ptr,
                                                 &wdf[this->weatherPeriod],
                                                 &this->FSCell,
                                                 &this->crownMetrics,
                                                 this->activeCrown,
                                                 this->ROSRV,
                                                 this->perimeterCells,
                                                 this->crownState,
                                                 this->crownFraction,
                                                 this->surfFraction,
                                                 this->surfaceIntensities,
                                                 this->RateOfSpreads,
                                                 this->surfaceFlameLengths,
                                                 this->crownFlameLengths,
                                                 this->crownIntensities,
                                                 this->maxFlameLengths);
            }

            else
            {
                // TODO  MAY 11: Pass the slope factor or the slopes of the
                // adjacent cells
                auto factors = BBOFactors.find(NFTypesCells[cell - 1]);
                aux_list = it->second.manageFireBBO(this->fire_period[this->year - 1],
                                                    this->availCells,
                                                    &df[cell - 1],
                                                    this->coef_ptr,
                                                    this->coordCells,
                                                    this->Cells_Obj,
                                                    this->args_ptr,
                                                    &wdf[this->weatherPeriod],
                                                    &this->FSCell,
                                                    &this->crownMetrics,
                                                    this->activeCrown,
                                                    this->ROSRV,
                                                    this->perimeterCells,
                                                    factors->second,
                                                    this->crownState,
                                                    this->crownFraction,
                                                    this->surfFraction,
                                                    this->surfaceIntensities,
                                                    this->RateOfSpreads,
                                                    this->surfaceFlameLengths);
            }
            // std::cout << "Sale de Manage Fire" << std::endl;
        }

        else
        {
            if (this->args.verbose)
                std::cout << "\nCell " << cell
                          << " does not have any neighbor available for receiving "
                             "messages"
                          << std::endl;
        }

        // If message and not a true flag
        if (aux_list.size() > 0 && aux_list[0] != -100)
        {
            if (this->args.verbose)
                std::cout << "\nList is not empty" << std::endl;
            this->messagesSent = true;
            sendMessageList[it->second.realId] = aux_list;
            if (this->args.verbose)
            {
                std::cout << "Message list content" << std::endl;
                for (auto& msg : sendMessageList[it->second.realId])
                {
                    std::cout << "  Fire reaches the center of the cell " << msg
                              << "  Distance to cell (in meters) was 100.0"
                              << " " << std::endl;
                }
            }
        }

        // Repeat fire conditions if true flag
        if (aux_list.size() > 0 && aux_list[0] == -100)
        {
            this->repeatFire = true;
        }

        // Burnt out inactive burning cells
        if (aux_list.size() == 0)
        {
            // not parallel here
            this->burnedOutList.push_back(it->second.realId);
            if (this->args.verbose)
            {
                std::cout << "\nMessage and Aux Lists are empty; adding to "
                             "BurnedOutList"
                          << std::endl;
            }
        }
    }
    /* End sending messages loop */

    // Check for burnt out updates via sets' difference
    for (auto& bc : this->burnedOutList)
    {
        auto lt = this->burningCells.find(bc);
        if (lt != this->burningCells.end())
        {
            this->burningCells.erase(bc);
        }
    }
    if (this->args.verbose)
        printSets(this->availCells, this->nonBurnableCells, this->burningCells, this->burntCells, this->harvestCells);

    return sendMessageList;
}

/**
 * @brief Processes incoming fire messages to determine the ignition and
 * progression of fire in cells.
 *
 * This method handles the reception and processing of messages sent by burning
 * cells. Based on the received messages, cells may ignite, continue burning,
 * or be marked as burnt out. The method also manages the transitions between
 * fire periods and updates relevant cell sets (e.g., available, burning,
 * burnt).
 *
 * @param sendMessageList A map where each key is the ID of a burning cell, and
 * the associated value is a list of neighboring cell IDs that received fire
 * messages from that cell.
 *
 * ### Detailed Behavior:
 *
 * - For each cell receiving messages:
 *   - Initializes the cell if it hasn't been processed before.
 *   - Checks ignition conditions and marks the cell as burnt if applicable.
 *   - Updates fire-related metadata, ensuring fire does not propagate back to
 * the sender cell.
 *
 * ### Key Updates:
 * - `burntCells`: Updated with cells that are fully burnt.
 * - `burningCells`: Updated with newly ignited cells.
 * - `availCells`: Reduced by removing newly burning cells.
 * - `fire_period`: Incremented at the end of each fire period.
 * - `year`: Incremented if no messages are sent and `repeatFire` is false.
 *
 * ### Verbose Mode:
 * When `args.verbose` is enabled:
 * - Logs detailed information about fire messages, ignition, and cell state
 * transitions.
 * - Prints the current state of cell sets (available, non-burnable, burning,
 * burnt, harvested).
 *
 * ### Weather Updates:
 * - Calls `updateWeather` to apply weather conditions for the next fire
 * period.
 * - Provides a note if the weather is constant, indicating its effect on the
 * fire model.
 */
void
Cell2Fire::GetMessages(std::unordered_map<int, std::vector<int>> sendMessageList)
{
    // Iterator
    std::unordered_map<int, Cells>::iterator it;

    // Information of the current step
    if (this->args.verbose)
    {
        std::cout << "\n---------------------- Step 3: Receiving and processing "
                     "messages from Ignition ----------------------"
                  << std::endl;
        std::cout << "Current Fire Period: " << this->fire_period[this->year - 1] << std::endl;
        printSets(this->availCells, this->nonBurnableCells, this->burningCells, this->burntCells, this->harvestCells);
    }

    // Conditions depending on number of messages and repeatFire flag
    // No messages but repetition
    if (this->repeatFire && !this->messagesSent)
    {
        if (this->args.verbose)
        {
            std::cout << "Fires are still alive, no message generated" << std::endl;
            std::cout << "Current fire period: " << this->fire_period[this->year - 1] << std::endl;
        }
        this->fire_period[this->year - 1] += 1;

        // Check if we need to update the weather
        this->updateWeather();
    }

    // Messages and repetition
    if (this->repeatFire && this->messagesSent)
    {
        if (this->args.verbose)
            std::cout << "Messages have been sent, next step. Current period: " << this->fire_period[this->year - 1]
                      << std::endl;
        this->repeatFire = false;
    }

    // No messages, no repeat (break and next year)
    if (!this->messagesSent && !this->repeatFire)
    {
        if (this->args.verbose)
        {
            std::cout << "\nNo messages during the fire period, end of year " << this->year << std::endl;
        }
        // Next year, reset weeks, weather period, and update burnt cells from
        // burning cells
        this->year += 1;
        this->weatherPeriod = 0;
        this->noMessages = true;
        // Update sets
        for (auto& bc : this->burningCells)
        {
            this->burntCells.insert(bc);
        }
        this->burningCells.clear();
        if (this->args.verbose)
            printSets(
                this->availCells, this->nonBurnableCells, this->burningCells, this->burntCells, this->harvestCells);
    }

    // Mesages and no repeat
    if (this->messagesSent && !this->repeatFire)
    {

        // frequency array
        std::unordered_map<int, int> globalMessagesList;
        for (auto& sublist : sendMessageList)
        {
            for (int val : sublist.second)
            {
                if (globalMessagesList.find(val) == globalMessagesList.end())
                {
                    globalMessagesList[val] = 1;
                }
                else
                {
                    globalMessagesList[val] = globalMessagesList[val] + 1;
                }
            }
        }

        // Initialize cells if needed (getting messages)
        for (auto& _bc : globalMessagesList)
        {
            int bc = _bc.first;
            if (this->Cells_Obj.find(bc) == this->Cells_Obj.end()
                && this->burntCells.find(bc) == this->burntCells.end())
            {
                // Initialize cell, insert it inside the unordered map
                InitCell(bc);
                it = this->Cells_Obj.find(bc);
            }
        }

        // Get burnt loop
        if (this->args.verbose)
        {
            for (auto& _bc : globalMessagesList)
            {
                printf("CELL %d inside global message list \n", _bc.first);
            }
        }

        std::unordered_set<int> burntList;
        bool checkBurnt;
        for (auto& _bc : globalMessagesList)
        {
            // printf("\n\nWE ARE DEBUGGING!!!! CELL TO BE ANALYZED GET BURNT IS
            // %d\n", _bc.first);
            int bc = _bc.first;
            if (this->burntCells.find(bc) == this->burntCells.end())
            {
                if (this->Cells_Obj.find(bc) == this->Cells_Obj.end())
                {

                    // Initialize cell, insert it inside the unordered map
                    InitCell(bc);
                    it = this->Cells_Obj.find(bc);
                }
                else
                    it = this->Cells_Obj.find(bc);

                // Check if burnable, then check potential ignition
                if (it->second.fType != 0)
                {
                    checkBurnt = it->second.get_burned(this->fire_period[this->year - 1],
                                                       1,
                                                       this->year,
                                                       df,
                                                       this->coef_ptr,
                                                       this->args_ptr,
                                                       &wdf[this->weatherPeriod],
                                                       this->activeCrown,
                                                       this->perimeterCells);
                }
                else
                {
                    checkBurnt = false;
                }

                // Print-out regarding the burnt cell
                if (this->args.verbose)
                {
                    std::cout << "\nCell " << it->second.realId << " got burnt (1 true, 0 false): " << checkBurnt
                              << std::endl;
                }

                // Update the burntlist
                if (checkBurnt)
                {
                    burntList.insert(it->second.realId);

                    // Cleaning step
                    // Fire can't be propagated back
                    int cellNum = it->second.realId - 1;
                    for (auto& angle : it->second.angleToNb)
                    {
                        int origToNew = angle.first;
                        // Which neighbor am I to the burnt cell
                        int newToOrig = (origToNew + 180) % 360;
                        int adjCellNum = angle.second;  // Check
                        auto adjIt = Cells_Obj.find(adjCellNum);
                        if (adjIt != Cells_Obj.end())
                        {
                            adjIt->second.ROSAngleDir.erase(newToOrig);
                        }
                    }
                }
            }
        }

        // Update sets
        for (auto& bc : burntList)
        {
            this->burntCells.insert(bc);
        }

        for (auto& bc : this->burnedOutList)
        {
            this->burntCells.insert(bc);
        }

        for (auto& bc : burntList)
        {
            this->burningCells.insert(bc);
        }

        for (auto& bc : burningCells)
        {
            auto lt = this->availCells.find(bc);
            if (lt != this->availCells.end())
            {
                this->availCells.erase(bc);
            }
        }

        // Display info for debugging
        if (this->args.verbose)
        {
            printSets(
                this->availCells, this->nonBurnableCells, this->burningCells, this->burntCells, this->harvestCells);
        }

        /*
         *					Next Period
         */
        this->fire_period[this->year - 1] += 1;

        // If weather is not constant (random weather to be supported in next
        // commit...)
        this->updateWeather();

        // Message for constant weather
        if (this->args.WeatherOpt.compare("constant") == 0 && this->args.verbose)
        {
            std::cout << "(NOTE: current weather is not used for ROS with "
                         "constant option)"
                      << std::endl;
        }
    }
}

/**
 * @brief Generates and outputs simulation results, including fire behavior
 * metrics, final grid status, and logs.
 *
 * This method processes the results of the fire simulation, updating cell
 * statuses and generating various outputs such as grid data, fire spread
 * metrics, and intensity logs. It supports multiple file formats (e.g., CSV,
 * ASCII) and organizes output into designated folders for easy analysis and
 * debugging.
 *
 * ### Behavior:
 * - Updates the status of cells:
 *   - `burntCells` and `burningCells` are marked as fully burnt (`status =
 * 2`).
 * - Computes summary statistics:
 *   - Reports the number and percentage of available, burnt, non-burnable, and
 * firebreak cells.
 * - Writes outputs to files:
 *   - **Grid Status**: Outputs the final grid state to a CSV file if
 * `args.FinalGrid` is enabled.
 *   - **Network Messages**: Logs fire message data to a CSV file if
 * `args.OutMessages` is enabled.
 *   - **Fire Spread Metrics**:
 *     - Rate of Spread (ROS)
 *     - Byram Intensity
 *     - Flame Length
 *     - Crown Fraction Burn
 *     - Surface Fraction Burn
 *     - Crown Fire Behavior
 * - **Ignition Log**: Logs ignition history if `args.IgnitionsLog` is enabled.
 *
 * ### Outputs:
 * - The output files are organized into subfolders under the designated output
 * directory (`args.OutFolder`).
 * - Naming conventions include simulation IDs (`sim`) to ensure unique file
 * names.
 * - File types:
 *   - CSV for grids and messages.
 *   - ASCII for rate of spread, intensity, flame length, and other fire
 * behavior metrics.
 *
 *
 * ### Example Output:
 * ```
 * ----------------------------- Results -----------------------------
 * Total Available Cells:    120 - % of the Forest: 40.0%
 * Total Burnt Cells:        80 - % of the Forest: 26.67%
 * Total Non-Burnable Cells: 100 - % of the Forest: 33.33%
 * Total Firebreak Cells:    10 - % of the Forest: 3.33%
 * ```
 *
 * ### Notes:
 * - Ensure the output directory structure exists before running the simulation
 * to avoid file I/O errors.
 * - This method supports optional outputs, which can be toggled using
 * command-line arguments.
 */
void
Cell2Fire::Results()
{
    /*****************************************************************************
     *
     *												Steps
     *4: Results and outputs
     *
     ******************************************************************************/
    // Iterator
    // Declare an iterator to unordered_map
    std::unordered_map<int, Cells>::iterator it;
    int i;

    for (auto& br : this->burntCells)
    {
        if (this->Cells_Obj.find(br) != this->Cells_Obj.end())
        {
            // Get object from unordered map
            it = this->Cells_Obj.find(br);

            // Initialize the fire fields for the selected cel
            it->second.status = 2;
        }
    }

    for (auto& br : this->burningCells)
    {
        if (this->Cells_Obj.find(br) != this->Cells_Obj.end())
        {
            // Get object from unordered map
            it = this->Cells_Obj.find(br);

            // Initialize the fire fields for the selected cel
            it->second.status = 2;
        }
    }

    // Final results for comparison with Python
    // DEBUGstd::cout  << "\n ------------------------ Final results for
    // comparison with Python ------------------------";

    // Final report
    float ACells = this->availCells.size();
    float BCells = this->burntCells.size();
    float NBCells = this->nonBurnableCells.size();
    float HCells = this->harvestCells.size();

    std::cout << "\n----------------------------- Results "
                 "-----------------------------"
              << std::endl;
    std::cout << "Total Available Cells:    " << ACells << " - % of the Forest: " << ACells / nCells * 100.0 << "%"
              << std::endl;
    std::cout << "Total Burnt Cells:        " << BCells << " - % of the Forest: " << BCells / nCells * 100.0 << "%"
              << std::endl;
    std::cout << "Total Non-Burnable Cells: " << NBCells << " - % of the Forest: " << NBCells / nCells * 100.0 << "%"
              << std::endl;
    std::cout << "Total Firebreak Cells: " << HCells << " - % of the Forest: " << HCells / nCells * 100.0 << "%"
              << std::endl;

    // Final Grid
    if (this->args.FinalGrid)
    {
        CSVWriter CSVFolder("", "");
        if (this->args.OutFolder.empty())
            this->gridFolder = this->args.InFolder + "simOuts" + separator() + "Grids" + separator() + "Grids"
                               + std::to_string(this->sim) + separator();
        else
            this->gridFolder
                = this->args.OutFolder + "Grids" + separator() + "Grids" + std::to_string(this->sim) + separator();
        // std::string gridName = this->gridFolder + "FinalStatus_" +
        // std::to_string(this->sim) + ".csv";
        outputGrid();
    }

    // Messages
    if (this->args.OutMessages)
    {
        this->messagesFolder = this->args.OutFolder + "Messages" + separator();
        std::string messagesName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        messagesName = this->messagesFolder + "MessagesFile" + oss.str() + ".csv";
        if (this->args.verbose)
        {
            std::cout << "We are generating the network messages to a csv file " << messagesName << std::endl;
        }
        CSVWriter CSVPloter(messagesName, ",");
        // CSVPloter.printCSVDouble_V2(this->FSCell.size() - this->nIgnitions, 4,
        // this->FSCell);
        CSVPloter.printCSVDouble_V2(this->FSCell.size() / 4, 4, this->FSCell);
    }

    // RateOfSpread
    if (this->args.OutRos)
    {
        this->rosFolder = this->args.OutFolder + "RateOfSpread" + separator();
        std::string rosName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        rosName = this->rosFolder + "ROSFile" + oss.str() + ".asc";
        if (this->args.verbose)
        {
            std::cout << "We are generating the Rate of Spread to a asc file " << rosName << std::endl;
        }
        CSVWriter CSVPloter(rosName, " ");
        CSVPloter.printASCII(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->RateOfSpreads);
    }

    // Intensity
    if (this->args.OutIntensity)
    {
        this->surfaceIntensityFolder = this->args.OutFolder + "SurfaceIntensity" + separator();
        std::string intensityName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        intensityName = this->surfaceIntensityFolder + "SurfaceIntensity" + oss.str() + ".asc";

        if (this->args.verbose)
        {
            std::cout << "We are generating the Byram Intensity to a asc file " << intensityName << std::endl;
        }
        CSVWriter CSVPloter(intensityName, " ");
        CSVPloter.printASCII(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->surfaceIntensities);
    }

    // Crown Intensity
    if ((this->args.OutIntensity) && (this->args.AllowCROS) && (this->args.Simulator == "S"))
    {
        this->crownIntensityFolder = this->args.OutFolder + "CrownIntensity" + separator();
        std::string intensityName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        intensityName = this->crownIntensityFolder + "CrownIntensity" + oss.str() + ".asc";
        if (this->args.verbose)
        {
            std::cout << "We are generating the Crown Intensity to a asc file " << intensityName << std::endl;
        }
        CSVWriter CSVPloter(intensityName, " ");
        CSVPloter.printASCII(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->crownIntensities);
    }

    // Surface Flame Length
    if (this->args.OutFl)
    {
        this->surfaceFlameLengthFolder = this->args.OutFolder + "SurfaceFlameLength" + separator();
        std::string flName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        flName = this->surfaceFlameLengthFolder + "SurfaceFlameLength" + oss.str() + ".asc";
        if (this->args.verbose)
        {
            std::cout << "We are generating the Flame Length to a asc file " << flName << std::endl;
        }
        CSVWriter CSVPloter(flName, " ");
        CSVPloter.printASCII(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->surfaceFlameLengths);
    }

    // Crown Flame length
    if ((this->args.OutFl) && (this->args.AllowCROS) && (this->args.Simulator == "S"))
    {
        this->crownFlameLengthFolder = this->args.OutFolder + "CrownFlameLength" + separator();
        std::string fileName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        fileName = this->crownFlameLengthFolder + "CrownFlameLength" + oss.str() + ".asc";
        if (this->args.verbose)
        {
            std::cout << "We are generating the Crown Flame Length to a asc file " << fileName << std::endl;
        }
        CSVWriter CSVPloter(fileName, " ");
        CSVPloter.printASCII(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->crownFlameLengths);
    }

    // Max Flame length
    if ((this->args.OutFl) && (this->args.AllowCROS) && (this->args.Simulator == "S"))
    {
        this->maxFlameLengthFolder = this->args.OutFolder + "MaxFlameLength" + separator();
        std::string fileName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        fileName = this->maxFlameLengthFolder + "MaxFlameLength" + oss.str() + ".asc";
        if (this->args.verbose)
        {
            std::cout << "We are generating the Max Flame Length to a asc file " << fileName << std::endl;
        }
        CSVWriter CSVPloter(fileName, " ");
        CSVPloter.printASCII(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->maxFlameLengths);
    }

    // Intensity
    if ((this->args.OutCrownConsumption) && (this->args.AllowCROS))
    {
        this->cfbFolder = this->args.OutFolder + "CrownFractionBurn" + separator();
        std::string cfbName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        cfbName = this->cfbFolder + "Cfb" + oss.str() + ".asc";
        if (this->args.verbose)
        {
            std::cout << "We are generating the Crown Fraction Burn to a asc file " << cfbName << std::endl;
        }
        CSVWriter CSVPloter(cfbName, " ");
        CSVPloter.printASCII(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->crownFraction);
    }

    // Intensity
    if ((this->args.OutSurfConsumption) && (this->args.Simulator == "C"))
    {
        this->sfbFolder = this->args.OutFolder + "SurfFractionBurn" + separator();
        std::string sfbName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        sfbName = this->sfbFolder + "Sfb" + oss.str() + ".asc";
        if (this->args.verbose)
        {
            std::cout << "We are generating the Surface Fraction Burn to a asc file " << sfbName << std::endl;
        }
        CSVWriter CSVPloter(sfbName, " ");
        CSVPloter.printASCII(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->surfFraction);
    }

    // Crown
    if ((this->args.OutCrown) && (this->args.AllowCROS))
    {
        this->crownFolder = this->args.OutFolder + "CrownFire" + separator();
        std::string crownName;
        std::ostringstream oss;
        oss.str("");
        oss << std::setfill('0') << std::setw(this->widthSims) << this->sim;
        crownName = this->crownFolder + "Crown" + oss.str() + ".asc";
        if (this->args.verbose)
        {
            std::cout << "We are generating the Crown behavior to a asc file " << crownName << std::endl;
        }
        CSVWriter CSVPloter(crownName, " ");
        // CSVPloter.printCrownAscii(this->rows, this->cols, this->xllcorner,
        // this->yllcorner, this->cellSide, this->crownMetrics, statusCells2);
        // /OLD VERSION
        CSVPloter.printASCIIInt(
            this->rows, this->cols, this->xllcorner, this->yllcorner, this->cellSide, this->crownState);
    }

    // Ignition Logfile
    if (currentSim == args.TotalSims && this->args.IgnitionsLog)
    {

        std::cout << "Writing ignitions log csv..." << endl;
        if (this->args.verbose)
        {
            std::cout << "(simulation_id, cell_id): ";
            for (i = 1; i < IgnitionHistory.size() + 1; i++)
            {
                std::cout << i << "," << IgnitionHistory[i] << "\t";
            }
        }

        std::string filename = "ignitions_log.csv";
        CSVWriter igHistoryFolder("", "");
        this->ignitionsFolder = this->args.OutFolder + "IgnitionsHistory" + separator();
        igHistoryFolder.MakeDir(this->ignitionsFolder);
        CSVWriter ignitionsFile(this->ignitionsFolder + filename);
        ignitionsFile.printIgnitions(IgnitionHistory);
    }
}

/**
 * @brief Outputs the current state of the forest grid to a CSV file.
 *
 * This method generates a binary representation of the forest grid, with cell
 * statuses indicating their condition (burning, burnt, harvested, etc.) during
 * the simulation. The file is saved with a unique name in the designated
 * output folder.
 *
 * ### Behavior:
 * - **Cell Status Update**:
 *   - Updates a vector (`statusCells2`) to reflect the current statuses of
 * cells:
 *     - `1` for burning or burnt cells.
 *     - `-1` for harvested cells.
 *     - `0` for all other cells.
 * - **File Naming**:
 *   - Constructs a file name based on the simulation's `gridNumber` and saves
 * it in the `gridFolder` directory.
 *   - File names follow the pattern: `ForestGrid<gridNumber>.csv`.
 * - **Verbose Mode**:
 *   - Logs the file name and output process to the console if `args.verbose`
 * is enabled.
 * - **Output Format**:
 *   - The CSV file represents the forest grid in rows and columns, with each
 * cell's status stored in `statusCells2`.
 *
 * ### Outputs:
 * - A CSV file is saved in the `gridFolder` directory, with the grid's state
 * for the current simulation step.
 * - Example CSV content:
 *   ```
 *   0, 0, 1, 0
 *   0, -1, 0, 1
 *   1, 0, 0, 0
 *   ```
 *
 * ### Notes:
 * - Ensure the `gridFolder` directory exists before calling this method to
 * avoid file I/O errors.
 * - The method automatically increments `gridNumber` after each call to ensure
 * unique file names.
 */
void
Cell2Fire::outputGrid()
{
    // FileName
    std::string gridName;
    std::vector<int> statusCells2(this->nCells, 0);  //(long int, int);

    // Update status
    for (auto& bc : this->burningCells)
    {
        statusCells2[bc - 1] = 1;
    }
    for (auto& ac : this->burntCells)
    {
        statusCells2[ac - 1] = 1;
    }
    for (auto& hc : this->harvestCells)
    {
        statusCells2[hc - 1] = -1;
    }
    std::ostringstream oss;
    oss.str("");
    oss << std::setfill('0') << std::setw(this->widthSims) << this->gridNumber;
    gridName = this->gridFolder + "ForestGrid" + oss.str() + ".csv";
    if (this->args.verbose)
    {
        std::cout << "We are plotting the current forest to a csv file " << gridName << std::endl;
    }

    CSVWriter CSVPloter(gridName, ",");
    CSVPloter.printCSV(this->rows, this->cols, statusCells2);
    this->gridNumber++;
}

/**
 * @brief Updates the weather conditions during the simulation based on
 * specified criteria.
 *
 * This method dynamically updates the weather parameters used in the
 * simulation based on the simulation's fire period and weather options. It can
 * optionally output the current state of the forest grid and log weather
 * updates if verbose mode is enabled.
 *
 * ### Behavior:
 * - **Weather Update Check**:
 *   - Weather is updated if:
 *     - The `WeatherOpt` argument is not set to `"constant"`.
 *     - The fire period multiplied by the fire period length exceeds the
 * current `weatherPeriod`.
 *   - When the conditions are met, the `weatherPeriod` is incremented.
 * - **Grid Output**:
 *   - If the `OutputGrids` argument is enabled, the current forest grid is
 * output using the `outputGrid` method.
 * - **Verbose Logging**:
 *   - If `verbose` mode is enabled:
 *     - Logs the weather update to the console.
 *     - Prints detailed weather information for the current period using
 * `CSVWeather.printWeatherDF`.
 */
void
Cell2Fire::updateWeather()
{
    if (this->args.WeatherOpt != "constant"
        && this->fire_period[this->year - 1] * this->args.FirePeriodLen / this->args.MinutesPerWP
               > this->weatherPeriod + 1)
    {
        this->weatherPeriod++;
        if (this->args.OutputGrids)
        {
            this->outputGrid();
        }
        if (this->args.verbose)
        {
            std::cout << "\nWeather has been updated" << std::endl;
            this->CSVWeather.printWeatherDF(wdf[this->weatherPeriod]);
        }
    }
}

/**
 * @brief Executes a single simulation step in the forest fire model.
 *
 * This method simulates one fire period, handling all related processes such
 * as ignition, message exchange, weather updates, and transitioning between
 * simulation years or scenarios. It is the core operational logic for
 * advancing the simulation in discrete steps.
 *
 * ### Behavior:
 * - **Verbose Logging**:
 *   - If `verbose` is enabled, prints details about the current simulation
 * state, including the year, fire period, weather period, and grid status.
 *
 * - **Simulation Logic**:
 *   - **End of Simulation Checks**:
 *     - Ends the simulation if the current year exceeds the total years
 * (`TotalYears`).
 *     - If the available cells or burning cells are empty, the simulation is
 * marked as complete.
 *   - **Ignition**:
 *     - Handles ignition logic during the first fire period. If no ignition
 * occurs, checks for available burning cells.
 *   - **Fire Spread**:
 *     - Processes fire spread by sending and receiving messages between cells.
 *   - **Weather Updates**:
 *     - Resets the weather period at the start of each new year.
 *   - **Fire Period Limits**:
 *     - If the current fire period exceeds the maximum allowed fire periods
 * (`MaxFirePeriods`), advances to the next year.
 *   - **Results Handling**:
 *     - Outputs results and weather history if required.
 *
 * - **Transition to Next Simulation**:
 *   - Advances to the next simulation if the maximum year or conditions for
 * termination are met.
 *   - Handles additional simulation-specific logic based on weather options
 * and history requirements.
 *
 */
void
Cell2Fire::Step(std::default_random_engine generator, int ep)
{
    // Iterator
    // Declare an iterator to unordered_map
    std::unordered_map<int, Cells>::iterator it;
    bool auxC = false;
    this->noMessages = false;
    // Conditions entering the step
    if (this->args.verbose)
    {
        std::cout << "********************************************" << std::endl;
        std::cout << "Year: " << this->year << std::endl;
        std::cout << "Fire Period: " << this->fire_period[this->year - 1] << std::endl;
        std::cout << "WeatherPeriod: " << this->weatherPeriod << std::endl;
        std::cout << "MaxFirePeriods: " << this->args.MaxFirePeriods << std::endl;
        printSets(this->availCells, this->nonBurnableCells, this->burningCells, this->burntCells, this->harvestCells);
        std::cout << "********************************************" << std::endl;
    }
    // One step (one fire period, ignition - if needed -, sending messages and
    // receiving them - if needed) For completeness: just in case user runs it
    // longer than the horizon (should not happen)
    if (this->year > this->args.TotalYears)
    {
        if (this->args.verbose)
        {
            printf("\nYear is greater than the Horizon, no more steps");
        }
        this->done = true;
        // Print-out results to folder
        if (this->args.verbose)
            this->Results();

        // Next Sim
        this->sim += 1;
    }
    // Info
    if (this->args.verbose)
    {
        std::cout << "\nSimulating year" << this->year << "\nOut of totalYears:" << this->args.TotalYears;
    }
    // New operational step (ONE fire period)
    if (this->fire_period[this->year - 1] > 0 && !this->done)
    {
        // Fire Spread (one time step of RL - Operational)
        // Send messages after ignition (does not advance time!)
        std::unordered_map<int, std::vector<int>> SendMessageList = this->SendMessages();
        // Get Message
        this->GetMessages(SendMessageList);
    }
    // Operational dynamic
    // Ignition if we are in the first period (added workaround for no Messages)
    if (!this->done && !this->noMessages)
    {
        if (this->fire_period[this->year - 1] == 0)
        {
            // std::cout << "Entra a Ignition step 0" << std::endl;
            //  Continue only if ignition  - No ignition (True): done
            if (this->RunIgnition(generator, ep))
            {
                // Next year
                this->weatherPeriod = 0;
                // If more than planning horizon, next sim
                if (this->year > this->args.TotalYears)
                {
                    // Print-out results to folder
                    this->Results();
                    // Next Sim if max year
                    this->done = true;
                }
            }
            else
            {
                // Start sending messages
                std::unordered_map<int, std::vector<int>> SendMessageList = this->SendMessages();
                // Get Message
                this->GetMessages(SendMessageList);
                // Check if no burning cells to stop
                if (this->burningCells.size() == 0)
                {
                    // Next Sim if max year
                    this->done = true;
                }
            }
        }
    }
    // Ending conditions
    if (this->fire_period[std::min(this->year, int(fire_period.size())) - 1] >= this->args.MaxFirePeriods)
    {
        // Extra breaking condition: Max fire periods then go to next year
        if (this->args.verbose)
        {
            printf("\nNext year due to max periods...\n");
        }
        // Next Year/Season update
        this->weatherPeriod = 0;
        auxC = true;
        for (auto& bc : burningCells)
        {
            auto lt = this->availCells.find(bc);
            if (lt != this->availCells.end())
            {
                this->availCells.erase(bc);
            }
            this->burntCells.insert(bc);
        }
        this->burningCells.clear();
    }
    // If more than planning horizon, next sim
    if (this->year > this->args.TotalYears)
    {
        // printf("\n\nEntra a year mayor al total...\n\n");
        //  Print-out results to folder
        this->Results();
        // Next Sim if max year
        this->sim += 1;
        this->done = true;
    }
    // Done flag (extra condition: no available cells or death of the team)
    if ((this->availCells.size() == 0) || (this->burningCells.size() == 0 && !this->noMessages) && !this->done && !auxC)
    {
        // Done
        this->done = true;
        // Print-out results to folder
        this->Results();
        // Next Sim if max year
        this->sim += 1;
    }

    // Print current status
    if (!this->done && this->args.verbose)
    {
        printf("\nFire Period: %d", this->fire_period[this->year - 1]);
        printf("\nYear: %d \n\n", this->year);
    }
}

void
Cell2Fire::InitHarvested()
{
    std::cout << "OK";
}

/**
 * @brief Retrieves the Rate of Spread (ROS) matrix for all cells.
 *
 * @return A vector of floats representing the ROS values for each cell.
 */
std::vector<float>
Cell2Fire::getROSMatrix()
{
    std::vector<float> ROSMatrix(this->nCells, 0);
    return ROSMatrix;
}

/**
 * @brief Retrieves the Fire Progress matrix for all cells.
 *
 * @return A vector of floats representing the fire progress values for each
 * cell.
 */
std::vector<float>
Cell2Fire::getFireProgressMatrix()
{
    std::vector<float> ProgressMatrix(this->nCells, 0);
    return ProgressMatrix;
}

/******************************************************************************

                                                                                                                                Main Program

*******************************************************************************/
/**
 * @brief Entry point for the Cell2Fire simulation program.
 *
 * This function initializes the simulation environment, reads input arguments,
 * and executes the main simulation loop, either in serial or parallel mode.
 * The program simulates fire spread across a forest landscape using stochastic
 * methods.
 *
 * @return Exit status of the program (0 for success).
 *
 * The main tasks performed include:
 * - Parsing command-line arguments.
 * - Initializing the forest simulation object and random number generators.
 * - Executing simulation episodes in parallel, with each episode representing
 * a replication.
 * - Resetting the environment and running simulation steps until completion
 * conditions are met.
 * - Handling multi-threading for parallel simulations.
 *
 */
int
main(int argc, char* argv[])
{
    // Read Arguments
    std::cout << "------ Command line values ------\n";
    arguments args;
    arguments* args_ptr = &args;
    parseArgs(argc, argv, args_ptr);
    GenDataFile(args.InFolder, args.Simulator);
    int ep = 0;
    int tstep = 0;
    int stop = 0;
    // Episodes loop (episode = replication)
    // CP: Modified to account the case when no ignition occurs and no grids are
    // generated (currently we are not generating grid when no ignition happened,
    // TODO)
    int num_threads = args.nthreads;
    int TID = 0;
    Cell2Fire Forest2(args);  // generate Forest object
    std::vector<Cell2Fire> Forests(num_threads, Forest2);

    // Multigenerator
    std::vector<std::default_random_engine> generators;
    for (stop = 0; stop < args.TotalSims; ++stop)
    {
        generators.emplace_back(default_random_engine(args.seed * stop));
    }

// Parallel zone
#pragma omp parallel num_threads(num_threads)
    {
        // Number of threads
        TID = omp_get_thread_num();
        if (TID == 0 && omp_get_num_threads() < 2)
        {
            cout << "There are " << omp_get_num_threads() << " threads" << endl;
        }
        else
        {
            cout << "Serial version execution" << endl;
        }
        Cell2Fire Forest = Forests[TID];
        // Random seed
        std::default_random_engine& generator = generators[TID];  // generators[args.nthreads]
        // Random generator and distributions
        std::uniform_int_distribution<int> udistribution(1, args.NWeatherFiles);  // Get random weather
        std::normal_distribution<double> ndistribution(0.0, 1.0);                 // ROSRV
        // Random numbers (weather file and ROS-CV)
        int rnumber;
        double rnumber2;
        std::uniform_int_distribution<int> udistributionIgnition(1, Forest.nCells);  // Get random ignition point
        // Steps and stop
        int ep = 0;
        int tstep = 0;
        int stop = 0;
#pragma omp for
        for (ep = 1; ep <= args.TotalSims; ep++)
        {
            TID = omp_get_thread_num();
            // Reset environment (passing new random numbers)
            generator = generators[TID];  // generators[args.nthreads]
            rnumber = udistribution(generator);
            rnumber2 = ndistribution(generator);
            // Reset
            Forest.reset(rnumber, rnumber2, ep);
            // Time steps during horizon (or until we break it)
            for (tstep = 0; tstep <= Forest.args.MaxFirePeriods * Forest.args.TotalYears; tstep++)
            {
                Forest.Step(generator, ep);

                if (Forest.done)
                {
                    break;
                }
            }
        }
    }
    delete[] df;
    return 0;
}
