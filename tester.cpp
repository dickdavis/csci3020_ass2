
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
    std::string code;
    std::string region;
    City cities[5];
};

struct Countries {
    Country countries[];
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
    std::string line;
    std::istringstream ss;
    int i = 0;
    int j = 0;

    file.open(name.c_str());
    if (!file) {
        cout << "Unable to open the input file!\n";
        cout << "Check if the file exists and that you have read permissions.\n";
    } else {
        cout << "Opening file for reading...\n";
        while (file) {
            getline(file, line);
            if (!file || line.length() == 0) {
                break;
            }
            ss.str(line);

            getline(ss, l_countries.countries[i].name, ',');
            cout << l_countries.countries[i].name;
            getline(ss, l_countries.countries[i].code, ',');
            cout << l_countries.countries[i].code;
            getline(ss, l_countries.countries[i].region, ',');
            cout << l_countries.countries[i].region;
            getline(ss, l_countries.countries[i].cities[j].name, ',');
            cout << l_countries.countries[i].cities[j].name;
            getline(ss, l_countries.countries[i].cities[j].district, ',');
            cout << l_countries.countries[i].cities[j].district;
            getline(ss, l_countries.countries[i].cities[j].population, ',');
            cout << l_countries.countries[i].cities[j].population;
            i++;
        }
    }
    file.close();
    cout << "The input file has been successfully parsed.\n\n";
}