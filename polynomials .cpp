//Polynomials: In this program, user enters polynomials. The program process each character in the string that the user inputs and stores them in nodes. 
//Day 2 of work: Got it successfully copy the users input and display them on screen. Got it successfully to calculate equations based on user's input of variable x 
//Day 3: It took awhile, but I finally got add_like function to work 
//12/8/2014: finally got it done and working properly 
//description of how it works: When the user inputs a polynomial, a list is created to store each nomial into a node. Each node stores separate information for coefficient, exponent, whether it's negative or positive and 

#include <iostream> 
#include <string> 
#include <vector> 
#include <cmath> 

using namespace std; 

void pause(){
	system("Pause"); 
}

int bigger(int first, int second){
	if(first > second){
		return first; 
	}
	else
		return second; 
}

class Node{
public: 
	Node(); 
	Node(string w);
	Node(string w, bool pos, bool ex, int coefficient, int exp); 
	Node(Node& copy); 
	~Node(); 
	void sign(bool isPos){positive = isPos;}; 
	void reverse();//reverse the string  
	void assign();//assign values to positive, coeff and expo  
	string get_word() {return word;}; 
	Node* get_prev() {return prev;};
	int get_expo(){return expo;}; 

private: 
	Node* next; 
	Node* prev; 
	string word;
	bool positive; 
	bool x_true; //determines if the nomial contains variable x 
	int coeff;//value of coefficient  
	int expo;//value of exponent  
friend class List; 
friend ostream& operator<<(ostream& out, const List& right); 
};

Node::Node() : next(NULL), prev(NULL), positive(true), expo(0){
	word = ""; 
}

Node::Node(string w) : next(NULL), prev(NULL), positive(true), expo(0){
	word = w; 
}

Node::Node(Node& copy){//beware that pointers List::start and List::end will not point to copied Node on default 
	word = copy.word; 
	positive = copy.positive; 
	coeff = copy.coeff; 
	expo = copy.expo; 
	prev = NULL; 
	next = NULL; 
}

Node::Node(string w, bool pos, bool ex, int coefficient, int exp): word(w), positive(pos), x_true(ex), coeff(coefficient), expo(exp){
	prev = NULL; 
	next = NULL; 
}

Node::~Node(){
//	delete [] next; 
//	delete [] prev;
}

class List{
public: 
	List(); 
	List(List& copy); 
	void push_back(string word); 
	void initiate(); 
	void process();//reverses the characters in each node 
	void reverse(); 
	int calculate(); 
	void order(); //rearranges the nomials so that the exponents are in decrease order
	void add_like(); //add nomials that have the same power
	void check_zero(); //check for nodes with zero coefficients; 
	List& operator+(const List& right); 
	List& operator-(const List& right); 
	List& operator*(const List& right); 
	void new_node(string w, bool pos, bool ex, int coefficient, int exp); //similar to push_back, but creates nodes with full set of data 
//	List& operator=(const List& right); 
private: 
	Node *start, *end;

friend ostream& operator<<(ostream& out, const List& right); 
friend void initiate(List& nomial); 
}; 

List::List() : start(NULL), end(NULL){

}

void List::push_back(string word){
	Node* temp; 
	if(start == NULL && end == NULL){
		temp = new Node(word); 
		start = temp; 
		end = temp; 
	}
	else{
		temp = new Node(word); 
		temp->prev = end; 
		end->next = temp; 
		end = temp; 
	}
}
void initiate(List& currentList); 
void enter(); 

int main()
{ 
	List equation1, equation2, result; 
	initiate(equation1); 
	enter(); 
	initiate(equation2); 
	result = equation1 * equation2; 
	cout << "result = " << result << endl;
	cout << "Solution to result is = " << result.calculate() << endl; 

	system("Pause"); 
	return 0; 
}

