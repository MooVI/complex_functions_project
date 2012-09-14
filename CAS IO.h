#pragma once
#include "TreeWalker.h"
namespace CAS {
class InputOutputMaster:public Create {
private:
	char hTest [MAXSIZE];int cRead;
	bool checkFunction (Expression ** peOutput,int cEnd) ;
	bool checkNamedConstant (Expression ** peOutput,int cEnd);
	int findClosingBracket (int cBracketStart,int cEnd);
	bool checkVariable (int cAscii,Expression ** peOutput);
	bool checkConstant (Expression ** peOutput);
        bool checkImaginary (Expression ** peOutput);
	bool checkOperator (int cAscii,int * pcIDENT, int * pcOrder);
	bool checkForPostFunctions (Expression ** peOutput);
	bool findLastOperator (int cStart,int cEnd,Printable** ppOutput);
	bool checkMinus (Expression ** peOutput,int cEnd);
	bool convertToPrintable (int cStart, int cEnd, Printable ** ppOutput );

public: 
	InputOutputMaster();
	void setVariables (complex<double> dInVar []);
	void setVariable (complex<double> dInVar,int IDENT);
	int getNumVar ();
	char getVariableName (int cIdent);
	bool convertInputString (const char * hInput,int cSize, Printable ** ppOutput);
	bool convertToOutputString (std::string * sOutput, Printable * ppInput);
};

class CasUnaryFunction {
public:
	InputOutputMaster * IO; Expression * UnaryFunction; int VariableIdentifier; bool newIO;
	complex<double> evaluateAt (complex<double> InputValue);
	complex<double> evaluateNthDerviativeAt (complex<double> InputValue,int N);
        CasUnaryFunction (){IO=NULL;newIO=false; UnaryFunction=NULL;};
	CasUnaryFunction (std::string iFunction,std::string iName="Function",bool * success=NULL,InputOutputMaster * inIO=NULL);
	CasUnaryFunction (const char * iFunction,int size,std::string iName="Function", bool * success=NULL,InputOutputMaster * inIO=NULL);
        void createFunction (std::string iFunction,std::string iName="Function",bool * success=NULL,InputOutputMaster * inIO=NULL);
	void createFunction (const char * iFunction,int size,std::string iName="Function", bool * success=NULL,InputOutputMaster * inIO=NULL);
	~CasUnaryFunction();
	std::string print (int NthDerivative=0);
	std::string latex (int NthDerivative=0);
	std::string getName ();
	std::string getInputVar ();
	CasUnaryFunction operator * (CasUnaryFunction);
        complex<double> operator () (complex<double> x);
private:
	void create (const char * iFunction,int size, std::string iName, bool * success,InputOutputMaster * inIO);
	std::string Name;
	};

inline complex<double> CasUnaryFunction::operator ()(complex<double> x){
    	IO->setVariable (x,VariableIdentifier);
	return UnaryFunction->evaluate ();
}

                
                
                
void setCinVariables(InputOutputMaster * IOMaster);
}