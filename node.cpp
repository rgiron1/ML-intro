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
        accuracy = ((float)rand()/RAND_MAX);
    }

    // node(int feature){
    //     srand (time(NULL));
    //     accuracy = (rand() % 100)/100;
    //     parents.push_back(parent);
    //     features.push_back(feature);
    // }

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