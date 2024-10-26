#include<iostream>
#include<queue>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        this->data = value;
        this->left = NULL;
        this->right = NULL;
    }
};

// Function of insert data in BST
Node* insertIntoBST(Node* root, int data) {
    if(root == NULL) {
        root = new Node(data);
        return root;
    }

    // its not the first node
    if(data > root->data) {
        root->right = insertIntoBST(root->right, data);
    }
    else{
        root->left = insertIntoBST(root->left, data);
    }
    return root;
}

// Function of create BinarySearchTree
void createBST(Node* &root) {
    cout << "Enter data: "<< endl;
    int data;
    cin >> data;

    while(data != -1) {
        root = insertIntoBST(root, data);
        cout << "Enter data: "<< endl;
        cin >> data;
    } 
}

// function of levelOrderTraversal to print node
void levelOrderTraversal(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if(temp == NULL) {
            cout << endl;
            if(!q.empty()) {
                q.push(NULL);
            }
        }
        else {
            cout << temp->data <<" ";
            if(temp->left != NULL) {
                q.push(temp->left);
            }
            if(temp->right != NULL) {
                q.push(temp->right);
            }
        }
    }
}

// Function of preOrderTraversal
void preOrder(Node* root) {
    if(root == NULL) {
        return;
    }
    // NLR
    cout << root-> data <<" ";
    preOrder(root->left);
    preOrder(root->right);
}

// Function of inOrderTraversal
void inOrder(Node* root) {
    if(root == NULL) {
        return;
    }
    // LNR (left Node Right)
    inOrder(root->left);
    cout << root-> data <<" ";
    inOrder(root->right);
}

// Function of postOrderTraversal
void postOrder(Node* root) {
    if(root == NULL) {
        return;
    }
    // LRN
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data <<" ";
} 

