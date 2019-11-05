#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void ReadFile(string s);
void Change(string s1, string s2);
int main(){
    ReadFile("ff.txt");
    Change("ff.txt", "ff2.txt");
    ReadFile("ff2.txt");

    return 0;
}

void ReadFile(string s){
    ifstream fin(s);
    if(!fin){
        cerr << "Could not open " << s << endl;
        exit(EXIT_FAILURE);
    }

    char data;
    fin.get(data);
    while(!fin.eof()){
        cout << data;
        fin.get(data);
    }
    fin.close();
}

void Change(string s1, string s2){
    ifstream fin(s1);
    ofstream fout(s2);
    if(!fin){
        cerr << "Could not open " << s1 << endl;
        exit(EXIT_FAILURE);
    }
    if(!fout){
        cerr << "Could not open " << s2 << endl;
        exit(EXIT_FAILURE);
    }
    char data;
    fin.get(data);
    while(!fin.eof()){
        fout << data;
        fin.get(data);
    }
    fin.close();
    fout.close();
}