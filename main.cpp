#include <stdlib.h>
#include <vector>
#include <iostream>
#include "search.cpp"
#include "time.h"
#include "classifier.cpp"

int main(){

    Classifier c;
    c.LoadEntriesFromFile("cs_170_small80.txt");
    vector<vector<double>> tmp = c.featuresGrouped();
    //vector<vector<double>> temp = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; // vector of 3 vector of features
    c.normalizer(tmp);
    for(int i = 0; i < c.givenData.size(); i++){
        cout << "INSTANCE ID: " << i + 1 << " " << endl;
        for(int j = 0; j < c.givenData[i].normalizedFeat.size(); j++){
            cout << c.givenData[i].normalizedFeat[j] << ", ";
        }
        cout << endl << endl;
    }

    // search s;
    // srand (time(NULL));    
    // int features;
    // int algo;
    // cout << "Welcome to Ryan Giron's and Simraj Singh's Feature Selection Algorithm" << endl << endl;

    // cout << "Please enter the number of features: ";

    // cin >> features;

    // cout << endl;

    // cout << "Type the number of the algorithm you would like to select:" << endl;
    // cout << "1) Foward Selection" << endl;
    // cout << "2) Backwards Elimination" << endl;

    // cin >> algo;

    // cout << endl;


    // node* n;

    // switch(algo){
    //     case 1: 
    //         cout << "Foward Selection: " << endl;
    //         n = s.forwardSelection(features);
    //         break;
    //     case 2: 
    //         cout << "Backwards Elimination: " << endl;
    //         n = s.backwardsElimination(features);
    //         break;
    //     default: 
    //         cout << "INVALID ENTRY! PLEASE TRY AGAIN" << endl;
    //         return 0;
    //         break;
    // }

    // cout << "Finished search! The best feature subset is {";
    // for(auto x : n->features){
    //     cout << x.second << " ";
    // }
    // cout << setprecision(3);
    // cout << "}, which has an accuracy of " << n->accuracy * 100 << "%" << endl;

}