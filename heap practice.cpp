//This program builds a heap tree. The difference with a heap and binary tree is that a heap tree seeks to fill all the bottom nodes first. The heap will look like a balanced tree more often than a binary tree. 
//Filling out the heap tree requires seeing if the branches of the top node are balanced or not and requires the use of recursion 
//The heap mainly stores numbers. 
//Building this program requires using visual models. I had to cut out the numbers of the heap in pieces of paper and arrange them to see how arranging the nodes around the heap would look like. 
//finally commpleted on 2/6/15, this was quite a challenge. I didn't even have the answers from the book. I had to figure this out all by myself. 
#include <iostream> 
#include <cmath> 

using namespace std; 

int totalnumnodes (int h, int n); 

class Node {
public: 
	Node(int n); 
	Node(); 
	void setLevel(int n); 
	void newNode(Node* cur); //uses binary tree method; 
	void print(Node * cur); //prints out the numbers of each individual nodes 
	void h_print(Node* cur, int lay);//With the help of Heap member function topToBottom, it prints out the heap from top to bottom. 
	void printLayer(Node* cur, int lay); 
	void fill(Node* n, int num, int lay); //recursive function that fills up the node; variable lay is the number of layers; variable num is to be inserted into the heap 
	int count();//counts how many children and grandchildren the node has including itself 
	void findRemove(Node* cur, int n, int subs);//finds and removes node with designated number; subs variable holds the last number of the heap to be added 
	void remove(Node* cur, int subs); //works with findRemove function to remove a node 
	void findChildren(Node* cur);
	int rearrange(Node* cur); //rearranges the heap so that numbers range from big to small, from top to bottom
	bool checkOrder(Node* cur); //checks the order of the numbers of the help 
private: 
	Node* left; 
	Node* right; 
	int num; 
	int layer; 
friend class Heap; 
friend bool isBalanced(Node* N); 
}; 

Node::Node() : num(0), layer(0){
	left = NULL; 
	right = NULL; 

}

Node::Node(int n) : num(n){
	left = NULL; 
	right = NULL; 
}

void Node::setLevel(int n){
	layer = n; 
}

void Node::newNode(Node* cur){
	Node* temp = this; 
	if(temp ==	NULL){
		temp = cur; 
	}
	else{
		if(cur->num > num){
			if(right != NULL)
				right->newNode(cur);  
			else
				right = cur; 
		}
		else{
			if(left != NULL)
				left->newNode(cur); 
			else
				left = cur; 
		}
	}

}

