#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define TSIZE 8

int tabu[TSIZE][TSIZE];

void printTabu();

void removeQueen(int l, int c);
bool putQueen(int l, int c);
bool queenProblem(int l);


int cont = 0;

int main()
{
	freopen("out.txt", "w", stdout);
	//cont = 0;
	//printTabu();
	//printf("Backtracking!\n");
	queenProblem(0);
	//printf("Backtracking!\n");
	//printf("Backtracking!\n");


	fclose(stdout);
	return 0;
}

void printTabu()
{
	printf("Solucao %d\n",++cont);
	for(int i=0;i<TSIZE;i++)
	{
		for(int j=0;j<TSIZE;j++)
		{
			printf("%d",tabu[i][j]);
		}

		printf("\n");
	}
	printf("\n");
}

bool queenProblem(int l)
{
	bool foundAWay = false;
	
	for(int j = 0; j < TSIZE && l < TSIZE; j++)
	{
		if( putQueen(l,j) )
		{
			if( l == (TSIZE-1) )
			{
				foundAWay = true;
				printTabu();
				removeQueen(l,j);
			}
			else
			{					
				
				foundAWay = queenProblem(l + 1);
				
				removeQueen(l,j);
			}
	}

	return foundAWay;
}



bool putQueen(int l,int c)
{
	if( tabu[l][c] > 0 ) return false;
	else
	{
		int k = min(l,c);

		for(int i = 0; i < TSIZE; i++ ) tabu[i][c]++;
		for(int j = 0; j < TSIZE; j++ ) {
			if( j != c ) tabu[l][j]++;
		}

		for(int i = (l-k), j = (c-k); i < TSIZE && j < TSIZE; i++, j++ )
		{
			if( i!=l || j!=c ) tabu[i][j]++;
		}

		for(int i = l, j = c; i < 8 && j >= 0; i++,j--) if( i!=l || j!=c ) tabu[i][j]++;
		for(int i = l, j = c; i >= 0 && j < TSIZE; i--,j++) if( i!=l || j!=c ) tabu[i][j]++;

		return true;
	}
}

void removeQueen(int l, int c){

	int k = min(l,c);

	for(int i = 0; i < TSIZE; i++ ) tabu[i][c]--;
	for(int j = 0; j < TSIZE; j++ ) if( j != c ) tabu[l][j]--;

	for(int i = (l-k), j = (c-k); i < TSIZE && j<TSIZE; i++, j++ )
	{
			if( i!=l || j!=c ) tabu[i][j]--;
	}

	for(int i = l, j = c; i < TSIZE && j >= 0; i++,j--) if( i!=l || j!=c ) tabu[i][j]--;
	for(int i = l, j = c; i >= 0 && j < TSIZE; i--,j++) if( i!=l || j!=c ) tabu[i][j]--;
}
