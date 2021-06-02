#include "classifier.cpp"
class Validator{
    public:
        vector<int> featuresSubset;
        int N = 0;

        void setN(int n){
            N = n;
        }

        double evaluateAccuracy(Classifier cl){
            double totalTests = 0;
            double correct = 0;
            for(int i = 0; i < cl.givenData.size(); i++){
                //cout << featuresSubset.size();
                if(featuresSubset.size() > 0){
                    if(cl.test(i, featuresSubset, 1) == cl.givenData[i].classifier){
                        correct++;
                    } 
                } else {
                correct += rand() % 2;
                }
                totalTests++;
            }
            return (correct/totalTests);
        }

};