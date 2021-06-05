#include <stdlib.h>
#include <vector>
#include <iostream>
#include "search.cpp"

int main(){
    Classifier c;
    

    search s;
    srand (time(NULL));    
    string filepath;
    int algo;
    cout << "Welcome to Ryan Giron's and Simraj Singh's Feature Selection Algorithm" << endl << endl;

    cout << "Please enter the file you would like to train and test: ";

    cin >> filepath;

    cout << endl;

    c.train(filepath);
    s.setClassifier(c);

    cout << "Type the number of the algorithm you would like to select:" << endl;
    cout << "1) Forward Selection" << endl;
    cout << "2) Backwards Elimination" << endl;

    cin >> algo;

    cout << endl;


    node* n;

    switch(algo){
        case 1: 
            cout << "Foward Selection: " << endl;
            n = s.forwardSelection();
            break;
        case 2: 
            cout << "Backwards Elimination: " << endl;
            n = s.backwardsElimination();
            break;
        default: 
            cout << "INVALID ENTRY! PLEASE TRY AGAIN" << endl;
            return 0;
            break;
    }

    cout << "Finished search! The best feature subset is {";
    for(auto x : n->features){
        cout << x.second << " ";
    }
    cout << setprecision(3);
    cout << "}, which has an accuracy of " << n->accuracy * 100 << "%" << endl;

}