// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

/*
* Gamma Correction Generator
* 
* Created: 02.04.2023
* Author: Arkadiusz Pytlik
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using std::cout;
using std::endl;
using std::cin;
using std::pow;
using std::fstream;
using std::string;
using std::ios;

int main()
{
    fstream file;
    string filename;
    int arraysize, pwm;
    double gamma, factor, val;
    
    cout << "Gamma Correction Table Generator\n\n";

    cout << "Enter array size (integer): ";
    cin >> arraysize;
    cout << endl;

    cout << "Enter max PWM value (integer): ";
    cin >> pwm;
    cout << endl;
    
    cout << "Enter Gamma correction (double): ";
    cin >> gamma;
    cout << endl;

    cout << "Enter file name: ";
    cin >> filename;
    cout << endl;

    

    factor = 1.0 / (double)arraysize;

    file.open(filename, ios::out);

    if (file.is_open() == true)
    {
        cout << "file " << filename << " created/opened" << endl;

        file << "/*" << endl;
        file << "* Gamma Correction LUT Generator" << endl;
        file << "* Author: Arkadiusz Pytlik" << endl;
        file << "* File name: " << filename << endl;
        file << "* Max PWM value: " << pwm << endl;
        file << "* Gamma value: " << gamma << endl;
        file << "*/" << endl;
        
        cout << endl;

        if (pwm < 256)
        {
            cout << "uint8_t ";
            file << "uint8_t ";
        }
        else
        {
            cout << "uint16_t ";
            file << "uint16_t ";
        }

        cout << "gamma[" << arraysize << "] =\n{\n\t";
        file << "gamma[" << arraysize << "] =\n{\n\t";

        for (int index = 0; index < arraysize; index++)
        {
            val = pwm * pow(factor * ((double)index + 1), gamma);

            if (index > 0)
            {
                if (index % 10 == 0)
                {
                    cout << ", " << endl;
                    file << ", " << endl;
                    cout << "\t";
                    file << "\t";
                }
                else
                {
                    cout << ", ";
                    file << ", ";
                }
            }

            if (val < 100)
            {
                cout << " ";
                file << " ";
            }

            if (val < 10)
            {
                cout << " ";
                file << " ";
            }

            cout << (int)val;
            file << (int)val;
        }

        cout << "\n};" << endl;
        file << "\n};" << endl;

        file.close();

        cout << "file " << filename << " closed" << endl;
    }
    else
    {
        cout << "Unable to open/create file" << filename << endl;
    }
    cout << "Pressing any key will terminate this program...";

    //cin.get();
    system("pause>nul");
}


