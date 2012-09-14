
#include "CAS IO.h"
#include "PhysicalConstants.h"
namespace CAS {

bool InputOutputMaster::checkFunction(Expression ** peOutput, int cEnd) {
    int cIdent;
    char hFunction [8];
    int cLength = 0;
    for (; cLength < 7 && !(hTest [cRead + cLength] == '('); cLength++) {
        hFunction [cLength] = hTest [cRead + cLength];
    }
    hFunction [cLength] = '\0';
    std::string compare = hFunction;
    for (cIdent = 0; cIdent < MAXFUNCTIONS; cIdent++) {
        if (asFunctions [cIdent] == compare) break;
    }
    if (cIdent == MAXFUNCTIONS) return false;
    int cCloseBracket = findClosingBracket(cRead + cLength, cEnd);
    Printable ** ppBracket = new Printable *;
    if (!(convertToPrintable(cRead + cLength + 1, cCloseBracket, ppBracket))) return false;
    *peOutput = static_cast<Expression*> (*ppBracket);
    cRead = cCloseBracket;
    *peOutput = Create::createFunction(cIdent, *peOutput);
    return true;
}

bool InputOutputMaster::checkNamedConstant (Expression ** peOutput,int cEnd) {
	char hFunction [8];int cLength=1;
	for (;cLength<7&&!(hTest [cRead+cLength]==']');cLength++){
		hFunction [cLength-1]=hTest [cRead+cLength];}
	if (cLength==1) return false;
	hFunction [cLength-1]='\0';
	std::string compare= hFunction;
	
	if(compare=="pi") *peOutput=new Constant (1,"pi",physics::pi,true);
	else if (compare=="g") *peOutput=new Constant (1,"g",physics::g);
	//space for more constants here
	else { Printable ** ppBracket=new Printable *;
		if(!convertToPrintable (cRead+1,cRead+cLength,ppBracket)) return false;
		*peOutput=static_cast<Expression*> (*ppBracket);
	}
	cRead+=cLength;
	
	return true;}

int InputOutputMaster::findClosingBracket (int cBracketStart,int cEnd){
	int cNumberOfOpenBrackets=1;
	for (int cTest=cBracketStart+1;cTest<cEnd;cTest++){
if (hTest [cTest]=='(')cNumberOfOpenBrackets++;
if (hTest [cTest]==')')cNumberOfOpenBrackets--;
if(cNumberOfOpenBrackets==0) return cTest;}
	return cEnd;}

bool InputOutputMaster::checkVariable (int cAscii,Expression ** peOutput){
int cvFunctionsOf [MAXFUNCTIONOF];
for (int cIdent=0;cIdent<cNumVar;cIdent++){


	if(cAscii==ahVariables [cIdent][0]) {
		
		
		for (int cIter=1;cIter<MAXFUNCTIONOF;cIter++) cvFunctionsOf [cIter]=ahVariables [cIdent][cIter];
		std::string sName;sName=(char)cAscii;
		*peOutput= static_cast<Expression*> (new Variable (cIdent,sName,cvFunctionsOf)); return true;}
}
if(cNumVar<MAXVARIABLES){
ahVariables [cNumVar][0]=cAscii;
for (int cIdent=1;cIdent<MAXFUNCTIONOF;cIdent++) {	cvFunctionsOf [cIdent]=-1;
ahVariables [cNumVar][cIdent]=-1;}
std::string sName;sName=(char)cAscii;
*peOutput= static_cast<Expression*> (new Variable (cNumVar,sName,cvFunctionsOf)); 
cNumVar++;
return true;}
else return false;
}

bool InputOutputMaster::checkImaginary (Expression ** peOutput){
    *peOutput= new Constant (1,"i",complex<double> (0,1));
    
}



bool InputOutputMaster::checkConstant (Expression ** peOutput){
	std::stringstream ssConverter (std::stringstream::in | std::stringstream::out|std::stringstream::app);int cAscii;
	do{ssConverter<<hTest [cRead];
		cRead++;
		cAscii=(int) hTest [cRead];}
		while ((cAscii>47&&cAscii<58)||cAscii==46);
		cRead--;
		complex<double> dcInValue;
		ssConverter>>dcInValue;
		*peOutput=new Constant (1,ssConverter.str(),dcInValue);
return true;}

bool InputOutputMaster::checkOperator (int cAscii,int * pcIDENT, int * pcOrder){
	for (int cIter=0;cIter<MAXOPERATORS;cIter++){
		if (cAscii==ahOperators [cIter] [0]) {
			if (*pcOrder<=ahOperators [cIter] [1]){
				*pcOrder=ahOperators [cIter] [1];
				*pcIDENT=cIter;
				return true;}
			else return false;}
	}
	return false;}
	
bool InputOutputMaster::checkForPostFunctions (Expression ** peOutput){return false;
}

bool InputOutputMaster::findLastOperator(int cStart, int cEnd, Printable** ppOutput) {
    int cPos, coName, cOrder;
    int bLeading = false;
    int cEndStore = cEnd;
    if (hTest[cStart] == '-' || hTest[cStart] == '+')bLeading = true;
    int last;
    //do{	
    last = 0;
    cPos = cStart;
    cOrder = 0; //higher signifies would be done after in BODMAS order
    for (int cIter = cStart; cIter < cEndStore; cIter++) {
        int cAscii = (int) hTest [cIter];
        if (cAscii == 40) cIter = findClosingBracket(cIter, cEnd); //if (hTest[cIter]== '(') ignore brackets
        else if (checkOperator(cAscii, &coName, &cOrder)) cPos = cIter;
    }
    if ((cPos == cStart && !bLeading) || cPos == cEnd - 1) return false;
    cEndStore = cPos;
    //}
    if (cPos!=cStart&&checkOperator(hTest[cPos - 1], &coName, &last)) {
        cPos--;
    };

    Expression * peInput1;
    Expression * peInput2;
    peInput1 = NULL;
    if (cPos != cStart) {
        if (!(convertToPrintable(cStart, cPos, ppOutput))) 
            return false;
        peInput1 = static_cast<Expression*> (*ppOutput);
    }
    if (!(convertToPrintable(cPos + 1, cEnd, ppOutput)))
        return false;
    peInput2 = static_cast<Expression*> (*ppOutput);
    *ppOutput = createBiInput(coName, peInput1, peInput2);
    if (*ppOutput == NULL) 
        return false;
    return true;
}

bool InputOutputMaster::checkMinus (Expression ** peOutput,int cEnd){
	Printable ** ppOutput=new Printable *;
	convertToPrintable (cRead+1,cEnd,ppOutput);
	*peOutput=static_cast<Expression*> (*ppOutput);
	*peOutput=createFunction(MINUS,*peOutput);
	cRead--;return true;}
		
bool InputOutputMaster::convertToPrintable (int cStart, int cEnd, Printable ** ppOutput ){
			cRead=cStart;
	//for (cRead=cStart;cRead<MAXSIZE;cRead++){ 
			if (findLastOperator (cStart,cEnd,ppOutput)) return true;
			Expression ** peProduct=new Expression *;Expression ** peMultiplyBy=new Expression *; bool bFirst=true;
			for (;cRead<cEnd;cRead++){
			int cAscii=(int) hTest [cRead];
			if (! (cAscii==41) ) {//ignore close brackets
			if (cAscii==40) {int cCloseBracket=findClosingBracket(cRead,cEnd);//(
								Printable ** ppBracket=new Printable *;
								 if(  ! (convertToPrintable (cRead+1,cCloseBracket,ppBracket) )) return false;//if (hTest[cRead]== '(') deal with brackets
								 *peMultiplyBy=static_cast<Expression*> (*ppBracket);
								 cRead=cCloseBracket;}
			else if (cAscii==91) checkNamedConstant (peMultiplyBy,cEnd);//[
			else if (cAscii>47&&cAscii<58) checkConstant (peMultiplyBy);//0-9
			else if(checkFunction (peMultiplyBy,cEnd)) ;
			else if(cAscii==45) {checkMinus (peMultiplyBy,cEnd);}//-
                        else if (cAscii==105) {checkImaginary (peMultiplyBy);}//i
            else checkVariable(cAscii, peMultiplyBy);
            checkForPostFunctions(peMultiplyBy);
            if (bFirst) {
                *peProduct = *peMultiplyBy;
                bFirst = false;
            } else {
                *peProduct = createOperator(MULTIPLY, *peProduct, *peMultiplyBy);
            }
        }
    }
    *ppOutput = static_cast<Printable*> (*peProduct);
    //delete peProduct;delete peMultiplyBy; //? I get an error with this in, but should it not be there?
    return true;
}

void InputOutputMaster::setVariables(complex<double> dInVar []) {
    glbArrayCopy< complex<double> > (Variable::dvValues, dInVar, cNumVar);
};

void InputOutputMaster::setVariable(complex<double> dInVar, int IDENT) {
    Variable::dvValues [IDENT] = dInVar;
}

int InputOutputMaster::getNumVar() {
    return cNumVar;
}

char InputOutputMaster::getVariableName(int cIdent) {
    return ahVariables [cIdent] [0];
}

bool InputOutputMaster::convertInputString(const char * hInput, int cSize, Printable ** ppOutput)
 {
    int cTest = 0;
    for (int cInput = 0; cInput < cSize; cInput++) {
        if (!(hInput[cInput] == ' ')) {
            hTest[cTest] = hInput[cInput];
            cTest++;
        }
    }//Extract spaces;
    for (int cInput = cTest; cInput < MAXSIZE; cInput++) {
        hTest[cInput] = 0;
    }//Delete rest of hTest so it does not mess with anything else;
    //std::cout<<std::endl;
    if (convertToPrintable(0, cTest, ppOutput)) return true;


    return false;

}

bool InputOutputMaster::convertToOutputString(std::string * sOutput, Printable * ppInput) {
    std::stringstream ssOutput;
    ppInput->print(&ssOutput);
    *sOutput = ssOutput.str();
    return true;
}

InputOutputMaster::InputOutputMaster() {
    cNumVar = 0;
}

void setCinVariables(InputOutputMaster * IOMaster) {
    complex<double> dInValues [MAXVARIABLES];
    std::string sInput;
    for (int cIter = 0; cIter < IOMaster->getNumVar(); cIter++) {
        std::cout << IOMaster->getVariableName(cIter) << " = ";
        std::getline(std::cin, sInput);
        std::stringstream ssConverter(sInput);
        ssConverter >> dInValues [cIter];
    }
    IOMaster->setVariables(dInValues);
}

complex<double> CasUnaryFunction::evaluateAt(complex<double> InputValue) {
    IO->setVariable(InputValue, VariableIdentifier);
    return UnaryFunction->evaluate();
}

complex<double> CasUnaryFunction::evaluateNthDerviativeAt(complex<double> InputValue, int N) {
    Expression ** derivative = new Expression *;
    *derivative = UnaryFunction;
    for (int i = 0; i < N; i++) {
        (*derivative)->differentiate(derivative, VariableIdentifier);
    }
    IO->setVariable(InputValue, VariableIdentifier);
    complex<double> ret;
    if ((*derivative) == NULL) ret = 0;
    else ret = (*derivative)->evaluate();
    delete derivative;
    return ret;

}

CasUnaryFunction::CasUnaryFunction(std::string iFunction, std::string iName, bool * success, InputOutputMaster * inIO) {
    create(iFunction.c_str(), iFunction.size(), iName, success, inIO);

}

CasUnaryFunction::CasUnaryFunction(const char* iFunction, int size, std::string iName, bool * success, InputOutputMaster * inIO) {
    create(iFunction, size, iName, success, inIO);

}

void CasUnaryFunction::createFunction(std::string iFunction, std::string iName, bool * success, InputOutputMaster * inIO) {
    create(iFunction.c_str(), iFunction.size(), iName, success, inIO);

}

void CasUnaryFunction::createFunction(const char* iFunction, int size, std::string iName, bool * success, InputOutputMaster * inIO) {
    create(iFunction, size, iName, success, inIO);

}

void CasUnaryFunction::create(const char* iFunction, int size, std::string iName, bool * success, InputOutputMaster * inIO) {
    std::vector<int> outIdentifiers;
    bool dummy;
    Name = iName;
    newIO = false;
    if (inIO == NULL) {
        IO = new InputOutputMaster;
        newIO = true;
    } else
        IO = inIO;
    if (success == NULL)
        success = &dummy;
    Printable * pFunction;
    if (!IO->convertInputString(iFunction, size, &pFunction)) *success = false;
    else {
        UnaryFunction = static_cast<Expression *> (pFunction);
        (*success) = true;
        if (inIO == NULL)
            if (IO->getNumVar() == 1)
                VariableIdentifier = 0;
            else
                (*success) = false; //Not a Unary Function!
        else if (TreeWalker::findVariables(UnaryFunction, &outIdentifiers) == 1)
            VariableIdentifier = outIdentifiers [0];
        else
            (*success) = false; //Not a Unary Function!
    }
}

std::string CasUnaryFunction::print(int NthDerivative) {
    Expression ** derivative = new Expression *;
    *derivative = UnaryFunction;
    for (int i = 0; i < NthDerivative; i++) {
        (*derivative)->differentiate(derivative, VariableIdentifier);
    }
    std::stringstream out;
    if ((*derivative) == NULL) out << "0";
    else (*derivative)->print(&out);
    if (NthDerivative > 0) delete derivative;
    return out.str();

}

std::string CasUnaryFunction::latex(int NthDerivative) {
    Expression ** derivative = new Expression *;
    *derivative = UnaryFunction;
    for (int i = 0; i < NthDerivative; i++) {
        (*derivative)->differentiate(derivative, VariableIdentifier);
    }
    std::stringstream out;
    if ((*derivative) == NULL) out << "0";
    else {
        out << "$";
        (*derivative)->latex(&out);
        out << "$";
    }
    if (NthDerivative > 0) delete derivative;
    return out.str();

}

std::string CasUnaryFunction::getName() {
    return Name;
}

std::string CasUnaryFunction::getInputVar() {
    std::stringstream out;
    out << IO->getVariableName(VariableIdentifier);
    return out.str();
}

CasUnaryFunction CasUnaryFunction::operator *(CasUnaryFunction A) {
    CasUnaryFunction ret = A;
    ret.UnaryFunction = Create::createOperator(MULTIPLY, A.UnaryFunction, UnaryFunction);
    return ret;
};

CasUnaryFunction::~CasUnaryFunction() {
    //delete UnaryFunction;
    //   if (newIO)
    //     delete IO;
}

}
	

	