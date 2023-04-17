#include<iostream>
#include <fstream>
#include <string>
//#include "compare.h"
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

//comparecpp

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

void newcompare(string prompt){
    string prcname;
    ifstream mainfile("./files/mainfile.txt", ios::in);
    if (!mainfile.is_open()) {
        cerr << "Error opening waitlist.txt" << endl;
        return;
    }
    prcname="./files/forkedfiles/"+prompt;
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
                    vue[iq]=newptr->data;
                    newptr=newptr->next;
                    iq++;
                }
                else{
                    fptr->data=ptr->data;
                    fptr=fptr->next;
                    int ip=0;
                    while(ip<=iq){
                        que[ip]=vue[ip];
                        ip++;
                    }
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
    newptr=headm;
    cout<<"Here's the changes:-\n";
    while(newptr->next!=NULL){
        cout<<newptr->data<<"\n";
        newptr=newptr->next;
    }
    return 0;

}


//maincpp
void normal(int);
void admin(int);
int prefrence(){
    string username,password;
    int answer;
    cout<<"input your username:";
    cin>>username;
    if(username!="admin"){
        cout<<"What do you wanna do?:";
        cout<<"1. Fork\n2. Push/Commit\n:-";
        cin>>answer;
        normal(answer);
    }else{
        cout<<"Enter password:";
        cin>>password;
        if(password=="secretp"){
            cout<<"What do you wanna do?:";
            cout<<"1.Handle\n2. Fork\n3. Push/Commit\n:-";
            cin>>answer;
            admin(answer);
        }
        else{
            cout<<"Wrong password try again!";
            prefrence();
        }
    }
    return 0;
}

void updates(){
    cout<<"Here are recent pull requests...";
    string a[10];
    ifstream waitlistFile("./db/waitlist.txt", ios::in); // Open the waitlist.txt file in the db folder for reading
    if (!waitlistFile.is_open()) {
        cerr << "Error opening waitlist.txt" << endl;
        return;
    }
    string line;
    int lineNumber = 1;
    while (getline(waitlistFile, line)) { // Read the waitlist.txt file line by line
        cout << lineNumber << ". " << line << endl; // Display the line number and the line
        a[lineNumber-1]=line;
        lineNumber++;
    }
    waitlistFile.close();

    int option;string prompt;
    cout<<"Which one would you like me to display changes for you?";
    cin>>option;
    prompt=a[option-1];
    newcompare(prompt);
}

void fork(string filename){
    string nametake,customname,srcname;
    cout<<"Write name of the file you want for yourself";
    cin>>nametake;
    customname="./files/forkedfiles/"+nametake+".txt";
    srcname="./files/"+filename+".txt";
    //read and append and make new file
    ifstream sourceFile(srcname, ios::in); // Open the source file for reading
    if (!sourceFile.is_open()) {
        cerr << "Error opening source file: " << srcname << endl;
        return;
    }

    ofstream destinationFile(customname, ios::out | ios::app); // Open the destination file for appending
    if (!destinationFile.is_open()) {
        cerr << "Error opening destination file: " << customname << endl;
        sourceFile.close();
        return;
    }

    string line;
    while (getline(sourceFile, line)) { // Read the source file line by line
        destinationFile << line << endl; // Append each line to the destination file
    }

    sourceFile.close();
    destinationFile.close();
    prefrence();
}

void waitlist(const string& srcName) {
    ofstream waitlistFile("./db/waitlist.txt", ios::out | ios::app); // Open the waitlist.txt file for appending
    if (!waitlistFile.is_open()) {
        cerr << "Error opening waitlist.txt" << endl;
        return;
    }

    waitlistFile << srcName << endl; // Append the srcName to the waitlist.txt file in a new line
    waitlistFile.close();
}

void commit(string filename){
    string srcname;
    srcname=filename+".txt";
    waitlist(srcname);
    cout<<"Pull request made successfully....";
    prefrence();
}

void normal(int ans){
string filename;
if(ans==1||ans==2){cout<<"Emter filename:";cin>>filename;}
switch(ans){
    case 1: fork(filename); break;
    case 2: commit(filename); break;
    default: cout<<"Wrong option selected try again!";prefrence(); break;
}
}

void admin(int ans){
string filename;
if(ans==3||ans==2){cout<<"Emter filename:";cin>>filename;}
switch(ans){
    case 1: updates(); break;
    case 2: fork(filename); break;
    case 3: commit(filename); break;
    default: cout<<"Wrong option selected try again!";prefrence(); break;
}
}



int main(){
    cout<<"runnin...";
    prefrence();
}