//it took me a day to figure this function out; it took me four pages of notes just to get this working 
//I figured that the way code the program to figure out which branch or node to insert the new number into is code to figure out if the branches of each node is "balanced" or not
//As a recursive function, it can look at each individual node or "fork" of the diverging branches and find out if any of the branches or balanced or not. 
//That is a way for the function to know where to insert the new number into. 
//Originally, I thought about more complicated solutions such as designating each node of the heap with a number that locates it but the "balance" method is more effective. 
void Node::fill(Node* n, int num, int lay){
	if(n == NULL){
		//cout << num << " gets a new node.";  
		n = new Node(num); 
		n->layer++; 
	}
	else{
		if(n->num < num){//compares current num to num; if the num to be inserted into the heap is bigger than the number of current node, it switches the cur->num place. 
			int temp = n->num; 
			n->num = num; 
			num = temp; 
		//	cout << temp << " is replaced by " << n->num << ". Current layer is " << lay << endl; 
		}

		if(isBalanced(n->left) && isBalanced(n->right) && isBalanced(n)){//if whole tree is balanced 
			if(n->left != NULL){
			//	cout << num << " goes left 1." << ". It's in layer " << n->layer + 1 << endl; 
				fill(n->left, num, n->left->layer); 	
			}
			else{
			//	cout << num << " goes left 2." << ". It's in layer " << n->layer + 1<< endl; 
				n->left = new Node(num);//these series of lines creating new nodes is necessary. Before I tried just writing the line fill(n->left, num), but if n->left == NULL, the code doesn't work. It doesn't like the idea of fill(NULL, num) 
				n->left->layer = lay + 1; 
			}
		}
		else if(isBalanced(n->left) && isBalanced(n->right) && !isBalanced(n)){//if whole tree is not balanced but left and right are. 
			if(n->right != NULL){	
			//	cout << num << " goes right 1R." << ". It's in layer " << n->right->layer << endl; 
				fill(n->right, num, n->right->layer); 
			}
			else {
			//	cout << num << " goes right 2R." << ". It's in layer " << lay + 1 << endl; 
				n->right = new Node(num); 
				n->right->layer = lay + 1; 
			}
		}
		else if(!isBalanced(n->left) && isBalanced(n->right)){//if left branch of current node is not balanced 
			if(n->left != NULL)	{
			//	cout << num << " goes left 3." << ". It's in layer " << n->layer + 1 << endl; 
				fill(n->left, num, n->left->layer); 
			}
			else{
			//	cout << num << " goes left 4." << ". It's in layer " << n->layer + 1 << endl; 
				n->left = new Node(num);
				n->left->layer = lay + 1; 
			}
		}
		else if(isBalanced(n->left) && !isBalanced(n->right)){//revised 
			if(n->left != NULL)	
			{
			//	cout << num << " goes right 5 3R." << ". It's in layer " << n->right->layer << endl; 
				fill(n->right, num, n->right->layer); 
			}
			else{ 
			//	cout << num << " goes left and gets a new home." << ". It's in layer " << n->layer + 1 << endl; 
				n->left = new Node(num); 
				n->left->layer = lay + 1; 
			}
		}
	}
}

int Node::count(){
	Node* temp = this; 
	if(temp == NULL)
		return 0; 
	else if(temp->left == NULL && temp->right == NULL){
		return 1; 
	}
	else if(temp->left != NULL && temp != NULL) 
		return 1 + temp->left->count() + temp->right->count(); 
	else if(temp->left != NULL && temp->right == NULL){//return 2 because in a heap, there aren't any nodes with one children and grandchildren at the same time. 
		return 2; 
	}
}

void Node::h_print(Node* cur, int lay){
	if(cur == NULL){
		return; 
	}
	else{
		for(int i = 1; i <= lay; i++){//prints all the layers one by one 
			printLayer(cur, i); 
		}
	}
}

void Node::printLayer(Node* cur, int lay){//prints numbers from a layer designated by variable lay. 
	if(cur == NULL){
		return; 
	}
	else{
		/*
		cout << "Number: " << cur->num << endl; 
		cout << "layer: " << cur->layer << endl;
		cout << "Compared layer: " << lay << endl;
		cout << endl; 
		*/
		if(lay == cur->layer){
			cout << cur->num << endl; 
		}
		printLayer(cur->left, lay); 
		printLayer(cur->right, lay); 
	}
}

class Heap{
public: 
	Heap(); 
	Heap(int num); 
	int defineLevel(); 
	void insertNode(int n);
	int count(Node* n); 
	void b_insert(int n); //binary insert method, creates a binary tree 
	void traverse(); 
	bool isHeapBal(); 
	void h_insert(int n); 
	int findLevel();//finds the number of layers the heap is made up of 
	int heapCount();//returns number of nodes; 
	void topToBottom(); 
	void removeFromHeap(int n); 
	void findChild(); 
	int popHeap(); //removes and return last number from heap 
	void rearrangeHeap(); 
private: 
	Node* top; 
	int total_nodes; //total number of nodes in the heap 
	int num_Levels;// total number of levels in a heap 

};

void Node::print(Node* cur){
	if(cur == NULL){
		return; 
	}
	print(cur->left); 
	cout << cur->num << endl; 
	print(cur->right); 
}

