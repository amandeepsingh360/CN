#include<bits/stdc++.h>
#define nline '\n'
#define ll long long int
#define pn cout<<"NO"<<nline;
#define py cout<<"YES"<<nline;
#define pi 3.141592653589793238
#include"treenode.h"
using namespace std;

treenode<int>*takeinputlevelwise(){
    int rootdata;
    cout<<"Enter root data"<<nline;
    cin>>rootdata;
    treenode<int> *root= new treenode<int>(rootdata);
    queue<treenode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(!pendingnodes.empty()){
        treenode<int> *front = pendingnodes.front();
        pendingnodes.pop();
        int n;
        cout<<"Enter number of child for "<<front->data<<nline;
        cin>>n;
        for(int i = 0; i < n; i++){
            int childdata;
            cout<<"Enter "<<i<<"th child of "<<front->data<<nline;
            cin>>childdata;
            treenode<int> *child= new treenode<int>(childdata);
            front->children.push_back(child);
            pendingnodes.push(child);
        }
    }
    return root;
}

void printlevelwise(treenode<int>*root){
    if(root == NULL){
        return;
    }
    queue<treenode<int>*> pendingnodes;
    pendingnodes.push(root);
    while(!pendingnodes.empty()){
        treenode<int>* front = pendingnodes.front();
        cout<<front->data<<":";
        pendingnodes.pop();
        int size = front->children.size();
        for(int i = 0; i < size - 1; i++){
            cout<<front->children[i]->data<<",";
            pendingnodes.push(front->children[i]);
        }
        int i = size;
        if(i > 0){
            cout<<front->children[i-1]->data;
            pendingnodes.push(front->children[i-1]);
        }
        cout<<nline;
    }
}

int countnodes(treenode<int>*root){
    int count = 0;
    for(int i = 0; i < root->children.size(); i++){
        count+=countnodes(root->children[i]);
    }
    return 1+count;
}

int sumofnodes(treenode<int>*root){
    if(root==NULL){
        return 0;
    }
    int sum = 0;
    for(int i = 0; i < root->children.size(); i++){
        sum+=sumofnodes(root->children[i]);
    }
    return root->data+sum;
}

int maxdatanode(treenode<int> *root){
    if(root==NULL){
        return 0;
    }
    int max = root->data;
    for(int i = 0; i < root->children.size(); i++){
        if(maxdatanode(root->children[i])>max){
            max = maxdatanode(root->children[i]);
        }
    }
    return max;
}

int height(treenode<int> *root){
    if(root==NULL){
        return 0;
    }
    int maxheight = 0;
    for(int i = 0; i < root->children.size(); i++){
        if(height(root->children[i]) > maxheight){
            maxheight = height(root->children[i]);
        }
    }
    return maxheight+1;
}

void printatlevelK(treenode<int> *root, int k){
    if(root==NULL){
        return;
    }
    if(k==0){
        cout<<root->data<<" ";
    }
    for(int i = 0; i < root->children.size(); i++){
        printatlevelK(root->children[i],k-1);
    }
}

int getLeafNodeCount(treenode<int>*root){
    if(root==NULL){
        return 0;
    }
    if(root->children.size()==0){
        return 1;
    }
    int sum = 0;
    for(int i = 0; i < root->children.size(); i++){
        sum+=getLeafNodeCount(root->children[i]);
    }
    return sum;
}

void preorder(treenode<int> *root){
    if(root == NULL){
        return;
    }
    cout<<root->data<<" ";
    for(int i = 0; i < root->children.size(); i++){
        preorder(root->children[i]);
    }
}

void postorder(treenode<int> *root){
    if(root== NULL){
        return;
    }
    for(int i = 0; i < root->children.size(); i++){
        postorder(root->children[i]);
    }
    cout<<root->data<<" ";
}

bool isPresent(treenode<int> *root, int x){
    if(root==NULL){
        return false;
    }
    if(root->data == x){
        return true;
    }
    for(int i = 0; i < root->children.size(); i++){
        if(isPresent(root->children[i],x)){
            return true;
        }
    }
    return false;
}

