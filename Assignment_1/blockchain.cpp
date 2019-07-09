#include "picosha2.h"
#include <iostream>
#include<cstdlib>
#include<string>
#include<fstream>
using namespace std;
using namespace picosha2;

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

string prevhash(){
	ifstream infile;
	Block input;

	string previoushash;
	infile.open("BLOCKS.dat", ios::binary | ios::in);
	if(!infile){
		cout << "not open"<<endl;
	}
	infile.read((char*)&input, sizeof(input));

	while(!infile.eof()){	
		infile.read((char*)&input, sizeof(input));

	}
	previoushash = input.cur_hash;

	infile.close();

	return previoushash;
}

void outputBlock(Block object2){
	ofstream outputFile; 
	outputFile.open("BLOCKS.dat",ios::binary | ios::app);
	outputFile.write((char*)&object2, sizeof(Block));
	outputFile.close();
	return;
}


void createBlock(){

	Block b;
	
	for(int i = 0; i < 5; i++){
		string payer, payee;
		cout << "Enter name of payer " << i+1 << std:: endl;
		
		cin >> payer;
		payer = hash256_hex_string(payer);
		// cout << payer << endl;
		for(int j=0; j < payer.length(); j++)
			b.trans[i].Payer[j] = payer[j];
		b.trans[i].Payer[payer.length()] = '\0';
		cout << "Enter name of payee " << i+1 << std:: endl;
		
		cin >> payee;
		payee = hash256_hex_string(payee);
		for(int j=0; j < payee.length(); j++)
			b.trans[i].Payee[j] = payee[j];
		b.trans[i].Payee[payee.length()] = '\0';
		cout << "Enter amount to be transacted " << std:: endl;
		cin >> b.trans[i].amount;
	}

	string temp1 = prevhash();
	for(int i=0; i < temp1.length(); i++)
		b.prev_hash[i] = temp1[i];
	b.prev_hash[temp1.length()] = '\0';
	
	string data;

	for(int i = 0; i < 5; i++){
		string dat;
		dat = b.trans[i].Payer;
		data = data + dat;
	}
	for(int i = 0; i < 5; i++){
		data = data + to_string(b.trans[i].amount);
	}
	for(int i = 0; i < 5; i++){
		string dat;
		dat = b.trans[i].Payee;
		data = data + dat;
	}
	string dat;
	dat = b.prev_hash;
	data = data + dat;
	// cout << data << endl;
	
	string temp2 = hash256_hex_string(data);
	for(int i=0; i < temp2.length(); i++)
		b.cur_hash[i] = temp2[i];

	b.cur_hash[temp2.length()] = '\0';
	// cout << b.cur_hash << endl;

	outputBlock(b);
	return;
}

int main(){

	createBlock();
	
	return 0;
}


