//This is program consist of a recursive function that finds the smallest number in the jump it game. 

#include <iostream> 
#include <iomanip> 
#include <time.h> 

using namespace std; 

void fill(int a[], int size); 
int jump(int a[], int current, int end); 
int main(){
	
	srand(time(0)); 
	cout << "Input the number of positive integers on the board: "; 
	int num; 
	cin >> num; 
	int *board = new int[num]; 
	fill(board, num); 
	for(int i = 0; i < num; i++){
		cout << board[i] << " "; 
	}
	cout << endl; 
	int smallest = jump(board, 0, num - 1); 
	cout << "The smallest number is " << smallest << endl; 
	cout << endl; 
	system("Pause"); 
	return 0; 
}

void fill(int a[], int size){
	a[0] = 0; 
	for(int i = 1; i < size; i++){
		a[i] = rand()%100 + 1; 
	}
}

int jump(int a[], int current, int end){//end is the last index of the array 
	if(current == end){
	//	cout << "Jump to " << a[end] << endl; 
		return a[end]; 
	}
	else{
		if(current + 1 == end){
			return a[current] + jump(a, current + 1, end); 
		}
		else if(current + 2 == end){
		//	cout << "Jump to " << a[end] << endl; 
			return a[current] + a[end]; 
		}
		else{
			if(jump(a, current + 1, end) > jump(a, current + 2, end)){
		//		cout << "Jump to " << a[current + 2] << endl; 
				return a[current] + jump(a, current + 2, end); 

			}
			else{ 
		//		cout << "Jump to " << a[current + 1] << endl; 
				return a[current] + jump(a, current + 1, end); 
			}

		}
	}
}