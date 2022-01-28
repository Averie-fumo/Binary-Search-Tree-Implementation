// Saleha Muzammil
//20L-1192
// BSCS 3B

#include <iostream>
#include <queue>
#include <stack>
using namespace std;


//template class BST
template <typename T>
class BST
{
private:
	// node class
	class node
	{
	private:
		T data;
		int height;
		node* left;
		node* right;
	
	public:
		friend class BST;
		friend bool operator==(BST& lhs, BST& rhs);
	};
	node* root;

	//private functions

	//parametized insert function
	void Insert(T data, node*& curr)
	{
		node* check = Search(data); 
		// if data exist don't enter
		if (check)
		{
			cout << "This element already exists in the BST." << endl;
			return;
		}
		// if root is null
		if (curr == nullptr)
		{
			curr = new node;
			curr->data = data;
			curr->left = nullptr;
			curr->right = nullptr;
			curr->height = 0;
		}
		// inserting in the BST
		else if (curr->data == data)
			return;
		else if (data < curr->data)
			Insert(data, curr->left);
		else if (data > curr->data)
			Insert(data, curr->right);
		return;
	}
	// parameterized search function
	node* search(int key, node* curr, node*& parent)
	{
		if (!curr)
			return NULL;
		if (curr->data == key)
		{
			return curr;
		}
		else if (!curr->left && !curr->right)
			return NULL;
		else if (key < curr-> data)
		{
			parent = curr;
			return search(key, curr->left, parent);
		}
		else if (key > curr-> data)
		{
			parent = curr;
			return search(key, curr->right, parent);
		}
		else
			return NULL;
	}
	// get height function
	int getHeight(node* curr)
	{
		if (curr == nullptr)
			return 0;
		int lefth = getHeight(curr->left); 
		int righth = getHeight(curr->right);

		if (lefth > righth)
			return (lefth+1); 
		return (righth +1);
	}
	//left visit right traversal
	void lvr(node* root)
	{
		if (root == NULL)
		{
			return;
		}
		lvr(root->left);
		cout << root->data << " ";
		lvr(root->right);
	}
	// left right visit traversal
	void lrv(node* curr)
	{
		if (curr == nullptr)
			return;
		lrv(curr->left);
		lrv(curr->right);
		cout << curr->data << " ";
	}
	// visit left right traversal
	void vlr(node* curr)
	{
		if (curr == nullptr)
			return;
		cout << curr->data << " ";
		vlr(curr->left);
		vlr(curr->right);
	}
	// parameterized count nodes function
	int Count_Nodes(node* curr)
	{
		if (!curr)
			return 0;
		if (curr)
		{
			return (Count_Nodes(curr->left) + Count_Nodes(curr->right) + 1);
		}
	}
	// parametrized mirror bst function
	void Mirror_BST(node* curr)
	{
		if (curr == nullptr)
			return;
		node* n1;
		Mirror_BST(curr->left);
		Mirror_BST(curr->right);

		n1 = curr->left;
		curr->left = curr->right;
		curr->right = n1;
	}
	// parametrized find width function
	int Find_width(node* curr, int level, int& len)
	{
		if (curr == nullptr)
			return len;
		if (level == 1)
			len++;
		else
		{
			Find_width(curr->left, level - 1, len);
			Find_width(curr->right, level - 1, len);
		}
		return len;
	}
	// parameterized make skew function
	void Make_Skew(node* n)
	{
		if (!n)
			return;

		int size = Count_Nodes();

		if (size == 1)
			return;
		T* array = new T[size];
		int i = size - 1;
		stack<node*> s;
		node* curr = n;

		while (curr != nullptr || !s.empty())
		{
			while (curr != nullptr)
			{
				s.push(curr);
				curr = curr->left;
			}
			curr = s.top();
			s.pop();
			array[i] = curr->data;
			curr = curr->right;
			i--;
		}
		delete curr;
		curr = nullptr;

		root->data = array[0]; 
		root->left = nullptr;
		root->right = nullptr;
		root->height = 0;
		
		for (int i = 1;i < size;i++)
			Insert(array[i]);
	}
	//parameterized isBST
	bool isBST(node* curr)
	{
		if (curr == nullptr)
			return true;
		if (!curr->left && !curr->right)
			return true;
		if (curr->left)
			if (curr->left->data > curr->data)
				return false;
		if (curr->right)
			if (curr->right->data < curr->data)
				return false;
		return (isBST(curr->left) && isBST(curr->right));

	}
	// parametrized common ancestors
	void Common_Ancestors(node* n1, node* n2)
	{
		if (root == NULL)
			return;

		node* curr = lowest_common(root, n1->data, n2->data);
		T lca = curr->data;

		ancestors_helper(root, lca, n1, n2);
	}
	// helper functions
	node* lowest_common(node* curr, T key1, T key2)
	{
		if (curr == NULL)
			return NULL;
		if (key1 > curr->data && key2 > curr->data)
			return lowest_common(curr->right, key1, key2);
		else if (key1 < curr->data && key2 < curr->data)
			return lowest_common(curr->left, key1, key2);
		else
		{
			return curr;
		}
	}
	bool ancestors_helper(node* curr, T lca, node* n1, node* n2)
	{
		if (curr == NULL)
			return false;
		if (curr->data == lca)
		{
			if (curr->data != n1->data && curr->data != n2->data)
				cout << curr->data << " ";
			return true;
		}
		if (ancestors_helper(curr->left, lca, n1, n2) || ancestors_helper(curr->right, lca, n1, n2))
		{
			if (curr->data != n1->data && curr->data != n2->data)
				cout << curr->data << " ";
			return true;
		}
		return false;
	}
	bool equalitycheck(node* n1, node* n2)
	{
		if (!n1 && !n2)
			return true;
		if (!n1 || !n2)
			return false;
		if (n1->data != n2->data)
			return false;
		return (equalitycheck(n1->left, n2->left) && equalitycheck(
			n1->right, n2->right));
	}
	// parametrized level order recursive function
	void printLevelOrderR(node* curr, int level)
	{
		if (curr == nullptr)
			return;
		if (level == 1)
			cout << curr->data << " ";
		else
		{
			printLevelOrderR(curr->left, level - 1);
			printLevelOrderR(curr->right, level - 1);
		}

	}

public:

