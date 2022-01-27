#include<bits/stdc++.h>
#define nline '\n'
#define ll long long int
#define pn cout<<"NO"<<nline;
#define py cout<<"YES"<<nline;
#define pi 3.141592653589793238
#include"binarytreenode.h"
#include"linkedlist.h"
using namespace std;

binarytreenode<int>*takeinputlevelwise(){
    int rootdata;
    cout<<"Enter root data"<<nline;
    cin>>rootdata;
    if(rootdata==-1){
        return NULL;
    }
    binarytreenode<int> *root = new binarytreenode<int>(rootdata);
    queue<binarytreenode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(!pendingnodes.empty()){
        binarytreenode<int>*front = pendingnodes.front();
        pendingnodes.pop();
        int leftchild;
        cout<<"Enter left child of "<<front->data<<nline;
        cin>>leftchild;
        if(leftchild!=-1){
            binarytreenode<int>* leftnode = new binarytreenode<int>(leftchild);
            front->left = leftnode;
            pendingnodes.push(leftnode);
        } 
        int rightchild;
        cout<<"Enter right child of "<<front->data<<nline;
        cin>>rightchild;
        if(rightchild!=-1){
            binarytreenode<int>* rightnode = new binarytreenode<int>(rightchild);
            front->right = rightnode;
            pendingnodes.push(rightnode);
        } 
    }
    return root;
}

void printlevelwise(binarytreenode<int>*root){
    if(root == NULL){
        return;
    }
    queue<binarytreenode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(!pendingnodes.empty()){
        binarytreenode<int>*front = pendingnodes.front();
        pendingnodes.pop();
        cout<<front->data<<":";
        if(front->left!=NULL){
            cout<<"L:"<<front->left->data<<",";
            pendingnodes.push(front->left);
        }
        else{
            cout<<"L:"<<-1<<",";
        }
        if(front->right!=NULL){
            cout<<"R:"<<front->right->data;
            pendingnodes.push(front->right);
        }
        else{
            cout<<"R:"<<-1;
        }
        cout<<nline;
    }
}

int countnodes(binarytreenode<int>*root){
    if(root == NULL){
        return 0;
    }
    return 1 + countnodes(root->left) + countnodes(root->right);
}

bool isNodePresent(binarytreenode<int>*root, int k){
    if(root == NULL){
        return false;
    }
    if(root->data == k){
        return true;
    }
    if(isNodePresent(root->left, k)){
        return true;
    }
    if(isNodePresent(root->right, k)){
        return true;
    }
    return false;
}

