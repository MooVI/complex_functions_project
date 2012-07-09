
#include "Base Expressions.h"
//Constant
 complex<double>  Constant::evaluate () {return dcValue;}
bool Constant::getInput (ExpPtrVector * Inputs){return false;}
bool Constant::simplify (Expression ** peOutput) {
	*peOutput=NULL; return false;
}
void Constant::latex(std::stringstream * ssOutput)
{if (Greek) *ssOutput<<"\\" ;
this->print(ssOutput);
if (Greek) *ssOutput<<" " ;	}
bool Constant::differentiate (Expression **peOutput, int cvWithRespectTo){
	*peOutput=NULL;
	return false;
}
void Constant::print(std::stringstream * ssOutput){*ssOutput<<scName;};

Constant::Constant (int ccInName,std::string scInName, complex<double> dcInValue,bool iGreek){ccName=ccInName; scName=scInName;dcValue=dcInValue;Greek=iGreek;}



//Operator 

bool Operator::getInput (ExpPtrVector * Inputs){
	
	Inputs->push_back (*peInput1);
	Inputs->push_back (*peInput1);
	return true;
}
void Operator::print(std::stringstream * ssOutput){*ssOutput<<'(';(*peInput1)->print(ssOutput);*ssOutput<<Printer::getCharOperator(coName);(*peInput2)->print(ssOutput);*ssOutput<<')';};
void Operator::create (Expression * peOutput){};
Operator::Operator (Expression *  peInInput1,Expression *  peInInput2){
		
		peInput1= new Expression*;
		*peInput1= 	peInInput1;
	peInput2= new Expression*;
		*peInput2= 	peInInput2;
	}
Operator::~Operator (){delete peInput1;delete peInput2;}


//Variable
void Variable::latex (std::stringstream * ssOutput){
	if (Greek) *ssOutput<<"\\";
	*ssOutput<<svName;
	if (Greek) *ssOutput<<" ";}
bool Variable::getInput (ExpPtrVector * Inputs){return false;}
complex<double>  Variable::evaluate () {return dvValues [cvName];}
bool Variable::simplify (Expression ** peOutput) {return false;}
bool Variable::differentiate (Expression **peOutput, int cvWithRespectTo){
	if (cvWithRespectTo==cvName) {*peOutput=NULL; return true;}
	for (int cvIterFunctionOf=0;cvIterFunctionOf<MAXFUNCTIONOF;cvIterFunctionOf++){
			if (cvWithRespectTo==cvFunctionOf [cvIterFunctionOf]){
				*peOutput= Create::createFunction (1, const_cast<Expression*> (static_cast<Expression*const> (this)));
				return true;
			}
	}
	*peOutput=NULL;
	return false;
}

	
void Variable::print(std::stringstream * ssOutput){*ssOutput<<svName;};

Variable::Variable (int cvInName,std::string svInName,int cvInFunctionOf []){
	cvName=cvInName; svName=svInName;
	Greek=isGreek(svName);
	glbArrayCopy<int> (cvFunctionOf,cvInFunctionOf,3);
}
complex<double> Variable::dvValues [MAXVARIABLES];

//Function 
bool Function::getInput (ExpPtrVector *Inputs){
	Inputs->push_back (*peInput);
	return true;
}
void Function::latex (std::stringstream * ssOutput){
	*ssOutput <<"\\";
        (*ssOutput)<<Printer::getStringFunction(cfName);
       // Operator * var;
      //  bool inputOperator = (var = dynamic_cast<Operator*> (*peInput));
      //  if (!inputOperator) This is a test to see whether the input is an operator
        //I have no idea why this would be here. I'm leaving it in until I remember.
            (*ssOutput)<<"{\\left(";
        (*peInput)->latex(ssOutput);
//        if (!inputOperator)
            *ssOutput<<"\\right)}";
}
void Function::print(std::stringstream * ssOutput) {(*ssOutput)<<Printer::getStringFunction(cfName)<<'(';(*peInput)->print(ssOutput);*ssOutput<<')';}
void Function::create (Expression * peOutput){};
Function::Function (Expression * peInInput){
		peInput=new Expression*;
		if(peInInput!=NULL)*peInput=peInInput;
		else *peInput=new Constant (0,"0",0);};
bool  Function::differentiate (Expression ** peOutput,int cvWithRespectTo){
                Expression * derivative= getDerivative(*peInput);
		if ((*peInput)->differentiate(peOutput,cvWithRespectTo)&&derivative!=NULL){
                    *peOutput=Create::createOperator(MULTIPLY,derivative,*peOutput);
                    return true;}
		else *peOutput=NULL;
		return false;}
		