	//constructor*
	BST()
	{
		root = NULL;
	}
	// search* 
	node* Search(T key)
	{
		if (!root)
			return NULL;
		node* parent = nullptr;
		if (root->data == key)
			return root;
		return search(key, root, parent);
	}
	// Insert*
	void Insert(T key)
	{
		Insert(key, root);
	}
	// finds successor 
	node* minKey(node* curr)
	{
		while (curr->left != nullptr)
			curr = curr->left; 
		return curr;
	}
	node* maxKey(node* curr)
	{
		while (curr->right)
			curr = curr->right;
		return curr;
	}
	// delete*
	bool Delete(T key)
	{
		if (!root)
			return false;
		node* curr = nullptr;
		node* parent = nullptr;
		curr = search(key, root, parent);
		if (!curr)
			return false;

		if (!curr->right && !curr->left)
		{
			if (curr == root)
			{
				root = nullptr; 
				curr = nullptr;
				delete curr;
				return true;
			}
			if (parent->left == curr)
				parent->left = nullptr;
			else
				parent->right = nullptr;

			curr = nullptr;
			delete curr; 
			return true;
		}
		else if (curr->right && curr->left)
		{
			node* successor = minKey(curr->right);
			T value = successor->data;

			Delete(value);
			curr->data = value;
		}
		else
		{
			node* child; 
			if (curr->left)
				child = curr->left;
			else
				child = curr->right; 
			if (curr == root)
				root = child;
			else
			{
				if (curr == parent->left)
					parent->left = child;
				else
					parent->right = child;

			}

			curr = nullptr;
			delete curr;
			return true;
		
		}


	}
	//inorder* 
	void inOrderR()
	{
		cout << "Inorder recursive printing: " << endl;
		lvr(root); 
		cout << endl;
	}
	void inOrderI()
	{
		cout << "Inorder iterative printing: " << endl;
		if (!root)
			return ;

		stack<node*> s;
		node* curr = root;

		while (curr != nullptr || !s.empty())
		{
			while (curr != nullptr)
			{
				s.push(curr);
				curr = curr->left;
			}
			curr = s.top();
			s.pop();
			cout << curr->data << " ";
			curr = curr->right;
		}
	}
	//postoder* 
	void postOrderR()
	{
		cout << "Postorder recursive printing: " << endl;
		lrv(root); 
		cout << endl;
	}
	void postOrderI()
	{
		cout << "Postorder iterative printing: " << endl;
		if (!root)
			return;

		stack<node*> s;
		node* curr = root;

		while (curr!=nullptr || !s.empty())
		{
			while (curr!=nullptr)
			{
				if (curr->right)
					s.push(curr->right);
				s.push(curr);
				curr = curr->left;

			}
			if (!s.empty())
			{
				curr = s.top();
				s.pop();
			}

			if (!s.empty() && curr->right && s.top() == curr->right)
			{
				s.pop();
				s.push(curr);
				curr = curr->right;
			}
			else
			{
				cout << curr->data << " ";
				curr = nullptr;
			}
		}
	}
	// preorder*
	void preOrderR()
	{
		cout << "Preorder recursive printing: " << endl;
		vlr(root);
		cout << endl;
	}
	void preOrderI()
	{
		cout << "Preorder iterativee printing: " << endl;
		if (root == NULL)
			return;

		node* curr = root;
		stack<node*> s;
		s.push(root);

		while (!s.empty())
		{
			curr = s.top();
			cout << curr->data << " ";
			s.pop();

			if (curr->right)
				s.push(curr->right);
			if (curr->left)
				s.push(curr->left);
		}
	}
	void printLevelOrderI()
	{
		cout << "Level order iterative printing: " << endl;
		if (root == nullptr)
			return;

		queue<node*> q;
		q.push(root);
		while (!q.empty())
		{
			node* n = q.front(); 
			cout << n->data << " "; 
			q.pop(); 

			if (n->left != nullptr)
				q.push(n->left); 
			if (n->right != nullptr)
				q.push(n->right);
		}
	}
	void printLevelOrderR()
	{
		cout << "Level order recursive printing: " << endl;
		int h = getHeight(root);

		node* curr = root;
		for (int i = 0; i <= h; i++)
		{
			printLevelOrderR(curr, i);
			cout << endl;
		}

	}
	//update key*
	bool Update_Key(T key1, T key2)
	{
		if (!Search(key1))
			return false;

		Delete(key1);
		Insert(key2);
		return true;

	}
	//assignment operator*
	BST& operator=(const BST<T> tree)
	{
		if (!tree.root)
		{
			root = nullptr;
			return *this;
		}
		node* curr = tree.root;
		stack<node*> s;
		s.push(curr);

		while (!s.empty())
		{
			curr = s.top();
			Insert(curr->data);
			s.pop();

			if (curr->right)
				s.push(curr->right);
			if (curr->left)
				s.push(curr->left);
		}
		return *this;
	}
	//equality operator*
	friend bool operator==(BST& const lhs, BST& const rhs)
	{
		if (!lhs.root && !rhs.root)
			return true;

		if (!lhs.root || !rhs.root)
			return false;

		if (lhs.Count_Nodes() != rhs.Count_Nodes())
			return false;
		if (lhs.root->data == rhs.root->data)
		{
			return (lhs.equalitycheck(lhs.root->left, rhs.root->left) &&
				rhs.equalitycheck(rhs.root->right, lhs.root->right));
		}
		else
			return false;
	}
	// count_nodes*
	int Count_Nodes()
	{
		return Count_Nodes(root);
	}
	//mirror bst*
	void Mirror_BST()
	{
		Mirror_BST(root);
	}
	//find width*
	int Find_width()
	{
		int h = getHeight(root);
		node* curr = root;
		int width = -1, spare = 0;

		for (int i = 0; i <= h;i++)
		{
			int len = 0;
			spare = Find_width(curr, i, len);
			if (spare > width)
				width = spare;
		}
		return width;
	}
	//path sum*
	void Path_Sum(vector<T>& sums)
	{
		if (!root)
			return; 
		if (!root->left && !root->right)
		{
			sums.push_back(root->data);
			return;
		}
		Path_Sum(sums, root);
	}
	void Path_Sum(vector<T>& sums, node* curr)
	{
		if (!curr)
			return;
		if (!curr->left && !curr->right)
		{
			T sum = root->data;
			sum += curr->data;
				node* parent = nullptr; 
				search(curr->data, root, parent);

				while (parent!= root)
				{
					sum += parent->data;
					search(parent->data, root, parent);
				}
				sums.push_back(sum);
		}
		Path_Sum(sums, curr->right);
		Path_Sum(sums, curr->left);
	
	}
	//make skew*
	void Make_Skew()
	{
		Make_Skew(root);
	}
	bool duplicatecheck(T data)
	{
		int i = 0;
		if (!root)
			return true;
		stack<node*> s;
		node* curr = root;

		while (curr != nullptr || !s.empty())
		{
			while (curr != nullptr)
			{
				s.push(curr);
				curr = curr->left;
			}
			curr = s.top();
			s.pop();
			if (curr->data == data)
				i++;
			curr = curr->right;
		}
		if (i> 1)
		return false;
		return true;
	}
	// isBST*
	bool isBST()
	{
		return isBST(root);
	}
	// common ancestors*
	void Common_Ancestors(T key1, T key2)
	{
		node* n1 = Search(key1);
		node* n2 = Search(key2); 
		if (!n1 || !n2)
			return;

		Common_Ancestors(n1, n2);
	}
	//destructor *
	~BST()
	{

		while (root)
		{
			Delete(root->data);
		}
		cout << endl << "Destructor." << endl; 
	}
};

