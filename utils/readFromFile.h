// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void readFromFile(string fileName)
{
    string line;
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line)) // Cin / getline
        {
            cout << line << '\n';
        }
        myfile.close();
    }

    else
        cout << "Unable to open file";
}