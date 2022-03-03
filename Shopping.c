#include<iostream>
using namespace std;

//a 3x3 grid 
char grid[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};

void printGrid(){
	cout<<endl<<" "<<grid[0][0]<<"| "<<grid[0][1]<<"| "<<grid[0][2];
	cout<<endl<<"---------";
	cout<<endl<<" "<<grid[1][0]<<"| "<<grid[1][1]<<"| "<<grid[1][2];
	cout<<endl<<"---------";
	cout<<endl<<" "<<grid[2][0]<<"| "<<grid[2][1]<<"| "<<grid[2][2];
}

char chooseTurn(int count){
	return (count%2==0)?'O':'X';
}

bool isCellNumberInvalid(int cellNumber){
	return cellNumber<1 || cellNumber>9;
}

bool isCellOccupied(int row,int column){
	return grid[row][column]=='X' || grid[row][column]=='O';
}

void insertTurn(int row,int column,char turn){
	grid[row][column]=turn;
}

bool isWinner(char turn){
	return	//horizontal comparison
			 (grid[0][0]==turn && grid[0][1]==turn && grid[0][2]==turn)
			|| (grid[1][0]==turn && grid[1][1]==turn && grid[1][2]==turn)
			|| (grid[2][0]==turn && grid[2][1]==turn && grid[2][2]==turn)
			
			//vertical comparsion
			|| (grid[0][0]==turn && grid[1][0]==turn && grid[2][0]==turn)
			|| (grid[0][1]==turn && grid[1][1]==turn && grid[2][1]==turn)
			|| (grid[0][2]==turn && grid[1][2]==turn && grid[2][2]==turn)
			
			//diagonal comparison
			|| (grid[0][0]==turn && grid[1][1]==turn && grid[2][2]==turn)
			|| (grid[0][2]==turn && grid[1][1]==turn && grid[2][0]==turn);
}

bool isDraw(int count){
	return count>9;
}

int main(){
	int count=1;

	cout<<endl<<"---3x3 Tic-Tac-Toe---";
	
	while(1){
		char turn=chooseTurn(count);
		cout<<endl<<"Turn:"<<turn;
		
		//print the grid
		printGrid();
		
		//read a cell number from the player
		int cellNumber;
		get_cell_number:
			cout<<endl<<"Enter a cell number(1-9):";
			cin>>cellNumber;
		
		if(isCellNumberInvalid(cellNumber)){
			cout<<endl<<"Invalid input!";
			goto get_cell_number;
		}

		//set row and column as per cell number
		int row,column;
		switch(cellNumber){
			case 1:row=0,column=0;break;
			case 2:row=0,column=1;break;
			case 3:row=0,column=2;break;	
			case 4:row=1,column=0;break;
			case 5:row=1,column=1;break;
			case 6:row=1,column=2;break;
			case 7:row=2,column=0;break;
			case 8:row=2,column=1;break;
			case 9:row=2,column=2;break;
		}

		if(isCellOccupied(row,column)){
			cout<<endl<<"Cell is occupied!";
			goto get_cell_number;
		}

		insertTurn(row,column,turn);
		count++;

		if(isWinner(turn)){
			cout<<endl<<"Winner is "<<turn<<"!";
			printGrid();
			break;
		}

		if(isDraw(count)){
			cout<<endl<<"Game is draw!";
			printGrid();
			break;
		}
	}
	return 0;
} 
