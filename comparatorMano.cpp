#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream in1("fibonacciOut.txt");
	ifstream in2("fibonacciOut2Joao.txt");
	
	int r1=0,r2=0;
	
	while( r1 == r2 && in1 >> r1 && in2 >> r2 ) 
	{
	
	}
	
	if(r1 != r2)
	{
		cout << "diferente!" << endl;
	}
	else
	{
		cout << "bateu tudo" << endl;
	}
	
	cin.get();
	
	return 0;
}
