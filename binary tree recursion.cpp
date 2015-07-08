#include <iostream> 
#include <string> 

using namespace std; 

class TreeNode{
public: 
	TreeNode(); 
	TreeNode(string n); 
	void setNode(TreeNode* n); 
	void print(); 
	bool find(string n); 
//	void remove(string n, TreeNode* parent); 
//	string findSmallest(TreeNode* left_p); 
	TreeNode* findParent(TreeNode* n); 
private: 
	TreeNode* left; 
	TreeNode* right; 
	string data; 
friend class Tree; 
}; 

TreeNode::TreeNode(){
	data = ""; 
	left = NULL; 
	right = NULL; 
}

TreeNode::TreeNode(string n){
	data = n; 
	left = NULL; 
	right = NULL; 
}

void TreeNode::print(){
	if(left != NULL){
		left->print(); 
	}
	cout << data << endl; 
	if(right != NULL){
		right->print(); 
	}
}

bool TreeNode::find(string n){
	if(this == NULL){
		return false; 
	}
	else if(data == n){
		return true; 
	}
	else if(data > n){
		return left->find(n); 
	}
	else if(data < n){
		return right->find(n); 
	}
}

/*
void TreeNode::remove(string n, TreeNode* parent){//think about what if root node is to be deleted 
	if(this == NULL){
		cout << n << " is not found." << endl; 
	}
	else{
		if(data > n){
			if(left != NULL)
				left->remove(n, this->left); 
			else
				cout << n << " is not found." << endl; 
		}
		else if (data < n){
			if(right != NULL) 
				right->remove(n, this->right); 
			else 
				cout << n << " is not found." << endl; 
		}
		else if (data == n){
			if(left == NULL && right == NULL){
				parent = NULL; 
				TreeNode* temp = this; 
				data = ""; 
				delete temp; 
			}
			else if(right != NULL){
				data = right->findSmallest(left); 
			}
			else if(left != NULL && right == NULL){//needs work
				TreeNode* temp = this; 
				parent->left = left; 
				data = ""; 
				left = NULL; 
				delete temp; 
			}
		}
	}
}

string TreeNode::findSmallest(TreeNode* left_p){
	if(left != NULL){
		return left->findSmallest(this); 
	}
	else{
		if(right == NULL){
			TreeNode* tempNode = this; 
			string temp = data; 
			data = ""; 
			delete tempNode; 
			return temp; 
		}
		else{
			TreeNode* tempNode = this; 
			string temp = data; 
			data = ""; 
			left_p->left = right; 
			delete tempNode; 
			return temp; 
		}
	}
}
*/

class Tree{
public: 
	Tree() {root = NULL; }; 
	void insertNode(string n); 
	void traverse(); 
	bool tree_find(string n); 
	void tree_remove(string n); 
private: 
	TreeNode* root; 
}; 

void Tree::insertNode(string n){
	TreeNode* temp = new TreeNode(n);  
	if(root == NULL){
		root = temp; 
	}
	else{
		root->setNode(temp); 
	}
}


void TreeNode::setNode(TreeNode* n){ 
	if(data > n->data){
		if(left == NULL){
			left = n; 
		}
		else{
			left->setNode(n); 
		}
	}
	else if (data < n->data){
		if(right == NULL){
			right = n; 
		}
		else{
			right->setNode(n); 
		}
	}
}

void Tree::traverse(){
	if(root != NULL){
		root->print(); 
	}
}

bool Tree::tree_find(string n){
	if(root != NULL){
		return root->find(n); 
	}
	else
		return false; 
}

