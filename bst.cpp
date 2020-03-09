#include <iostream>


using namespace std;

struct Node{
    ~Node() {
        //if (left) delete left;
        //if (right) delete right;
    }
    Node() {}
    Node(int x) : value{x} {}
    Node * parent = NULL;
    Node * left = NULL;
    Node * right = NULL;
    int value;
};

void printInOrder(Node *n) {
    if (!n) return;
    printInOrder(n->left);
    cout << n->value << " ";
    printInOrder(n->right);
}

void printPreOrder(Node *n) {
    if (!n) return;
    cout << n->value << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

void printPostOrder(Node *n) {
    if (!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->value << " ";
}

struct Node * successor(struct Node *n) { 
  if( n->right != NULL ) { 
    while (n->left != NULL) { 
        n = n->left; 
    } 
    return n; 
  }
    struct Node *p = n->parent; 
    while(p != NULL && n == p->right) { 
    n = p; 
    p = p->parent; 
  } 
  return p; 
} 

void insert(Node *&n, int x) {
    if (n == NULL) { 
        n = new Node(x);
        cout << "Element inserted" << endl;
        return;
    }

    if (n->value > x) {
        if (n->left == NULL) {
            n->left = new Node(x);
            n->left->parent = n;
            cout << "Element inserted" << endl;
            return;
        }
        else (insert(n->left, x));
    }
    else if (n->value < x) {
        if (n->right == NULL) {
            n->right = new Node(x);
            n->right->parent = n;
            cout << "Element inserted" << endl;
            return;
        }
        else (insert(n->right, x));
    }
    else cout << "Element already present" << endl;
}

// void deleteNode(Node *n, int x) {
//     if (!n) cout << "Element not found" << endl;
//     else if (n->value < x) deleteNode(n->left, x);
//     else if (n->value > x) deleteNode(n->right, x);
//     else if (n->value == x) {
//         if (n->left == NULL) { 
            
//             Node *temp = n->right; 
//             free(n); 
//             return temp; 
//         } 
//         else if (root->right == NULL) 
//         { 
//             struct node *temp = root->left; 
//             free(root); 
//             return temp; 
//         } 
//         cout << "Element deleted" << endl;
//     }
//     else cout << "wattttdelete" << endl;
// }


struct Node * minValueNode(struct Node* node) 
{ 
    struct Node* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
} 

/* Given a binary search tree and a key, this function deletes the key 
   and returns the new root */
struct Node* deleteNode(struct Node* &root, int key) { 
    // base case 
    if (root == NULL) return root; 
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (key < root->value) root->left = deleteNode(root->left, key); 
  
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (key > root->value) root->right = deleteNode(root->right, key); 

    else { 
        // node with only one child or no child 
        if (root->left == NULL) { 
            struct Node *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) { 
            struct Node *temp = root->left; 
            free(root); 
            return temp; 
        } 
  
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        struct Node* temp = minValueNode(root->right); 
  
        // Copy the inorder successor's content to this node 
        root->value = temp->value; 
  
        // Delete the inorder successor 
        root->right = deleteNode(root->right, temp->value); 
    } 
    return root; 
} 

void access(Node *n, int x) {
    if (!n) cout << "Element not found" << endl;
    else if (n->value < x) access(n->left, x);
    else if (n->value > x) access(n->right, x);
    else if (n->value == x) cout << "Element accessed" << endl;
    else cout << "wattttaccess" << endl;
}

bool ifNodeExists(struct Node* node, int key) { 
    if (node == NULL) 
        return false; 
  
    if (node->value == key) 
        return true; 
  
    /* then recur on left sutree */
    bool res1 = ifNodeExists(node->left, key); 
  
    if(res1) return true; // node found, no need to look further 
  
    /* node is not found in left, so recur on right subtree */
    bool res2 = ifNodeExists(node->right, key); 
  
    return res2; 
} 

void doOperation(string op, Node *&n, int x = 0) {
    if (op == "insert" || op == " insert") {
        insert(n, x);
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
        //access(n, x);
        bool found = ifNodeExists(n, x);
        if (found) cout << "Element accessed" << endl;
        else cout << "Element not found" << endl;
    }
    else if (op =="delete"|| op == " delete") {
        Node *deleted = deleteNode(n, x);
        if (deleted == n && n != NULL) cout << "Element not found" << endl;
        else cout << "Element deleted" << endl << n->value <<endl;
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
            //cout << strarr[i] << endl;
        }
        else {
            //cout << strarr[i] << endl;
            doOperation(strarr[i], head);
        }
    }
    return 0;
}

// "print, insert 50, insert 60, insert 40, insert 10, insert 20, access 10, print, insert 15, print, insert 40, insert 30, print, delete 40, print, insert 40, insert 70, print, delete 100, print"

// "print, insert 50, insert 60, insert 40, insert 10, insert 20, access 10, print, insert 15, print, insert 40, insert 30, print, delete 40, print, insert 40, insert 70, print, delete 100, print"
