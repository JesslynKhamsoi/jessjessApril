/*
* Binary Search Tree implementation
*  - heavily lifted from https://gist.github.com/mgechev/5911348
*
* Simple integer keys and basic operations BST
*
* Aaron Crandall - 2016 - Added / updated:
*  * Inorder, Preorder, Postorder printouts
*  * Stubbed in level order printout
*
*/

#include <iostream>
#include <queue>
using namespace std;

/*
*  Node datastructure for single tree node
*/
template <class T>
struct Node {
	T value;
	Node *left;
	Node *right;

	Node(T val) {
		this->value = val;
	}

	Node(T val, Node<T> left, Node<T> right) {
		this->value = val;
		this->left = left;
		this->right = right;
	}
};

/*
* Binary Search Tree (BST) class implementation
*/
template <class T>
class BST {

private:
	Node<T> *root;

	void addHelper(Node<T> *root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	void printInOrderHelper(Node<T> *root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	void printPostOrderHelper(Node<T> *root) {
		if (!root) return;
		printPostOrderHelper(root->left);
		printPostOrderHelper(root->right);
		cout << root->value << ' ';
	}

	void printPreOrderHelper(Node<T> *root) {
		if (!root) return;
		cout << root->value << ' ';
		printPreOrderHelper(root->left);
		printPreOrderHelper(root->right);
	}

	void printLevelOrderHelper(Node<T> *root) {
		if (!root) return;
		bool done = false; // true if at end of tree
		int level = 1;
		
			std::queue<Node<T> *> tree;
			tree.push(root);
			Node <T> *cur = root;
		do{
			while (cur != nullptr)
			{
				for (int j = 0; j < level; j++)
				{
					cur = cur->left;
				}
			}
		if ((cur->left == nullptr) && (cur->right == nullptr))
		{
			done = true; //end of left side
		}
		if (cur->left != nullptr)
		{
			tree.push(cur->left);
		}
		if (cur->right != nullptr)
		{
			tree.push(cur->right);
		}
		// checking right side of level
		cur = root;

		while (cur != nullptr)
		{
			for (int j = 0; j < level; j++)
			{
				cur = cur->right;
			}
		}
		if ((done == true) && (cur->left == nullptr) && (cur->right == nullptr))
		{
			done = true; // end of tree?
		}
		else
		{
			done = false;// at least right side still has more nodes
		}
		if (cur->left != nullptr)
		{
			tree.push(cur->left);
		}
		if (cur->right != nullptr)
		{
			tree.push(cur->right);
		}
		level++; //level of tree goes up 
	}while (done == true);
	//print queue FIFO
	while (!tree.empty())
	{
		cout << ' ' << tree.front();
		tree.pop();
	}
	cout << '\n';
	cout << "UNIMPLEMENTED AT THIS TIME -- REPLACE!" << endl;
	cout << " ** Requred to use the STL queue class (that's a huge hint)!" << endl;
	cout << " ** Doing this with a loop will be just fine." << endl;
}

int nodesCountHelper(Node<T> *root) {
	if (!root) return 0;
	else return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
}

int heightHelper(Node<T> *root) {
	if (!root) return 0;
	else return 1 + max(heightHelper(root->left), heightHelper(root->right));
}

void printMaxPathHelper(Node<T> *root) {
	if (!root) return;
	cout << root->value << ' ';
	if (heightHelper(root->left) > heightHelper(root->right)) {
		printMaxPathHelper(root->left);
	}
	else {
		printMaxPathHelper(root->right);
	}
}

bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
	if (!current) return false;
	if (current->value == value) {
		if (current->left == NULL || current->right == NULL) {
			Node<T>* temp = current->left;
			if (current->right) temp = current->right;
			if (parent) {
				if (parent->left == current) {
					parent->left = temp;
				}
				else {
					parent->right = temp;
				}
			}
			else {
				this->root = temp;
			}
		}
		else {
			Node<T>* validSubs = current->right;
			while (validSubs->left) {
				validSubs = validSubs->left;
			}
			T temp = current->value;
			current->value = validSubs->value;
			validSubs->value = temp;
			return deleteValueHelper(current, current->right, temp);
		}
		delete current;
		return true;
	}
	return deleteValueHelper(current, current->left, value) ||
		deleteValueHelper(current, current->right, value);
}

	public:
		void add(T val) {
			if (root) {
				this->addHelper(root, val);
			}
			else {
				root = new Node<T>(val);
			}
		}

		void print() {
			printInOrderHelper(this->root);
		}

		void printInOrder() {
			printInOrderHelper(this->root);
		}

		void printPostOrder() {
			printPostOrderHelper(this->root);
		}

		void printPreOrder() {
			printPreOrderHelper(this->root);
		}

		void printLevelOrder() {
			printLevelOrderHelper(this->root);
		}

		int nodesCount() {
			return nodesCountHelper(root);
		}

		int height() {
			return heightHelper(this->root);
		}

		void printMaxPath() {
			printMaxPathHelper(this->root);
		}

		bool deleteValue(T value) {
			return this->deleteValueHelper(NULL, this->root, value);
		}
};


int main() {
	BST<int> *bst = new BST<int>();
	bst->add(4);
	bst->add(2);
	bst->add(1);
	bst->add(3);
	bst->add(6);
	bst->add(5);
	bst->add(7);
	bst->add(9);
	bst->add(8);


	cout << "Inorder: \t";
	bst->printInOrder();
	cout << endl;

	cout << "Postorder: \t";
	bst->printPostOrder();
	cout << endl;

	cout << "Preorder: \t";
	bst->printPreOrder();
	cout << endl;

	cout << "Levelorder: \t";
	bst->printLevelOrder();
	cout << endl;
	cout << "Should produce:\t4 2 6 1 3 5 7 9 8" << endl;


	cout << endl;
	cout << "Nodes count: " << bst->nodesCount();
	cout << endl;
	cout << "Height: " << bst->height();
	cout << endl;
	cout << "Max path: ";
	bst->printMaxPath();
	cout << endl;
	return 0;
}