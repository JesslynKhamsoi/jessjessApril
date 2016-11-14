
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <queue>
#include <iostream>
#include <stdlib.h>
using namespace std;

template<class T>
class AVLNode {
public:
	// Default blank AVLNode constructor
	AVLNode() {
		left = right = nullptr;
		height = 0;
		parent = nullptr;
	}

	// Constructor with provided element (data) and children
	AVLNode(const T& el, AVLNode *l = nullptr, AVLNode *r = nullptr, AVLNode *p = nullptr) {
		key = el;
		left = l;
		right = r;
		height = 0;
		parent = p; //added parents, to minimize traversing through tree
	}

	T key;                  // Key to compare/insert on of type <T>
	AVLNode *left, *right;  // Children of this node
	int height;      // Height of this node in the tree
	AVLNode *parent;
};


	/*
	* Main AVLTree class that stores AVLNode objects
	*  -- REQUIRES: implementation of rotation functions
	*  -- REQUIRES: implementation of node heights
	*  -- REQUIRES: implementation of contains function
	*  -- REQUIRES: implementation of remove function
	*/
	template<class T>
	class AVLTree
	{
	public:
		AVLTree() { 
			parent = nullptr;
			root = nullptr; 
			 }
		//make destructor
		void insert(const T& key) { insert(root, key, parent); }
		void printTree() { printTree(root); }

		bool contains(const T& key) { return(contains(root, key)); }
		void remove(const T& key) { remove(root, key); }

	private:
		AVLNode<T>* root;
		AVLNode<T>* parent;

		void leftRotation(AVLNode<T>* &node, int type) { //added parameter type, indicated whether a double or single rotate is being done
			
			AVLNode<T> * n = node;
			AVLNode<T>* left = n->left;
			n->left = left->right;
			left->right = n;
			left->parent = n->parent;
			n->parent = left;
			

			if (left->parent == nullptr) // case where there is a new root
			{
				root = left;
				if ((type == 0)&&(left->right)&&(left->right->left)) //if doing double rotation and checking for null pointers
				{
					left->right->left->parent = root->right; //resetting a parent for this case
				}
			}
			else {
				if (type == 1) //if single rotation
				{
					left->parent->left = left;
				}
				else
				{
					left->parent->right = left; //if double rotation where root does not become left
				}
			}
		}
	
			
		void rightRotation(AVLNode<T> * &node, int type) //switched left and right names //1 for single 0 for double rotation
		{
			
			AVLNode<T> * n = node;
			AVLNode<T>* right = n->right;
			n->right = right->left;
			right->left = n;
			right->parent = n->parent;
			n->parent = right;
			n = right;

			if (right->parent == nullptr)
			{
				root = right;
				if ((type == 0) && (right->left) && (right->left->right))
				{
					right->left->right->parent = root->left;
				}
			
			}
			else {
				if (type == 1)//if single rotation
				{
					right->parent->right = right;
				}
				else { right->parent->left = right; } //if double rotation where root does not become right
			}
			
		}
		void leftRight(AVLNode<T>* &node)
		{
			AVLNode<T>* top = node;
			if (top->parent) //finds node to pass into rotate functions
			{
				if (top->parent->right == top)
				{
					do
					{
						top = top->parent;
					} while (top->parent->right == top);
				}
			}
			rightRotation(top, 0);
			leftRotation(top->parent->parent, 0);
		}
		void rightLeft(AVLNode<T>* &node)
		{
			AVLNode<T>* top = node;
			if (top->parent)
			{
				if (top->parent->left == top)
				{
					do
					{
						if (top->parent->left == top)
							top = top->parent;
					} while (top->parent->left == top);
				}
			}
			leftRotation(top, 0);
			rightRotation(top->parent->parent, 0);
		}
		/*
		*  Insert function needs updating!
		*  This function needs to update heights as it returns from recursive insert.
		*  If the heights of a node are more than 2 different, rotate to fix
		*  After fixing, repair the heights of all nodes in the rotated tree
		*/
		void insert(AVLNode<T>* &node, const T& key, AVLNode<T>* &parent) {
			if (node == nullptr) {
				node = new AVLNode<T>(key);
				node->parent = parent;

			}
			else if (key > node->key) {

				insert(node->right, key,node);
			}
			else {
				insert(node->left, key,node);
			}

			if (difference(root) >= 2) //need to balance?
			{
				balance(node);
				
			}
		}
		void balance(AVLNode<T>* node)
		{
			if (!node) { return; }
			if ((node!= nullptr)&&(node->parent != nullptr) && (node->parent->parent != nullptr)) //checks for nullptrs
			{
				//rightLeft -- really leftRight, switched names to make more sense to myself
				if ((root->left) != nullptr && root->right != nullptr)
				{
					if (difference(root->right) == 1) 
					{
						if (height(root->right) > height(root->left))
						{
							rightLeft(node->parent->parent);
						}
					}
				
			
				  //leftRight case
					if ((difference(root->left) == 1) && (height(root->left) > height(root->right)))//((node == node->parent->right) && (node->parent == node->parent->parent->left))
					{
						leftRight(node->parent->parent);
					}
				}
				//single rotation cases
				if ((node == node->parent->left) && (node->parent == node->parent->parent->left))
				{
					leftRotation(node->parent->parent, 1);
				}
	
				else if ((node == node->parent->right) && (node->parent == node->parent->parent->right))
				{
					rightRotation(node->parent->parent, 1);
				}
				
			}
			
		}
		int height(AVLNode<T>* root) //recursive version results in stack overflow
		{
			int lH = 0,  rH = 0;
			AVLNode<T>* left = root;
			AVLNode<T>* right = root;
			while(left)
			{
				lH++;
				left = left->left;
			}
			while(right)
			{
				rH++;
				right = right->right;
			}
			return 1 + std::max(lH, rH);

			
		}
		
		int difference(AVLNode<T>* root) //returns difference between height of left and right side of tree
		{
			int diff = abs((height( root->left) - height(root->right)));
			return diff;

		}

		// MUST IMPLEMENT CONTAINS
		bool contains(AVLNode<T>* root, const T& key) {
			if (root->key == key)
			{
				return true;
			}
			else {
				if (key < root->key)
				{
					root = root->left;
				}
				else
				{
					root = root->right;
				}
				if (root)
				{
					contains(root, key); //recursivley traverse through tree until element found, or is officially missing
				}
			}
			cout << "CONTAINS STILL UNIMPLEMENTED" << endl;
			return(false);
		}

		// MUST IMPLEMENT REMOVE
		void remove(AVLNode<T>* node, const T& key)
		{
			AVLNode<T>* root_new = root;
			AVLNode<T>* n = node;
			if (node->key == key)
			{
				if (node == root) //must reset root if deleting root
					{ 
						//cases where there are only two nodes
						if ((node->right == nullptr&&node->left == nullptr)) 
						{
							root = nullptr;
						}
						else if((root->left)&&(root->right == nullptr))
						{
							root_new = root->left;
							root_new->parent = nullptr;
						}
						//case where there is only one node
						else if((root->right) && (root->left == nullptr))
						{
							root_new = root->right;
							root_new->parent = nullptr;
						}
						else{ //case with full tree

							if (height(root->left) >= height(root->right)) //if left side of tree is greater the new root comes from the left
							{
								node = node->left;
								do
								{
									if (node->right)
									{
										root_new = node->right;
										node = node->right;
									}
									else
									{
										root_new = node;
									}

								} while (node->right);
								root_new->right = root->right;
								root_new->right->parent = root_new;
								root_new->parent = nullptr; 
							}
							else //if right side is greater
							{
								node = node->right;
								do
								{
									if (node->left)
									{
										root_new = node->left;
										node = node->left;
									}
									else
									{
										root_new = node;
									}

								} while (node->left);
								root_new->left = root->left;
								root_new->left->parent = root_new;
								root_new->parent = nullptr;

							}
							root = root_new; //root reset
						}
						
				}

			
			delete(n); //delete node
		}
			
			else { //if node != root, find it recursively
				if (key < node->key)
				{
					node = node->left;
				}
				else
				{
					node = node->right;
				}
				if (!node)
				{
					remove(node, key);
				}

				cout << "REMOVE STILL UNIMPLEMENTED" << endl;
			}
		}

		// Should do a level order printout with actual depth (no alignment)
		void printTree(AVLNode<T>* node) {
			queue<AVLNode<T>*> bufQueue;
			int curr_height = node->height;
			bufQueue.push(node);
			while (!bufQueue.empty()) {
				AVLNode<T>* curr = bufQueue.front();
				if (curr->left != nullptr) { bufQueue.push(curr->left); }
				if (curr->right != nullptr) { bufQueue.push(curr->right); }
				if (curr->height < curr_height) {
					cout << endl;
					curr_height = curr->height;
				}
				cout << curr->key << " ";
				bufQueue.pop();
			}
			cout << endl;
		}
	};

#endif



	