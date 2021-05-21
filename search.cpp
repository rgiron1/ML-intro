#include <stdlib.h>
#include <vector>
#include <queue>
#include <iomanip>
#include "node.cpp"
#include <iostream>
class search{
    public:
        node* forwardSelection(int features){
            node* root = new node();
            int numOfChildren = features;
            bool foundNewMax = false;
            
            node* curr = root;
            cout << setprecision(3);
            cout << "Using no features and random evaluation, We get an accuracy of " << root->accuracy * 100 << "%" << endl << endl;
            cout << "Beginning search" << endl << endl;
            while(numOfChildren != 0){
                node* maxNode = curr;
                foundNewMax = false;
                for(int i = 1; i < features + 1; i++){ // loop through features we wanna add
                    if(!curr->features.count(i)){ // if the feature we wanna add already exsists then we dont make a child
                        node* child = new node();
                        child->features = curr->features;
                        child->setFeatures(i);
                        cout << "Using the feature set {";
                        for(auto x : child->features){
                            cout << x.second << " ";
                        }
                        cout << setprecision(3);
                        cout << "} the accuracy is: " << child->accuracy * 100<< "%" << endl;
                        curr->setChild(child);
                        if(child->accuracy > maxNode->accuracy){ //check for the max accuracy 
                            maxNode = child;
                            foundNewMax = true;
                        }
                    }
                }

                if(!foundNewMax){ //if our flag has been triggered exit the algorithm 
                    cout << "(Warning! Accuracy has decreased!)" << endl;
                    return curr;
                }

                cout << "Feature set {";
                for(auto x : maxNode->features){
                        cout << x.second << " ";
                    }
                cout << setprecision(3);
                cout << "} was the best, accuracy is " << maxNode->accuracy * 100 << "%" << endl << endl; 

                numOfChildren--;
                curr = maxNode; 
            }
        }

        node* backwardsElimination(int features){
            node* root = new node();
            int numOfChildren = 0;
            bool foundNewMax = false;
            for(int i = 1; i < features + 1; i++){
                root->features[i] = i;
            }
            
            node* curr = root;
            cout << setprecision(3);
            cout << "Using all features and random evaluation, We get an accuracy of " << root->accuracy * 100 << "%" << endl << endl;
            cout << "Beginning search" << endl << endl;
            while(numOfChildren != features){
                node* maxNode = curr;
                foundNewMax = false;
                for(int i = 1; i < features + 1; i++){ // loop through features we wanna add
                    if(curr->features.count(i)){ // if the feature we wanna add already exsists then we dont make a child
                        node* parent = new node();
                        parent->features = curr->features;
                        parent->features.erase(i);
                        cout << "Using the feature set {";
                        for(auto x : parent->features){
                            cout << x.second << " ";
                        }
                        cout << setprecision(3);
                        cout << "} the accuracy is: " << parent->accuracy * 100<< "%" << endl;
                        curr->setParent(parent);
                        if(parent->accuracy >= maxNode->accuracy){ //check for the max accuracy 
                            maxNode = parent;
                            foundNewMax = true;
                        }
                    }
                }

                if(!foundNewMax){ //if our flag has been triggered exit the algorithm 
                    cout << "(Warning! Accuracy has decreased!)" << endl;
                    return curr;
                }

                cout << "Feature set {";
                for(auto x : maxNode->features){
                        cout << x.second << " ";
                    }
                cout << setprecision(3);
                cout << "} was the best, accuracy is " << maxNode->accuracy * 100 << "%" << endl << endl; 

                numOfChildren++;
                curr = maxNode; 
            }
        }
};
