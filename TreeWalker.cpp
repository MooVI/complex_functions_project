#include "TreeWalker.h"
#include <algorithm>

typedef std::vector<int> IntContainer;
typedef IntContainer::iterator IntIterator;

int TreeWalker::findVariables (Expression * Input, std::vector<int> * outIdentifiers){
	ExpPtrVector Inputs;
	int n=0;
	if (Input->getInput (&Inputs)){
		for (ExpPtrIterator i=Inputs.begin(); i!=Inputs.end();i++){
			std::vector <int> inOutIdentifiers;
			TreeWalker::findVariables ((*i),&inOutIdentifiers);
			for (IntIterator u=inOutIdentifiers.begin();u<inOutIdentifiers.end();u++){
				IntIterator test = std::find(inOutIdentifiers.begin(), inOutIdentifiers.end(), (*u));
				if (test !=inOutIdentifiers.end()) {
				outIdentifiers->push_back ((*u));
				n++;
				}
			}
		}
	}
	else if (Variable * var = dynamic_cast<Variable *> (Input)){
		outIdentifiers->push_back(var->cvName);
		n++;
	}
	return n;
}






