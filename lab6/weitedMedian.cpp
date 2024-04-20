#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Custom struct to represent an element with its weight
struct Element {
    int value;
    double weight;
};

// Function to compare two elements based on their values
bool compare(const Element& a, const Element& b) {
    return a.value < b.value;
}

// Function to compute the weighted median
double weightedMedian(vector<Element>& elements) {
    // Sort the elements based on their values
    sort(elements.begin(), elements.end(), compare);
    
    // Calculate cumulative weights
    double totalWeight = 0.0;
    for (auto& element : elements) {
        totalWeight += element.weight;
        element.weight = totalWeight;
    }
    
    // Find the index of the median
    double halfTotalWeight = totalWeight / 2.0;
    int medianIndex = -1;
    for (int i = 0; i < elements.size(); ++i) {
        if (elements[i].weight >= halfTotalWeight) {
            medianIndex = i;
            break;
        }
    }
    
    // Find the weighted median
    double weightedMedianValue;
    if (medianIndex == 0 || elements[medianIndex - 1].weight == halfTotalWeight) {
        weightedMedianValue = elements[medianIndex].value;
    } else {
        double lowerValue = elements[medianIndex - 1].value;
        double upperValue = elements[medianIndex].value;
        double lowerWeight = elements[medianIndex - 1].weight;
        double upperWeight = elements[medianIndex].weight;
        weightedMedianValue = lowerValue + ((halfTotalWeight - lowerWeight) / (upperWeight - lowerWeight)) * (upperValue - lowerValue);
    }
    
    return weightedMedianValue;
}

int main() {
    // Example usage
    vector<Element> elements = {{5, 0.2}, {8, 0.3}, {12, 0.1}, {3, 0.2}, {7, 0.2}};
    double weightedMedianValue = weightedMedian(elements);
    cout << "Weighted Median: " << weightedMedianValue << endl;
    return 0;
}
