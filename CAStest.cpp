#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <complex>
#include "PhysicalConstants.h"
#include "CAS IO.h"
using std::cout;
using namespace std;

/* Program variable names capitalised after lower case identifier.
   Identifiers as follows:    First half:  p - pointer to
                                                                                   c - constant (but not necessarily a `const') integer identifying
                                                                                   d - double for evaluation
                                                                                   s - string
                                                                                   ss - stringstream
                                                                                   h - char
                                                                                   a - int array
                                                                                   b - bool
                                                          Second Half: e - Expression
                                                                                   f - Function
                                                                                   o - Operator
                                                                                   v - Variable
                                                                                   r - Relation
                                                                                   p - Printable

        Program functions are lower case first letter, then capitalised. */

int main() {
    
    while (true) {
        std::string hInput;
        std::cout << "Enter a unary function, friend, and I will try to work out what the hell you're saying.\n";
        bool success;
        stringstream test;
        int x = 9;
        test<< "sin("<<x<<"x)";
        std::string tester =test.str();
        std::getline(std::cin, hInput);
        CasUnaryFunction UnaryTest(hInput,"Function", &success);
        if (success) {
            std::cout << UnaryTest.latex() << std::endl;
            std::cout << UnaryTest.latex(1) << std::endl;
            std::cout << "Evaluate at (Re, Im):";
            complex<double> z;
            std::cin >> z;
            
            std::cin.ignore(256, '\n');
            std::cout << UnaryTest.evaluateAt(z) << std::endl;
            std::cout << UnaryTest.evaluateNthDerviativeAt(z, 1) << std::endl;
        }
        else {
            std::cout << "Sorry, failed to parse function. Are you sure you entered a variable?" <<std::endl;
        }
    }
    return 0;
}