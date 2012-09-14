#include "Functions.h"
#include "math.h"
namespace CAS {
//Exponential
		Expression *Exponential::getDerivative (Expression * peInput){
		Expression * ret= Create::createFunction (EXP,peInput);
		return ret;}
complex<double>  Exponential::evaluate (){return exp( ((*peInput)->evaluate()) );}
bool  Exponential::simplify (Expression ** peOutput) {return false;}
void Exponential::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= new Constant (0,"1",1);
		else { Expression * peDummy=  new Exponential (peInput,cfInName);
			*peOutput=peDummy;}}
Exponential::Exponential(Expression *peInput, int cfInName):Function (peInput){
	cfName=cfInName;
	}

//Natural Log

complex<double>  NaturalLogarithm::evaluate (){return log( ((*peInput)->evaluate()) );}
	Expression * NaturalLogarithm::getDerivative (Expression * peInput){
		Expression * ret= Create::createFunction (RECIPROCAL,peInput);
		return ret;}
bool  NaturalLogarithm::simplify (Expression ** peOutput) {return false;}
void NaturalLogarithm::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= NULL;
		else { Expression * peDummy=  new NaturalLogarithm (peInput,cfInName);
			*peOutput=peDummy;}}
	NaturalLogarithm::NaturalLogarithm(Expression *peInput, int cfInName):Function (peInput){
		cfName=cfInName;
	}

//Sine

	complex<double>  Sine::evaluate (){return sin( ((*peInput)->evaluate()) );}
	Expression * Sine::getDerivative (Expression * peInput){
		Expression * ret= Create::createFunction (COS,peInput);
		return ret;}
	bool  Sine::simplify (Expression ** peOutput) {return false;}
	void Sine::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= NULL;
		else { Expression * peDummy=  new Sine (peInput,cfInName);
			*peOutput=peDummy;}}
	Sine::Sine(Expression *peInput, int cfInName):Function (peInput){cfName=cfInName;
	}

//Cosine
	
	complex<double>  Cosine::evaluate (){return cos( ((*peInput)->evaluate()) );}
	Expression * Cosine::getDerivative (Expression * peInput){
		Expression * ret= Create::createFunction(MINUS,Create::createFunction (SIN,peInput));
		return ret;}
	bool  Cosine::simplify (Expression ** peOutput) {return false;}
	void Cosine::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= NULL;
		else { Expression * peDummy=  new Cosine (peInput,cfInName);
			*peOutput=peDummy;}}
	Cosine::Cosine(Expression *peInput, int cfInName):Function (peInput){cfName=cfInName;
	}

//Tangent

	complex<double>  Tangent::evaluate (){return tan( ((*peInput)->evaluate()) );}
	Expression * Tangent::getDerivative (Expression * peInput){
		Expression * ret= Create::createFunction(RECIPROCAL,Create::createFunction(SQUARE,Create::createFunction (COS,peInput)));
		return ret;}
	bool  Tangent::simplify (Expression ** peOutput) {return false;}
	void Tangent::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= NULL;
		else { Expression * peDummy=  new Tangent (peInput,cfInName);
			*peOutput=peDummy;}}
	Tangent::Tangent(Expression *peInput, int cfInName):Function (peInput){cfName=cfInName;
	}

//Signum

	complex<double>  Signum::evaluate (){complex<double> z = (*peInput)->evaluate();
                                             return z/abs(z);  }
	Expression * Signum::getDerivative (Expression * peInput){
                
		return NULL;}
	bool  Signum::simplify (Expression ** peOutput) {return false;}
	void Signum::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= NULL;
		else { Expression * peDummy=  new Signum (peInput,cfInName);
			*peOutput=peDummy;}}
	Signum::Signum(Expression *peInput, int cfInName):Function (peInput){cfName=cfInName;
	}
        
        void Signum::latex (std::stringstream * ssOutput){
	(*ssOutput)<<"\\mathrm{sgn}";
        Operator * var;
        bool inputOperator = (var = dynamic_cast<Operator*> (*peInput));
        if (!inputOperator)
            (*ssOutput)<<"{\\left(";
        (*peInput)->latex(ssOutput);
        if (!inputOperator)
            *ssOutput<<"\\right)}";
}
        
        //Hyperbolic Sine

	complex<double>  Sinh::evaluate (){return sinh( ((*peInput)->evaluate()) );}
	Expression * Sinh::getDerivative (Expression * peInput){
		Expression * ret= Create::createFunction(COSH, peInput);
		return ret;}
	bool  Sinh::simplify (Expression ** peOutput) {return false;}
	void Sinh::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= NULL;
		else { Expression * peDummy=  new Sinh (peInput,cfInName);
			*peOutput=peDummy;}}
	Sinh::Sinh(Expression *peInput, int cfInName):Function (peInput){cfName=cfInName;
	}
        
        //Hyperbolic Cosine

	complex<double>  Cosh::evaluate (){return cosh( ((*peInput)->evaluate()) );}
	Expression * Cosh::getDerivative (Expression * peInput){
		Expression * ret= Create::createFunction(SINH, peInput);
		return ret;}
	bool  Cosh::simplify (Expression ** peOutput) {return false;}
	void Cosh::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= NULL;
		else { Expression * peDummy=  new Cosh (peInput,cfInName);
			*peOutput=peDummy;}}
	Cosh::Cosh(Expression *peInput, int cfInName):Function (peInput){cfName=cfInName;
	}
        
        //Hyperbolic Tangent

	complex<double> Tanh::evaluate (){return tanh( ((*peInput)->evaluate()) );}
	Expression *Tanh::getDerivative (Expression * peInput){
		Expression * ret= Create::createFunction(RECIPROCAL,Create::createFunction(SQUARE,Create::createFunction (COSH,peInput)));
		return ret;}
	bool Tanh::simplify (Expression ** peOutput) {return false;}
	void Tanh::create (Expression ** peOutput,Expression *peInput, int cfInName){
		if (peInput==NULL) *peOutput= NULL;
		else { Expression * peDummy=  new Tanh (peInput,cfInName);
			*peOutput=peDummy;}}
	Tanh::Tanh(Expression *peInput, int cfInName):Function (peInput){cfName=cfInName;
	}
}