void Node::findRemove(Node* cur, int n, int subs){//function needs to remember the parent of each node 
	if(cur->left == NULL && cur->right == NULL && cur->num != n){
		cout << "Number is not found." << endl; 
		return; 
	}
	else if(cur->num == n){//condition is true if n is found in top node 
		remove(cur, subs); 
	}
	else if(cur->left->num == n){
//		cout << "Number is found!" << endl; 
		remove(cur->left,  subs); 
	}
	else if(cur->right != NULL && cur->right->num == n){//cur->right != NULL may seem redundant but it is necessary 
//		cout << "Number is found!" << endl; 
		remove(cur->right, subs); 
	}
	else{
		if(cur->left != NULL && cur->right != NULL){
			findRemove(cur->left, n, subs); 
			findRemove(cur->right, n, subs); 
		}
		else if(cur->left != NULL && cur->right == NULL){
			findRemove(cur->left, n, subs); 
		}
		else if(cur->left == NULL && cur->right == NULL){
			return; 
		}
	}
}

void Node::remove(Node* cur, int subs){//it doesn't remove nodes at the bottom yet; needs more work put into it. 
	if(cur->left == NULL && cur->right == NULL){ 
		cur->num = subs;  
	}
	else if(cur->left != NULL &&  cur->right == NULL){
			cur->num = subs; //correct
		}
	else{
		Node* temp = cur->left; 
		int move; //records number to be moved
		if(isBalanced(cur)){//correct
			if(cur->right->left == NULL && cur->right->right == NULL){
				cur->num = cur->right->num; 
				cur->right->num = subs; 
			}
			else{//correct
				cur->num = cur->right->num; 
				remove(cur->right, subs); 
			}
		}
		
		else if(isBalanced(cur->left) && !isBalanced(cur->right) && !isBalanced(cur)){
			if(cur->right == NULL){
				cur->num = subs; 
			}
			else{//correct 
				cur->num = cur->right->num; 
				remove(cur->right, subs);// I need to put more thought into this line. 
			}
		}
		else if(!isBalanced(cur) && isBalanced(cur->left) && isBalanced(cur->right)){//correct 
				cur->num = cur->right->num; 
				remove(cur->right,subs); 
		}
		else if(!isBalanced(cur->left) && isBalanced(cur->right)){//correct 
			cur->num= cur->right->num; 
			remove(cur->right, subs); 
		}
	}
}

void Node::findChildren(Node* cur){
	if(cur == NULL)
		return; 
	else{
		cout << "Current node number is " << cur->num << endl; 
		if(cur->left != NULL && cur->right != NULL){
			cout << "The left child is " << cur->left->num << endl; 
			cout << "The right child is " << cur->right->num; 
			cout << endl << endl; 
			findChildren(cur->left); 
			findChildren(cur->right); 
		}
		else if(cur->left != NULL && cur->right == NULL){
			cout << "The left child is " << cur->left->num; 
			cout << "There is no right child." << endl; 
			cout << endl; 
			findChildren(cur->left); 
		}
		else if(cur->left == NULL && cur->right == NULL){
			cout << "This node doesn't have any children." << endl << endl; 
		}

	}
}

int Node::rearrange(Node* cur){
	if(cur->left == NULL && cur->right == NULL)//if recursive function encounters a node without children, return it's number 
		return cur->num; 
	else if(cur->left != NULL && cur->right == NULL){
		if(cur->num < cur->left->num){
			int temp2 = cur->num; 
			cur->num = cur->left->num; 
			cur->left->num = temp2; 
			return cur->num; 
		}
		else 
			return cur->num; 
	}
	else{
		int temp; 
		int le = rearrange(cur->left); 
		int ri = rearrange(cur->right); 
		//cout << "Le = " << le << endl; 
		//cout << "Ri = " << ri << endl; 
		if(le > ri){
		//	cout << "1.) left: " << cur->left->num << " > " << "right: " << cur->right->num << endl; 
			if(cur->num < cur->left->num){
		//		cout << "2.) cur: " << cur->num << " < " << "left: " << cur->left->num << endl; 
				temp = cur->left->num;
				cur->left->num = cur->num; 
				cur->num = temp; 
				return cur->num; 
			}
			else{
		//		cout << "3.) cur: " << cur->num << " >= " << "left: " << cur->left->num << endl;  
				return cur->num; 
			}

		}
		else{
			if(cur->right == NULL){
			//	cout << "right = " << 0 << endl; 
			//	cout << "cur = " << cur->num << endl;
				return cur->num; 
			}
			else{
			//	cout << "4.) left: " << cur->left->num << " < " << "right: " << cur->right->num << endl; 
				temp = cur->num; 
				if(cur->num < cur->right->num){
			//		cout << "5.) cur: " << cur->num << " < " << "right: " << cur->right->num << endl; 
					cur->num = cur->right->num; 
					cur->right->num = temp; 
					return cur->num; 
				}
				else{
			//		cout << "6.) cur: " << cur->num << " >= " << "right: " << cur->right->num << endl; 
					return cur->num; 
				}
			}
		}
	}
}

