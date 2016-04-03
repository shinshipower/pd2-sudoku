#include "Sudoku.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdio.h>

using namespace std;

Sudoku::Sudoku() {
	iii=0;
	for(iii=0;iii<81;iii++){
		map[iii]=0;
		ans[iii]=0;
	}
	
}


int Sudoku::SolveSudoku::Ans = 0;
int Sudoku::SolveSudoku::O_board[];

void Sudoku::giveQuestion(){

	int M17[] {0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,0,0,3,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,5,0,0,4,0,1,6,0,0,0,0,0,0,0,7,1,0,0,0,0,0,0,5,0,0,0,0,2,0,0,0,0,0,0,8,0,0,4,0,0,3,0,9,1,0,0,0,0};
	int ii;
	for(ii=0;ii<81;ii++){map[ii]=M17[ii];}
	change();
	printOut(false);

}

void Sudoku::readIn(){

	int ii,jj;
	int row[9];
	for(ii=0;ii<9;ii++){
			cin>>row[0]>>row[1]>>row[2]>>row[3]>>row[4]>>row[5]>>row[6]>>row[7]>>row[8];
			//cout<<"I got : "<<row[0]<<row[1]<<row[2]<<row[3]<<row[4]<<row[5]<<row[6]<<row[7]<<row[8]<<endl;

		for(jj=0;jj<9;jj++){

			map[ii*9+jj]=row[jj];
		}
	}
	
}

void Sudoku::changeNum(int a, int b){
	int ii;
	for(ii=0;ii<81;ii++){
		if(map[ii] == a)
			map[ii]=b;
		else if(map[ii] == b)
			map[ii]=a;
	}

}

void Sudoku::changeRow(int a, int b){

	int tmp;
	int ii,jj;
	for(ii=0;ii<9;ii++){
		if (ii/3 == a){
			for (jj=0;jj<9;jj++){
				tmp = map[ii*9+jj];
				map[ii*9+jj] = map[(b*3+ii%3)*9+jj];
				map[(b*3+ii%3)*9+jj] = tmp;
			}
		}
	}

}
void Sudoku::changeCol(int a, int b){

	int tmp;
	int ii,jj;
	for (ii = 0;ii<9;ii++){
		for(jj=0;jj<9;jj++){
			if(jj/3==a){
				tmp = map[ii*9+jj];
				map[ii*9+jj]=map[ii*9+(b*3+jj%3)];
				map[ii*9+(b*3+jj%3)]=tmp;			

			}	
		}
	}

}

void Sudoku::rotate(int n){
int ii,jj,kk;
int p = n%4;
if( n != 0){
	for(kk = 0;kk<p;kk++){
		for(ii=0; ii<9/2; ii++)
   		for( jj=0; jj<(9+1)/2; jj++)
       			cyclic_roll(map[ii*9+jj], map[(9-1-jj)*9+ii], map[(9-1-ii)*9+(9-1-jj)], map[jj*9+(9-1-ii)]);
	}
}
}

void Sudoku::cyclic_roll(int &a, int &b, int &c, int &d){

int temp = a;
   a = b;
   b = c;
   c = d;
   d = temp;


}

void Sudoku::flip(int n){
	int ii,jj,tmp;
	if(n==0){
		for(ii=0;ii<9/2;ii++){
			for(jj=0;jj<9;jj++){
			tmp = map[ii*9+jj];
			map[ii*9+jj] = map[(9-1-ii)*9+jj];
			map[(9-1-ii)*9+jj] = tmp;
			}
		
		}
	}
	if(n == 1){
		for(ii=0;ii<9;ii++){
			for(jj=0;jj<9/2;jj++){
			tmp = map[ii*9+jj];
			map[ii*9+jj] = map[ii*9+9-1-jj];
			map[ii*9+9-1-jj] = tmp;
			}
		
		}
	}
	
	
}

void Sudoku::solve(){
	int anss;
	vector <int > digboard(81);
	int ii;
	for(ii=0;ii<81;ii++)
		digboard[ii]=map[ii];

	SolveSudoku Board_Solve(digboard,0);
	anss=Board_Solve.getAns();
	digboard = Board_Solve.get_board();

	for(ii=0;ii<81;ii++)
		ans[ii]=digboard[ii];

	if(anss == 0)
		cout<<'0'<<endl;
	if(anss == 1){
		cout<<'1'<<endl;
		printOut(true);
	}
	if(anss > 1){
		cout<<'2'<<endl;
	}


}


void Sudoku::transform(){
	//readIn();
	change();
	printOut(false);	

}

void Sudoku::change(){
	srand(time(NULL));
	changeNum(rand()%9 +1, rand()%9 +1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3, rand()%3);
	rotate(rand()%4);
	flip(rand()%2);
}

void Sudoku::printOut(bool isAns){
	int m;
	if(!isAns)
		for(m=0;m<81;++m)
			printf("%d%c",map[m] ,(m+1)%9==0?'\n':' ');
	else
		for(m=0;m<81;++m)
			printf("%d%c",ans[m], (m+1)%9==0?'\n':' ');

}

