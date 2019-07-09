#include "picosha2.h"
#include <iostream>
#include<cstdlib>
#include<string>
#include<fstream>
using namespace std;

class Transaction{
	public: 
		char Payer[256];
		char Payee[256]; 
		int amount;
};

class Block{
	public:
		Transaction trans[5];
		char prev_hash[256];
		char cur_hash[256];
};

int main(){
	ifstream infile;
	Block input;

	//string previoushash;
	infile.open("BLOCKS.dat", ios::binary | ios::in);
	if(!infile){
		cout << "not open"<<endl;
		return 0;
	}
	infile.read((char*)&input, sizeof(input));

	int j;
	while(!infile.eof()){	
		cout << "BLOCK " << j+1 << endl;
		for(int i = 0; i < 5; i++){
			cout << "Transaction " << i+1 << endl;
			cout << "payer " << i+1 <<" : " << input.trans[i].Payer << endl; 
			cout << "payee " << i+1 <<" : " << input.trans[i].Payee << endl; 
			cout << "Transaction amount: " << input.trans[i].amount << endl;
		}

		cout << "previous hash: " << input.prev_hash << endl;
		cout << "current hash: " << input.cur_hash << endl << endl;

		j++;
		infile.read((char*)&input, sizeof(input));
	}
}