#ifndef ListArr_H
#define ListArr_H
#include<iostream>
#include<queue>
#include "ListArrADT.h"
using namespace std;
template<typename T>
class ListArr: public ListArrADT<T>{
private:
	struct Node{
        T* data;
		Node* next;
        int capacidad;
        int usado;
		Node(int capacidad){
			this->capacidad = capacidad;
			this->data = new T[capacidad];
			this->next = nullptr;
			this->usado = 0;
		}
	};
    struct ResumeNode{
		Node* Right;
        Node* Left;
        ResumeNode* RightR;
        ResumeNode* LeftR;
        int capacidad;
        int usado;
		ResumeNode(){
			this->Right = nullptr;
			this->RightR = nullptr;
			this->Left = nullptr;
			this->LeftR = nullptr;
			this->usado = 0;
			this->capacidad = 0;
		}
	};
	ResumeNode* Head;
	int capacity;
	//Las Siguientes funciones estan en private ya que son funciones que buscamos usar dentro del mismo ListArr y no deben ser accedidas desde fuera ya que pueden dañar el funcionamiento del mismo
	void DTree(ResumeNode* RN);//Destruye el arbol de ResumeNode dejando solo al ResumeNode Head
	void CTree(); //Crea y da valores a capacidad y usado en el arbol de nodos Resumenes
	void CTreehelp(ResumeNode* RN, int i); //crea los ResumeNode y los une en un arbol binario de altura i (Cuidado que si se quiere usar este no elimina el ARbol anterio y como se cambia LeftR y RightR se van a quedar los nodos del arbol anterior ocupando espacio e inaccesible por lo que no podran ser borrados)
	queue<ResumeNode*> CTreeFreeRN(ResumeNode* RN, queue<ResumeNode*> NQ); //Busca ResumeNode que no este ligado a otro ResumeNode(hojas) en el arbol y que tampoco esten completos osea no tengo un Node
	void CTreeAsign(ResumeNode* RN); //Pasa por todo el arbol de ResumeNode Recien Construido (con usado y capacidad 0) y va sumando los valores de a los nodos uno en unohasta que cada uno tenga su valor correspondiente (notar que no sirve si los ResumeNode ya tenian un valor previamente)
public:
	ListArr(int capacity);
	~ListArr();
	int size();
	void insert_left(T v);
	void insert_right(T v);
	void insert(T v, int i);
	void print();
	bool find(T v);
    T delete_left();
    T delete_right();
};
#endif