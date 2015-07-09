#include <iostream> 

using namespace std; 

int factorial(int x); 

int main(){

	char ans; 
	do{

	int x; 
	cout << "This is a factorial program. \nPlease enter a number you wish to find the factorial of." <<endl; 
	cin >> x; 
	
	cout << "The factorial of the number " << x << " is: " << factorial(x) << endl; 

	cout << "Would you like to try this again? [Y/N]"; 
	cin >> ans; 

	}while (ans == 'y' || ans == 'Y'); 
system("Pause"); 
return 0; 
}

int factorial(int x){
	int i = 0, result = 1;
	while(x != i){
		result = result * (x - i); 
		i++; 
	}
	return result; 
}