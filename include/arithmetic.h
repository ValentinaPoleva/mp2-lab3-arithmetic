#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

#define MAX_TOK 128
#define MAX_VAR 26

using namespace std;

class TArithmetic
{
protected:
	string _str;	
	string _tok[MAX_TOK];
	int nTok;
	int nVar;
	char nameVar[MAX_VAR];
	double valueVar[MAX_VAR];
public:
	TArithmetic(string _str=" ");
	~TArithmetic();
	void SetVars(int n, char *name, double *value);
	void DivideIntoTokens();
	string WriteStr();
	void CheckBrackets();
	double PolishNotation();
private:
	int Priority(char a);
	int SeePrior(TStack<char> &st);
	double DoOp(char op, double dig1, double dig2);
	bool IsOpearation(char str);
	double SetVar(char a);
};

TArithmetic::TArithmetic(string str) {
	_str=str;
}

TArithmetic::~TArithmetic()
{

}

void TArithmetic::SetVars(int n, char *name, double *value) {
	nVar = n;
	for (int i=0; i<nVar; i++) {
		nameVar[i]=name[i];
		valueVar[i]=value[i];
	}
}

string TArithmetic::WriteStr() {
	int i=0;
	string temp = "";
	while (_tok[i] != "") {
		temp+=_tok[i]+" ";
		i++;
	}
	return temp;
}

void TArithmetic::CheckBrackets() {
	TStack<char> stB;
	if (!stB.IsEmpty())	{
		while (stB.IsEmpty()) stB.GetElem();
	}
	int i=0;
	while (i<_str.length())	{
		if (_str[i]=='(') stB.SetElem(_str[i]);
		if (_str[i]==')') {
			if (stB.IsEmpty()) throw("illigal bracket");
			stB.GetElem();
		}
		i++;
	}
	if (!stB.IsEmpty()) throw("illigal bracket");
}

bool TArithmetic::IsOpearation(char str)
{
	if ((str == '+') ||
		(str == '-') ||
		(str == '*') ||
		(str == '/') ||
		(str == '^'))
		return true; 
	else return false;
}

double TArithmetic::SetVar(char a) {
	for (int i=0; i<MAX_VAR; i++) {
		if (nameVar[i]==a)
			return valueVar[i];
	}
	throw ("illigal variable");
}

double TArithmetic::DoOp(char op, double dig1, double dig2) {
	switch (op)	{
			case '^': return(pow(dig1, dig2)); 
			case '*': return(dig1 * dig2); 
			case '/': return(dig1 / dig2); 
			case '+': return(dig1 + dig2); 
			case '-': return(dig1 - dig2); 
			}
}

int TArithmetic::SeePrior(TStack<char> &st)
{
	char tmp;
	tmp=st.GetElem();
	st.SetElem(tmp);
	return Priority(tmp);
}

int TArithmetic::Priority(char a)
{
	switch(a)
	{
	case '^': return 3;
	case '*': case '/': return 2;
	case '+': case '-': return 1;
	case '(': return 0;
	}
}

void TArithmetic::DivideIntoTokens() {
	int i=0;
	int j=0;
	while (i < _str.length()) {
		if ((_str[i]>='0')&&(_str[i]<='9')) {
				while ((i < _str.length())&&(((_str[i]>='0')&&(_str[i]<='9'))||(_str[i]=='.'))) {
					_tok[j] += _str[i];
					i++;
				}
				i--;
				j++;
			}
		else
			if ((_str[i]>='a')&&(_str[i]<='z')) {
				_tok[j]=_str[i];
				j++;
			}
			else
				switch (_str[i]) {
				case '(': 
				case ')': 
				case '*': 
				case '+': 
				case '-': 
				case '/': 
				case '^': {
					_tok[j]=_str[i];
					j++;
					break;
				}
				default:
					break;
			} 
			
		i++;
	}
	nTok = j;
}

double TArithmetic::PolishNotation() {
	CheckBrackets();
	DivideIntoTokens();
	TStack<double> stackD(256);
	TStack<char> stackO(256);
	double dig1=0; 
	double dig2=0;
	
	int i=0;
	while (i<nTok) {
		/*handler digits*/
		if ((_tok[i][0]>='0')&&(_tok[i][0]<='9'))
			stackD.SetElem(stod(_tok[i]));
		else
			/*handler variables*/
			if (isalpha(_tok[i][0]))
				stackD.SetElem(SetVar(_tok[i][0]));
				/*handler open bracket*/
				if (_tok[i][0]=='(')
					stackO.SetElem(_tok[i][0]);
				else
				/*handler operations*/
				if (IsOpearation(_tok[i][0])) {
					if (((!stackO.IsEmpty())&&(SeePrior(stackO)==0))||(stackO.IsEmpty())||(Priority(_tok[i][0])>=SeePrior(stackO)))
						stackO.SetElem(_tok[i][0]);
					else
						if (Priority(_tok[i][0])<SeePrior(stackO)) {
							while ((!stackO.IsEmpty())&&(Priority(_tok[i][0])<SeePrior(stackO))) {
								char tmp = stackO.GetElem();
								dig2=stackD.GetElem();
								dig1=stackD.GetElem();
								stackD.SetElem(DoOp(tmp,dig1,dig2));
							}
							stackO.SetElem(_tok[i][0]);
						}
				}
				else
					/*handler close bracket*/
					if (_tok[i][0]==')') {
						while (!SeePrior(stackO)==0) {
							char tmp = stackO.GetElem();
							dig2=stackD.GetElem();
							dig1=stackD.GetElem();
							stackD.SetElem(DoOp(tmp,dig1,dig2));
						}
						char tmp = stackO.GetElem();
					}
		i++;
	}
	/*handler operations without brackets*/
	while (!stackO.IsEmpty()) {
		char tmp=stackO.GetElem();
		dig2=stackD.GetElem();
		dig1=stackD.GetElem();
		stackD.SetElem(DoOp(tmp,dig1,dig2));
	}

	return stackD.GetElem();
}


