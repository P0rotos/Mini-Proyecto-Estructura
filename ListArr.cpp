#include<iostream>
#include<cmath>
#include<queue>
#include "ListArr.h"
using namespace std;
template<typename T>
void ListArr<T>::DTree(ResumeNode* RN){
    if(RN->LeftR != nullptr){
        DTree(RN->LeftR);
    }
    if(RN->RightR != nullptr){
        DTree(RN->RightR);
    }
    delete RN->RightR;
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
    Head->LeftR = nullptr;
    Head->RightR = nullptr;
    Head->Left = nullptr;
    Head->Right = nullptr;
    Head->capacidad = 0;
    Head->usado = 0;
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
    queue<ResumeNode*> Nqueue;
    Nqueue = CTreeFreeRN(Head, Nqueue);
    while(First != nullptr){
        temp = Nqueue.front();
        Nqueue.pop();
        temp->Left = First;
        cout << temp->Left->usado << endl;
        First = First->next;
        temp->Right = First;
        if (First != nullptr){
            cout << temp->Right->usado << endl;
            First = First->next;
        }
    }
    CTreeAsign(Head);
}
template<typename T>
void ListArr<T>::CTreehelp(ResumeNode* RN, int i){
    if (i>1){
        cout << "HELP???";
        ResumeNode* R = new ResumeNode();
        ResumeNode* L = new ResumeNode();
        RN->RightR = R;
        RN->LeftR = L;
        i--;
        CTreehelp(R, i);
        CTreehelp(L, i);
    }
}
template<typename T>
queue<typename ListArr<T>::ResumeNode*> ListArr<T>::CTreeFreeRN(ResumeNode* RN, queue<ResumeNode*> NQ){
    if (RN->LeftR != nullptr){
        cout << "d";
        NQ = CTreeFreeRN(RN->LeftR, NQ);
    }
    if (RN->RightR != nullptr){
        cout << "e";
        NQ = CTreeFreeRN(RN->RightR, NQ);
    }
    if (RN->RightR == nullptr){
        cout << "f";
        NQ.push(RN);
    }
    return(NQ);
}
template<typename T>
void ListArr<T>::CTreeAsign(ResumeNode* RN){
    RN->usado = 0;
    RN->capacidad = 0;
    if (RN->RightR != nullptr){
        CTreeAsign(RN->LeftR);
        CTreeAsign(RN->RightR);
    }
    if (RN->Left != nullptr){
        cout << RN->usado <<" "<<RN->capacidad<<endl;
        RN->usado = RN->usado + RN->Left->usado;
        RN->capacidad = RN->capacidad + RN->Left->capacidad;
        cout << RN->usado <<" "<<RN->capacidad<<endl;
    }
    if (RN->Right != nullptr){
        cout << RN->usado <<" "<<RN->capacidad<<endl;
        RN->usado = RN->usado + RN->Right->usado;
        RN->capacidad = RN->capacidad + RN->Right->capacidad;
        cout << RN->usado <<" "<<RN->capacidad<<endl;
    }    
    if (RN->LeftR != nullptr){
        RN->usado = RN->usado + RN->LeftR->usado;
        RN->capacidad = RN->capacidad + RN->LeftR->capacidad;
    }
    if (RN->RightR != nullptr){
        RN->usado = RN->usado + RN->RightR->usado;
        RN->capacidad = RN->capacidad + RN->RightR->capacidad;
    }
    
}
template<typename T>
ListArr<T>::ListArr(int capacity){
    this->capacity = capacity;
    this->Head = new ResumeNode();
    Node* Nuevo = new Node(capacity);
    this->Head->Left = Nuevo;
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
    return(Head->usado);
}
template<typename T>
void ListArr<T>::insert_left(T v){
    ResumeNode* RN = Head;
    bool reconstruir = false;
    RN->usado++;
    while (RN->LeftR !=  nullptr){
        RN = RN->LeftR;
        RN->usado++;
    }
    if (RN->Left->usado < RN->Left->capacidad) {
        for (int i = RN->Left->usado; i > 0; i--) {
            RN->Left->data[i] = RN->Left->data[i-1];
        }
        RN->Left->data[0] = v;
        RN->Left->usado++;
    }else{
        if (RN->Left->next != nullptr && RN->Left->next->usado < RN->Left->next->capacidad){        
            for (int i = RN->Left->next->usado; i > 0; i--) {
                RN->Left->next->data[i] = RN->Left->next->data[i-1];
            }
            RN->Left->next->data[0] = RN->Left->data[RN->Left->usado-1];
            RN->Left->next->usado++;        
            for (int i = RN->Left->usado-1; i > 0; i--) {
                RN->Left->data[i] = RN->Left->data[i-1];
            }
            RN->Left->data[0] = v;
        }else{         
            Node* newNode = new Node(capacity);
            newNode->next = RN->Left->next;
            RN->Left->next = newNode;
            newNode->data[0] = RN->Left->data[RN->Left->usado-1];
            newNode->usado++;        
            for (int i = RN->Left->usado-1; i > 0; i--) {
                RN->Left->data[i] = RN->Left->data[i-1];
            }
            RN->Left->data[0] = v;
            CTree();
        }
    }
}
template<typename T>
void ListArr<T>::insert_right(T v){
    ResumeNode* RN = Head;
    RN->usado++;
    while(RN->Left == nullptr){
        if (RN->RightR != nullptr && RN->RightR->usado > 0){
            RN = RN->RightR;
            RN->usado++;
        }else{
            RN = RN->LeftR;
            RN->usado++;
        }
    }
    Node* act;
    if (RN->Right != nullptr && RN->Right->usado > 0){
        act = RN->Right;
    }else{
        act = RN->Left;
    }
    if(act->usado < act->capacidad){
        act->data[act->usado] = v;
        act->usado++;
    }else{
        if (act->next != nullptr && act->next->usado < act->next->capacidad){
            act->next->data[act->next->usado] = v;
            act->next->usado++;
        }else{
            Node* Nuevo = new Node(capacity);
            Nuevo->data[0] = v;
            Nuevo->usado++;
            Nuevo->next = act->next;
            act->next = Nuevo;
            CTree();
        }
    }
}
template<typename T>
void ListArr<T>::insert(T v, int i){
    ResumeNode* temp = Head;
    Node* temp2;
    bool recontruir = false;
    if (i<=this->size()){
        temp->usado++;
        while(temp->LeftR != nullptr){
            if (i<=temp->LeftR->usado){
                temp = temp->LeftR;
                temp->usado++;
            }else{
                i = i - temp->LeftR->usado;
                temp = temp->RightR;
                temp->usado++;
            }
        }
        if (i<=temp->Left->usado){
            temp2 = temp->Left;
        }else{
            i = i - temp->Left->usado;
            temp2 = temp->Right;
        }
        if (temp2->usado < temp2->capacidad){
            for (int j = i; j < temp2->usado; j++){
                T temp3 = temp2->data[temp2->usado-j+i];
                temp2->data[temp2->usado-j+i] = temp2->data[temp2->usado-1-j+i];
                temp2->data[temp2->usado-1-j+i] = temp3;
            }
            temp2->data[i] = v;
            temp2->usado++;
        }else{
            if (temp2->next != nullptr && temp2->next->usado < temp2->next->capacidad){            
                for (int j = temp2->next->usado; j > 0; j--) {
                    temp2->next->data[j] = temp2->next->data[j-1];
                }
                temp2->next->data[0] = temp2->data[temp2->usado-1];            
                temp2->next->usado++;        
                for (int j = temp2->usado-1; j > i; j--) {
                    temp2->data[j] = temp2->data[j-1];
                }
                temp2->data[i] = v;
            }else{         
                Node* newNode = new Node(capacity);
                newNode->next = temp2->next;
                temp2->next = newNode;
                newNode->data[0] = temp2->data[temp2->usado-1];
                newNode->usado++;        
                for (int j = temp2->usado-1; j > i; j--) {
                    temp2->data[j] = temp2->data[j-1];
                }
                temp2->data[i] = v;
                CTree();
            }
        }
    }
}
template<typename T>
void ListArr<T>::print(){ 
    Node* current;
    ResumeNode* temp = Head;
    while(temp->Left == nullptr){
        temp = temp->LeftR;
    }
    current = temp->Left;
    do{
        for (int i = 0; i < current->usado; i++){
            cout << current->data[i] <<" ";
        }
        current = current->next;
    }while(current != nullptr);
}
template<typename T>
bool ListArr<T>::find(T v){
    Node* current;
    ResumeNode* temp = Head;
    while(temp->Left == nullptr){
        temp = temp->LeftR;
    }
    current = temp->Left;
    bool flag = false;
    while(current != nullptr){
        for (int i = 0; i < current->usado; i++){
            if (current->data[i]==v){
                flag = true;
                break;
            }
        }
        if (flag){
            break;
        }
        current = current->next;
    }
    return flag;
}
template<typename T>
T ListArr<T>::delete_left(){    
    if (size()==0){
        return(0);
    }
    ResumeNode* RN = Head;
    RN->usado--;
    while (RN->LeftR !=  nullptr){
        RN = RN->LeftR;
        RN->usado--;
    }
    Node* act= RN->Left;
    T out;
    if(act->usado-1 != 0){
        out = act->data[0];
        act->usado--;
        for (int i = 0; i < act->usado; i++){
            act->data[i] = act->data[i+1];
        }
    }else{        
        out = act->data[0];
        RN->Left = RN->Right;
        delete act;
        CTree();
    }
    return(out);
}
template<typename T>
T ListArr<T>::delete_right(){
    if (size()==0){
        return(0);
    }
    ResumeNode* RN = Head;
    RN->usado--;
    while(RN->Left == nullptr){
        if (RN->RightR != nullptr && RN->RightR->usado > 0){
            RN = RN->RightR;
            RN->usado--;
        }else{
            RN = RN->LeftR;
            RN->usado--;
        }
    }
    Node* act;
    if (RN->Right != nullptr && RN->Right->usado > 0){
        act = RN->Right;
    }else{
        act = RN->Left;
    }
    T out;
    if(act->usado-1 != 0){
        out = act->data[act->usado-1];
        act->usado--;
    }else{
        out = act->data[0];
        if (act == RN->Right){
            delete act;
            RN->Left->next = nullptr;
        }else{
            if(RN != Head){
                Node* First;
                ResumeNode* tempRN = Head;
                while (tempRN->LeftR != nullptr){
                    cout << "a";
                    tempRN = tempRN->LeftR;
                }
                First = tempRN->Left;
                while (First->next!=act){
                    cout << "b";
                    First = First->next;
                }
                First->next = nullptr;
                delete act;
            }
        }
        if (RN != Head){
            cout << "c";
            CTree();
        }
    }
    return(out);
}