// Function of find  minimum value in BST
Node* minValue(Node* root) {
    if(root == NULL) {
        cout << "NO MIN VALUE: " << endl;
        return NULL;
    }

    Node* temp = root;
    while(temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

// Function of find maximum Node value in BST
Node* maxValue(Node* root) {
    if(root == NULL) {
        cout <<"NO MAX VALUE: "<< endl;
        return NULL;
    }

// if tree has node > 0 count
    Node* temp = root;

    while(temp->right != NULL) {
        temp = temp->right;
    }
    return temp;
}

// Function of search element in BST
bool searchInBST(Node* root, int target) {
    // Base Case
    if(root == NULL) {
        return false;
    }

    // 1 case main solve karunga 
    if(root->data == target) {
        return true;
    }

    // Baaki recursion sambhal lega
    //left ya right
    bool leftAns = false;
    bool rightAns = false;
    if(target > root->data) {
        rightAns = searchInBST(root->right, target);
    }
    else {
        leftAns = searchInBST(root->left, target);
    }
    return rightAns || leftAns;
}


// Function of delete Node From BST
Node* deleteFromBST(Node* root, int target) {
    // case1.target ko dhundo
    // case2. target ko delete karo

    if(root == NULL) {
        return NULL;
    }

    if(root->data == target) {
        // ab delete karenge
        // 4->case solve karna hai

        //1 case-> leaf node
        if(root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        //2 case-> left non null and right null
       else if(root->left != NULL && root->right == NULL) {
            Node* childSubtree = root->left;
            delete root;
            return childSubtree;
        }
        //3 case-> left me null and right me not null
      else if(root->left == NULL && root->right != NULL) {
            Node* childSubtree = root->right;
            delete root;
            return childSubtree;
        }
        //4 case-> left not null and right not null
        else {
            //a -> left subtree ki max value lao
            Node* maxi = maxValue(root->left);
            // replacement
            root->data = maxi->data;

            // delete actual maxi wali node
            root->left = deleteFromBST(root->left, maxi->data);
            return root;
        }
    }
    else if(root->data > target) {
        // left me chalo
        root->left =  deleteFromBST(root->left, target);
    }
    else {
        // right me chalo
        root->right =  deleteFromBST(root->right, target);
    }
    return root;
}


// Function to create BST from Inorder
Node* bstFromInorder(int inorder[], int s, int e) {
    // base case
    if(s > e) {
        return NULL;
    }

    // ek case ham solve karenge
    int mid = (s+e)/2;
    int element = inorder[mid];
    Node* root = new Node(element);

    // Baaki Recursion shambhal lega
    root->left = bstFromInorder(inorder,s,mid-1);
    root->right = bstFromInorder(inorder,mid+1,e);


  return root;
 
}



// Function to convert BST into Sorted doubly linked list
void convertBSTtoDLL(Node* root, Node* &head) {
    // Base case
    if(root == NULL) {
        return;
    }

    // LNR => RNL karna hai
    //R
    convertBSTtoDLL(root->right, head);

    //N
    //attaching next pointer of current node to head of LL
    root->right = head;
    //attaching prev pointer of head of LL to current node
    if(head != NULL)
    head->left = root;
    // head update
    head = root;

    //L
    convertBSTtoDLL(root->left, head);
}

// function to print linked list
void printLinkedList(Node* head) {
    Node* temp = head;
    cout <<"Printing the entire linkedList" << endl;
    while(temp != NULL) {
        cout << temp->data <<"->";
        temp = temp->right;
    }
    cout << endl;
}



// Function to convert Sorted Doubly linkedList into BST
Node* convertDLLtoBST(Node* &head, int n) {
    // Base case
    if(head == NULL || n<=0) {
        return NULL;
    }

    //LNR (Inorder)
    //L
    Node* leftSubtree = convertDLLtoBST(head, n/2);

    //N
    Node* root = head;
    root->left = leftSubtree;
    // head update
    head = head->right;

    //R
    Node* rightSubtree = convertDLLtoBST(head, n-n/2-1);
    root->right = rightSubtree;
    return root;

}



int main() {

 /*   Node* root = NULL;
    createBST(root);
// 50 30 60 25 40 70 80 55
// -1 to terminate node
    levelOrderTraversal(root); 

    cout << endl << "Inorder: " ;
    inOrder(root);
    cout << endl << "Preorder: ";
    preOrder(root);
    cout << endl << "postorder: ";
    postOrder(root);

    cout << endl;
    Node* minNode = minValue(root);
    if(minNode == NULL) {
        cout <<"There is no node in tree, so no min value"<<endl;

    }else{
        cout <<" Min Value is: "<< minNode->data << endl;
    }


    cout << endl;
    Node* maxNode = maxValue(root);
    if(maxNode == NULL) {
        cout <<" There is no node in tree, so no max value "<< endl;
    }
    else {
        cout <<"Max Value is: "<< maxNode->data << endl;
    }

    cout << endl;

    */

/*
    int t;
    cout <<"Enter the target: "<< endl;
    cin >> t;

    while(t != -1) {
        bool ans = searchInBST(root, t);
        if(ans == true) {
            cout << "Found" << endl;
        }
        else {
            cout <<" Not Found"<< endl;
        }
        
        cout <<"Enter the target: "<<endl;
        cin >> t;
    }

*/

/*
    int target;
    cout << "Enter the value of target: "<< endl;
    cin >> target;

    while(target != -1) {
        root = deleteFromBST(root, target);
        cout << endl <<"Printing the level Order Traversl: "<< endl;
        levelOrderTraversal(root);

        cout <<"enter the value of target: "<< endl;
        cin >> target;
    }


*/

/*

int inorder[] = {10,20,30,40,50,60,70};
int size = 7;
int s = 0;
int e = size-1;

Node* root = bstFromInorder(inorder,s,e);

levelOrderTraversal(root);

Node* head = NULL;
convertBSTtoDLL(root, head);
printLinkedList(head);

*/

Node* first = new Node(10);
Node* second = new Node(20);
Node* third = new Node(30);

first->right = second;
second->left = first;
second->right = third;
third->left = second;

Node* head = first;
//10<->20<->30

Node* root = convertDLLtoBST(head,3);
levelOrderTraversal(root);

    return 0;
}



// Note-> Inorder of a BST is always Sorted