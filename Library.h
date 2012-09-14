#pragma once
#include <string>
#include <iostream>
#include <complex>
#include "Expression.h"
namespace CAS {
using std::complex;
template <typename T> int sgn(T val)
{
    return (val > T(0)) - (val < T(0));
}


class Printable;	
	class Expression;
		class Constant;
		class Variable;
		class Operator;
			class Multiplication;
			class Addition;
			class Subtraction;
			class Division;
			class Power;
		class Function;
			class Sine;
			class Cosine;
			class Tangent;
			class Exponential;
			class NaturalLogarithm;
			class Signum;
                        class Sinh;
                        class Cosh;
                        class Tanh;
                       


#define ADD 0
#define MULTIPLY 1
#define SUBTRACT 2
#define DIVIDE 3
#define POWER 4
#define GREATER 5
#define LESS 6

#define EXP 0
#define LN 1
#define MINUS 2
#define RECIPROCAL 3
#define SQUARE 4
#define SIN 5
#define COS 6
#define TAN 7
#define SGN 8
#define SQRT 9
#define SINH 10
#define COSH 11
#define TANH 12
#define COSEC 13
#define SEC 14
#define COT 15
#define COSECH 16
#define SECH 17
#define COTH 18
			
#define MAXSIZE 100
#define MAXFUNCTIONOF 3

#define MAXOPERATORS 7
#define MAXFUNCTIONS 19
#define MAXVARIABLES 10

typedef void (*ptrCreateOperator) (Expression **,Expression *,Expression *, int);
typedef void (*ptrCreateFunction) (Expression **,Expression *,int);

class Library {
protected:
	int cNumVar;
	static char ahOperators [MAXOPERATORS] [2]; static std::string asFunctions [MAXFUNCTIONS];static char ahPostFunctions [10];static char ahVariables [MAXVARIABLES] [4];
	static ptrCreateOperator poCreate [MAXOPERATORS];
	static ptrCreateFunction pfCreate [MAXFUNCTIONS];
public: Library (){};
		void libInit ();};



class Create: public Library{
protected:
public:
static Expression * createFunction (int IDENT, Expression * peInput);
static Expression * createOperator (int IDENT, Expression * peInput1,Expression * peInput2);
static Expression * createRelation (int IDENT, Expression * peInput1, Expression *peInput2);
static Printable * createBiInput (int IDENT, Expression * peInput1, Expression *peInput2);
Create (){libInit();}
};

class Printer: public Library{
public:
	static char getCharOperator(int IDENT);
	static std::string getStringFunction (int IDENT);
};

class ConCreateFunctions{
public:
	static void OneOver (Expression ** peOutput,Expression *peInput, int cfInName);
	static void Minus (Expression ** peOutput,Expression *peInput, int cfInName);
	static void Squared (Expression ** peOutput,Expression *peInput, int cfInName);
	static void Power (Expression ** peOutput,Expression *peInput1,Expression * peInput2, int cfInName);
	static void SquareRoot (Expression ** peOutput,Expression *peInput, int cfInName);
        static void Cot (Expression ** peOutput,Expression *peInput, int cfInName);
        static void Cosec (Expression ** peOutput,Expression *peInput, int cfInName);
        static void Sec (Expression ** peOutput,Expression *peInput, int cfInName);
        static void Coth (Expression ** peOutput,Expression *peInput, int cfInName);
        static void Cosech (Expression ** peOutput,Expression *peInput, int cfInName);
        static void Sech (Expression ** peOutput,Expression *peInput, int cfInName);
        
};

bool isGreek (std::string inName);
}