int getcountofNodesGreaterThanX(treenode<int>*root, int x){
    if(root == NULL){
        return 0;
    }
    int ans = 0;
    if(root->data>x){
        ans++;
    }
    for(int i = 0; i < root->children.size(); i++){
        ans+=getcountofNodesGreaterThanX(root->children[i],x);
    }
    return ans;
}

pair<int, int> getMaxChildSumNode(treenode<int>*root){
    if(root == NULL){
        return {0,0};
    }
    int maxsum = 0, max = root->data;
    for(int i = 0; i < root->children.size(); i++){
        maxsum+=root->children[i]->data;
    }
    for(int i = 0; i < root->children.size(); i++){
        pair<int, int> p = getMaxChildSumNode(root->children[i]);
        if(p.first>maxsum){
            maxsum = p.first;
            max = p.second; 
        }
    }
    pair<int, int> p = {maxsum,max};
    return p;
} 

bool structurallyIdentical(treenode<int> *root1, treenode<int>*root2){
    if(root1==NULL||root2==NULL){
        return false;
    }
    if(root1->data != root2->data){
        return false;
    }
    if(root1->children.size() != root2->children.size()){
        return false;
    }
    for(int i = 0; i < root1->children.size(); i++){
        if(root1->children[i]->data != root2->children[i]->data){
            return false;
        }
    }
    return true;
}

treenode<int> *nextLargerElement(treenode<int>*root, int x){
    treenode<int>*ans = NULL;
    if(root->data>x){
        ans = root;
    }
    for(int i = 0; i < root->children.size(); i++){
        treenode<int> *temp = nextLargerElement(root->children[i], x);
        if(temp!=NULL){
            if(ans!=NULL){
                if(temp->data>ans->data){
                    ans = temp;
                }
            }
            else{
                ans = temp;
            }
        }
    }
    return ans;
}

void helper(priority_queue<pair<int,treenode<int>*>> &arr, treenode<int>*root){
    if(root == NULL){
        return;
    }
    for(int i = 0; i < root->children.size(); i++){
        helper(arr,root->children[i]);
    } 
    arr.push({root->data,root});
}

treenode<int> *getSecondLargestNode(treenode<int>*root){
    if(root == NULL){
        return NULL;
    }
    priority_queue<pair<int, treenode<int>*>> arr;
    helper(arr,root);
    int temp = arr.top().first;
    while((arr.top()).first==temp){
        arr.pop();
    }
    return (arr.top()).second;
}

void replacehelper(treenode<int>*root, int depth){
    if(root == NULL){
        return;
    }
    root->data = depth;
    for(int i = 0; i < root->children.size(); i++){
        replacehelper(root->children[i],depth+1);
    }
}
void replacewithdepth(treenode<int>*root){
    replacehelper(root,0);
}
int main(){
    treenode<int>*root = takeinputlevelwise();
    printlevelwise(root);
    cout<<"Number of Nodes : "<<countnodes(root)<<nline;
    cout<<"Sum of Nodes : "<<sumofnodes(root)<<nline;
    cout<<"Maximum Data of node : "<<maxdatanode(root)<<nline;
    cout<<"Height of the tree : "<<height(root)<<nline;
    cout<<"Print tree at depth 1\n";
    printatlevelK(root,1);
    cout<<nline;
    cout<<"Number of leaf nodes : "<<getLeafNodeCount(root)<<nline;
    cout<<"Pre-Order Traversal : \n";
    preorder(root);
    cout<<nline;
    cout<<"Post-Order Traversal : \n";
    postorder(root);
    cout<<nline;
    cout<<"6 present ot not : "<<isPresent(root,6)<<nline;
    cout<<"Number of nodes which have count greater than 3"<<getcountofNodesGreaterThanX(root,3)<<nline;
    pair<int,int> p = getMaxChildSumNode(root);
    cout<<"Maximum Child Sum Node : "<<p.second<<nline;
    // cout<<"Compare both Trees"<<structurallyIdentical(root,takeinputlevelwise())<<nline;
    cout<<"Next larger element after 3 : "<<nextLargerElement(root,3)->data<<nline;
    cout<<"Second Largest Node : "<<getSecondLargestNode(root)->data<<nline;
    replacewithdepth(root);
    cout<<"Printing tree after replacing elements with depth\n";
    printlevelwise(root);
    return 0;
}