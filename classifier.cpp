#include "data.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <iomanip>
#include <queue>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Classifier{
    public:
    vector<Data> givenData; //Data structure that contains trained data
    int numOfFeatures;
    vector<int> featuresSubset;
    //parse here and put the data table into given data.

    struct compareEuclideanDistance{
        bool operator() (Data a, Data b){
            return (a.distance > b.distance);
        }
    };  

    void LoadEntriesFromFile(string filepath){
        cout << "Loading data from " << filepath << endl;
        ifstream fin;
        fin.open(filepath);
        if (!fin.is_open()){
            cerr << "Error loading file \"" << filepath << "\"" << endl;
            exit(404);
        }

        string buffer;
        while (getline(fin, buffer)){
            stringstream line(buffer);
            int classifier;
            line >> classifier;
            Data d;
            d.setClassifier(classifier);
            double feature;
            while (line >> feature)
            {
                d.addFeature(feature);
            }
            givenData.push_back(d);
        }


        for(int i = 0 ; i < givenData.size(); i++){
            givenData[i].features.erase(givenData[i].features.begin());
        }
        numOfFeatures = givenData[0].features.size();

        // for(int i = 0; i < 13; i++){
        //     cout << givenData[i].classifier << " ";
        //     for(int j = 0; j < givenData[0].features.size(); j++){
        //         cout << givenData[i].features[j] << " ";
        //     }
        //     cout << "size:" << givenData[0].features.size() << endl;
        // }
    }

    vector<vector<double>> featuresGrouped(){
        vector<vector<double>> featureColumns(numOfFeatures);
        for(int i = 0; i < givenData.size(); i++){
            for(int j = 0; j < givenData[i].features.size(); j++){
                featureColumns[j].push_back(givenData[i].features[j]);
            }
        }

        return featureColumns;
    }

    void normalizer(vector<vector<double>> featureSet){
        vector<double> meanByStd;
        
        cout << "Normalizing data of " << givenData.size() << " data entries" << endl;
        
        for(int i = 0; i < featureSet.size(); i++){ //Loop to calculate (avg/stdev) for each feature set
            double avg = 0.0;
            double variance = 0.0;
            double stdev = 0.0;
            avg = accumulate(featureSet[i].begin(), featureSet[i].end(), 0.0) / (double)featureSet[i].size();

            for(int j = 0; j < featureSet[i].size(); j++){
                variance += pow((featureSet[i][j] - avg), 2);
            }
            stdev = sqrt(variance/(double)featureSet[i].size());
            meanByStd.push_back(avg/stdev);            
            //cout << setprecision(5) << "Avg/Stdev: " << avg / stdev << endl;
        }
        
        //NORMALIZING FEATURES
        for(int i = 0; i < givenData.size(); i++){
            for(int j = 0; j < givenData[i].features.size(); j++){
                givenData[i].normalizedFeat.push_back(givenData[i].features[j] - meanByStd[j]); //writing the normalized features to the i'th data entry
                // Data object now has updated class variable with normalized feature values
            }
        }
    }

    void train(string filepath){
        auto start = high_resolution_clock::now();
        LoadEntriesFromFile(filepath);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop-start);
        cout << "Time taken to import data is: " << duration.count()/1000.0 << " ms. " << endl << endl;
        
        start = high_resolution_clock::now();
        
        vector<vector<double>> featSet = featuresGrouped();

        normalizer(featSet);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop-start);
        cout << "Time taken to normalize data is: " << duration.count()/1000.0 << " ms. " << endl << endl;

        //stop
        // for(int i = 0; i < givenData.size(); i++){
        //     cout << "INSTANCE ID: " << i + 1 << " " << endl;
        //     for(int j = 0; j < givenData[i].normalizedFeat.size(); j++){
        //         cout << givenData[i].normalizedFeat[j] << ", ";
        //     }
        //     cout << endl << endl;
        // }
    }


    double calculateDistance(Data testPoint, Data neighbor){
        double dist = 0;
        for(int i = 0; i < featuresSubset.size(); i++){

            dist += (pow((testPoint.normalizedFeat[featuresSubset[i]] - neighbor.normalizedFeat[featuresSubset[i]]),2));
            
        }
        //cout << "Distance from the test to the neighbor is: " << neighbor.distance << endl;
        return sqrt(dist);
    }

    int test(int id, vector<int> featuresToUse, int N){
        int predictedClass;
        featuresSubset = featuresToUse;
        priority_queue<Data, vector<Data>, compareEuclideanDistance> q;
        for(int i = 0; i < givenData.size(); i++){
            if(i == id){
                continue;
            }
            givenData[i].setDistance(calculateDistance(givenData[id], givenData[i]));
            q.push(givenData[i]);

        }
        vector<Data> nearestNeighbors;
        int class1 = 0;
        int class2 = 0;
        for(int i = 0; i < N; i++){
            nearestNeighbors.push_back(q.top());
            if(q.top().classifier == 1){
                class1++;
            } else {
                class2++;
            }
        }
        
        if(max(class1, class2) == class1){
            predictedClass = 1;
        } else {
            predictedClass = 2;
        }

    
        return predictedClass;
    }

};