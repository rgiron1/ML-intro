#include <vector>

using namespace std;

class Data{
    public:

    int classifier;
    vector<double> features;
    vector<double> normalizedFeat;

    void setClassifier(int c){
        classifier = c; 
    }

    void addFeature(double feat){
        features.push_back(feat);
    }

    // void setNormalized(vector<double> v){
    //     normalizedFeat = v;
    // }

};