#include "WriteCSV.h"

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

#if defined _WIN32 || defined __CYGWIN__
#include <Windows.h>
#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

/*
 * Constructur
 */
CSVWriter::CSVWriter(std::string filename, std::string delm)
{
    this->fileName = filename;
    this->delimeter = delm;
    this->linesCount = 0;
}

/*
 * Prints iterator into a row of a csv file
 */
template <typename T>
void
CSVWriter::addDatainRow(T first, T last)
{
    std::fstream file;
    // Open the file in truncate mode if first line else in Append Mode
    file.open(this->fileName, std::ios::out | (this->linesCount ? std::ios::app : std::ios::trunc));

    // Iterate over the range and add each element to file seperated by
    // delimeter.
    for (; first != last;)
    {
        file << *first;
        if (++first != last)
            file << this->delimeter;
    }
    file << "\n";
    this->linesCount++;

    // Close the file
    file.close();
}

void
CSVWriter::asciiHeader(int rows, int cols, double xllcorner, double yllcorner, int cellside)
{
    std::fstream file;
    // Open the file in truncate mode if first line else in Append Mode
    file.open(this->fileName, std::ios::out | (this->linesCount ? std::ios::app : std::ios::trunc));
    // first line: coles
    file << "ncols";
    file << this->delimeter;
    file << cols;
    file << "\n";
    // second line: rows
    file << "nrows";
    file << this->delimeter;
    file << rows;
    file << "\n";
    // third line: xllcorner
    file << "xllcorner";
    file << this->delimeter;
    file << xllcorner;
    file << "\n";
    // fourth line: yllcorner
    file << "yllcorner";
    file << this->delimeter;
    file << yllcorner;
    file << "\n";
    // cellsize
    file << "cellsize";
    file << this->delimeter;
    file << cellside;
    file << "\n";
    // NODATA_value
    file << "NODATA_value";
    file << this->delimeter;
    file << -9999;
    file << "\n";
    this->linesCount++;
    // Close the file
    file.close();
}

/*
 *     Creates CSV
 */
void
CSVWriter::printCSV(int rows, int cols, std::vector<int> statusCells)
{
    // Create a rowVector for printing
    std::vector<int> rowVector;

    // Adding vector to CSV File
    int r, c;

    // Printing rows (output)
    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < cols; c++)
        {

            std::vector<int>::const_iterator first = statusCells.begin() + c + r * cols;
            std::vector<int>::const_iterator last = statusCells.begin() + c + r * cols + cols;
            std::vector<int> rowVector(first, last);

            this->addDatainRow(rowVector.begin(), rowVector.end());
            c += cols;
        }
    }
}

/*
 *     Creates CSVDouble
 */
void
CSVWriter::printCSVDouble(int rows, int cols, std::vector<double> network)
{
    // Create a rowVector for printing
    std::vector<double> rowVector;

    // Adding vector to CSV File
    int r, c;
    bool out;
    out = false;

    // Printing rows (output)
    for (r = 0; r < rows; r++)
    {

        for (c = 0; c < cols; c++)
        {
            if (network[c + r * cols] < 1 || std::ceil(network[c + r * cols]) != network[c + r * cols])
            {
                out = true;
                break;
            }

            std::vector<double>::const_iterator first = network.begin() + c + r * cols;
            std::vector<double>::const_iterator last = network.begin() + c + r * cols + cols;
            std::vector<double> rowVector(first, last);

            this->addDatainRow(rowVector.begin(), rowVector.end());
            c += cols;
        }

        if (out)
        {
            break;
        }
    }
}

// Ofstream version to save faster
void
CSVWriter::printCSVDouble_V2(int rows, int cols, std::vector<double> network)
{
    bool outs = false;
    std::ofstream ofs(this->fileName, std::ofstream::out);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (network[c + r * cols] < 1 || network[c + r * cols + 1] < 1
                || std::ceil(network[c + r * cols]) != network[c + r * cols])
            {
                outs = true;
                break;
            }
            ofs << (int)network[c + r * cols] << this->delimeter << (int)network[c + r * cols + 1] << this->delimeter
                << (int)network[c + r * cols + 2] << this->delimeter << network[c + r * cols + 3] << "\n";
            c += cols;
        }

        if (outs)
        {
            break;
        }
    }
    // Close file
    ofs.close();
}