//push_back works fine 
void List::initiate(){
	string word; 
	List nomial; 
	Node* temp; 
	cout << "Please enter a polynomial: "; 
	getline(cin, word);
	string c, sum = ""; //sum will accumulate each character of the nomial before c come accross a space or an arithmetic sign  
	for(int i = word.length() - 1; i >= 0; i--){//the whole sentence will be read backwards
		c = word.substr(i, 1); 
		if(c == "-" || c == " " || c == "+"){//if c is holding a space value, do nothing 
			if(c == "+" || c == "-"){//only form a new node if c holds a - or + sign 
				nomial.push_back(sum); 
				if(c == "-") {//okay 
					temp = nomial.end; 
					temp->sign(false); 
				}
				else if(c== "+"){//okay 
					temp = nomial.end; 
					temp->sign(true); 
				}
				sum = ""; //resets sum 
			}
		}
		else if (isalnum(c[0]) && i !=0){//okay
			sum += c; 	
		}
		/*
		else if (c[0] == '^' && i != 0){
			sum+= c; 
		}*/
		else if(isalnum(c[0]) && i == 0){//if first character of string is alpha or numeric, then form a node. 
			sum += c;
			nomial.push_back(sum); 
		}
	}
	nomial.process(); 
	enter(); 
	cout << nomial; 
	enter(); 
	*this = nomial; 
}

void initiate(List& nomial){
	string word; 
	Node* temp; 
	cout << "Please enter a polynomial: "; 
	getline(cin, word);
	string c, sum = ""; //sum will accumulate each character of the nomial before c come accross a space or an arithmetic sign  
	for(int i = word.length() - 1; i >= 0; i--){//the whole sentence will be read backwards
		c = word.substr(i, 1); 
		if(c == "-" || c == " " || c == "+"){//if c is holding a space value, do nothing 
			if(c == "+" || c == "-"){//only form a new node if c holds a - or + sign 
				nomial.push_back(sum); 
				if(c == "-") {//okay 
					temp = nomial.end; 
					temp->sign(false); 
				}
				else if(c== "+"){//okay 
					temp = nomial.end; 
					temp->sign(true); 
				}
				sum = ""; //resets sum 
			}
		}
		else if (isalnum(c[0]) && i !=0){//okay
			sum += c; 	
		}
		/*
		else if (c[0] == '^' && i != 0){
			sum+= c; 
		}*/
		else if(isalnum(c[0]) && i == 0){//if first character of string is alpha or numeric, then form a node. 
			sum += c;
			nomial.push_back(sum); 
		}
	}
	nomial.process(); 
	enter(); 
	cout << nomial; 
	enter(); 
}

void List::process(){
	Node* temp; 
	List tempList; 
	temp = end; 
	while(temp != NULL){
		temp->reverse(); 
//		cout << temp->get_word() << " "; 
//		enter(); 
		temp->assign(); 
		temp = temp->prev; 
	}
	reverse(); 
	add_like(); 
//	order(); 
	check_zero(); 
}

void Node::assign(){//does not work with inputs such as 23x^2, that's because the symbol ^ is not recorded 
	string c; 
	bool constant = true; //checks if nomial is a constant
	int pos_x; //position of exponent; 
	for(int i = 0; i < word.length(); i++){
		if(word.substr(i, 1) == "x"){
			constant = false; 
//			cout << "This is not a constant. Pos_x = " << i << endl; 
			pos_x = i; 
		}
	}

	if(constant){//if nomial is just a constant 
		c = word; 
		x_true = false;//nomial does not carry variable x  
		coeff = stoi(c); 
		expo = 0; 
	}

	else{//if nomial has an exponent
		x_true = true;//nomial does carry variable x  
		if(pos_x == 0){
			coeff = 1; 
		}
		else{
			string Cof = word.substr(0, pos_x);  
			coeff = stoi(Cof); 
		}
		if(pos_x != word.length()-1){//records the exponent and converts it from string to integer 
			string exponent = word.substr(pos_x + 1); 
			expo = stoi(exponent); 
			}
		else{
			expo = 1; 
			}
		}
}

void List::check_zero(){

	Node* temp, *temp2, *del; 
	temp = start; 
	bool move; 
	while(temp != NULL){
		move = true; 
		if(temp->coeff == 0 || temp->coeff == NULL){
			if(temp == start && temp != end){
				start = start->next; 
				del = temp; 
				temp = temp->next; 
				delete del; 
				temp->prev = NULL; 
				move = false; 
			}
			else if(temp == end && temp != start){
				end = end->prev; 
				del = temp; 
				temp = temp->prev; 
				delete del; 
				temp->next = NULL; 
				move = true; 
			}
			else if(temp == end && temp == start){
				delete temp; 
				temp = NULL; 
				move = false; 
			}
			else{
				temp2= temp; 
				del = temp; 
				temp = temp->prev;
				temp2 = temp2->next; 
				delete del; 
				temp->next = temp2; 
				temp2->prev = temp; 
				move = true; 
			}
		}
		if(move){
		temp = temp->next; 
		}
	}
	
}

