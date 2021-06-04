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
            cout << "Validating Classifier with the feature set {";
            for(int i = 0; i < featuresSubset.size(); i++){
                cout << featuresSubset[i] + 1 << " ";
            }
            cout << "}" << endl;
            for(int i = 0; i < cl.givenData.size(); i++){
                cout << "Testing instance " << i + 1 << endl;
                if(featuresSubset.size() > 0){
                    if(cl.test(i, featuresSubset, 1) == cl.givenData[i].classifier){
                        cout << "Instance " << i + 1 << " is correct" << endl;           // REMOVE FOR PART 3
                        correct++;
                    } else {
                         cout << "Instance " << i + 1 << " is incorrect" << endl;
                    }
                } else {
                correct += rand() % 2;
                }
                totalTests++;
            }
            return (correct/totalTests);
        }

};