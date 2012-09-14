#pragma once
#include "Base Expressions.h"
namespace CAS {
class Multiplication:public Operator{
public:
	complex<double>  evaluate ();
	void latex(std::stringstream * ssOutput);
	bool  simplify (Expression ** peOutput);
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	static void create (Expression ** peOutput,Expression *peInput1,Expression *peInput2,int coInName);
	Multiplication (Expression *peInput1,Expression *peInput2, int coInName);

	};

class Division:public Operator{
public:
	complex<double>  evaluate ();
	void latex(std::stringstream * ssOutput);
	bool  simplify (Expression ** peOutput);
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	static void create (Expression ** peOutput,Expression *peInput1,Expression *peInput2,int coInName);
	Division (Expression *peInput1,Expression *peInput2, int coInName);

};

class Addition:public Operator{
public:
	complex<double>  evaluate ();
	void latex(std::stringstream * ssOutput);
	bool  simplify (Expression ** peOutput) ;
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	static void create (Expression ** peOutput,Expression *peInput1,Expression *peInput2, int coInName);
	Addition (Expression *peInput1,Expression *peInput2, int coInName);
	};

class Subtraction:public Operator{
public:
	complex<double>  evaluate ();
	void latex(std::stringstream * ssOutput);
	bool  simplify (Expression ** peOutput);
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	static void create (Expression ** peOutput,Expression *peInput1,Expression *peInput2, int coInName);
	Subtraction(Expression *peInput1,Expression *peInput2, int coInName);
};

class Power:public Operator{
public:
	complex<double>  evaluate ();
	void latex(std::stringstream * ssOutput);
	bool  simplify (Expression ** peOutput);
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	static void create (Expression ** peOutput,Expression *peInput1,Expression *peInput2, int coInName);
	Power(Expression *peInput1,Expression *peInput2, int coInName);
};

class GreaterThan:public Operator{
public:
	complex<double>  evaluate ();
	void latex(std::stringstream * ssOutput);
	bool  simplify (Expression ** peOutput);
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	static void create (Expression ** peOutput,Expression *peInput1,Expression *peInput2, int coInName);
	GreaterThan(Expression *peInput1,Expression *peInput2, int coInName);
};

class LessThan:public Operator{
public:
	complex<double>  evaluate ();
	void latex(std::stringstream * ssOutput);
	bool  simplify (Expression ** peOutput);
	bool differentiate (Expression **peOutput, int cvWithRespectTo);
	static void create (Expression ** peOutput,Expression *peInput1,Expression *peInput2, int coInName);
	LessThan(Expression *peInput1,Expression *peInput2, int coInName);
};
}