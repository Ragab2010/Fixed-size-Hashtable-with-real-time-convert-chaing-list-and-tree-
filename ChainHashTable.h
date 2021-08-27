/*
 * ChainHashTable.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ENG.HamaDa
 */

#ifndef CHAINHASHTABLE_H_
#define CHAINHASHTABLE_H_
#include  <list>
#include <iostream>
#include "HashTable.h"



template <typename T>
class ChainHashTable{
public:
	enum{lazy_deleted =-1 ,empty =0  ,hold};
	enum{LIST =0 ,BSTT};
	class BST{
	public:
	    T key;
	      BST *left, *right;
	};

	class HashTableEntry{
	public:
		unsigned int m_flag ;
		unsigned int m_flag_list_BST;
		std::list<T> head;
		 BST *head_BST;
		unsigned int size_BST;

	};


	HashTableEntry *m_table;
	unsigned int size_of_hashtable;

 	/*****************the main Method prototype***********************/
 	//constructor
 	ChainHashTable(unsigned int (*hashFunc)(const int &data , unsigned int &size), unsigned int n=101);
     bool insert(const T &data);//insert data to Hashtable
     bool find(const T &data) ;//find data in Hashtable of no
     bool remove(const T &data);//remove element from hashtable
     void dump();//print all the information (size , data) for hashtable
     int at(int index, std::vector<T> &contents);//copy BST or List into vector
 	/****************************************************************/


    unsigned int (*hashFunc)(const int &data , unsigned int &size);

	//ChainHashTable(unsigned int (*hashFunc)(const int &data , unsigned int &size), unsigned int n=101);

	void hashTableInitalize(unsigned int (*hashFun)(const int &data , unsigned int &size), unsigned int n);





     void convertBstToList(BST* head, int index );

     int sizeoftree(BST* root);
     /*preorder*/
     void retrive( BST* head);

     void retrive( BST* head , int index );

     /*find*/
     bool find(BST* root ,int data);


     bool remove(BST* head);

     bool remove( BST* head ,BST** above_root,int data ,int index);

     void insert( BST** head,   BST* node);

     bool convertListToBst(unsigned int index);



    ~ChainHashTable();
};//class



template <typename T>
ChainHashTable<T>::ChainHashTable(unsigned int (*hashFunc)(const int &data , unsigned int &size), unsigned int n){
		this->size_of_hashtable =n;
		this->m_table = new HashTableEntry[n];
		this->hashFunc=hashFunc;
		for (unsigned int i = 0; i < n; ++i) {
			(m_table+i)->m_flag=0;
			(m_table+i)->m_flag_list_BST =LIST;
			(m_table+i)->head_BST =NULL;
			(m_table+i)->size_BST =0;
		}
	}

template <typename T>
	void ChainHashTable<T>::hashTableInitalize(unsigned int (*hashFun)(const int &data , unsigned int &size), unsigned int n){
		this->size_of_hashtable =n;
		this->m_table = new HashTableEntry[n];
		this->hashFunc=hashFunc;
		for (unsigned int i = 0; i < n; ++i) {
			(m_table+i)->m_flag=0;
			(m_table+i)->m_flag_list_BST =LIST;
			(m_table+i)->head_BST =NULL;
			(m_table+i)->size_BST =0;
		}
	}

    // Functions in a standard hash table interface,
    // independent of implementation:
