#include "Library.h"
#include "Operators.h"
#include "Functions.h"

bool isGreek (std::string inName){
	if (inName=="theta"||inName=="phi"||inName=="psi"||
		inName=="Theta"||inName=="Phi"||inName=="Psi"||
		inName=="chi"||inName=="Chi"||inName=="omega"||
		inName=="Omega"||inName=="epsilon"||inName=="Epsilon"||
		inName=="pi"||inName=="Pi"||inName=="omicron"||
		inName=="Omicron"||inName=="delta"||inName=="Delta"||
		inName=="alpha"||inName=="beta"||inName=="gamma"||
		inName=="Alpha"||inName=="Beta"||inName=="Gamma"||
		inName=="sigma"||inName=="Sigma") return true;
	else return false;
}

char Printer::getCharOperator(int IDENT){
	if(IDENT<MAXOPERATORS) return ahOperators [IDENT] [0];
	else return 0;//Error!
}
std::string Printer::getStringFunction(int IDENT){
	if(IDENT<MAXFUNCTIONS) return asFunctions [IDENT];
	else return 0;//Error!
}

Expression * Create::createFunction (int IDENT, Expression * peInput){
Expression * peOutput;
if(IDENT>MAXFUNCTIONS) {peOutput=NULL;std::cout<<"ERROR. Undefined elementary function!"<<std::endl;}//Error!!!
	else {(*pfCreate[IDENT]) (&peOutput,peInput,IDENT);}
	return peOutput;}
		
Expression * Create::createOperator (int IDENT, Expression * peInput1,Expression * peInput2){
	Expression * peOutput;
	if(IDENT>MAXOPERATORS) peOutput=NULL;//Error!!!
	else {(*poCreate[IDENT]) (&peOutput,peInput1,peInput2,IDENT);}
	return peOutput;}

Expression * Create::createRelation (int IDENT, Expression * peInput1,Expression * peInput2){
Expression * ret=NULL;


return ret;}
Printable * Create::createBiInput (int IDENT, Expression * peInput1, Expression *peInput2){
	Printable *ret;
	ret=  static_cast<Printable*>(createOperator (IDENT, peInput1,peInput2));
	if (ret==NULL) ret= static_cast<Printable*> (createRelation (IDENT,  peInput1, peInput2));
	return ret;}

char Library::ahOperators[MAXOPERATORS] [2];
std::string Library::asFunctions [MAXFUNCTIONS];
char Library::ahPostFunctions [10];
char Library::ahVariables [MAXVARIABLES] [4];
ptrCreateOperator Library::poCreate [MAXOPERATORS];
ptrCreateFunction Library::pfCreate [MAXFUNCTIONS];

void Library::libInit(){
	ahOperators [0] [0]='+';ahOperators [0] [1]=4; poCreate [0]=Addition::create;
	ahOperators [1] [0]='*';ahOperators [1] [1]=3; poCreate [1]=Multiplication::create;
	ahOperators [2] [0]='-';ahOperators [2] [1]=4; poCreate [2]=Subtraction::create;
	ahOperators [3] [0]='/';ahOperators [3] [1]=2; poCreate [3]=Division::create;
	ahOperators [4] [0]='^';ahOperators [4] [1]=1; poCreate [4]=Power::create;
	ahOperators [5] [0]='>';ahOperators [5] [1]=5; poCreate [5]=GreaterThan::create;
	ahOperators [6] [0]='<';ahOperators [6] [1]=5; poCreate [6]=LessThan::create;

	asFunctions [0]="exp";pfCreate[0]=Exponential::create;
	asFunctions [1]="ln";pfCreate[1]=NaturalLogarithm::create;
	asFunctions [2]="-";pfCreate[2]=ConCreateFunctions::Minus;
	asFunctions [3]="1/";pfCreate[3]=ConCreateFunctions::OneOver;
	asFunctions [4]="^2";pfCreate[4]=ConCreateFunctions::Squared;
	asFunctions [5]="sin";pfCreate[5]=Sine::create;
	asFunctions [6]="cos";pfCreate[6]=Cosine::create;
	asFunctions [7]="tan";pfCreate[7]=Tangent::create;
	asFunctions [8]="sgn";pfCreate[8]=Signum::create;
	asFunctions [9]="sqrt";pfCreate[9]=ConCreateFunctions::SquareRoot;
	asFunctions [10]="sinh";pfCreate[10]=Sinh::create;
        asFunctions [11]="cosh";pfCreate[11]=Cosh::create;
        asFunctions [12]="tanh";pfCreate[12]=Tanh::create;
        asFunctions [13]="cosec";pfCreate[13]=ConCreateFunctions::Cosec;
        asFunctions [14]="sec";pfCreate[14]=ConCreateFunctions::Sec;
        asFunctions [15]="cot";pfCreate[15]=ConCreateFunctions::Cot;
        asFunctions [16]="cosech";pfCreate[16]=ConCreateFunctions::Cosech;
        asFunctions [17]="sech";pfCreate[17]=ConCreateFunctions::Sech;
        asFunctions [18]="coth";pfCreate[18]=ConCreateFunctions::Coth;
       

}

void ConCreateFunctions::OneOver (Expression ** peOutput,Expression *peInput, int cfInName){
		Expression * peOne=new Constant (1,"1",1);
		*peOutput=Create::createOperator (DIVIDE,peOne,peInput);
		}

void ConCreateFunctions::Minus (Expression ** peOutput,Expression *peInput, int cfInName){
		Expression * peZero=new Constant (1,"",0);
		*peOutput=Create::createOperator (SUBTRACT,peZero,peInput);
		}

void ConCreateFunctions::Squared (Expression ** peOutput,Expression *peInput, int cfInName){
		*peOutput=Create::createOperator (MULTIPLY,peInput,peInput);}

void ConCreateFunctions::Power (Expression ** peOutput,Expression *peInput1,Expression * peInput2, int cfInName){
		*peOutput=Create::createFunction ( EXP,(peOutput,Create::createOperator (MULTIPLY,peInput2,Create::createFunction (LN,peInput1))));}

void ConCreateFunctions::SquareRoot (Expression ** peOutput,Expression *peInput, int cfInName){
		*peOutput=Create::createOperator (POWER,peInput,static_cast<Expression *>(new Constant (0,"1/2",0.5)));
}

void ConCreateFunctions::Cosec(Expression ** peOutput, Expression *peInput, int cfInName) {
    ConCreateFunctions::OneOver(peOutput, Create::createFunction(SIN, peInput), cfInName);
}

void ConCreateFunctions::Sec(Expression ** peOutput, Expression *peInput, int cfInName) {
     ConCreateFunctions::OneOver(peOutput, Create::createFunction(COS, peInput), cfInName);
}

void ConCreateFunctions::Cot(Expression ** peOutput, Expression *peInput, int cfInName) {
    ConCreateFunctions::OneOver(peOutput, Create::createFunction(TAN, peInput), cfInName);
}

void ConCreateFunctions::Cosech(Expression ** peOutput, Expression *peInput, int cfInName) {
    ConCreateFunctions::OneOver(peOutput, Create::createFunction(SINH, peInput), cfInName);
}

void ConCreateFunctions::Sech(Expression ** peOutput, Expression *peInput, int cfInName) {
    ConCreateFunctions::OneOver(peOutput, Create::createFunction(COSH, peInput), cfInName);
}

void ConCreateFunctions::Coth(Expression ** peOutput, Expression *peInput, int cfInName) {
    ConCreateFunctions::OneOver(peOutput, Create::createFunction(TANH, peInput), cfInName);
}