bool Node::checkOrder(Node* cur){
	if(cur->left == NULL && cur->right == NULL){
		return true; 
	}
	else if(cur->left != NULL && cur->right == NULL){
		if(cur->num >= cur->left->num){
			return (true && checkOrder(cur->left)); 
		}
		else
			return false; 
	}
	else if(cur->left == NULL && cur->right != NULL){
		if(cur->num >= cur->right->num){
			return (true && checkOrder(cur->right)); 
		}
		else
			return false; 
	}
	else{
		if((cur->num >= cur->left->num) && (cur->num >= cur->right->num)){
			return (true && checkOrder(cur->left) && checkOrder(cur->right)); 
		}
		else 
			return false; 
	}
}

Heap::Heap(){
	top = NULL; 
}

Heap::Heap(int num){
	top = new Node(num); 
	top->setLevel(1); 
}

int Heap::count(Node* n){
	if(n->left == NULL && n->right == NULL){
		return 1; 
	}
	else if(n->left != NULL && n->right == NULL){
		return 1 + count(n->left); 
	}
	else if(n->left == NULL && n->right != NULL){
		return 1 + count(n->right); 
	}
	else{
		return 1 + count(n->right) + count(n->left); 
	}
}

bool isBalanced(Node* N){
	if(N == NULL){
		return true; 
	}
	else if(N->left != NULL && N->right != NULL){
		if(N->left->count() == N->right->count())
			return true; 
		else
			return false;
		// return (isBalanced(N->left) && isBalanced(N->right)); 
	}
	else if(N->left == NULL && N->right == NULL){
		return true; 
	}
	else
		return false; 
}

bool Heap::isHeapBal(){
	if(top == NULL)
		return true; 
	else
		return isBalanced(top); 
}

void Heap::b_insert(int n){
	Node* temp = new Node(n);  
	if(top == NULL){
		top = temp; 
	}
	else{
		top->newNode(temp); 
	}
}

void Heap::traverse(){
	if(top != NULL){
		Node* temp = top; 
		top->print(top);
	}
}

void Heap::h_insert(int n){
	Node* temp; 
	if(top == NULL){
		cout << n << " becomes top root. " << endl; 
		top = new Node(n); 
		top->layer = 1; 
	}
	else{
		temp = top;  
		top->fill(temp, n, 1); 
	}
}

int Heap::heapCount(){
	Node*temp; 
	if(top == NULL)
		return 0; 
	else{
		temp = top; 
		return temp->count(); 
	}
}

int Heap::findLevel(){
	if(top == NULL)
		return 0; 
	else{
		int total = heapCount(); 
		int level = 1; 
		int level_nodes; 
		bool found = false; 
		while(!found){
			level_nodes = totalnumnodes(level, 0); 
			if((static_cast<double>(total)/level_nodes) <= 1.0){//had to make total a type double or else the division will round off the decimals 
				found = true; 
			}
			else 
				level++;  
		}
		return level; 
	}
}

void Heap::topToBottom(){
	if(top == NULL){
		cout << "There is nothing in this heap." << endl; 
	}
	else {
		int level = findLevel(); 
		top->h_print(top, level); 
	}
}