void Node::reverse(){//works 
	string temp = ""; 
	int size = word.length() - 1; 
	for(int i = size; i >= 0; i--){
		temp += word.substr(i,1); 
	}
	word = temp; 

//	cout << word << endl; 
//	cout << "Length: " << word.length() << endl; 

}
/*
List& List::operator=(const List& right){//under construction 
	Node* temp, *del, *del2; 
	List tempList; 
	temp = right.start; 
	if(start!= NULL && end != NULL){//purpose is to make sure function starts with empty list 
		del = start; 
		start = NULL; 
		while(del != NULL){
			del2 = del; 
			del = del->next; 
			delete del2; //might run into some problems 
			del->prev = NULL; 
		}
	}

	while(temp!=NULL){
		tempList.new_node(temp->word, temp->positive, temp->x_true, temp->coeff, temp->expo); 
		temp = temp->next; 
	}
	return tempList; 
}
*/
ostream& operator<<(ostream& out, const List& right){
	Node* temp; 
	temp = right.start; 
	while (temp != NULL){
		if(!temp->positive){
			out << "-";  
			if(temp->prev != NULL){
				out << " "; 
			}
		}
		else if (temp->prev != NULL){
			out << "+ "; 
		}
		if(temp->coeff != 0 && temp->coeff != 1){
			out << temp->coeff; 
		}
		else if(temp->coeff == 1 && temp->x_true){
			out << ""; 
		}
		else if(!temp->x_true && temp->coeff == 1){
			out << "1"; 
		}
		if(temp->x_true){
			out << "x"; 
		}
		if(temp->expo > 1){
			out << "^" << temp->expo; 
		}
		out << " "; 
		temp = temp->next; 
	}
	return out; 
}

void enter(){
	cout << endl; 
}

void List::reverse(){
	Node *temp, *newNode, *del; 
	List tempList; 
	temp = end; 
	while(temp != NULL){
		if(tempList.start == NULL && tempList.end == NULL){
//Node(string w, bool pos, bool ex, int coefficient, int exp)
			newNode = new Node(temp->word, temp->positive, temp->x_true, temp->coeff, temp->expo); 	
			tempList.start = newNode; 
			tempList.end = newNode; 
		}
		else{
			newNode = new Node(temp->word, temp->positive, temp->x_true, temp->coeff, temp->expo); 				
			newNode->prev = tempList.end; 
			tempList.end->next = newNode; 
			tempList.end = newNode; 
		}
		temp = temp->prev; 
	}
	start = tempList.start; 
	end = tempList.end; 
}

int List::calculate(){
	int var; 
	cout << "Input the value of x: ";
	cin >> var; 
	int result = 0; 
	Node* temp; 
	temp = start; 
	while(temp != NULL){
/*
	bool positive; 
	bool x_true; //determines if the nomial contains variable x 
	int coeff;//value of coefficient  
	int expo;//value of exponent  
*/
		int coefficient = temp->coeff; 
		int exponent = temp->expo; 
		if(!temp->positive){
			coefficient *= -1; 
		}
		if(temp->x_true){
			result += (coefficient * std::pow(var*1.0, temp->expo));  
		}
		else{
			result += (coefficient); 
		}
		temp = temp->next; 
	}

	return result; 

}

List& List::operator+(const List& right){
	Node* temp, *temp_right; 
	temp = end;
	temp_right = right.start; 
	temp->next = temp_right; 
	temp_right->prev  = temp;
	end = right.end; 
	temp = start; 
	add_like(); 

	return *this; 

}
 
List& List::operator-(const List& right){
	Node* temp, *temp_right; 
	temp_right = right.start; 
	while(temp_right != NULL){
		if(temp_right->positive == false){
			temp_right->positive = true; 
		}
		else{
			temp_right->positive = false; 
		}
		temp_right = temp_right->next; 
	}
	temp = end; 
	temp_right = right.start; 
	temp->next = temp_right; 
	temp_right->prev = temp; 
	end = right.end; 
	add_like(); 
	check_zero(); 
	return *this; 
}

