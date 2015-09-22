/*******************
Copyright 2015 Richard Davis
CSCI 3020 Section W1
Fall 2015
Assignment 2
Programmed on Arch Linux (kernel version 4.1.6-1-ARCH) using g++ (v5.2.0)
This program converts a legacy csv file to an XML document
*******************/

#include <fstream>
#include <iostream>
#include <string>
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
    City cities[500];
    int cityCount;
};

struct Countries {
    Country countries[200];
    int countryCount;
};

// prototypes for the functions
void userInput(std::string &, std::string &);
bool fileRead(std::string, Countries &);
void fileWrite(std::string, Countries);

// where the magic happens
int main() {
    std::string ifile_name, ofile_name;
    Countries m_countries;
    bool wasRead;

    cout << "CSV-to-XML Converter\n";
    cout << "Author: Richard Davis\n";

    userInput(ifile_name, ofile_name);

    wasRead = fileRead(ifile_name, m_countries);

    if (wasRead) {
        fileWrite(ofile_name, m_countries);
    }

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
bool fileRead(std::string name, Countries &l_countries) {
    std::ifstream file;
    std::istringstream ss;
    std::string line;
    std::string testName;
    std::string tempRegion;
    std::string tempCode;
    int i = 0;
    int j = 0;
    int charIndex;
    int secondIndex;
    std::string tempString;
    bool first = true;

    file.open(name.c_str());
    if (!file) {
        cout << "Unable to open the input file!\n";
        cout << "Check if the file exists and that you have read permissions.\n";
        return false;
    } else {
        cout << "Opening file for reading...\n";
        while (true) {
            getline(file, line);
            if (line.find("&") != std::string::npos) {
                charIndex = line.find("&");
                tempString = line.substr(charIndex+1, line.length()-1);
                line.erase(charIndex);
                line.insert(charIndex, "&amp;");
                line.insert(line.length(), tempString);
                secondIndex = line.find_last_of("&");
                if (secondIndex != charIndex) {
                    tempString = line.substr(secondIndex+1, line.length()-1);
                    line.erase(secondIndex);
                    line.insert(secondIndex, "&amp;");
                    line.insert(line.length(), tempString);
                }
            }
            if (line.find("\"") != std::string::npos) {
                charIndex = line.find("\"");
                tempString = line.substr(charIndex+1, line.length()-1);
                line.erase(charIndex);
                line.insert(charIndex, "&quot;");
                line.insert(line.length(), tempString);
                secondIndex = line.find_last_of("\"");
                if (secondIndex != charIndex) {
                    tempString = line.substr(secondIndex+1, line.length()-1);
                    line.erase(secondIndex);
                    line.insert(secondIndex, "&quot;");
                    line.insert(line.length(), tempString);
                }
            } 
            if (line.find("<") != std::string::npos) {
                charIndex = line.find("<");
                tempString = line.substr(charIndex+1, line.length()-1);
                line.erase(charIndex);
                line.insert(charIndex, "&lt;");
                line.insert(line.length(), tempString);
                secondIndex = line.find_last_of("<");
                if (secondIndex != charIndex) {
                    tempString = line.substr(secondIndex+1, line.length()-1);
                    line.erase(secondIndex);
                    line.insert(secondIndex, "&lt;");
                    line.insert(line.length(), tempString);
                }
            } 
            if (line.find(">") != std::string::npos) {
                charIndex = line.find(">");
                tempString = line.substr(charIndex+1, line.length()-1);
                line.erase(charIndex);
                line.insert(charIndex, "&gt;");
                line.insert(line.length(), tempString);
                secondIndex = line.find_last_of(">");
                if (secondIndex != charIndex) {
                    tempString = line.substr(secondIndex+1, line.length()-1);
                    line.erase(secondIndex);
                    line.insert(secondIndex, "&gt;");
                    line.insert(line.length(), tempString);
                }
            } 
            if (line.find("\'") != std::string::npos) {
                charIndex = line.find("\'");
                tempString = line.substr(charIndex+1, line.length()-1);
                line.erase(charIndex);
                line.insert(charIndex, "&apos;");
                line.insert(line.length(), tempString);
                secondIndex = line.find_last_of("\'");
                if (secondIndex != charIndex) {
                    tempString = line.substr(secondIndex+1, line.length()-1);
                    line.erase(secondIndex);
                    line.insert(secondIndex, "&apos;");
                    line.insert(line.length(), tempString);
                }
            }
            if (!file || line.length() == 0) {
                break;
            }
            ss.clear();
            ss.str(line);
            getline(ss, testName, ',');
            if (first) { 
                l_countries.countries[i].name = testName;
                getline(ss, l_countries.countries[i].region, ',');
                getline(ss, l_countries.countries[i].code, ',');
                getline(ss, l_countries.countries[i].cities[j].name, ',');
                getline(ss, l_countries.countries[i].cities[j].district, ',');
                getline(ss, l_countries.countries[i].cities[j].population);
                if (l_countries.countries[i].cities[j].population.length() >  3 &&  l_countries.countries[i].cities[j].population.length() < 7) {
                    l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-3, ",");
                } else if (l_countries.countries[i].cities[j].population.length() >  6 &&  l_countries.countries[i].cities[j].population.length() < 10){
                    l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-3, ",");
                    l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-7, ",");
                }
                l_countries.countryCount = 1;
                l_countries.countries[i].cityCount = 1;
                first = false;
            } else { 
                if (testName.compare(l_countries.countries[i].name) == 0) { // if country is same as previous
                    j++;
                    getline(ss, tempRegion, ',');
                    getline(ss, tempCode, ',');
                    getline(ss, l_countries.countries[i].cities[j].name, ',');
                    getline(ss, l_countries.countries[i].cities[j].district, ',');
                    getline(ss, l_countries.countries[i].cities[j].population);
                    if (l_countries.countries[i].cities[j].population.length() >  3 &&  l_countries.countries[i].cities[j].population.length() < 7) {
                    l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-3, ",");
                    } else if (l_countries.countries[i].cities[j].population.length() >  6 &&  l_countries.countries[i].cities[j].population.length() < 10){
                        l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-3, ",");
                        l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-7, ",");
                    }
                    l_countries.countries[i].cityCount++;                    
                } else { // if country is different than previous country
                    i++;
                    j=0;
                    l_countries.countries[i].name = testName;
                    getline(ss, l_countries.countries[i].region, ',');
                    getline(ss, l_countries.countries[i].code, ',');
                    getline(ss, l_countries.countries[i].cities[j].name, ',');
                    getline(ss, l_countries.countries[i].cities[j].district, ',');
                    getline(ss, l_countries.countries[i].cities[j].population);
                    if (l_countries.countries[i].cities[j].population.length() >  3 &&  l_countries.countries[i].cities[j].population.length() < 7) {
                    l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-3, ",");
                    } else if (l_countries.countries[i].cities[j].population.length() >  6 &&  l_countries.countries[i].cities[j].population.length() < 10){
                        l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-3, ",");
                        l_countries.countries[i].cities[j].population.insert(l_countries.countries[i].cities[j].population.length()-7, ",");
                    }
                    l_countries.countryCount++;
                    l_countries.countries[i].cityCount = 1;
                }
            }
        } // end while loop
        cout << "The input file has been successfully parsed.\n\n";
        file.close();
        return true;
    }
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
        file << "<countries xmlns:country-data=\"http://library.smalltown.us/country\" xmlns:city-data=\"http://library.smalltown.us/city\">\n";
        for (int i = 0; i < l_countries.countryCount; i++) {
            file << "\t<country-data:country>\n";
            file << "\t\t<country-data:name>" << l_countries.countries[i].name << "</country-data:name>\n";
            file << "\t\t<country-data:region>" << l_countries.countries[i].region << "</country-data:region>\n";
            file << "\t\t<country-data:code>" << l_countries.countries[i].code << "</country-data:code>\n";
            for (int j = 0; j < l_countries.countries[i].cityCount; j++) {
                file << "\t\t<city-data:city>\n";
                file << "\t\t\t<city-data:name>" << l_countries.countries[i].cities[j].name << "</city-data:name>\n";
                file << "\t\t\t<city-data:district>" << l_countries.countries[i].cities[j].district << "</city-data:district>\n";
                file << "\t\t\t<city-data:population>" << l_countries.countries[i].cities[j].population << "</city-data:population>\n";
                file << "\t\t</city-data:city>\n";
            }
            file << "\t</country-data:country>\n";
        }
        file << "</countries>";
        cout << "The input file has been converted to an XML document.\n";
    }
    file.close();
}
