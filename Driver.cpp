/*
 * Driver.cpp
 *
 *  Created on: ??þ/??þ/????
 *      Author: ENG.HamaDa
 */

#include <iostream>
#include "ChainHashTable.h"


using namespace std;

unsigned int hasing(const int &data ,  unsigned int &size) {
    return (int) data%size;
}

/*****************the main Method prototype***********************/
//constructor
/*
	ChainHashTable(unsigned int (*hashFunc)(const int &data , unsigned int &size), unsigned int n=101);
	bool insert(const T &data);//insert data to Hashtable
	bool find(const T &data) ;//find data in Hashtable of no
	bool remove(const T &data);//remove element from hashtable
	void dump();//print all the information (size , data) for hashtable
	int at(int index, std::vector<T> &contents);//copy BST or List into vector */
/****************************************************************/

int main(){

	ChainHashTable<int> ahmed(hasing , 10);
	ahmed.insert(1);
	ahmed.insert(11);
	ahmed.insert(21);
	ahmed.insert(31);
	ahmed.insert(41);
	ahmed.insert(51);
	ahmed.insert(61);
	ahmed.insert(71);
	ahmed.insert(81);
	ahmed.insert(91);
	ahmed.insert(101);
	/*now print the infromation*/
	cout<<"--------------------------------------------------------"<<endl;
	ahmed.dump();
	ahmed.insert(121);//12 element will convert to BST
	/*now the list is convert to BST*/
	ahmed.insert(131);
	ahmed.insert(141);
	/*now print the infromation and will show that's the hastable index 1 is converted to BST*/
	cout<<"--------------------------------------------------------"<<endl;
	ahmed.dump();
	/*we will remove  5 element from BST and see will it  convert again to linkedlist*/
	ahmed.remove(91 );
	ahmed.remove(81);
	ahmed.remove(101 );
	ahmed.remove(121 );
	ahmed.remove(131 );
	cout<<"--------------------------------------------------------"<<endl;
	/*show the information about the hastable*/
	ahmed.dump();






	//ahmed.dump();


	return 0;
}
