#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

class node{
    public:
    float accuracy;
    vector<node*> parents;
    vector<node*> children;
    map<int,int> features;


    node(){
        accuracy = 0.0;
    }

    void setFeatures(int feat){
        features[feat] = feat;
    }

    void setChild(node* child){
        children.push_back(child);
    }

    void setParent(node* parent){
        parents.push_back(parent);
    }

};