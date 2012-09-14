#include "Operators.h"
#include "math.h"
namespace CAS {
//Multiplication

complex<double> Multiplication::evaluate() {
    return (((*peInput1)->evaluate()) * ((*peInput2)->evaluate()));
}

bool Multiplication::simplify(Expression ** peOutput) {
    return false;
}

bool Multiplication::differentiate(Expression **peOutput, int cvWithRespectTo) {
    Expression ** peDiff1 = new Expression *;
    Expression ** peDiff2 = new Expression *;
    if ((*peInput1)->differentiate(peDiff1, cvWithRespectTo)) *peDiff1 = Create::createOperator(MULTIPLY, *peDiff1, *peInput2);
    if ((*peInput2)->differentiate(peDiff2, cvWithRespectTo)) *peDiff2 = Create::createOperator(MULTIPLY, *peDiff2, *peInput1);
    if (*peDiff1 == NULL && *peDiff2 == NULL) return false;
    *peOutput = Create::createOperator(ADD, *peDiff1, *peDiff2);
    delete peDiff1;
    delete peDiff2;
    return true;
}

void Multiplication::create(Expression ** peOutput, Expression *peInput1, Expression *peInput2, int coInName) {
    if (peInput1 == NULL && peInput2 == NULL) {
        *peOutput = NULL;
    } else if (peInput1 == NULL) *peOutput = peInput2;
    else if (peInput2 == NULL) *peOutput = peInput1;
    else {
        Expression * peDummy = new Multiplication(peInput1, peInput2, coInName);
        *peOutput = peDummy;
    }
}

void Multiplication::latex(std::stringstream * ssOutput) {
    (*peInput1)->latex(ssOutput);
    if (Constant * var = dynamic_cast<Constant *> (*peInput2)) {
        *ssOutput << "*";
    }
    
    (*peInput2)->latex(ssOutput);
}

Multiplication::Multiplication(Expression *peInput1, Expression *peInput2, int coInName) : Operator(peInput1, peInput2) {
    coName = coInName;
};

//Division

complex<double> Division::evaluate() {
    return ((*peInput1)->evaluate()) / ((*peInput2)->evaluate());
} // One over Two

bool Division::simplify(Expression ** peOutput) {
    return false;
}

bool Division::differentiate(Expression **peOutput, int cvWithRespectTo) {
    Expression ** peDiff1 = new Expression *;
    Expression ** peDiff2 = new Expression *;
    if ((*peInput1)->differentiate(peDiff1, cvWithRespectTo)) *peDiff1 = Create::createOperator(MULTIPLY, *peDiff1, *peInput2);
    if ((*peInput2)->differentiate(peDiff2, cvWithRespectTo)) *peDiff2 = Create::createOperator(MULTIPLY, *peDiff2, *peInput1);
    if (*peDiff1 == NULL && *peDiff2 == NULL) return false;
    *peOutput = Create::createOperator(SUBTRACT, *peDiff1, *peDiff2);
    *peDiff1 = Create::createOperator(MULTIPLY, *peInput2, *peInput2);
    *peOutput = Create::createOperator(coName, *peOutput, *peDiff1);
    delete peDiff1;
    delete peDiff2;
    return true;
}

void Division::create(Expression ** peOutput, Expression *peInput1, Expression *peInput2, int coInName) {
    if (peInput1 == NULL || peInput2 == NULL) {
        *peOutput = NULL;
    } else {
        Expression * peDummy = new Division(peInput1, peInput2, coInName);
        *peOutput = peDummy;
    }
}

void Division::latex(std::stringstream * ssOutput) {
    *ssOutput << "\\frac {";
    (*peInput1)->latex(ssOutput);
    *ssOutput << "}{";
    (*peInput2)->latex(ssOutput);
    *ssOutput << "}";
}

Division::Division(Expression *peInput1, Expression *peInput2, int coInName) : Operator(peInput1, peInput2) {
    coName = coInName;
};

//Addition

complex<double> Addition::evaluate() {
    return ((*peInput1)->evaluate())+((*peInput2)->evaluate());
}

bool Addition::simplify(Expression ** peOutput) {
    return false;
}

bool Addition::differentiate(Expression **peOutput, int cvWithRespectTo) {
    Expression ** peDiff1 = new Expression *;
    Expression ** peDiff2 = new Expression *;
    if ((*peInput1)->differentiate(peDiff1, cvWithRespectTo) && *peDiff1 == NULL) *peDiff1 = static_cast<Expression*> (new Constant(1, "1", 1));
    if ((*peInput2)->differentiate(peDiff2, cvWithRespectTo) && *peDiff2 == NULL) *peDiff2 = static_cast<Expression*> (new Constant(1, "1", 1));
    if (*peDiff1 == NULL && *peDiff2 == NULL) return false;
    *peOutput = Create::createOperator(ADD, *peDiff1, *peDiff2);
    return true;
}

void Addition::create(Expression ** peOutput, Expression *peInput1, Expression *peInput2, int coInName) {
    if (peInput1 == NULL && peInput2 == NULL) {
        *peOutput = NULL;
    } else if (peInput1 == NULL) *peOutput = peInput2;
    else if (peInput2 == NULL) *peOutput = peInput1;
    else {
        Expression * peDummy = new Addition(peInput1, peInput2, coInName);
        *peOutput = peDummy;
    }
}

void Addition::latex(std::stringstream * ssOutput) {
    *ssOutput << "\\left(";
    (*peInput1)->latex(ssOutput);
    *ssOutput << "+";
    (*peInput2)->latex(ssOutput);
    *ssOutput<<"\\right)";
}

Addition::Addition(Expression *peInput1, Expression *peInput2, int coInName) : Operator(peInput1, peInput2) {
    coName = coInName;
};

//Subtraction

complex<double> Subtraction::evaluate() {
    return ((*peInput1)->evaluate())-((*peInput2)->evaluate());
}

bool Subtraction::simplify(Expression ** peOutput) {
    return false;
}

bool Subtraction::differentiate(Expression **peOutput, int cvWithRespectTo) {
    Expression ** peDiff1 = new Expression *;
    Expression ** peDiff2 = new Expression *;
    if ((*peInput1)->differentiate(peDiff1, cvWithRespectTo) && *peDiff1 == NULL) *peDiff1 = static_cast<Expression*> (new Constant(1, "1", 1));
    if ((*peInput2)->differentiate(peDiff2, cvWithRespectTo) && *peDiff2 == NULL) *peDiff2 = static_cast<Expression*> (new Constant(1, "1", 1));
    if (*peDiff1 == NULL && *peDiff2 == NULL) return false;
    *peOutput = Create::createOperator(coName, *peDiff1, *peDiff2);
    return true;
}

void Subtraction::create(Expression ** peOutput, Expression *peInput1, Expression *peInput2, int coInName) {
    if (peInput1 == NULL && peInput2 == NULL) {
        *peOutput = NULL;
    } else {
        if (peInput1 == NULL)peInput1 = new Constant(0, "", 0);
        if (peInput2 == NULL) *peOutput = peInput1;
        else {
            Expression * peDummy = new Subtraction(peInput1, peInput2, coInName);
            *peOutput = peDummy;
        }
    }
}

void Subtraction::latex(std::stringstream * ssOutput) {
  *ssOutput << "\\left(";
    (*peInput1)->latex(ssOutput);
    *ssOutput << "-";
    (*peInput2)->latex(ssOutput);
    *ssOutput<<"\\right)";
}

Subtraction::Subtraction(Expression *peInput1, Expression *peInput2, int coInName) : Operator(peInput1, peInput2) {
    coName = coInName;
};

//Power

complex<double> Power::evaluate() {
    return pow((*peInput1)->evaluate(), ((*peInput2)->evaluate()));
} // One ^ Two

bool Power::simplify(Expression ** peOutput) {
    return false;
}

bool Power::differentiate(Expression **peOutput, int cvWithRespectTo) {
    Expression ** peDiff1 = new Expression *;
    Expression ** peDiff2 = new Expression *;
    if ((*peInput1)->differentiate(peDiff1, cvWithRespectTo)){
        if(*peDiff1 == NULL)
            *peDiff1 = static_cast<Expression*> (new Constant(1, "1", 1));
    }
    else *peDiff1=NULL;
    if ((*peInput2)->differentiate(peDiff2, cvWithRespectTo)){
        if (*peDiff2 == NULL) 
            *peDiff2 = static_cast<Expression*> (new Constant(1, "1", 1));
    }
    else *peDiff2=NULL;
    
    if (*peDiff1 == NULL && *peDiff2 == NULL) {
        *peOutput = NULL;
        return false;
    }
    if (*peDiff1 != NULL && *peDiff2 != NULL)
        *peOutput = Create::createOperator(MULTIPLY, Create::createOperator(coName, *peInput1, *peInput2),
            Create::createOperator(ADD, Create::createOperator(MULTIPLY, *peDiff2,
            Create::createFunction(LN, *peInput1)),
            Create::createOperator(MULTIPLY, *peInput2,
            Create::createOperator(DIVIDE, *peDiff1, *peInput1))
            )
            );
    else if (*peDiff2 != NULL)
        *peOutput = Create::createOperator(MULTIPLY, Create::createOperator(coName, *peInput1, *peInput2), Create::createOperator(MULTIPLY, *peDiff2,
            Create::createFunction(LN, *peInput1)));
    else
        *peOutput = Create::createOperator(MULTIPLY, Create::createOperator(coName, *peInput1, Create::createOperator(SUBTRACT, *peInput2, new Constant(1, "1", 1))),
            Create::createOperator(MULTIPLY, *peDiff1, *peInput2));
    return true;
}

void Power::create(Expression ** peOutput, Expression *peInput1, Expression *peInput2, int coInName) {
    if (peInput1 == NULL && peInput2 == NULL) {
        *peOutput = NULL;
    } else {
        if (peInput1 == NULL)peInput1 = new Constant(0, "", 0);
        if (peInput2 == NULL) *peOutput = new Constant(1, "1", 1);
        else {
            Expression * peDummy = new Power(peInput1, peInput2, coInName);
            *peOutput = peDummy;
        }
    }
}

void Power::latex(std::stringstream * ssOutput) {
    *ssOutput << "{";
    (*peInput1)->latex(ssOutput);
    *ssOutput << "}^{";
    (*peInput2)->latex(ssOutput);
    *ssOutput << "}";
}

Power::Power(Expression *peInput1, Expression *peInput2, int coInName) : Operator(peInput1, peInput2) {
    coName = coInName;
};

//Greater Than

complex<double> GreaterThan::evaluate() {
    return (int) (norm((*peInput1)->evaluate()) > norm((*peInput2)->evaluate()));
} // One > Two, 1 if true, 0 if false

bool GreaterThan::simplify(Expression ** peOutput) {
    return false;
}

bool GreaterThan::differentiate(Expression **peOutput, int cvWithRespectTo) {
    *peOutput = NULL;
    return false;
}

void GreaterThan::create(Expression ** peOutput, Expression *peInput1, Expression *peInput2, int coInName) {
    if (peInput1 == NULL && peInput2 == NULL) {
        *peOutput = NULL;
    } else {
        if (peInput1 == NULL)peInput1 = new Constant(0, "0", 0);
        if (peInput2 == NULL) *peOutput = new Constant(0, "0", 0);
        else {
            Expression * peDummy = new GreaterThan(peInput1, peInput2, coInName);
            *peOutput = peDummy;
        }
    }
}

void GreaterThan::latex(std::stringstream * ssOutput) {
    *ssOutput << "\\left(";
    (*peInput1)->latex(ssOutput);
    *ssOutput << ">";
    (*peInput2)->latex(ssOutput);
    *ssOutput<<"\\right)";
}

GreaterThan::GreaterThan(Expression *peInput1, Expression *peInput2, int coInName) : Operator(peInput1, peInput2) {
    coName = coInName;
};

//Less Than

complex<double> LessThan::evaluate() {
    return (int) (norm((*peInput1)->evaluate()) < norm((*peInput2)->evaluate()));
} // One < Two, 1 if true, 0 if false

bool LessThan::simplify(Expression ** peOutput) {
    return false;
}

bool LessThan::differentiate(Expression **peOutput, int cvWithRespectTo) {
    *peOutput = NULL;
    return false;
}

void LessThan::create(Expression ** peOutput, Expression *peInput1, Expression *peInput2, int coInName) {
    if (peInput1 == NULL && peInput2 == NULL) {
        *peOutput = NULL;
    } else {
        if (peInput1 == NULL)peInput1 = new Constant(0, "0", 0);
        if (peInput2 == NULL) *peOutput = new Constant(0, "0", 0);
        else {
            Expression * peDummy = new LessThan(peInput1, peInput2, coInName);
            *peOutput = peDummy;
        }
    }
}

void LessThan::latex(std::stringstream * ssOutput) {
    *ssOutput << "\\left(";
    (*peInput1)->latex(ssOutput);
    *ssOutput << "<";
    (*peInput2)->latex(ssOutput);
    *ssOutput<<"\\right)";
}

LessThan::LessThan(Expression *peInput1, Expression *peInput2, int coInName) : Operator(peInput1, peInput2) {
    coName = coInName;
};

}