void
CSVWriter::printASCII(
    int rows, int cols, double xllcorner, double yllcorner, int cellside, std::vector<float> statusCells)
{
    // Create a rowVector for printing
    std::vector<float> rowVector;

    // Adding vector to CSV File
    int r, c;
    // Add header to ascii file

    this->asciiHeader(rows, cols, xllcorner, yllcorner, cellside);

    // Printing rows (output)
    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < cols; c++)
        {

            std::vector<float>::const_iterator first = statusCells.begin() + c + r * cols;
            std::vector<float>::const_iterator last = statusCells.begin() + c + r * cols + cols;
            std::vector<float> rowVector(first, last);

            this->addDatainRow(rowVector.begin(), rowVector.end());
            c += cols;
        }
    }
}

void
CSVWriter::printASCIIInt(
    int rows, int cols, double xllcorner, double yllcorner, int cellside, std::vector<int> statusCells)
{
    // Create a rowVector for printing
    std::vector<int> rowVector;

    // Adding vector to CSV File
    int r, c;
    // Add header to ascii file

    this->asciiHeader(rows, cols, xllcorner, yllcorner, cellside);

    // Printing rows (output)
    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < cols; c++)
        {

            std::vector<int>::const_iterator first = statusCells.begin() + c + r * cols;
            std::vector<int>::const_iterator last = statusCells.begin() + c + r * cols + cols;
            std::vector<int> rowVector(first, last);

            this->addDatainRow(rowVector.begin(), rowVector.end());
            c += cols;
        }
    }
}

void
CSVWriter::printWeather(std::vector<std::string> weatherHistory)
{
    std::ofstream ofs(this->fileName, std::ofstream::out);
    int i;

    for (i = 0; i < weatherHistory.size(); i++)
    {
        ofs << weatherHistory[i] << "\n";
    }
    // Close file
    ofs.close();
}

void
CSVWriter::printIgnitions(std::unordered_map<int, int> ignitionsHistory)
{
    std::ofstream ofs(fileName, std::ofstream::out);
    int i;

    // Print column titles
    ofs << "sim,point\n";

    // Iterate through the map and print key-value pairs
    for (i = 1; i < ignitionsHistory.size() + 1; i++)
    {
        ofs << i << "," << ignitionsHistory[i] << "\n";
        // ofs << i << "," << ignitionsHistory[i-1] << "\n";
    }

    // Close file
    ofs.close();
}

void CSVWriter::printCO2(std::vector<float> co2History)
{
	std::ofstream ofs(this->fileName, std::ofstream::out);
	int i;

	for (i = 0; i < co2History.size(); i++)
	{
		ofs << co2History[i] << "\n";
	}
	// Close file 
	ofs.close();
}

void
CSVWriter::printCSV_V2(int rows, int cols, std::vector<int> statusCells)
{
    std::ofstream ofs(this->fileName, std::ofstream::out);
    std::string toOut;
    int r, c, i;

    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < cols; c++)
        {
            std::string toOut;
            for (i = 0; i < cols; i++)
            {
                toOut += std::to_string(statusCells[c + r * cols + i]) + this->delimeter;
            }
            ofs << toOut << "\n";
            c += cols;
        }
    }
    // Close file
    ofs.close();
}

void
CSVWriter::MakeDir(std::string pathPlot)
{
    // Default folder simOuts
    const char* Dir;
#if defined _WIN32 || defined __CYGWIN__
    Dir = pathPlot.c_str();
    int ret = _mkdir(Dir);
#else
    std::string inst = "mkdir -p ";
    pathPlot = inst + pathPlot;
    Dir = pathPlot.c_str();
    int ret = system(Dir);
#endif
}