void List::add_like(){
	Node* first, * temp, *temp2; 
	Node* second; 
	first=start; 
	int count = 0;
	while(first!=NULL){
		second = first; 		
		second = second->next; 
		while(second != NULL){
			if(first->get_expo() == second->get_expo()){
				if(!first->positive){
					first->coeff *= -1; 
					first->positive = false; 
				}
				if(!second->positive){
					second->coeff *= -1; 
					second->positive = false; 
				}
				first->coeff += second->coeff; 
				if(first->coeff < 0){
					first->positive = false;
					first->coeff *= -1;//this is necessary because add_like is the only function that knows how to deal with multiplying a negative number with a positive number
				}
				else{
					first->positive = true; 
				}
				if(second == end){
					end = end->prev; 
					delete second;
					second = end; 
					end->next = NULL; //I had a lot of trouble getting add_like function to work without this line. 
				}

				else{
					temp = second; 
					temp2 = second; 
					second = second->prev; 
					temp2=temp2->next; 
					temp2->prev = second; 
					second->next = temp2; 
					delete temp; 
				}
			}
			second = second->next;
		}
		first = first->next; 
	}
}

void List::new_node(string w, bool pos, bool ex, int coefficient, int exp){
	Node *newNode;  
	if(start == NULL && end == NULL){
		newNode = new Node(w, pos, ex, coefficient, exp); 	
		start = newNode; 
		end = newNode; 
		}
	else{
		newNode = new Node(w, pos, ex, coefficient, exp); 				
		newNode->prev = end; 
		end->next = newNode; 
		end = newNode; 
		}
}

void List::order(){//work in progress
	Node* temp, *temp2, *temp3, *temp_prev, *temp_next, *temp1_prev; 
	temp = start;  
	while(temp != NULL){
		temp2 = temp->next; 
		int biggest = temp->expo;  
		while(temp2 != NULL){
			biggest = bigger(biggest, temp2->expo); 
			temp2 = temp2->next; 
		}
		//after going through one loop; 
		temp3 = temp; 
		bool found = false;
		while(temp3 != NULL && temp->expo!= biggest && !found){
			if(temp3->expo == biggest){
				if (temp3 == end){
					end = end->prev; 
					temp3->prev = NULL; 
					temp3->next = temp; 
					temp->prev = temp3;
					end->next = NULL; 
					found = true; 
				}
				else{//for some reason if input is 5 + 4x^2, end does not point to 4x^2 nomial
					temp_prev = temp3->prev; 
					temp_next = temp3->next; 
					temp_prev->next = temp_next; 
					temp_next->prev = temp_prev; 
					if(temp == start){
						temp3->prev = NULL; 
						temp3->next = temp; 
						start = temp3; 
					}
					else{
						temp1_prev = temp->prev; 
						temp1_prev->next = temp3; 
						temp3->prev = temp1_prev; 
						temp3->next = temp; 
						temp->prev = temp3; 
					}
				}
			}
			temp3 = temp3->next; 
		}
		if(temp->expo == biggest){
			temp = temp->next; 
		}
		else{}
	}
}

List& List::operator*(const List& right){
	List result; 
	Node* temp, *temp2; 
	temp = start; 
	int co, po; 
	bool pos, expo_true;
	while(temp != NULL){
		temp2 = right.start; 
		while(temp2 != NULL){
			co = temp->coeff * temp2->coeff; 
			po = temp->expo + temp2->expo; 
			
			if(temp->x_true || temp2->x_true){
				expo_true = true; 
			}
			else{
				expo_true = false; 
			}

			if(!temp->positive && temp2->positive){
				pos = false; 
			}
			else if(temp->positive && !temp2->positive){
				pos = false; 
			}
			else if((temp->positive && temp2->positive) || (!temp->positive && !temp2->positive)){
				pos = true; 
			}

			//(string w, bool pos, bool ex, int coefficient, int exp)
			result.new_node("mult", pos, expo_true, co, po);
			temp2 = temp2->next; 
		}
		temp = temp->next; 
	}
	result.add_like(); 
	return result; 
}
