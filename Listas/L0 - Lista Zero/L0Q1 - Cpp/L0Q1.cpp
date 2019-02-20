#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;

const int MAX_SIZE = 171;

long long int fibArray[MAX_SIZE];

inline void CacheFibArray()
{
	fibArray[0] = 1;
	fibArray[1] = 1;

	for(int i=2;i<MAX_SIZE;i++)
	{
		fibArray[i] = fibArray[i-1] + fibArray[i-2];
	}
}



int main()
{
	CacheFibArray();

	ifstream in("L0Q1.in");
	ofstream out("L0Q1.out");

	int i = 0;

	while(in >> i)
	{
		out << fibArray[i] << endl;
	}

	out.close();

	return 0;
}
