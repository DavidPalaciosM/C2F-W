#ifndef WRITECSV
#define WRITECSV

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <unordered_map>
#include <unordered_set>
#include <set>

 /*
 * A class to read data from a csv file.
 */
class CSVWriter{ 
public:
	// inmutable 
	std::string fileName;
	std::string delimeter;
	
	// mutable
	int linesCount;
	
	
	// Constructor
	CSVWriter(std::string filename, std::string delm = ",");
 
	// Function to write data (row) to a CSV File
	template<typename T>
	void addDatainRow(T first, T last);
	
	// Function to write the entire file 
	void printCSV(int rows, int cols, std::vector<int> statusCells);
	void printCSVDouble(int rows, int cols, std::vector<double> network);
	void printCSVDouble_V2(int rows, int cols, std::vector<double> network);
	void printASCII(int rows, int cols, double xllcorner, double yllcorner, int cellside, std::vector<float> statusCells);
	void printASCIIInt(int rows, int cols, double xllcorner, double yllcorner, int cellside, std::vector<int> statusCells);
	void asciiHeader(int rows, int cols, double xllcorner, double yllcorner, int cellside);
	void printWeather(std::vector<std::string> weatherHistory);
	void printCO2(std::vector<float> co2History);
	void printCSV_V2(int rows, int cols, std::vector<int> statusCells);
	// Function to create a directory
	void MakeDir(std::string pathPlot);
};
 
#endif