int height(binarytreenode<int>*root){
    if(root == NULL){
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

void mirrortree(binarytreenode<int>*root){
    if(root == NULL){
        return;
    }
    binarytreenode<int>*temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirrortree(root->left); 
    mirrortree(root->right); 
}

void preorder(binarytreenode<int>*root){
    if(root == NULL){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(binarytreenode<int>*root){
    if(root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

binarytreenode<int> *buildTreefrom_pre_in(int *pre, int preS, int preE, int *in, int inS, int inE){
    int rootdata = pre[0];
    int rootindex = 0;
    for(int i = inS; i <= inE; i++){
        if(pre[i] == rootdata){
            rootindex = i;
            break;
        }
    }
    int LinS = inS;
    int LinE = rootindex-1;
    int LpreS = preS+1;
    int LpreE = LpreS + LinE - LinS;
    int RinS = rootindex+1;
    int RinE = inE;
    int RpreS = LpreE + 1;
    int RpreE = preE;
    binarytreenode<int> *root = new binarytreenode<int>(rootdata);
    binarytreenode<int> *leftnode = buildTreefrom_pre_in(pre, LpreS, LpreE, in, LinS, LinE);
    binarytreenode<int> *rightnode = buildTreefrom_pre_in(pre, RpreS, RpreE, in, RpreS, RpreE);
    root->left = leftnode;
    root->right = rightnode;
    return root;
}
binarytreenode<int> *buildTreefrom_pre_in(int *pre, int prelen, int *in, int inlen){
    return buildTreefrom_pre_in(pre, 0, prelen-1, in, 0, inlen-1);
}

binarytreenode<int> *buildTreefrom_post_in(int *post, int postS, int postE, int *in, int inS, int inE){
    int rootdata = post[postE];
    int rootindex = -1;
    for(int i = inS; i<=inE; i++){
        if(in[i] == rootdata){
            rootindex = i;
            break;
        }
    }
    int LpostS = postS;
    int LinS = inS;
    int LinE = rootindex - 1;
    int LpostE = LpostS + LinE - LinS;
    int RinE = inE;
    int RpostE = postE - 1;
    int RpostS = LpostE + 1;
    int RinS = rootindex + 1;
    binarytreenode<int>*root = new binarytreenode<int>(rootdata);
    root->left = buildTreefrom_post_in(post, LpostS, LpostE, in, LinS, LinE);
    root->right = buildTreefrom_post_in(post, RpostS, RpostE, in, RinS, RinE);
    return root;
}
binarytreenode<int> *buildTreefrom_post_in(int *post, int postlen, int *in, int inlen){
    return buildTreefrom_post_in(post, 0, postlen-1, in, 0, inlen-1);
}

int diameter(binarytreenode<int> *root){
    if(root == NULL){
        return 0;
    }
    int option1 = height(root->left) + height(root->right);
    int option2 = diameter(root->left);
    int option3 = diameter(root->right);
    return max(option1,max(option2, option3));
}

pair<int, int> heightDiameter(binarytreenode<int>*root){
    if(root == NULL){
        return {0,0};
    }
    pair<int, int> left = heightDiameter(root->left);
    pair<int, int> right = heightDiameter(root->right);
    int lh = left.first;
    int ld = left.second;
    int rh = right.first;
    int rd = right.second;
    int height = 1 + max(lh,rh);
    int diameter = max(lh+rh,max(ld,rd));
    return {height,diameter};
}

pair<int, int> MinandMax(binarytreenode<int>*root){
    if(root == NULL){
        return {INT_MAX,INT_MIN};
    }
    int minans, maxans;
    pair<int, int> leftnode = MinandMax(root->left);
    pair<int, int> rightnode = MinandMax(root->right);
    minans = min(leftnode.first,min(rightnode.first,root->data));
    maxans = max(leftnode.second,max(rightnode.second,root->data));
    return {minans, maxans};
}

int sumofnodes(binarytreenode<int>*root){
    if(root == NULL){
        return 0;
    }
    return root->data + sumofnodes(root->left) + sumofnodes(root->right);
}

int mod(int a){
    if(a<0){
        return -a;
    }
    else{
        return a;
    }
}

bool isBalanced(binarytreenode<int>*root){
    if(root == NULL){
        return true;
    }
    int balanceFactor = mod(height(root->left)-height(root->right));
    if(balanceFactor > 1){
        return false;
    }
    bool a = isBalanced(root->left);
    bool b = isBalanced(root->right);
    return a & b;
}

void levelorderTraversal(binarytreenode<int>*root){
    if(root == NULL){
        return;
    }
    queue<binarytreenode<int>*> pendingnodes;
    pendingnodes.push(root);
    pendingnodes.push(NULL);
    while(!pendingnodes.empty()){
        binarytreenode<int> *front = pendingnodes.front();
        pendingnodes.pop();
        if(front!=NULL){
            cout<<front->data<<" ";
            if(front->left!=NULL){
                pendingnodes.push(front->left);
            }
            if(front->right!=NULL){
                pendingnodes.push(front->right);
            }
        }
        else{
            if(pendingnodes.empty()){
                break;
            }
            cout<<nline;
            pendingnodes.push(NULL);
        }
    }
}

binarytreenode<int> *removeLeafNodes(binarytreenode<int>*root){
    if(root == NULL){
        return NULL;
    }
    if(root->left == NULL && root->right == NULL){
        return NULL;
    }
    root->left = removeLeafNodes(root->left);
    root->right = removeLeafNodes(root->right);
    return root;
}

vector<node*> constructLinkedListforEachLevel(binarytreenode<int>*root){
    vector<node*> v;
    if(root == NULL){
        v.push_back(NULL);
        return v;
    }
    queue<binarytreenode<int>*> pendingnodes;
    pendingnodes.push(root);
    pendingnodes.push(NULL);
    node*head = NULL;
    node*tail = NULL;
    while(!pendingnodes.empty()){
        binarytreenode<int>*front = pendingnodes.front();
        pendingnodes.pop();
        if(front == NULL){
            v.push_back(head);
            if(pendingnodes.empty()){
                break;
            }
            head = NULL;
            tail = NULL;
            pendingnodes.push(NULL);
        }
        else{
            node *newnode = new node(front->data);
            if(head == NULL){
                head = newnode;
                tail = newnode;
            }
            else{
                tail->next = newnode;
                tail = newnode;
            }
            if(front->left!=NULL){
                pendingnodes.push(front->left);
            }
            if(front->right!=NULL){
                pendingnodes.push(front->right);
            }
        }
    }
    return v;
}

void zigZagOrder(binarytreenode<int>*root){
    if(root == NULL){
        return;
    }
    stack<binarytreenode<int>*> s1;
    s1.push(root);
    stack<binarytreenode<int>*> s2;
    while(!(s1.empty() && s2.empty())){
        while(!s1.empty()){
            binarytreenode<int> *front = s1.top();
            s1.pop();
            cout<<front->data<<" ";
            if(front->left != NULL){
                s2.push(front->left);
            }
            if(front->right != NULL){
                s2.push(front->right);
            }
            if(s1.empty()){
                cout<<nline;
            }
        }
        while(!s2.empty()){
            binarytreenode<int> *front = s2.top();
            s2.pop();
            cout<<front->data<<" ";
            if(front->right != NULL){
                s1.push(front->right);
            }
            if(front->left != NULL){
                s1.push(front->left);
            }
            if(s2.empty()){
                cout<<nline;
            }
        }
    }
} 

void printNodesWithoutSibling(binarytreenode<int>*root){
    if(root == NULL){
        return;
    }
    if(root->left == NULL && root->right != NULL){
        cout<<root->right->data<<" ";
    }
    if(root->left != NULL && root->right == NULL){
        cout<<root->left->data<<" ";
    }
    printNodesWithoutSibling(root->left);
    printNodesWithoutSibling(root->right);
}
// 1 2 3 4 5 6 7 -1 -1 -1 -1 -1 -1 -1 -1
int main(){
    binarytreenode<int>*root = takeinputlevelwise();
    printlevelwise(root);
    cout<<"Number of nodes : "<<countnodes(root)<<nline;
    cout<<"Is 5 present in tree : "<<isNodePresent(root, 5)<<nline;
    cout<<"Height of the tree : "<<height(root)<<nline;
    cout<<"Preorder Traversal : "<<nline;
    preorder(root);
    cout<<nline;
    cout<<"Postorder Traversal : "<<nline;
    postorder(root);
    cout<<nline;
    cout<<"Diameter of the tree is : "<<diameter(root)<<nline;
    cout<<"Optimised Approach to Calculate Diameter & height"<<nline;
    pair<int, int> p = heightDiameter(root);
    cout<<"Height : "<< p.first<<nline;
    cout<<"Diameter : "<< p.second<<nline;
    pair<int, int> pnew = MinandMax(root);
    cout<<"Minimum node : "<<pnew.first<<nline;
    cout<<"Maximum node : "<<pnew.second<<nline;
    cout<<"Sum of Nodes : "<<sumofnodes(root)<<nline;
    cout<<"Is Balanced : "<<isBalanced(root)<<nline;
    cout<<"Level Order Traversal : "<<nline;
    levelorderTraversal(root);   
    cout<<nline;
    cout<<"Level Order Traversal through Linked List : "<<nline;
    vector<node*> v = constructLinkedListforEachLevel(root);
    for(auto i:v){
        print(i);
    }
    cout<<"Print Tree in Zig-Zag Order : "<<nline;
    zigZagOrder(root);
    cout<<nline;
    cout<<"Printing Nodes without Sibling : ";
    printNodesWithoutSibling(root);
    cout<<nline;
    cout<<"After Mirroring the tree"<<nline;
    mirrortree(root);
    printlevelwise(root);
    cout<<nline;
    cout<<"Removing all Leaf nodes...."<<nline;
    binarytreenode<int>* newroot = removeLeafNodes(root);
    printlevelwise(newroot);
    return 0;
}