int main()
{
	BST<int> tree1;
	cout << "BST of int data type has been created." << endl;
	cout << "Enter keys of BST. Press -1 to terminate the loop." << endl;

	int i = 0;
	cout << "Enter key: ";
	cin >> i;
	while (i != -1)
	{
		tree1.Insert(i);
		cout << "Enter key: ";
		cin >> i;
	}

	if (tree1.isBST())
		cout << endl << "The tree is a BST. " << endl;
	else
		cout << "the tree is not BST." << endl;

	cout << "Number of nodes of BST: " << tree1.Count_Nodes() << endl;
	cout << "Width of BST: " << tree1.Find_width() << endl;

	vector<int> array;
	cout << "Path sums of BST: ";
	tree1.Path_Sum(array);

	for (int i = 0; i < array.size();i++)
		cout << array.at(i) << " ";
	cout << endl;

	cout << "Printing the BST..." << endl << endl;
	tree1.inOrderI(); 	cout << endl;
	tree1.inOrderR();   cout << endl;
	tree1.postOrderI();	cout << endl;
	tree1.postOrderR();	cout << endl;
	tree1.preOrderI();	cout << endl;
	tree1.preOrderR();	cout << endl;
	tree1.printLevelOrderI();	cout << endl;
	tree1.printLevelOrderR();	cout << endl;

	cout << "Enter a key to search: ";
	cin >> i;
	if (tree1.Search(i))
		cout << "Found." << endl;
	else
		cout << "Not found." << endl;

	int m, n;
	cout << "Enter two keys to find their common ancestors: " << endl;
	cout << "Key1: ";
	cin >> m;
	cout << "Key2: ";
	cin >> n;
	cout << "Common ancestors are: ";
	tree1.Common_Ancestors(m, n);
	cout << endl;



	cout << "Enter a key to delete: ";
	cin >> i;
	if (tree1.Delete(i))
	{
		cout << "Deleted successfully." << endl;
		cout << endl << "Current BST:" << endl;
		tree1.printLevelOrderR();
	}
	else
		cout << "Key could not be deleted." << endl;

	cout << "Enter a key to update: ";
	cin >> m;
	cout << "Enter th key you want to replace it with: ";
	cin >> n;
	if (tree1.Update_Key(m, n))
	{
		cout << "Updated successfully." << endl;
		cout << endl << "Current BST:" << endl;
		tree1.printLevelOrderR();
	}
	else
		cout << "Key could not be updated." << endl;

	cout << "Creating another BST tree now..." << endl
		<< "Deep copying first tree in the second using = operator..." << endl;
	BST<int> tree2 = tree1;

	cout << "Checking if the BSTs are equal to each other." << endl;
	if (tree1 == tree2)
		cout << "BSTs are equal." << endl;
	else
		cout << "BSTs are unequal." << endl;


	cout << "Changing the BST into its mirror." << endl << endl;
	cout << "Before..." << endl;
	tree1.printLevelOrderR();
	tree1.Mirror_BST();
	cout << endl << "After..." << endl;
	tree1.printLevelOrderR();

	cout << "Converting into skew tree.." << endl;
	tree1.Make_Skew(); 
	cout << endl << "Current BST:" << endl;
	tree1.printLevelOrderR();




	return 0;
}"# Binary-Search-Tree-Implementation" 
