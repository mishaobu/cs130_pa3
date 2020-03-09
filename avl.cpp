#include <iostream>


using namespace std;

class Node {  
    public: 
    int key;  
    Node *left;  
    Node *right;  
    int height;  
};  


void printInOrder(Node *n) {
    if (!n) return;
    printInOrder(n->left);
    cout << n->key << " ";
    printInOrder(n->right);
}

void printPreOrder(Node *n) {
    if (!n) return;
    cout << n->key << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

void printPostOrder(Node *n) {
    if (!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->key << " ";
}
 
int max(int a, int b);  
  

int height(Node *N)  {  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  
  

int max(int a, int b)  {  
    return (a > b)? a : b;  
}  
  
Node* newNode(int key)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; 
    return(node);  
}  
   
Node *rightRotate(Node *y) {  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    x->right = y;  
    y->left = T2;  
  
    y->height = max(height(y->left), height(y->right)) + 1;  
    x->height = max(height(x->left), height(x->right)) + 1;  
  
    return x;  
}  
  
Node *leftRotate(Node *x)  {  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    y->left = x;  
    x->right = T2;  
  
    x->height = max(height(x->left), height(x->right)) + 1;  
    y->height = max(height(y->left), height(y->right)) + 1;  

    return y;  
}  
  
int getBalance(Node *N)  {  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  


Node* insert(Node* &node, int key)  {  
    if (node == NULL) {
        return newNode(key);
    }
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
        return node;  
  
    node->height = 1 + max(height(node->left), height(node->right));  
  

    int balance = getBalance(node);  
  
    if (balance > 1 && key < node->left->key) return rightRotate(node);  
  
    if (balance < -1 && key > node->right->key) return leftRotate(node);  
  
    if (balance > 1 && key > node->left->key)  {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
      if (balance < -1 && key < node->right->key) {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
   return node;  
}  

Node * minValueNode(Node* node) {  
    Node* current = node;  
    while (current->left != NULL)  current = current->left;  
    return current;  
}  

Node* deleteNode(Node* root, int key)  {   
    if (root == NULL) return root;  
    if ( key < root->key ) root->left = deleteNode(root->left, key);  
    else if( key > root->key ) root->right = deleteNode(root->right, key);  
  

    else {  
        if ((root->left == NULL) || (root->right == NULL) ) {  
            Node *temp = root->left ? root->left : root->right;  

            if (temp == NULL) {  
                temp = root;  
                root = NULL;  
            }  
            else  
            *root = *temp; 
            free(temp);  
        }  
        else {  
            Node* temp = minValueNode(root->right);  
 
            root->key = temp->key;  
            root->right = deleteNode(root->right, temp->key);  
        }  
    }  
  
    if (root == NULL) return root;  
  
    root->height = 1 + max(height(root->left), height(root->right));  

    int balance = getBalance(root);  
  
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);  
  
    if (balance > 1 && getBalance(root->left) < 0)  {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    if (balance < -1 && getBalance(root->right) <= 0)  return leftRotate(root);  
  
    if (balance < -1 && getBalance(root->right) > 0) {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}  


void access(Node *n, int x) {
    if (!n) cout << "Element not found" << endl;
    else if (n->key < x) access(n->left, x);
    else if (n->key > x) access(n->right, x);
    else if (n->key == x) cout << "Element accessed" << endl;
    else cout << "wattttaccess" << endl;
}

void doOperation(string op, Node *&n, int x = 0) {
    if (op == "insert" || op == " insert") {
        n = insert(n, x);
        cout << "Element inserted" << endl;
    }
    else if (op == "print"|| op == " print") {
        if (n == NULL) {
            cout << "Empty tree" << endl;
            return;
        }
        printPreOrder(n); cout << endl;
        printInOrder(n); cout << endl;
        printPostOrder(n); cout << endl;
    } 
    else if (op == "access"|| op == " access") {
        access(n, x);
    }
    else if (op =="delete"|| op == " delete") {
        Node *deleted = deleteNode(n, x);
        if (!deleted) cout << "Element not found" << endl;
        else cout << "Element deleted" << endl;
    }
    else { "error wtf"; }
}


int main(int argc, char* argv[]) {
    Node *head = NULL;

    if (argc != 2) exit(-1);

    string strarr[100];
    for (int i = 0; i<100; i++) strarr[i] = "";

    int numArgs = 0;
    bool newArg = false;

    string v = argv[1];
    for (int i = 0; i < v.length(); i++) {
        if (v[i] == ' ' || v[i] == ',') {
            newArg = true;
            continue;
        }
        else {
            if (newArg == true) numArgs += 1;
            newArg = false;
            string s(1, v[i]);
            strarr[numArgs] = strarr[numArgs] + s;
        }
    } 
    for (int i =0; i<numArgs+1; i++) {
        if (strarr[i] == "insert" || strarr[i] == "access" || strarr[i] == "delete") {
            doOperation(strarr[i], head, stoi(strarr[i+1]));
            i += 1;
        }
        else {
            doOperation(strarr[i], head);
        }
    }
    return 0;
}
