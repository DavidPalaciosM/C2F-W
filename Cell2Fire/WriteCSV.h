#ifndef WRITECSV
#define WRITECSV

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/*
 * A class to read data from a csv file.
 */
class CSVWriter
{
  public:
    // inmutable
    std::string fileName;
    std::string delimeter;

    // mutable
    int linesCount;

    // Constructor
    CSVWriter(std::string filename, std::string delm = ",");

    // Function to write data (row) to a CSV File
    template <typename T>
    void addDatainRow(T first, T last);

    // Function to write the entire file
    void printCSV(int rows, int cols, std::vector<int> statusCells);
    void printCSVDouble(int rows, int cols, std::vector<double> network);
    void printCSVDouble_V2(int rows, int cols, std::vector<double> network);
    void
    printASCII(int rows, int cols, double xllcorner, double yllcorner, int cellside, std::vector<float> statusCells);
    void
    printASCIIInt(int rows, int cols, double xllcorner, double yllcorner, int cellside, std::vector<int> statusCells);
    void asciiHeader(int rows, int cols, double xllcorner, double yllcorner, int cellside);
    void printWeathers(std::unordered_map<int, std::string> weathersHistory);
    void printIgnitions(std::unordered_map<int, int> ignitionsHistory);
    void printCSV_V2(int rows, int cols, std::vector<int> statusCells);
    // Function to create a directory
    void MakeDir(std::string pathPlot);
};

#endif
