#pragma once
#include <sstream>
#include <vector>
#include <complex>
#include "Library.h"


class Expression;
typedef std::vector<Expression*>   ExpPtrVector;
typedef ExpPtrVector::iterator ExpPtrIterator;

class Printable {
public: virtual void print(std::stringstream * ssOutput)=0;
		virtual void latex(std::stringstream * ssOutput)=0;
		Printable(){};
		~Printable(){}};

class Expression:public Printable {public:
	virtual std::complex<double>  evaluate ()=0;
	virtual bool simplify (Expression ** peOutput)=0;
	virtual bool differentiate (Expression **peOutput, int cvWithRespectTo)=0;
	virtual void print(std::stringstream * ssOutput)=0;
	virtual bool getInput (ExpPtrVector * Inputs)=0;
	virtual void latex(std::stringstream * ssOutput)=0;

public: Expression (){};
		~Expression(){};
};


 

class Relation: public Printable{
	protected:
	Expression ** peInput1,** peInput2; int crName;
	public:
	virtual bool verify ();
	virtual bool simplify (Relation ** peOutput);
	virtual bool differentiate (Relation **peOutput, int cvWithRespectTo);
	virtual void solveFor (Relation **peOutput, int cvSolveFor);
	virtual void print(std::stringstream * ssOutput);
	static void create (Expression * peOutput){};
	Relation(Expression * peInInput1,Expression *  peInInput2){
		
		peInput1= new Expression*;
		*peInput1= 	peInInput1;
	peInput2= new Expression*;
		*peInput2= 	peInInput2;
	}
	~Relation (){delete peInput1;delete peInput2;}
};

template <class Mytype>
void glbArrayCopy (Mytype  To [],Mytype From [],int cLength){
	for (int cIter=0;cIter<cLength;cIter++){
		To[cIter]=From[cIter];
	}}

