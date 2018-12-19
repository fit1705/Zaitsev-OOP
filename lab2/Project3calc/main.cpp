
#include <iostream>
#include <fstream>
#include "Calculator.h"
using namespace std;
int main() {
	
	ifstream fin;
	ofstream fout;
	fin.open("in.txt");
	fout.open("out.txt");
	Calculator calculator;
	calculator.complete(fin, fout);

}