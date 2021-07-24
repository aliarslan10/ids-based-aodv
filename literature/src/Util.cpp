/*
 * Util.cpp
 *
 * Created on: 30 Tem 2020
 * Author: Ali Arslan
 */

#include "Util.h"

double Util::calculateTwoNodeDistance(int receiverX, int receiverY, int senderX, int senderY) {
    double x = double(pow(abs(receiverX - senderX), 2));
    double y = double(pow(abs(receiverY - senderY), 2));
    return sqrt(x + y);
}

double Util::calculateDiagonalDistance(int xSideLength, int ySideLength) {
     return sqrt(double(pow((xSideLength), 2) + pow((ySideLength), 2)));
 }

bool Util::isMaliciousNode(string malicious, int nodeIndex) {

    bool nodeMaliciousStatus = false;

    if (!malicious.empty()) {
        vector<int> maliciousNodes;
        stringstream maliciousNodesFromConfig(malicious);

        for (int i; maliciousNodesFromConfig >> i;) {
            maliciousNodes.push_back(i);
            if (maliciousNodesFromConfig.peek() == ',')
                maliciousNodesFromConfig.ignore();
        }

        for (int malicious : maliciousNodes) {
            if(malicious == nodeIndex){
                nodeMaliciousStatus = true;
            }
        }
    }

    return nodeMaliciousStatus;
}

vector<int> Util::csvToVector(string commaSeparatedValue) {
    vector<int> values;
    stringstream streamedValue(commaSeparatedValue);

    for (int i; streamedValue >> i;) {
        values.push_back(i);
        if (streamedValue.peek() == ',')
            streamedValue.ignore();
    }

    return values;
}

string Util::vectorToCSV(vector<int> vector) {
    string neighbors;
    for(int item : vector) {
        neighbors += to_string(item) + ",";
    }
    neighbors.pop_back();
    return neighbors;
}

vector<int> Util::checkMaliciousNodes(vector<int> neighbors, vector<int> rreqSenders) {

    for(int sender : rreqSenders) {
        neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), sender), neighbors.end());
    }

    return neighbors;
}


int Util::randomNumberGenerator(int min, int max) {
    srand(static_cast <unsigned int> (time(0)));
    return rand() % max + min;
}

vector<int> Util::selectRandomValues(vector<int> items, int quantity) {

    vector<int> selectedValues;
    int selectedItem;

    quantity = (quantity < items.size()) ? quantity : items.size();

    for (int i = 0; i < quantity; i++) {
        selectedItem = rand() % items.size();
        cout << "selectedItem - index : " << selectedItem << endl;
        cout << "iterator - selected value : " << items[selectedItem] << endl;
        selectedValues.push_back(items[selectedItem]);
        items.erase(find(items.begin(), items.end(), items[selectedItem]));
    }
    return selectedValues;
}


vector<int> Util::updateVector(vector<int> items, vector<int> selectedValues) {
  for (int value : selectedValues) {
    items.erase(find(items.begin(), items.end(), value));
  }
  return items;
}
