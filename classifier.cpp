#include "data.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <iomanip>
#include <math.h>

using namespace std;

class Classifier{
    public:
    vector<Data> givenData;
    int numOfFeatures;
    //parse here and put the data table into given data.

    void LoadEntriesFromFile(string filepath){
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

    void train(){
        
    }


    Data test(Data testEntry){


    }

};