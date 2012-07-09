#pragma once
#include "Base Expressions.h"


class Exponential:public Function{
public:
	Expression * getDerivative (Expression * peInput);
	complex<double>  evaluate ();
	bool  simplify (Expression ** peOutput) ;
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
	Exponential(Expression *peInput, int cfInName);
};


class NaturalLogarithm:public Function{
public:
	complex<double>  evaluate ();
	Expression * getDerivative (Expression * peInput);
	bool  simplify (Expression ** peOutput);
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
	NaturalLogarithm(Expression *peInput, int cfInName);
};

class Sine:public Function{
public:
	complex<double>  evaluate ();
	Expression * getDerivative (Expression * peInput);
	bool  simplify (Expression ** peOutput) ;
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
	Sine(Expression *peInput, int cfInName);
};

class Cosine:public Function{
public:
	complex<double>  evaluate ();
	Expression * getDerivative (Expression * peInput);
	bool  simplify (Expression ** peOutput) ;
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
	Cosine(Expression *peInput, int cfInName);
};

class Tangent:public Function{
public:
	complex<double>  evaluate ();
	Expression * getDerivative (Expression * peInput);
	bool  simplify (Expression ** peOutput) ;
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
 Tangent(Expression *peInput, int cfInName);
};

class Signum:public Function{
public:
	Expression * getDerivative (Expression * peInput);
	complex<double>  evaluate ();
	bool  simplify (Expression ** peOutput) ;
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
        void latex (std::stringstream * ssOutput);
	Signum(Expression *peInput, int cfInName);
};


class Sinh:public Function{
public:
	Expression * getDerivative (Expression * peInput);
	complex<double>  evaluate ();
	bool  simplify (Expression ** peOutput) ;
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
	Sinh(Expression *peInput, int cfInName);
};

class Cosh:public Function{
public:
	Expression * getDerivative (Expression * peInput);
	complex<double>  evaluate ();
	bool  simplify (Expression ** peOutput) ;
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
	Cosh(Expression *peInput, int cfInName);
};

class Tanh:public Function{
public:
	Expression * getDerivative (Expression * peInput);
	complex<double>  evaluate ();
	bool  simplify (Expression ** peOutput) ;
	static void create (Expression ** peOutput,Expression *peInput, int cfInName);
	Tanh(Expression *peInput, int cfInName);
};

