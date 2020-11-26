//AVL Sonia Sankpal
#include<bits/stdc++.h> 
using namespace std; 
typedef int T;
typedef int KEY;
struct Elem {
	Elem():left(0), right(0), height(-1), rightThread(false) {}
	KEY key;
	T data;
	Elem *left;
	Elem *right;
	int height;
	bool rightThread; //normal right child link or a threadlink
};

Elem* newElem(KEY key, T data)  
{  
    Elem* Node = new Elem(); 
    Node->key = key;  
	Node->data = data;
    Node->left = NULL;  
    Node->right = NULL;  
    Node->height = 1; // new Elem is initially 
                      // added at leaf  
    return(Node);  
}  

int max(int a, int b); 

 //to get height of the tree 
int height(Elem *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 
 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

Elem *rightRotate(Elem *y) 
{ 
	Elem *x = y->left; 
	Elem *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), 
					height(y->right)) + 1; 
	x->height = max(height(x->left), 
					height(x->right)) + 1; 

	// Return new root 
	return x; 
} 

Elem *leftRotate(Elem *x) 
{ 
	Elem *y = x->right; 
	Elem *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left), 
					height(x->right)) + 1; 
	y->height = max(height(y->left), 
					height(y->right)) + 1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of Elem N 
int balanceFactor(Elem *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - 
		height(N->right); 
} 

Elem* insert(Elem* Elem,KEY key, T data) 
{ 
	/* 1. Perform the normal BST rotation */
	if (Elem == NULL) 
		return(newElem(key,data)); 

	if (key < Elem->key) 
		Elem->left = insert(Elem->left, key,data); 
	else if (key > Elem->key) 
		Elem->right = insert(Elem->right, key,data); 
	else // Equal keys not allowed 
		return Elem; 

	/* 2. Update height of this ancestor Elem */
	Elem->height = 1 + max(height(Elem->left), 
						height(Elem->right)); 

	/* 3. Get the balance factor of this 
		ancestor Elem to check whether 
		this Elem became unbalanced */
	int balance = balanceFactor(Elem); 

	// If this Elem becomes unbalanced, 
	// then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < Elem->left->key) 
		return rightRotate(Elem); 

	// Right Right Case 
	if (balance < -1 && key > Elem->right->key) 
		return leftRotate(Elem); 

	// Left Right Case 
	if (balance > 1 && key > Elem->left->key) 
	{ 
		Elem->left = leftRotate(Elem->left); 
		return rightRotate(Elem); 
	} 

	// Right Left Case 
	if (balance < -1 && key < Elem->right->key) 
	{ 
		Elem->right = rightRotate(Elem->right); 
		return leftRotate(Elem); 
	} 

	/* return the (unchanged) Elem pointer */
	return Elem; 
} 

Elem * minValueElem(Elem* Node) 
{ 
	Elem* current = Node; 

	/* loop down to find the leftmost leaf */
	while (current->left != NULL) 
		current = current->left; 

	return current; 
} 

Elem* destructCode(Elem* root, int key) 
{ 
	
	//STANDARD BST DELETE 
	if (root == NULL) 
		return root; 

	if ( key < root->key ) 
		root->left = destructCode(root->left, key); 

	else if( key > root->key ) 
		root->right = destructCode(root->right, key); 

	else
	{ 
		// Elem with only one child or no child 
		if( (root->left == NULL) || 
			(root->right == NULL) ) 
		{ 
			Elem *temp = root->left ? 
						root->left : 
						root->right; 

			// No child case 
			if (temp == NULL) 
			{ 
				temp = root; 
				root = NULL; 
			} 
			else // One child case 
			*root = *temp;  
			free(temp); 
		} 
		else
		{ 
			//Get the inorder successor
			   
			Elem* temp = minValueElem(root->right); 

			// Copy the inorder successor's 
			// data to this Elem 
			root->key = temp->key; 

			// Delete the inorder successor 
			root->right = destructCode(root->right, 
									temp->key); 
		} 
	} 

	// If the tree had only one Elem 
	// then return 
	if (root == NULL) 
	return root; 

	// UPDATE HEIGHT  
	root->height = 1 + max(height(root->left), 
						height(root->right)); 

	int balance = balanceFactor(root); 

	// If this Elem becomes unbalanced

	// Left Left Case 
	if (balance > 1 && 
		balanceFactor(root->left) >= 0) 
		return rightRotate(root); 

	// Left Right Case 
	if (balance > 1 && 
		balanceFactor(root->left) < 0) 
	{ 
		root->left = leftRotate(root->left); 
		return rightRotate(root); 
	} 

	// Right Right Case 
	if (balance < -1 && 
		balanceFactor(root->right) <= 0) 
		return leftRotate(root); 

	// Right Left Case 
	if (balance < -1 && 
		balanceFactor(root->right) > 0) 
	{ 
		root->right = rightRotate(root->right); 
		return leftRotate(root); 
	} 

	return root; 
} 

// preorder traversal of the tree. 

void preOrder(Elem *root) 
{ 
	if(root != NULL) 
	{ 
		cout << root->key << "-" <<root->data <<"||"; 
		preOrder(root->left); 
		preOrder(root->right); 
	} 
} 
void printTree(ostream& out, int level, Elem *root)
{

    if (root == NULL)
        return;

    if (level == 1) {

            out <<root->key << " - "<< root->data << " || ";

    }
    else if (level > 1) {
        printTree(cout,level - 1,root->left);
        printTree(cout,level - 1,root->right);
    }
}


// Driver Code 
int main() 
{ 
Elem *root = NULL; 

	root = insert(root, 10,10); 
	root = insert(root, 5,5); 
	root = insert(root, 2,2); 
	root = insert(root, 15,15); 
	root = insert(root, 20,20); 
	root = insert(root, 17,17); 
	root = insert(root, -13,-13); 
	root = insert(root, 27,27); 


	cout << "Preorder traversal of the constructed AVL tree is \n"; 
	preOrder(root); 

	root = destructCode(root, 10); 

	cout << "\nPreorder traversal after deletion of 10 \n"; 
	preOrder(root); 
	
	cout<<"\nprint tree level wise \n";
	printTree(cout,2,root);

	return 0; 
} 