template <typename T>
     bool ChainHashTable<T>::insert(const T &data){
	 typename std::list<T>::iterator it;
    	 unsigned int i = hashFunc(data, size_of_hashtable);
    	 if ((((m_table+i)->head.size()) <=11) && ((m_table+i)->m_flag_list_BST ==LIST)){
    		 //(m_table+i)->m_flag_list_BST =LIST;
        	 if((i < size_of_hashtable )&&(this->find(data) != true)){
        		 (m_table+i)->m_flag=hold;
            	 (m_table+i)->head.push_back(data);
            	 return true;

        	 }else{// i if
        		 return false;
        	 }//else if

    	 }
    	 else if ((((m_table+i)->head.size()) >11) && ((m_table+i)->m_flag_list_BST ==LIST)){//size if
    		 (m_table+i)->m_flag_list_BST = BSTT;
    		 convertListToBst(i);
    		 BST *temp =new  BST;
    		 temp->key =data;
    		 temp->left =NULL;
    		 temp->right =NULL;
    		 insert(&((m_table+i)->head_BST),temp);
    		 (m_table+i)->size_BST++;
    		 /*******remove the list*******/
    		 (m_table+i)->head.clear();
    		 (m_table+i)->m_flag =empty;
    		 return true ;

    	 }
    	 else if((((m_table+i)->head.size()) >11) && ((m_table+i)->m_flag_list_BST ==BSTT)){
    		 //(m_table+i)->m_flag_list_BST =BST;
    		 BST *temp =new  BST;
    		 temp->key =data;
    		 temp->left =NULL;
    		 temp->right =NULL;
			insert(&((m_table+i)->head_BST),temp);
			(m_table+i)->size_BST++;
			return true;
    	 }
    	 else{
    	 	 return false;
    	 }
     }

template <typename T>
     bool ChainHashTable<T>::find(const T &data) {
		typename std::list<T>::iterator it;
    	 unsigned int i = hashFunc(data, size_of_hashtable);
    	 if((m_table)->m_flag_list_BST ==LIST){
			 if((i < size_of_hashtable) && ((m_table+i)->m_flag == hold)){
				 for (it=(m_table+i)->head.begin() ; it != (m_table+i)->head.end() ;++it ) {
					if(*it == data){
						return true;
					}
				}//for

			 } //IF LINKEDLIST

    	 }else{//tree;
    		 /***********************/
    		 return (find( (m_table+i)->head_BST, data));
    	 }

    		 return false;

     }

template <typename T>
     bool ChainHashTable<T>::remove(const T &data){
		bool found;
    	 unsigned int i = hashFunc(data, size_of_hashtable);
    	 if((m_table+i)->m_flag_list_BST ==LIST){
        	 found =this->find(data);
        	 if(found == true){
            	 (m_table+i)->head.remove(data);
            	 if((m_table+i)->head.size()  == 0){
            		 (m_table+i)->m_flag =lazy_deleted;
            	 }
            	 return true;
        	 }else{
        		 return false;
        	 }
    	 }else{
    		 /********************/
    		 found =this->find((m_table+i)->head_BST,data);
    		 if(found ==true){
    			 remove( (m_table+i)->head_BST ,&(m_table+i)->head_BST , data , i);
    			 (m_table+i)->size_BST--;
    			 if((m_table+i)->size_BST < 8){
   				 convertBstToList((m_table+i)->head_BST , i );
    				 (m_table+i)->size_BST=0;
    				 (m_table+i)->m_flag_list_BST=LIST;
    				 return true;
    			 }
    		 }
    	 }


    	 return false;
     }

    // Functions for debugging and grading:
template <typename T>
     void ChainHashTable<T>::dump(){
    	 std::list<int>::iterator it;
    	 std::cout<<"ChainHashTable dump; size:" <<size_of_hashtable <<" buckets"<<std::endl;

    	 for (unsigned int i = 0; i < size_of_hashtable; ++i) {
    		 std::cout<<"["<< i<<"]:";
    		 if((m_table+i)->m_flag_list_BST == BSTT){
    			 retrive(((m_table+i)->head_BST));
    			 std::cout<<" BST"<<std::endl;

    		 }else{
        		 for (it=(m_table+i)->head.begin() ; it != (m_table+i)->head.end() ;++it ) {
        			 std::cout<<*it<<" , ";
    			}
        		 std::cout<<" List"<<std::endl;
    		 }
		}//for hastable
     }

template <typename T>
     int ChainHashTable<T>::at(int index, std::vector<T> &contents) {
    	 std::list<int>::iterator it;
    	 if((index < 0) ||((unsigned int)index > size_of_hashtable)){
    		  throw std::out_of_range("the index it out of rang of Hashtable");
    		  return false;
    	 }
    	 for (it=(m_table+index)->head.begin() ; it != (m_table+index)->head.end() ;++it ){
    		 contents.push_back(*it);
    	 }
    	 return (m_table+index)->head.size();

     }

