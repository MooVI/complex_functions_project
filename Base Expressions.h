#pragma once
#include "Expression.h"
namespace CAS {
class Constant:public Expression{
protected:
	int ccName; complex<double> dcValue; std::string scName;bool Greek;
	public:
	bool getInput (ExpPtrVector *  Inputs);
	complex<double>  evaluate (); 
	void latex(std::stringstream * ssOutput);
	bool simplify (Expression ** peOutput);
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	void print(std::stringstream * ssOutput);
	Constant (int ccInName,std::string scInName, complex<double> dcInValue,bool iGreek=false);
};


class Operator: public Expression {
	protected:
	Expression ** peInput1, **peInput2; int coName;
	public:
	bool getInput (ExpPtrVector *  Inputs);
	virtual complex<double>  evaluate ()=0;
	virtual bool  simplify (Expression ** peOutput)=0;
	virtual bool differentiate (Expression **peOutput, int cvWithRespectTo)=0;
	void print(std::stringstream * ssOutput);
	virtual void latex(std::stringstream * ssOutput)=0;
	static void create (Expression * peOutput);
	Operator (Expression *  peInInput1,Expression *  peInInput2);
	~Operator ();
};

class Variable:public Expression {
	bool Greek; 
public:
	static complex<double> dvValues [MAXVARIABLES];
		int cvName; int cvFunctionOf [MAXFUNCTIONOF]; std::string svName;
		public:
	bool getInput (ExpPtrVector * Inputs);
	complex<double>  evaluate () ;
	bool simplify (Expression ** peOutput); 
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	void print(std::stringstream * ssOutput);
	void latex(std::stringstream * ssOutput);
	Variable (int cvInName,std::string svInName,int cvInFunctionOf []);
};


class Function : public Expression {
protected:
Expression ** peInput;  int cfName;
virtual Expression * getDerivative (Expression * peInput)=0;
void print(std::stringstream * ssOutput);
	 public:
	bool getInput (ExpPtrVector *  Inputs);
	virtual complex<double> evaluate ()=0;
	virtual bool  simplify (Expression ** peOutput)=0;
	void latex(std::stringstream * ssOutput);
	//bool getInput (Expression ** peOutput) {*peOutput=*peInput;};
	static void create (Expression * peOutput);
	Function (Expression * peInInput);
	bool differentiate (Expression ** peOutput,int cvWithRespectTo);
	

};
}