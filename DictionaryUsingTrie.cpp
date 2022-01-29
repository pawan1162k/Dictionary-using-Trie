#include<iostream>
#include <windows.h>
#include<bits/stdc++.h>
using namespace std;

struct TrieNode{
    bool end;
    struct TrieNode*next[26];
    vector<string> meaning;
    TrieNode(){
        end=false;
        for(int i=0;i<26;i++){
            next[i]=NULL;
        }
    }
};

void insert(TrieNode*root,string key,string mean){
    int i=0;
    TrieNode*temp=root;
    int n=key.size();
    while(i<n){
        if(temp->next[key[i]-'a']==NULL){
            temp->next[key[i]-'a']=new TrieNode();
        }
        temp=temp->next[key[i]-'a'];
        i++;
    }
    temp->meaning.push_back(mean);
    temp->end=true;
}

void displayAll(TrieNode*root,string s){
    if(root==NULL){
        return;
    }
    if(root->end==true){
        cout<<s<<"->";
        int i=0;
        for(auto z=root->meaning.begin();z!=root->meaning.end();z++){
            cout<<i<<". "<<*z<<endl;
            i++;
        }
    }
    for(int i=0;i<26;i++){
        displayAll(root->next[i],s+char(i+'a'));
    }
}


void display(TrieNode*root,string s,int &count){
    if(root==NULL || count==3){
        return;
    }
    if(root->end==true){
        cout<<s<<"->";
        int i=0;
        for(auto z=root->meaning.begin();z!=root->meaning.end();z++){
            cout<<i<<". "<<*z<<endl;
            i++;
        }
        count++;
    }
    for(int i=0;i<26;i++){
        if(root->next[i]!=NULL && count<3){
            display(root->next[i],s+char(i+'a'),count);
        }
    }
    return;
}

void suggest(string searchWord,TrieNode*root) {
    string s="";
    for(int i=0;i<searchWord.length();i++){
        s+=searchWord[i];
        if(root!=NULL){
            int count=0;
            root=root->next[searchWord[i]-'a'];
        }
    }
    int count=0;
    display(root,s,count);
    return;
}

int main(){
    HANDLE console_color;
    console_color=GetStdHandle(STD_OUTPUT_HANDLE);
    TrieNode*root=new TrieNode();
    int flag=true;
    while(flag){
        int choice=0;   
        SetConsoleTextAttribute(console_color, 11);
        cout<<"-----------------------------------------------"<<endl;
        SetConsoleTextAttribute(console_color, 10);
        cout<<"1."<<" Search word"<<endl;
        cout<<"2."<<" Insert word"<<endl;
        cout<<"3."<<" Display all words in dictionary"<<endl;
        cout<<"4."<<" Exit"<<endl;
        SetConsoleTextAttribute(console_color, 11);
        cout<<"-----------------------------------------------"<<endl;
        SetConsoleTextAttribute(console_color, 7);

        cin>>choice;
        switch(choice){
            case 1:
            {
                string wor;
                cin>>wor;
                suggest(wor,root);
                break;
            }
            case 2:
            {
                for(int i=0;i<10;i++){
                    string s;
                    string m;
                    cout<<"Enter the word: -";
                    cin>>s;
                    cout<<endl;
                    cout<<"Enter the meaning that word: -";
                    cin>>m;
                    cout<<endl;
                    TrieNode*t1=root;
                    insert(t1,s,m);
                }
                break;
            }
            case 3:
            {
                TrieNode*t2=root;
                displayAll(t2,"");
            }
            default:
            {
                exit(0);
                flag=0;
            }
        }
    }
    
    return 0;
}