template <typename T>
int ChainHashTable<T>::sizeoftree(BST* root){
	if(root == NULL)
		return 0;
	else
		return (sizeoftree(root->left)+ 1 +sizeoftree(root->right));
}
template <typename T>
void ChainHashTable<T>::convertBstToList(BST* head, int index ){

    if (head == NULL){
   	 return ;
    }
     convertBstToList(head->left , index);
     convertBstToList(head->right ,index);
     if(head != NULL)
   	  (m_table + index)->head.push_front(head->key);
     delete head;
     //return true;
}



template <typename T>
void ChainHashTable<T>::retrive( BST* head){
    if (head){
   	 std::cout<<head->key<<" , ";
    }else{
   	 return;
    }
     retrive(head->left);
     retrive(head->right);
}


template <typename T>
void ChainHashTable<T>::retrive( BST* head , int index ){
    if (head){
		 BST *temp =new  BST;
		 temp->key =head->key;
		 temp->left =NULL;
		 temp->right =NULL;
		 insert( &((m_table+index)->head_BST) , temp);
    }else{
   	 return;
    }
     retrive(head->left);
     retrive(head->right);


}


template <typename T>
bool ChainHashTable<T>::find(BST* root ,int data){
	 if(root != NULL){
   	 if(root->key == data){
   		 return true;
   	 }

	 }else{
		 return false;
	 }


	 if(data < root->key){
		// std::cout<<"data<key= "<<root->key<<std::endl;
		 find(root->left , data);
	 }

	 else if(data > root->key){
		// std::cout<<"data>key= "<<root->key<<std::endl;
		 find(root->right , data);
	 }


}


template <typename T>
bool ChainHashTable<T>::remove(BST* head){
	 if(head == NULL)
		 return true;
	 if(head != NULL){
		 remove(head->left);
	 }
	 if(head != NULL){
   	 remove(head->right);
	 }
	 delete head;

	 return true;
}


template <typename T>
bool ChainHashTable<T>::remove( BST* head ,BST** above_root,int data ,int index){
         if(data == head->key ){
         	BST* temp;
         	if (((head->left) == NULL) && ((head->right) == NULL)){
         		(*above_root)->left =(*above_root)->right=NULL;
         		delete head;
         	}

 			else if((head->left != NULL) && (head->right == NULL)){
 				(*above_root)->left =head->left;
 				delete head;
 			}
 			else if((head->left == NULL) && (head->right != NULL)){
 				(*above_root)->right =head->right;
 				delete head;
 			}
 			else if((head->left != NULL) && (head->right != NULL)){
 				temp = head->left;
 				(*above_root)->right = head->right;
 				delete head;
 				retrive(temp , index);
 				remove(temp);
 			}

 			return true;

        }// if head->key == data

         if (data < head->key)
        	 remove(head->left,&head ,data , index);
         else if (data > head->key)
        	 remove(head->right ,&head,data , index);


     }


template <typename T>
void ChainHashTable<T>::insert( BST** head,   BST* node){
         /* If the tree is empty, return a new node */
         if ((*head) == NULL){
        	 (*head) =node;
        	return ;
         }else{
              if (node->key < ((*head))->key)
                  insert(&(*head)->left, node);
              else if (node->key > (*head)->key)
                  insert(&(*head)->right, node);
         }



}


template <typename T>
bool ChainHashTable<T>::convertListToBst(unsigned int index){
	 typename std::list<T>::iterator it;
	 BST* temp;
	 for (it=(m_table+index)->head.begin() ; it != (m_table+index)->head.end() ;++it ){
		 temp = new BST;
		 temp->key =*it;
		 temp->left =NULL;
		 temp->right =NULL;
		 insert( &((m_table+index)->head_BST), temp);
		 (m_table+index)->size_BST++;

	 }
	 return true;
}

     template <typename T>
     ChainHashTable<T>::~ChainHashTable(){
    	for (unsigned int i = 0; i <size_of_hashtable ; ++i) {
    		if((m_table+i)->m_flag_list_BST == LIST){
    			if((m_table+i)->m_flag){
    				(m_table+i)->head.clear();
    			}
    		}//LIST
    		else{
    			remove((m_table+i)->head_BST);
    			(m_table+i)->size_BST=0;
    		}

		}
    	delete [] m_table;
    }


#endif /* CHAINHASHTABLE_H_ */
