#include<iostream>
#include <fstream>
#include <string>
#include "compare.h"
using namespace std;
//using std::string;

struct node{
    string data;
    node *next;
};
node *ptr;
node *ptrprev;
node* headm = NULL;
node* headc = NULL;
node* headf = NULL;
node *newptr;
node *fptr;
node *ptrr;

int bothcompare();
node* newNode(string data)
{
    node* new_node = new node;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insertend(string numin,node **head){
    node* new_node = newNode(numin);
    if(*head==NULL){
        *head = new_node;
    }
    else{
        ptr=*head;
        while(ptr->next==NULL){
            ptr=ptr->next;
        }
        ptr->next=new_node;       
    }
}

void instspec(string numin,int po,node **head){
    node* new_node = newNode(numin);
    int i;
    if(*head==NULL){
        cout<<"not possible";
    }
    else{
        ptr=*head;
        while(i<po){
            ptrprev = ptr;
            ptr=ptr->next;
            i++;
        }
        if(ptr==NULL){
            cout<<"invalid position";
        }
        else{
            new_node->next=ptr;
            ptrprev->next=new_node;
        }
    }
}

int newcompare(string prompt){
    string prcname;
    ifstream mainfile("./files/mainfile.txt", ios::in);
    if (!mainfile.is_open()) {
        cerr << "Error opening waitlist.txt" << endl;
        return;
    }
    prcname="./files/"+prompt;
    ifstream checkfile(prcname, ios::in);
    if (!checkfile.is_open()) {
        cerr << "Error opening waitlist.txt" << endl;
        return;
    }
    string line;
    while (getline(checkfile, line)) {
        insertend(line,&headc);
    }
    string linetwo;
    while(getline(mainfile,linetwo)){
        insertend(linetwo,&headm);
    }
    mainfile.close();
    checkfile.close();
    bothcompare();
    return 0;
}

int bothcompare(){
    string que[100],vue[100];
    string found,confirm;
    int glob,guard,checker;
    int mainptg,b[100];
    if(headc==NULL){
        cout<<"nothing to see!";
    }else{
        ptr=headc;
        newptr=headm;
        fptr=headf;
        int iq=0;

        while(ptr->next!=NULL){
            while(newptr->next!=NULL){
                checker=0;
                if(ptr->data!=newptr->data){
                    newptr=newptr->next;
                    iq++;
                }
                else{
                    fptr->data=ptr->data;
                    fptr=fptr->next;
                    int i;
                    while(que[i]!=""){
                        ptrr=headf;
                        node* new_node = newNode(que[i]);
                        new_node->next=headf;
                        headf=new_node;
                        i++;
                    }
                }
            }
            ptr=ptr->next;
        }
    }
    return 0;

}