/*
void Tree::tree_remove(string n){
	TreeNode* toberemoved = root; //pointer points to root 
	TreeNode* parent = NULL; //pointer is created and is set to NULL 
	bool found = false; 
	while(!found && toberemoved != NULL){//this block of code will go through the entire tree to find string n 
		if(toberemoved->data < n) //move the toberemoved pointere to the right 
		{
			parent = toberemoved; //the purpose of parent to point to node preceding node being pointed by toberemoved 
			toberemoved = toberemoved->right; 
		}
		else if(n < toberemoved->data) //move the toberemoved pointere to the left 
		{
			parent = toberemoved; 
			toberemoved = toberemoved->left;  
		}
		else //if n == toberemoved->data, found = true; 
			found = true; 
	}
	if(!found) //if the string n is not found in tree, exit out of function 
		return; 
	if(toberemoved->left == NULL || toberemoved->right == NULL){//if either left or right children of "toberemoved" node is NULL, this block of text is executed. The next following block will not be
		TreeNode* new_child;
		//following code deals with the fate of new_child 
		if(toberemoved->left == NULL){
			new_child = toberemoved->right;//new_child is pointed to right node  
		}
		else
			new_child = toberemoved->left;//new_child is pointed to left node; if both left and right is NULL, new_child points to NULL. This is will account for the fact that toberemoved node has no children. The parent will inherit nothing. 
		if(parent == NULL){//this executes if the root node is targeted by toberemoved 
			root = new_child; 
			delete toberemoved; 
		}
		else if(parent->left == toberemoved){//if toberemoved node is left child of parent
			parent->left = new_child; //makes sense since new_child->data < parent->data
			delete toberemoved; 
		}
		else {
			parent->right = new_child; 
			delete toberemoved; 
		}
		return; //function exits out 
	}
	//following block of code executes if both left and right children of toberemoved are not NULL  
	TreeNode* smallest_parent = toberemoved; 
	TreeNode* smallest = toberemoved->right;
	while(smallest->left != NULL){
		smallest_parent = smallest; 
		smallest = smallest->left; 
	}
	toberemoved->data = smallest->data; 
	if(smallest_parent == toberemoved)
		smallest_parent->right = smallest->right; 
	else 
		smallest_parent->left = smallest->right; // it does account for the fact if smallest has no children. 
}
*/
/*
void Tree::tree_remove(string n){
	TreeNode* toberemoved = root; 
	TreeNode* parent = toberemoved; 
	bool found = false; 
	while(!found && toberemoved != NULL){
		if(toberemoved->data < n){
			parent = toberemoved;
			toberemoved = toberemoved->right; 
		}
		else if(toberemoved->data > n){
			parent = toberemoved; 
			toberemoved = toberemoved->left; 
		}
		else if(toberemoved->data == n){
			found = true;  
		}
	}
	if(!found){
		return; 
	}
	if(toberemoved->left == NULL || toberemoved->right == NULL){
		TreeNode* child = NULL; //necessary 
		if(toberemoved->left != NULL){
			child = toberemoved->left; 
		}
		else if(toberemoved->right != NULL){
			child = toberemoved->right; 
		}
		if(root == toberemoved){
			root = child; 
			delete toberemoved; 
			return; 
		}
		if(parent->left == toberemoved){
			parent->left = child; 	
			delete toberemoved; 
		}
		else if(parent->right == toberemoved){
			parent->right = child; 	
			delete toberemoved; 
		}
		return; 
	}
	TreeNode* ParSmall = toberemoved->right; 
	TreeNode* Smallest = ParSmall; 
	while(Smallest->left != NULL){
		ParSmall = Smallest; 
		Smallest = Smallest->left; 
	}
	toberemoved->data = Smallest->data; 
	if(Smallest == ParSmall){
		toberemoved->right = NULL;
		delete Smallest; 
	}
	else if(Smallest->right != NULL){
		ParSmall->left = Smallest->right; 
		delete Smallest; 
	}
	else{
		ParSmall->left = NULL; 
		delete Smallest; 
	}
}
*/

void Tree::tree_remove(string n){
	TreeNode* toberemoved = root; 
	TreeNode* parent = toberemoved; 
	bool found = false; 
	while(!found && toberemoved != NULL){
		if(toberemoved->data > n){
			parent = toberemoved; 
			toberemoved = toberemoved->left; 
		}
		else if(toberemoved->data < n){
			parent = toberemoved; 
			toberemoved = toberemoved->right; 
		}
		else if(toberemoved->data == n){
			found = true; 
		}
	}

	if(!found)
		return; 

	if(toberemoved->left == NULL || toberemoved->right == NULL){
		TreeNode* child = NULL; 
		if(toberemoved->left != NULL){
			child = toberemoved->left; 
		}
		else if(toberemoved->right != NULL){
			child = toberemoved->right; 
		}
		if(parent->left == toberemoved){
			parent->left = child; 
			delete toberemoved; 
		}
		else if (parent->right == toberemoved){
			parent->right = child; 
			delete toberemoved; 
		}
		else if(toberemoved == root){
			root = child; 
			delete toberemoved; 
		}
		return; 
	}

	TreeNode* Smallest = toberemoved->right; 
	TreeNode* ParSmall = toberemoved; 
	while(Smallest->left != NULL){
		ParSmall = Smallest; 
		Smallest = Smallest->left; 
	}
	toberemoved->data = Smallest->data; 
	if(ParSmall == toberemoved){
		toberemoved->right = Smallest->right; 
		delete Smallest; 
	}
	else{
		ParSmall->left = Smallest->right; 
		delete Smallest; 
	}
}

int main(){
	Tree names; 
	names.insertNode("Prince"); 
	names.insertNode("Doctor"); 
	names.insertNode("Zebra"); 
	names.insertNode("Pony"); 
	names.insertNode("Snake"); 
	names.insertNode("Albert");
	names.insertNode("Superman"); 
	names.insertNode("Batman");
	names.insertNode("Spiderman"); 
	names.insertNode("Punisher");
	names.traverse(); 

	/*
	cout << "Please, add names to the list. Type ~ to indicate end of input." << endl; 
	string input; 
	cin >> input; 
	while(input != "~"){
		names.insertNode(input); 
		cout << "Please, add another name to the list." << endl; 
		cin >> input; 
	}

	cout << endl; 
	names.traverse(); 
	*/
	char ans; 
	do{
	cout << "Please, enter a name to be removed: "; 
	string input; 
	cin >> input; 
	names.tree_remove(input); 
	names.traverse(); 

	cout << endl; 
	cout << "Repeat? [y/n]"; 
	cin >> ans; 
	}while(ans == 'y' || ans == 'Y'); 
system("Pause"); 
return 0; 
}