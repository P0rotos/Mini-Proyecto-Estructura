#include<iostream>
#include<cmath>
#include <ctime>
#include <ratio>
#include <chrono>
#include "ListArr.cpp"
using namespace std;
int main(int argc, char const *argv[]){
    srand (time(NULL));
    int reps = 20;
    /*test de tiempo y espacio de insert_right*/
    /*for (int k = 0; k < 11; k++){
        for (int j = 0; j < 5; j++){
            double duration = 0;
            int adi = 0;
            int testeo = ((int)pow(10,j+4)/20);
            int cap = ((int)pow(10,j+4)/(int)pow(2,k));
            cout << cap << endl;
            ListArr<int> A(cap);
            for(int i = 0; i < reps; i++){
                auto start = chrono::high_resolution_clock::now();
                //####################INICIO DEL CLOCK####################
                for (int i = 1+adi; i <= testeo+adi; i++){
                    A.insert_right(i);
                }
                //#####################FIN DEL CLOCK######################
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> diff = end - start;
                adi = adi+testeo;
                duration += diff.count();
            }
            duration /= reps;
            cout << "Duracion para n=" << testeo*20 << " y b=" << testeo*20/cap << " con espacio=" << A.sizeofListArr() << " bytes: "<< duration << endl;
        }
    }*/
    /*test de espacio de delete_left*/
    /*
    for (int k = 0; k < 11; k++){
        for (int j = 0; j < 2; j++){
            int testeo = ((int)pow(10,j+4)/10);
            int cap = ((int)pow(10,j+4)/(int)pow(2,k));
            cout << cap << endl;
            ListArr<int> A(cap);
            for (int l = 1; l < 5; l++){
                for (int i = 1; i <= testeo*l; i++){
                    A.insert_right(i);
                }
                cout << "n=" << testeo << " y b=" << testeo*10/cap << " size actual=" << A.size() << " con espacio=" << A.sizeofListArr() << " bytes"<< endl;
            }
            for (int l = 1; l < 5; l++){
                for (int i = 1; i <= testeo*l; i++){
                    A.delete_left();
                }
                cout << "n=" << testeo*10 << " y b=" << testeo*10/cap << " con espacio=" << A.size() << " con espacio=" << A.sizeofListArr() << " bytes"<< endl;
            }
        }
    }*/
    /*test de espacio de delete_ right*/
    /*
    for (int k = 0; k < 11; k++){
        for (int j = 0; j < 2; j++){
            int testeo = ((int)pow(10,j+4)/10);
            int cap = ((int)pow(10,j+4)/(int)pow(2,k));
            cout << cap << endl;
            ListArr<int> A(cap);
            for (int l = 1; l < 5; l++){
                for (int i = 1; i <= testeo*l; i++){
                    A.insert_right(i);
                }
                cout << "n=" << testeo << " y b=" << testeo*10/cap << " size actual=" << A.size() << " con espacio=" << A.sizeofListArr() << " bytes"<< endl;
            }
            for (int l = 1; l < 5; l++){
                for (int i = 1; i <= testeo*l; i++){
                    A.delete_right();
                }
                cout << "n=" << testeo*10 << " y b=" << testeo*10/cap << " con espacio=" << A.size() << " con espacio=" << A.sizeofListArr() << " bytes"<< endl;
            }
        }
    }*/
    /*test de tiempo de find*/
    /*for (int k = 0; k < 11; k++){
        for (int j = 0; j < 5; j++){
            double duration = 0;
            int adi = 0;
            int testeo = ((int)pow(10,j+4)/20);
            int cap = ((int)pow(10,j+4)/(int)pow(2,k));
            cout << cap << endl;
            ListArr<int> A(cap);
            for(int i = 0; i < reps; i++){                
                for (int i = 1+adi; i <= testeo+adi; i++){
                    A.insert_right(i);
                }
                auto start = chrono::high_resolution_clock::now();
                //####################INICIO DEL CLOCK####################
                A.find((testeo+adi)/2);
                //#####################FIN DEL CLOCK######################
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> diff = end - start;
                adi = adi+testeo;
                duration += diff.count();
            }
            duration /= reps;
            cout << "Duracion para n=" << testeo*20 << " y b=" << testeo*20/cap << " con espacio=" << A.sizeofListArr() << " bytes: "<< duration << endl;
        }
    }*/
    /*test tiempo y espacio de insert_left con tiempo maximo antes de salir de la prueba de 10 segundos*/
    /*srand (time(NULL));
    bool flag = false;
    for (int k = 0; k < 11; k++){
        for (int j = 0; j < 5; j++){
            double duration = 0;
            int adi = 0;
            int testeo = ((int)pow(10,j+4)/20);
            int cap = ((int)pow(10,j+4)/(int)pow(2,k));
            cout << cap << endl;
            ListArr<int> A(cap);
            for(int i = 0; i < reps; i++){
                auto start = chrono::high_resolution_clock::now();
                //####################INICIO DEL CLOCK####################
                for (int i = 1+adi; i <= testeo+adi; i++){
                    A.insert_left(i);
                    auto check = chrono::high_resolution_clock::now();
                    chrono::duration<double> diffcheck = check - start;
                    if (diffcheck.count() > 10){
                        flag = true;
                        break;
                    }
                }
                //#####################FIN DEL CLOCK######################
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> diff = end - start;
                if (diff.count()>10 || flag){
                    flag = true;
                    break;
                }
                adi = adi+testeo;
                duration += diff.count();
            }
            duration /= reps;
            if (flag){
                cout << "Duracion para n=" << testeo*20 << " y b=" << testeo*20/cap << " llego a un tiempo mayor a 10 segundo" << endl;
                flag = false;
            }else{
                cout << "Duracion para n=" << testeo*20 << " y b=" << testeo*20/cap << " con espacio=" << A.sizeofListArr() << " bytes: "<< duration << endl;
            }
        }
    }*/
    return 0;
}
