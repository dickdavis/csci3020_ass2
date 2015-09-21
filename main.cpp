/*******************
Copyright 2015 Richard Davis
CSCI 3020 Section W1
Fall 2015
Assignment 2
Programmed on Arch Linux (kernel version 4.1.6-1-ARCH) using g++ (v5.2.0)
This program converts a legacy text file to an XML document
*******************/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>

using std::cout;
using std::cin;

struct City {
    std::string name;
    std::string district;
    std::string population;
};

struct Country {
    std::string name;
    std::string region;
    std::string code;
    City cities[5];
};

struct Countries {
    Country countries[10];
};

// prototypes for the functions
void userInput(std::string &, std::string &);
void fileRead(std::string, Countries &);
void fileWrite(std::string, Countries);

// where the magic happens
int main() {
    std::string ifile_name, ofile_name;
    Countries m_countries;

    cout << "CSV-to-XML Converter\n";
    cout << "Author: Richard Davis\n";

    userInput(ifile_name, ofile_name);

    fileRead(ifile_name, m_countries);

    return 0;
}

// prompts user for input, repeats back, appends ".xml" to output file if not specified by user.
void userInput(std::string &in, std::string &out) {
    cout << "Enter the name of the input file =>";
    cin >> in;
    cout << "The input file you have entered is: " << in + "\n\n";

    cout << "Enter the name of the output file =>";
    cin >> out;
    if (out.find(".xml") == std::string::npos) {
        out = out + ".xml";
    }
    cout << "The output file you have entered is: " << out + "\n\n";
}

// opens input file, reads and stores values in nested structs, and then closes file
void fileRead(std::string name, Countries &l_countries) {
    std::ifstream file;
    std::istringstream ss;
    std::string line;
    std::string testName;
    std::string tempRegion;
    std::string tempCode;
    int i = 0;
    int j = 0;
    bool first = true;

    file.open(name.c_str());
    if (!file) {
        cout << "Unable to open the input file!\n";
        cout << "Check if the file exists and that you have read permissions.\n";
    } else {
        cout << "Opening file for reading...\n";
        while (true) {
            cout << "in the loop\n";
            getline(file, line);
            if (!file || line.length() == 0) {
                break;
            }
            ss.clear();
            ss.str(line);
            getline(ss, testName, ',');
            cout << testName << std::endl;
            if (first) {
                cout << "first time through loop\n";
                l_countries.countries[i].name = testName;
                getline(ss, l_countries.countries[i].region, ',');
                getline(ss, l_countries.countries[i].code, ',');
                getline(ss, l_countries.countries[i].cities[j].name, ',');
                getline(ss, l_countries.countries[i].cities[j].district, ',');
                getline(ss, l_countries.countries[i].cities[j].population);
                first = false;
            } else {
                cout << "not the first time\n";
                if (testName.compare(l_countries.countries[i].name) == 0) {
                    cout << "same country as previous\n";
                    j++;
                    getline(ss, tempRegion, ',');
                    getline(ss, tempCode, ',');
                    getline(ss, l_countries.countries[i].cities[j].name, ',');
                    getline(ss, l_countries.countries[i].cities[j].district, ',');
                    getline(ss, l_countries.countries[i].cities[j].population);                    
                } else {
                    cout << "different country\n";
                    i++;
                    j=0;
                    l_countries.countries[i].name = testName;
                    getline(ss, l_countries.countries[i].region, ',');
                    getline(ss, l_countries.countries[i].code, ',');
                    getline(ss, l_countries.countries[i].cities[j].name, ',');
                    getline(ss, l_countries.countries[i].cities[j].district, ',');
                    getline(ss, l_countries.countries[i].cities[j].population);
                }
            }
        } // end while loop
    }
    file.close();
    cout << "The input file has been successfully parsed.\n\n";
}

// opens/creates output file, uses for loops to traverse structs as it writes xml to file, and then closes file
void fileWrite(std::string name, Countries l_countries) {
    std::ofstream file;
    file.open(name.c_str(), std::ios::out);
    if (!file) {
        cout << "Unable to open the output file!\n";
        cout << "Ensure you have write permissions in your working directory.\n";
    } else {
        cout << "Opening file for writing...\n";
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<!-- Processed by Richard Davis’s converter -->\n";
        file << "<countries>\n";
        file << "\t<country>\n";
        file << "\t\t<name>\n";
        file << "\t\t<code>\n";
        file << "\t\t<region>\n";
        file << "\t\t<city>\n";
        file << "\t\t\t<name></name>\n";
        file << "\t\t\t<district></district>\n";
        file << "\t\t\t<population></population>\n";
        file << "\t\t</city>\n";
        file << "\t<country>\n";
        file << "</countries>";
    }
    file.close();
    cout << "The input file has been converted to an XML document.\n";
}
