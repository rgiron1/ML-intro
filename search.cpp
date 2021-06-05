#include <stdlib.h>
#include <vector>
#include <queue>
#include <iomanip>
#include "node.cpp"
#include <iostream>
#include "validator.cpp"
class search{
    public:
        Classifier classifier;

        void setClassifier(Classifier cl){
            classifier = cl;
        }

        node* forwardSelection(){
            node* root = new node();
            int features = classifier.numOfFeatures;
            int numOfChildren = features;
            bool foundNewMax = false;
            Validator v;
            node* curr = root;
            root->accuracy = v.evaluateAccuracy(classifier);
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
                        Validator validOfChildren;
                        for(auto x : child->features){
                            validOfChildren.featuresSubset.push_back(x.second);
                        }
                        cout << "Using the feature set {";
                        for(auto x : child->features){
                            cout << x.second << " ";
                        }
                        child->accuracy = validOfChildren.evaluateAccuracy(classifier);
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

                cout << endl << "Feature set {";
                for(auto x : maxNode->features){
                        cout << x.second << " ";
                    }
                cout << setprecision(3);
                cout << "} was the best, accuracy is " << maxNode->accuracy * 100 << "%" << endl << endl; 

                numOfChildren--;
                curr = maxNode; 
            }
        }

        node* backwardsElimination(){
            node* root = new node();
            int features = classifier.numOfFeatures;
            int numOfChildren = 0;
            bool foundNewMax = false;
            for(int i = 1; i < features + 1; i++){
                root->features[i] = i;
                Validator rootValid;
                rootValid.featuresSubset.push_back(i);
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
                        Validator validOfChild;
                        for(auto x : parent->features){
                            validOfChild.featuresSubset.push_back(x.second);
                        }
                        cout << "Using the feature set {";
                        for(auto x : parent->features){
                            cout << x.second << " ";
                        }
                        parent->accuracy = validOfChild.evaluateAccuracy(classifier);
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
