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
    cout << "Entro";
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
    cout << "Entro";
    CTreehelp(Head, count);
    queue<ResumeNode*> Nqueue;
    cout << "Entro";
    Nqueue = CTreeFreeRN(Head, Nqueue);
    while(First != nullptr){
        temp = Nqueue.front();
        Nqueue.pop();
        temp->Left = First;
        First = First->next;
        temp->Right = First;
        if (First != nullptr){
            First = First->next;
        }
    }
    CTreeAsign(Head);
}
template<typename T>
void ListArr<T>::CTreehelp(ResumeNode* RN, int i){
    if (i>1){
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
    cout << "entro";
    if (RN->LeftR != nullptr){
        NQ = CTreeFreeRN(RN->LeftR, NQ);
    }
    if (RN->RightR != nullptr){
        NQ = CTreeFreeRN(RN->RightR, NQ);
    }
    if (RN->RightR == nullptr){
        NQ.push(RN);
    }
    return(NQ);
}
template<typename T>
void ListArr<T>::CTreeAsign(ResumeNode* RN){
    if (RN->usado == 0 && RN->RightR != nullptr){
        CTreeAsign(RN->LeftR);
        CTreeAsign(RN->RightR);
    }
    if (RN->Left != nullptr){
        RN->usado == RN->usado + RN->Left->usado;
        RN->capacidad == RN->capacidad + RN->Left->capacidad;
    }
    if (RN->Right != nullptr){
        RN->usado == RN->usado + RN->Right->usado;
        RN->capacidad == RN->capacidad + RN->Right->capacidad;
    }    
    if (RN->LeftR != nullptr){
        RN->usado == RN->usado + RN->LeftR->usado;
        RN->capacidad == RN->capacidad + RN->LeftR->capacidad;
    }
    if (RN->RightR != nullptr){
        RN->usado == RN->usado + RN->RightR->usado;
        RN->capacidad == RN->capacidad + RN->RightR->capacidad;
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
                temp = temp->RightR;
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
                temp2 = temp->Right;
                temp2->usado++;
            }
            if (temp2->capacidad<temp2->usado){
                recontruir = true;
            }
            if (!recontruir){
                temp2->data[temp2->usado-1] = v;
                for (int j = 0; j < temp2->usado-i-1; j++){
                    T temp3 = temp2->data[temp2->usado-1-j];
                    temp2->data[temp2->usado-1-j] = temp2->data[temp2->usado-2-j];
                    temp2->data[temp2->usado-2-j] = temp3;
                }
            }else{
                if (temp2->next!=nullptr&&temp2->next->usado<temp2->next->capacidad){
                    T temp4 = temp2->data[temp2->usado-1];
                    temp2->data[temp2->usado-1] = v;
                    for (int j = 0; j < temp2->usado-i-1; j++){
                        T temp3 = temp2->data[temp2->usado-1-j];
                        temp2->data[temp2->usado-1-j] = temp2->data[temp2->usado-2-j];
                        temp2->data[temp2->usado-2-j] = temp3;
                    }
                    temp2 = temp2->next;                    
                    temp2->data[temp2->usado-1] = v;
                    for (int j = 0; j < temp2->usado-1; j++){
                        T temp3 = temp2->data[temp2->usado-1-j];
                        temp2->data[temp2->usado-1-j] = temp2->data[temp2->usado-2-j];
                        temp2->data[temp2->usado-2-j] = temp3;
                    }
                }else{
                    Node* newNode = new Node(capacity);  
                    newNode->data[0] = temp2->data[temp2->usado-1];
                    newNode->usado++;
                    temp2->data[temp2->usado-1] = v;
                    for (int j = 0; j < temp2->usado-i-1; j++){
                        T temp3 = temp2->data[temp2->usado-1-j];
                        temp2->data[temp2->usado-1-j] = temp2->data[temp2->usado-2-j];
                        temp2->data[temp2->usado-2-j] = temp3;
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
    ResumeNode* temp = Head;
    while(temp->Left == nullptr){
        if (temp->LeftR->usado != 0){
            temp = temp->LeftR;
        }else{
            temp = temp->RightR;
        }
    }
    if (temp->Left->usado != 0){
        temp->Left->usado--;
        for (int i = 0; i < temp->Left->usado; i++){                        
            T temp2 = temp->Left->data[i];
            temp->Left->data[i] = temp->Left->data[i+1];
            temp->Left->data[i+1] = temp2;
        }
        if (temp->Left->usado == 0){ 
            T out =  temp->Left->data[temp->Left->usado];
            Node* First;
            ResumeNode* temp3 = Head;
            while(temp3->Left == nullptr){
                temp3 = temp3->LeftR;
            }
            First = temp3->Left;
            if (First->usado!=0){
                while(First->next->usado!=0){
                    First = First->next;
                }
                if (First->next->next != nullptr){
                    First->next = First->next->next;
                }
            }else{
                if (temp3->Right != nullptr){           
                    Node* aux;
                    aux = temp3->Left;
                    temp3->Left = temp3->Right;
                    delete aux;
                }
            }
            if (temp3->Right != nullptr){
                delete temp->Left;
                CTree();
                return(out);
            }
        }
        return(temp->Left->data[temp->Left->usado]);
    }else{
        cout << "No hay datos";
        return(0);
    }
}
template<typename T>
T ListArr<T>::delete_right(){
    ResumeNode* temp = Head;
    while(temp->Left == nullptr){
        if (temp->RightR->usado != 0){
            temp = temp->RightR;
        }else{
            temp = temp->LeftR;
        }
    }
    Node* act;
    if (temp->Right != nullptr && temp->Right->usado != 0){
        act = temp->Right;
    }else{
        act = temp->Left;
    }
    if (act->usado == 0){
        act->usado--;
        if (act->usado == 0){ 
            T out =  act->data[act->usado];
            Node* First;
            ResumeNode* temp3 = Head;
            while(temp3->Left == nullptr){
                temp3 = temp3->LeftR;
            }
            First = temp3->Left;
            if (First->usado!=0){
                while(First->next->usado!=0){
                    First = First->next;
                }
                First->next = nullptr;
                delete act;
            }
            CTree();
            return(out);
        }
        return(act->data[act->usado]);
    }else{
        cout << "No hay datos";
        return(0);
    }
}
