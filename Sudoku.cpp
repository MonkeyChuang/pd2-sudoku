#include "Sudoku.h"
Sudoku::Sudoku()
{
	for(int i=0;i<Sudo_size;i++)
		map[i]=0;
	depth=1;
	max_depth=0;
	flagS=0;
	flagM=0;
}		
void Sudoku::printOut()
{
	for(int i=0;i<Sudo_size;i++)
		cout<<map[i]<<(((i+1)%9!=0)?' ':'\n');
}
void Sudoku::giveQuestion()
{
	int init_Que[Sudo_size]={0,0,2,0,9,0,3,0,0,8,0,5,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,9,0,0,6,0,0,4,0,0,0,0,0,0,0,0,5,8,0,0,0,0,0,0,0,0,1,0,7,0,0,0,0,2,0,0,3,0,0,5,0,0,0,0,0,0,0,0,1,0,0,0,0,0};			
	for(int i=0;i<Sudo_size;i++)
		cout<<init_Que[i]<<(((i+1)%9!=0)?' ':'\n');
}	
void Sudoku::readIn()
{
	for(int i=0;i<Sudo_size;i++)
	{
		cin>>map[i];
		ans[i]=map[i];
	}
	setMaxdepth();
}
void Sudoku::changeRow(int r1,int r2)
{
	for(int n=0;n<3;n++)
	{
		for(int k=0;k<9;k++)
		{
			interChange(&map[9*(3*r1+n)+k],&map[9*(3*r2+n)+k]);
		}
	}
}
void Sudoku::changeCol(int c1,int c2)
{
	for(int n=0;n<3;n++)
	{
		for(int k=0;k<9;k++)
		{
			interChange(&map[9*k+(3*c1+n)],&map[9*k+(3*c2+n)]);
		}
	}
}
void Sudoku::changeNum(int a,int b)
{
	if(a!=b)
	{
		for(int loc=0;loc<Sudo_size;loc++)
		{
			if(map[loc]==a)
				map[loc]=b;
			else if(map[loc]==b)
				map[loc]=a;
		}
	}	
}
void Sudoku::rotate(int rotate_time)
{
	if(rotate_time!=0)
	{
		for(int i=0;i<rotate_time;i++)
		{	
			for(int i=0;i<(Sudo_size-1)/4;i++)
			{
				int loc1,loc2,loc3,loc4,buf2,buf3,buf4;
				loc1=9*(i/5)+i%5;
				loc4=9*(-i%5+8)+i/5;
				loc3=9*(-i/5+8)+8-i%5;
				loc2=9*(i%5)+8-i/5;
				buf2=map[loc2];
				buf3=map[loc3];
				buf4=map[loc4];
				map[loc2]=map[loc1];
				map[loc3]=buf2;
				map[loc4]=buf3;
				map[loc1]=buf4;
			}
		}
	}
}
void Sudoku::flip(int dir)
{
	if(dir==0)
	{
		for(int init_loc=0;init_loc<(Sudo_size-9)/2;init_loc++)
		{
			int fin_loc=9*(8-(init_loc/9))+init_loc%9;
			if(map[init_loc]==0 && map[fin_loc]==0)
				continue;
			else
				interChange(&map[init_loc],&map[fin_loc]);
		}
	}	
	else if(dir==1)
	{
		for(int i=0;i<(Sudo_size-9)/2;i++)
		{
			int init_loc=9*(i/4)+i%4;
			int fin_loc=9*(i/4)+8-(i%4);
			if(map[init_loc]==0 && map[fin_loc]==0)
				continue;
			else
				interChange(&map[init_loc],&map[fin_loc]);
		}
	}							
}
void Sudoku::transform()
{
	readIn();
	srand(time(NULL));
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	changeNum(rand()%9+1,rand()%9+1);
	rotate(rand()%4);
	flip(rand()%2);
	printOut();
}
void Sudoku::solve()
{
	if(!(isCorrect()))
		cout<<"0\n";
	else
	{
		isSol();
		if(flagS==2)			
			cout<<"2\n";
		else if(flagS==1)
		{
			cout<<flagS<<"\n";
			depth=1;
			for(int i=0;i<Sudo_size;i++)
				ans[i]=map[i];
			isSol();
			for(int i=0;i<Sudo_size;i++)
				cout<<ans[i]<<(((i+1)%9!=0)?' ':'\n');
		}		
		else
			cout<<"0\n";
	}
}		
void Sudoku::interChange(int *a,int *b)
{
	int buff;
	buff=*a;
	*a=*b;
	*b=buff;
}				
void Sudoku::setMaxdepth()
{
	for(int i=0;i<Sudo_size;i++)
	{
		if(ans[i]==0)
			max_depth++;
	}
}
int Sudoku::findSquare(int loc)
{
	int n=0;
	while(n<Sudo_size)
	{
		if(map[n]==0)
			loc--;
		if(loc==0)
			break;
		n++;
	}
	return n;
}
bool Sudoku::Validity(int loc,int candi)
{
	for(int col=0;col<9;col++)
	{
		  if(loc!=9*(loc/9)+col && candi==ans[9*(loc/9)+col])
			return false;
	}
	for(int row=0;row<9;row++)
	{
		 if(loc!=9*row+loc%9 && candi==ans[9*row+loc%9])
			return false;
	}
	for(int i=0;i<9;i++)
	{
		 if(loc!=27*((loc/9)/3)+3*((loc%9)/3)+i%3+9*(i/3) && candi==ans[27*((loc/9)/3)+3*((loc%9)/3)+i%3+9*(i/3)])
			return false;
	}
	return true;
}
bool Sudoku::isSol()
{
	if(depth==max_depth+1 && flagS==0)
	{				
/*		if(flagM==1)
		{
			flagS=2;
			return true;
		}
*/		flagS++;
		for(int i=0;i<Sudo_size;i++)
			ans1[i]=ans[i];
		depth--;
		ans[findSquare(depth)]=0;
		return false;
	}
	else if(depth==max_depth+1 && flagS==1)
	{	
		flagS++;
		return true;
	}
	else
	{
		for(int val=1;val<10;val++) 
		{
			if(Validity(findSquare(depth),val))
			{
				ans[findSquare(depth)]=val;
				depth++;
				if(isSol())
					return true;						
			}
		}
		depth--;
		ans[findSquare(depth)]=0;
		return false;
	}
}
bool Sudoku::isCorrect()
{
	for(int i=0;i<Sudo_size;i++)
	{
		if(ans[i]!=0 && !(Validity(i,ans[i])))
			return false;
	}
	return true;			
}	
void Sudoku::preJudge()
{
	int count=0;
	int all_zero=1;
	bool exist[9];
	
	for(int n=0;n<9;n++)					//absence of two kind of numbers(1..9) 
		exist[n]=false;
	for(int i=0;i<Sudo_size;i++)
	{
		if(map[i]!=0)
			exist[map[i]-1]=true;	
	}
	for(int n=0;n<9;n++)
	{
		if(exist[n])
			count++;
	}
	if(count<8)
	{
		flagM=1;	
		return;	
	}
	count=0;
	
	for(int i=0;i<Sudo_size;i++)		//less than 17 clues
	{
		if(map[i]!=0)
			count++;
	}
	if(count<17)
	{
		flagM=1;
		return;
	}	
	count=0;

	for(int i=0;i<Sudo_size;i++)		//two empty rows
	{
		if(i%9==0)
		{
			if(i!=0 && all_zero==1)
				count++;
			else
				all_zero=1;
		}
		if(count==2)
		{
			flagM=1;
			return;
		}	
		if(map[i]!=0)
			all_zero=0;
	}
	count=0;
	
	for(int col=0;col<9;col++)			//two empty columns
	{
		all_zero=1;
		for(int row=0;row<9;row++)
		{
			if(map[9*row+col]!=0)
				all_zero=0;
		}
		if(all_zero==1)
			count++;
		if(count==2)
		{
			flagM=1;
			return;
		}
	}
	count=0;
			
	for(int box=0;box<9;box++)			//two empty 3x3 boxes 
	{
		all_zero=1;
		for(int i=0;i<9;i++)
		{
			if(map[27*(box/3)+3*(box%3)+9*(i/3)+i%3]!=0)
				all_zero=0;
		}
		if(all_zero==1)
			count++;
		if(count==2)
		{
			flagM=1;
			return;
		}
	}
					
}