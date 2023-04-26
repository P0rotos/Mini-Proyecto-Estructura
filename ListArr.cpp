#include<iostream>
#include<cmath>
#include "ListArr.h"
using namespace std;
template<typename T>
void ListArr<T>::DTree(ResumeNode* RN){
    if(RN->LeftR != nullptr){
        DTree(RN->LeftR);
    }
    if(RN->RigthR != nullptr){
        DTree(RN->RigthR);
    }
    delete RN->RigthR;
    delete RN->LeftR;
}
template<typename T>
void ListArr<T>::CTree(){
    Node* First;
    ResumeNode* temp = Head;
    while(temp->Left == nullptr){
        temp = temp->LeftR;
    }
    First = temp->Left;
    DTree(Head);
    Node* current = First;
    int count = 0;
    while(current != nullptr){
        count++;
        current = current->next;
    }
    if (count == 0){
        count = 1;
    }else{
        count = (int)((log2(count))+1);
    }
    CTreehelp(Head, count);
    temp = CTreeFreeRN(Head);
    while(First != nullptr){
        if (temp->Right != nullptr){
            temp = CTreeFreeRN(Head);
        }else{
            if (temp->Left == nullptr){
                temp->Left = First;
                First = First->next;
            }else{
                temp->Rigth = First;
                First = First->next;
            }
        }
    }
    CTreeAsign(Head);
}
template<typename T>
void ListArr<T>::CTreehelp(ResumeNode* RN, int i){
    if (i>1){
        ResumeNode* R = new ResumeNode();
        ResumeNode* L = new ResumeNode();
        RN->RigthR = R;
        RN->LeftR = L;
        CTreeHelp(R, i--);
        CTreeHelp(L, i--);
    }
}
template<typename T>
ListArr<T>::ResumeNode* ListArr<T>::CTreeFreeRN(ResumeNode* RN){
    ResumeNode* temp;
    if (RN->LeftR != nullptr){
        temp = CTreeFreeRN(RN->LeftR);
        if (temp != nullptr){
            return(temp);
        }
    }
    if (RN->RigthR != nullptr){
        temp = CTreeFreeRN(RN->RigthR);
        if (temp != nullptr){
            return(temp);
        }
    }
    if (RN->Right == nullptr && RN->RigthR == nullptr){
        return(RN);
    }else{
        return(nullptr);
    }
}
template<typename T>
void ListArr<T>::CTreeAsign(ResumeNode* RN){
    if (RN->usado == 0 && RN->RigthR != nullptr){
        CTreeAsign(RN->LeftR);
        CTreeAsign(RN->RigthR);
    }
    if (RN->Left != nullptr){
        RN->usado == RN->usado + RN->Left->usado;
        RN->capacidad == RN->capacidad + RN->Left->capacidad;
    }
    if (RN->Rigth != nullptr){
        RN->usado == RN->usado + RN->Rigth->usado;
        RN->capacidad == RN->capacidad + RN->Rigth->capacidad;
    }    
    if (RN->LeftR != nullptr){
        RN->usado == RN->usado + RN->LeftR->usado;
        RN->capacidad == RN->capacidad + RN->LeftR->capacidad;
    }
    if (RN->RigthR != nullptr){
        RN->usado == RN->usado + RN->RigthR->usado;
        RN->capacidad == RN->capacidad + RN->RigthR->capacidad;
    }
    
}
template<typename T>
ListArr<T>::ListArr(int capacity){
    this->capacity = capacity;
    Head = new Resumenode();
    Node* Nuevo = new Node(capacity);
    Head->Left = Nuevo;
}
template<typename T>
ListArr<T>::~ListArr(){
    Node* current;
    ResumeNode* temp = Head;
    while(temp->Left == nullptr){
        temp = temp->LeftR;
    }
    current = temp->Left;
    DTree(Head);
    delete Head;
    while (current != nullptr){
		Node* next = current->next;
		delete current;
		current = next;
    }
}
template<typename T>
int ListArr<T>::size(){

}
template<typename T>
void ListArr<T>::insert_left(T v){

}
template<typename T>
void ListArr<T>::insert_right(T v){

}
template<typename T>
void ListArr<T>::insert(T v, int i){
    ResumeNode* temp = Head;
    Node* temp2;
    bool recontruir = false;
    while(i<=size()){
        if (temp->LeftR != nullptr){
            if (i+1<=temp->LeftR->capacidad&&temp->LeftR->usado<=i+1){
                temp = temp->LeftR;
                temp->usado++;
                if (temp->capacidad<temp->usado){
                    recontruir = true;
                }
            }else{
                i = i - temp->LeftR->usado;
                temp = temp->RigthR;
                temp->usado++;
                if (temp->capacidad<temp->usado){
                    recontruir = true;
                }
            }
        }else{
            if (i+1<=temp->Left->capacidad&&temp->Left->usado<=i+1){
                temp2 = temp->Left;
                temp2->usado++;
            }else{
                i = i - temp->Left->usado;
                temp2 = temp->Rigth;
                temp2->usado++;
            }
            if (temp2->capacidad<temp2->usado){
                recontruir = true;
            }
            if (!recontruir){
                temp2->data[temp2->used-1] = v;
                for (int j = 0; j < temp2->used-i-1; j++){
                    T temp3 = temp2->data[temp2->used-1-j];
                    temp2->data[temp2->used-1-j] = temp2->data[temp2->used-2-j];
                    temp2->data[temp2->used-2-j] = temp3;
                }
            }else{
                if (temp2->next!=nullptr&&temp2->next->usado<temp2->next->capacidad){
                    T temp4 = temp2->data[temp2->used-1];
                    temp2->data[temp2->used-1] = v;
                    for (int j = 0; j < temp2->used-i-1; j++){
                        T temp3 = temp2->data[temp2->used-1-j];
                        temp2->data[temp2->used-1-j] = temp2->data[temp2->used-2-j];
                        temp2->data[temp2->used-2-j] = temp3;
                    }
                    temp2 = temp2->next;                    
                    temp2->data[temp2->used-1] = v;
                    for (int j = 0; j < temp2->used-1; j++){
                        T temp3 = temp2->data[temp2->used-1-j];
                        temp2->data[temp2->used-1-j] = temp2->data[temp2->used-2-j];
                        temp2->data[temp2->used-2-j] = temp3;
                    }
                }else{
                    Node* newNode = new Node(capacity);  
                    newNode->data[0] = temp2->data[temp2->used-1];
                    newNode->usado++;
                    temp2->data[temp2->used-1] = v;
                    for (int j = 0; j < temp2->used-i-1; j++){
                        T temp3 = temp2->data[temp2->used-1-j];
                        temp2->data[temp2->used-1-j] = temp2->data[temp2->used-2-j];
                        temp2->data[temp2->used-2-j] = temp3;
                    }
                    newNode->next = temp2->next;
                    temp2->next = newNode;
                    CTree();
                }
            }
        }
    }
}
template<typename T>
void ListArr<T>::print(){

}
template<typename T>
bool ListArr<T>::find(T v){

}
template<typename T>
T ListArr<T>::delete_left(){

}
template<typename T>
T ListArr<T>::delete_right(){

}