Sudoku::SolveSudoku::SolveSudoku(vector<int> board,int A)
{
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
        {
            in_board[i*SIZE+j] = board[i*SIZE+j];
        }
    //初始化 count, tag, Found變數
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
        {
            count[i*SIZE+j] = 0;
        }
    for (i=0;i<SIZE*SIZE;i++)
        for (j=0;j<SIZE;j++)
        {
            tag[i][j]=0;
        }
    Found = 0;
    setAns(A);
    sol();
}

void Sudoku::SolveSudoku::sol()
{
    int check, Max, iMax;
    /* 一般解法
    Found: 計算已知數字的個數
    count, tag: 掃描直、橫排又九宮格找出空格裡排除的數字
    */
    for (i=0;i<SIZE*SIZE;i++)
    {
        if (in_board[i])
        {
            Found++;
        }
        else
        {
            for (j=0;j<SIZE;j++)
            {
                if (in_board[(i/SIZE)*SIZE+j] && !tag[i][in_board[(i/SIZE)*SIZE+j]-1])
                {
                    count[i]++;
                    tag[i][in_board[(i/SIZE)*SIZE+j]-1] = true;
                }
                if (in_board[j*SIZE+i%SIZE] && !tag[i][in_board[j*SIZE+i%SIZE]-1])
                {
                    count[i]++;
                    tag[i][in_board[j*SIZE+i%SIZE]-1] = true;
                }
                check = in_board[((i/(SIZE*3))*3+j/3)*SIZE + ((i%SIZE)/3)*3+j%3] - 1;
                if (in_board[((i/(SIZE*3))*3+j/3)*SIZE + ((i%SIZE)/3)*3+j%3] && !tag[i][check])
                {
                    count[i]++;
                    tag[i][check] = true;

                }
            }
        }
    }
    /* 將排除數字有8個的空格填入正確的數字&增加Found個數
    並更新其直、橫排、九宮格內之空格的count, tag
    */
    for (i=0;i<SIZE*SIZE;i++)
    {
        if (!in_board[i] && count[i]==8)
        {
            count[i] = 0;
            Found++;
	//	cout<<"found is now "<< Found<< "and Ans = "<<Ans<< endl;////////////////////////////
            for (j=0;j<SIZE;j++)
            {
                if(!tag[i][j])
                {
                    in_board[i] = j+1;
                    for (k=0;k<SIZE;k++)
                    {
                        if (!in_board[(i/SIZE)*SIZE+k] && !tag[(i/SIZE)*SIZE+k][j])
                        {
                            count[(i/SIZE)*SIZE+k]++;
                            tag[(i/SIZE)*SIZE+k][j] = true;
                        }
                        if (!in_board[k*SIZE+i%SIZE] && !tag[k*SIZE+i%SIZE][j])
                        {
                            count[k*SIZE+i%SIZE]++;
                            tag[k*SIZE+i%SIZE][j] = true;
                        }
                        check = ((i/(SIZE*3))*3+k/3)*SIZE + ((i%SIZE)/3)*3+k%3;
                        if (!in_board[check] && !tag[check][j])
                        {
                            count[check]++;
                            tag[check][j] = true;
                        }

                    }
                }
            }
            i = -1; //新填入空格數字就重新開始迴圈
        }

    }
    if (Found == 81) //全部空格數字都找到
    {
        setAns(Ans+1); //數獨解個數加1
	for(i=0;i<81;i++)
		O_board[i]=in_board[i];
	//cout<<"WTF"<<" "<<Found<<endl;
	//system("pause");
    }
    else //一般解法不行，只好用暴力解了XD
    {  //cout<<"WTF AGAIN"<<endl;
        //找出排除數字最多的空格
        Max = 0;
        iMax = -1;
        for (i=0;i<SIZE*SIZE;i++)
        {
            if (count[i] > Max)
            {
                Max = count[i];
                iMax = i;
            }
        }
        //暴力解開始!!
        //從排除數字最多的空格開始猜答案，把每個有可能的解法都跑一次
        for (j=0;j<SIZE;j++)
        {
            if(!tag[iMax][j])
            {
                in_board[iMax] = j+1;
                /*
                建立一個新的解題物件，並把目前數獨解個數代入
                若有新的解，將會更新數獨解(Ans)的個數，in_board則為其解
                若題目有多重解(Ans>1)，in_board只會紀錄下最後一組的數獨解
                */
                SolveSudoku *tmp = new SolveSudoku(get_board(),getAns());
                //刪除此物件，並開始下一個可能解(節省記憶體的用量)
                delete tmp;
            }
        }
    }
}

vector < int > Sudoku::SolveSudoku::get_board() //取得數獨解答
{
    vector <int> out_board(SIZE*SIZE);
    for (i=0;i<SIZE*SIZE;i++)
    {
        out_board[i] = O_board[i];
    }
    return out_board;
}

int Sudoku::SolveSudoku::getAns() //取得數獨解答的個數
{
    return Ans;
}

void Sudoku::SolveSudoku::setAns(int A)//設定數獨解答的個數
{
    Ans = A;
}
