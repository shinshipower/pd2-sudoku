#include "Sudoku.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

void Sudoku::transform(){
	readIn();
	change();
	printOut(false);	

}

void Sudoku::change(){
	srand(time(NULL);
	changeNum(rand()%9 +1, rand()%9 +1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3, rand()%3);
	rotate(rand()%4);
	flip(rand()%2);
}

void Sudoku::printOut(bool isAns){
	int m;
	if(!isAns)
		for(i=0;i<9;++i)
			printf("%d%c",map[m] ,(i+1)%9==0?'\n':' ');
	else
		for(i=0;i<9;++i)
			printf("%d%c",ans[m], (i+1)%9==0?'\n':' ');

}
