#include <vector>

using namespace std;

class Data{
    public:

    int classifier;
    double distance;
    vector<double> features;
    vector<double> normalizedFeat;

    void setClassifier(int c){
        classifier = c; 
    }

    void addFeature(double feat){
        features.push_back(feat);
    }


    void setDistance(double dist){
        distance = dist;
    }

};