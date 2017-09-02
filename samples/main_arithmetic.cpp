#include "arithmetic.h"

int main() {
	string str;
	bool var;

	cout << "Are you want to use vars?" << endl;
	cin >> var;
	if (var) {
		int n;
		bool rep;
		char *name;
		double *value;
		cout << "Number of variables: ";
		cin >> n;
		name = new char[n];
		value = new double[n];
		for (int i=0; i<n; i++) { 
			cout << "enter name " << i+1 << " var: ";
			cin >> name[i];
			cout << "enter value " << name[i]<< ": ";
			cin >> value[i];
		}
		cout << "Enter expression:" << endl;
		cin >> str;
		TArithmetic Ar(str);
		Ar.SetVars(n,name,value);
		cout << "Value = " << Ar.PolishNotation() << endl;
		
		system("pause");
			
	}
	else
	{
		cout << "Enter expression:" << endl;
		cin >> str;
		TArithmetic Ar(str);
		cout << "Value = " << Ar.PolishNotation() << endl;
	}
	
	return 1;
}