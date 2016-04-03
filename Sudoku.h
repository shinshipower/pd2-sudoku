#define SIZE 9
#include <vector>
using namespace std;

class Sudoku
{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a, int b);
		void changeRow(int a, int b);
		void changeCol(int a, int b);
		void rotate(int n);
		void flip(int n);
		void transform();
	
		void change();
		void printOut(bool isAns);
	

	
		

	private:
		int i,j,k;
		int in_board[SIZE*SIZE];
		int count[SIZE*SIZE];
		int Found;
		bool tag[SIZE*SIZE][SIZE];
		void setAns(int A);
		int map[SIZE*SIZE];


};