void Heap::removeFromHeap(int n){//complements function findRemove(Node* cur, int n) 
	int number = popHeap(); 
	cout << "Number = " << number << endl;
	if(top == NULL){
		cout << "The heap is empty." << endl; 
		return; 
	}
	else if(number == n){
		return; 
	}
	else{
		top->findRemove(top, n, number); 
		topToBottom(); 
		cout << endl;
		bool ordered; 
		do{//using this do-while loop is necessary because one line of rearrangeHeap() code is not enough. It may ignore grandchildren of exchanged heaps, especially when the heap is very large 
		rearrangeHeap(); 
		ordered = top->checkOrder(top);
		}while(!ordered); 
	}
}

void Heap::findChild(){
	if(top == NULL){
		return; 
	}
	else{
		top->findChildren(top); 	
	}
}

int Heap::popHeap(){
	Node* pop = top; 
	Node* temp; 
	int number; 
	if(top == NULL){
		return 0; 
	}
	if(top->left == NULL && top->right == NULL){
		number = top->num; 
		temp = top;
		top = NULL; 
		delete temp; 
		return number; 
	}
	while((pop->left != NULL && pop->right != NULL) || (pop->left != NULL && pop->right == NULL)){
		if(isBalanced(pop) && isBalanced(pop->left) && isBalanced(pop->right)){
			temp = pop; 
			pop = pop->right; 
		}
		else if(pop->right == NULL){
			temp = pop; 
			pop = pop->left; 
		}
		else if(!isBalanced(pop) && isBalanced(pop->left) && isBalanced(pop->right)){
			temp = pop; 
			pop = pop->left; 
		}
		else if(isBalanced(pop->left) && !isBalanced(pop->right)){
			temp = pop; 
			pop = pop->right; 
		}
		else if(!isBalanced(pop->left) && isBalanced(pop->right)){
			temp = pop; 
			pop = pop->left; 
		}
	}
	number = pop->num; 
	if(temp->left == pop){
		temp->left = NULL; 
	}
	else if(temp->right == pop){
		temp->right = NULL; 
	}
	delete pop; 
	return number; 
}

void Heap::rearrangeHeap(){
	if(top == NULL){
		return; 
	}
	else{
		int number = top->rearrange(top); 
	}
}


int main(){
	Heap numbers; 
	numbers.h_insert(25); 
	numbers.h_insert(20);
	numbers.h_insert(50); 
	numbers.h_insert(14); 
	numbers.h_insert(23);
	numbers.h_insert(30);
	numbers.h_insert(75); 
	numbers.h_insert(14); 
	numbers.h_insert(5); 
	numbers.h_insert(60); 
	numbers.h_insert(34);
	numbers.h_insert(61);
	numbers.h_insert(80);
	numbers.h_insert(55);
	numbers.h_insert(100);
	
	bool balanced;  
	numbers.topToBottom();
	balanced = numbers.isHeapBal(); 
	if(balanced){
		cout << "The heap is balanced." << endl; 
	}
	else 
		cout << "The heap is not balanced." << endl;
/*
	char ans; 
	int input; 
	do{
		cout << "Please insert a number into the heap: "; 
		cin >> input; 
		numbers.h_insert(input); 
		cout << "Enter more numbers? [y/n]"; 
		cin >> ans; 
	}while(ans == 'y' || ans == 'Y'); 


*/
	cout << "The number of nodes in this heap is: " << numbers.heapCount() << endl; 
	cout << "The number of layers in the heap is " << numbers.findLevel() << endl; 

//	numbers.findChild(); 

	char ans2; 
	do{
		int removed; 
		cout << "Type a number to be removed: " << endl; 
		cin >> removed; 
		numbers.removeFromHeap(removed); 
		cout << endl; 
//		system("Pause");
		numbers.topToBottom(); 
		cout << endl; 
		cout << "Remove another number? [y/n];"; 
		cin >> ans2; 
	}while (ans2 == 'y' || ans2 == 'Y'); 

	system("Pause"); 
	return 0; 
}

int totalnumnodes(int h, int n){
	if(h == n + 1){
		return 1; 
	}
	else{ 
		return pow(2.0, (h - n) - 1) + totalnumnodes(h, n + 1); 
	}
}