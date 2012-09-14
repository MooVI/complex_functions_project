#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <complex>
#include "PhysicalConstants.h"
#include "CAS IO.h"
#include "../../../Plotting/Plotter/Plotter.h"
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
        bool success; CasUnaryFunction f;
        while (!success){
        std::string fname;
        std::cout<<"Enter function: ";
        std::getline(std::cin,fname);
        f.createFunction(fname,fname,&success);
        };
        int N= 100; vector<double> ox (N*N),oy(N*N),oz(N*N);
        double x=0,y=0;double boundx=4;double boundy=4;
        for (int i = 0; i < N; i++) {
            x+= boundx/ ((double) N);
            y = -boundy/2.0;
            for (int j = 0; j < N; j++) {
                
                y+= boundy/ ((double) N);
                complex<double> z = f (std::complex<double> (x,y));
                oz[i*N+j]=z.real();
                ox[i*N+j]=x;
                oy[i*N+j]=y;
                
            }}
        ScatterPlotter plotter;
        plotter.plot(ox,oy,oz);
        std::string hInput;
        std::cout << "Enter a unary function, friend, and I will try to work out what the hell you're saying.\n";
        
        stringstream test;
     
        test<< "sin("<<x<<"x)";
        std::string tester =test.str();
        std::getline(std::cin, hInput);
        CasUnaryFunction UnaryTest;
        UnaryTest.createFunction(hInput,hInput, &success);
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