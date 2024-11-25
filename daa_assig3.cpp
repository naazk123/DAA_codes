#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A class to represent an item with a value, weight, and value-to-weight ratio
class Item {
public:
    int value;  // Value of the item
    int weight; // Weight of the item
    double ratio; // Value-to-weight ratio

    // Constructor to initialize an item
    Item(int value, int weight) {
        this->value = value;
        this->weight = weight;
        this->ratio = (double)value / weight;
    }
};

// Comparator function to sort items based on value-to-weight ratio in descending order
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Function to solve the Fractional Knapsack problem using the greedy method
double fractionalKnapsack(int capacity, vector<Item>& items) {
    // Sort items based on the value-to-weight ratio in descending order
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;  // To store the total value of the knapsack

    for (auto& item : items) {
        // If the knapsack can still hold the whole item, take it
        if (capacity >= item.weight) {
            capacity -= item.weight;
            totalValue += item.value;
        }
        // Otherwise, take the fraction of the item
        else {
            totalValue += item.value * ((double)capacity / item.weight);
            break;  // Knapsack is full
        }
    }

    return totalValue;  // Return the total value of the knapsack
}

int main() {
    // Example items: value, weight
    vector<Item> items = {
        Item(60, 10),  // Item 1 (value=60, weight=10)
        Item(100, 20), // Item 2 (value=100, weight=20)
        Item(120, 30)  // Item 3 (value=120, weight=30)
    };

    int capacity = 50;  // Knapsack capacity

    double maxValue = fractionalKnapsack(capacity, items);

    cout << "Maximum value in Knapsack = " << maxValue << endl;

    return 0;
}
