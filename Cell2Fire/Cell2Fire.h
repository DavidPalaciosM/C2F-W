#ifndef CELL2FIRE
#define CELL2FIRE

// Headers
#include "Cells.h"
#include "Spotting.h"
#include "FuelModelSpain.h"
#include "FuelModelKitral.h"
#include "ReadCSV.h"
#include "WriteCSV.h"
#include "ReadArgs.h"
#include "Lightning.h"
#include "DataGenerator.h"

// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <string.h>
#include <random>
#include <algorithm> 
#include <memory>

using namespace std;

std::string c2fw_version = "v0.0.1";

class Cell2Fire {
	// DFs 
	private:
		CSVReader CSVWeather;
		CSVReader CSVForest;
			
    public: 
		 // Main inputs
		 arguments args;
		 arguments* args_ptr;
		 fuel_coefs* coef_ptr;
		 fuel_coefs coefs[18];	
		 
		 // Integers
		 int sim;
		 int rows;
		 int cols;
		 int widthSims;
		 int weatherPeriod = 0;
		 int year = 1;
		 int gridNumber = 0;
		 int weatherperiod = 0;
		 int counter_wt = 0;
		 long int nCells;
		 int nIgnitions = 0;
		 double xllcorner;
		 double yllcorner;
		 // Booleans
		 bool noIgnition = true;  		//  None = -1
		 bool activeCrown=false;
		 bool messagesSent = false;
		 bool repeatFire = false;
		 bool done = false;
		 bool noMessages = false;
		 
		 // Doubles
		 double cellSide;
		 double areaCells;
		 double perimeterCells;
		 double ROSRV;
			
		// Strings	
		 string gridFolder;
		 string messagesFolder;
		 string rosFolder;
		 string crownFolder;
		 string intensityFolder;
		 string sfbFolder;
		 string cfbFolder;
		 string flFolder;
		 string historyFolder;
		 string ignitionsFolder;
	
		 // Vectors
		 std::vector<int> fire_period;
		 std::vector<std::vector<int>> coordCells;
		 std::vector<std::unordered_map<std::string, int>> adjCells;
		 std::vector<std::vector<std::string>> DF;
		 std::vector<std::vector<std::string>> WDist;
		 std::vector<std::string> WeatherHistory;
		 std::vector<float> ignProb; // (long int&, int);
		 std::vector<int> statusCells; //(long int, int);
		 std::vector<int> fTypeCells; // (long int&, int); 
		 std::vector<string> fTypeCells2; // (long int&, const char [9]);
		 std::vector<std::vector<std::string>> WeatherDF;
		 std::vector<int> IgnitionPoints;
		 vector<int> burnedOutList;
		 std::vector<double> FSCell;
		 std::vector<float> crownMetrics;
		 std::vector<int>crownState;
		 std::vector<float>Intensities;
		 std::vector<float>crownFraction;
		 std::vector<float>surfFraction;
		 std::vector<float>RateOfSpreads;
		 std::vector<float>FlameLengths;
		 std::vector<std::vector<int>> IgnitionSets;
		 // std::vector<int> IgnitionHistory;

		 // Sets
		 std::unordered_set<int> availCells;				
		 std::unordered_set<int> nonBurnableCells; 	
		 std::unordered_set<int> burningCells;
		 std::unordered_set<int> burntCells;
		 std::unordered_set<int> harvestCells;
		 
		 // Cells Dictionary
		 std::unordered_map<int, Cells> Cells_Obj;
		 
		 // Constructor
        Cell2Fire(arguments args);
		
		// Methods
		void InitCell(int id);
        void reset(int rnumber, double rnumber2, int simExt);
		bool RunIgnition(std::default_random_engine generator, int ep);
		std::unordered_map<int, std::vector<int>> SendMessages();
		void GetMessages(std::unordered_map<int, std::vector<int>> sendMessageList);
		void Results();
		void outputGrid();
		void updateWeather();
		void Step(std::default_random_engine generator, int ep);
		void InitHarvested();
		
		// Utils
		std::vector<float> getROSMatrix();
		std::vector<float> getFireProgressMatrix();
};

#endif
