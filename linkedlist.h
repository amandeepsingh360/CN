#include<iostream>
#include<climits>
using namespace std;

class node{
    public:
    int data;
    node *next;
    node(int data){
        this -> data = data;
        this -> next = NULL;
    }
    ~node(){
        if(next) {
            delete next;
        }
    }
};

void print(node *head){
    node *temp = head;
    while(temp != NULL){
        cout<<temp -> data<<" ";
        temp = temp -> next;
    }
    cout<<endl;
}

node* takeinput(){
    int data;
    cin>>data;
    node *head = NULL;
    while(data != -1){
        node *newnode = new node(data); 
        if (head == NULL){
            head = newnode;
        }
        else{
            node *temp = head;
            while(temp -> next != NULL){
                temp = temp -> next;
            }
            temp -> next = newnode;
        }
        cin>>data;
    }
    return head;
}

node* insert(node* head, int i, int data){
    node* newnode = new node(data);
    int count = 0;
    if (i == 0){
        newnode -> next = head;
        return newnode;
    }
    else{
        node* temp = head;
        while(temp != NULL && count < i - 1){
            temp = temp -> next;
            count++;
        }
        if(temp != NULL){
            newnode -> next = temp -> next;
            temp -> next = newnode;
        }
        return head;
    }      
}
node* takeinput_better(){
    int data;
    cin>>data;
    node * head = NULL;
    node * tail = NULL;
    while(data != -1){
        node* newnode = new node(data);
        if (head == NULL){
            head = newnode;
            tail = newnode;
        }
        else{
            node* temp = head;
            tail -> next = newnode;
            tail = tail -> next;  
            //OR
            //tail = newnode; 
        }
        cin>>data;
    }
    return head;
}
