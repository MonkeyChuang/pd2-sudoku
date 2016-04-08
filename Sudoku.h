#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Sudoku
{
	public:
		Sudoku();
		void printOut();
		void giveQuestion();
		void readIn();
		void changeRow(int r1,int r2);
		void changeCol(int c1,int c2);
		void changeNum(int a,int b);
		void rotate(int rotate_time);
		void flip(int dir);
		void transform();
		void solve();

	private:
		static const int Sudo_size=81;
		int map[Sudo_size];
		int flagS,flagM;						//S: number of solution ; M:multiple solution
		int ans[Sudo_size];
		int ans1[Sudo_size];
		int depth;
		int max_depth;

		void interChange(int *a,int *b);
		void setMaxdepth();
		int findSquare(int loc);
		bool Validity(int loc,int candi);
		bool isSol();
		bool isCorrect();
		void preJudge();
};
