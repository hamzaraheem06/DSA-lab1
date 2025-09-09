#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

vector<int> modeOfArray(vector<int>& nums) {
    if (nums.empty()) return {};

    vector<int> mode;
    unordered_map<int, int> freq; // using a frequency map

    for (int i = 0; i < nums.size(); i++) {
        freq[nums[i]] += 1;
    }

    int maxFreq = 0; // randomly select the maxFreq

    for (auto it = freq.begin(); it != freq.end(); ++it) {
        if (it->second > maxFreq) maxFreq = it->second;
    }

    for (auto it = freq.begin(); it != freq.end(); ++it) {
        if (it->second == maxFreq) mode.push_back(it->first);
    }

    sort(mode.begin(), mode.end());

    return mode;
}

// Helper function: compare vectors
bool areEqual(vector<int>& a, vector<int>& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// Test 1: array with a clear mode
void testMode1() {
    vector<int> nums{1, 2, 2, 3, 4, 2, 5};
    vector<int> expected = {2};
    vector<int> result = modeOfArray(nums);

    if (areEqual(expected, result)) {
        cout << "Test 1 (clear mode) passed!" << endl;
    } else {
        cout << "Test 1 (clear mode) failed!" << endl;
    }
}

void display(vector<int> arr) {

    string res = "[ ";
    for (int i = 0; i < arr.size(); i++) {
        res.append(std::to_string(arr[i])); 
        if (i != arr.size() - 1) res.append(", ");
    }
    res.append(" ]");
    cout<<res<<endl; 
}


// Test 2: multiple modes (same frequency)
void testMode2() {
    vector<int> nums{4, 4, 5, 5, 6, 6};
    vector<int> expected = {4, 5, 6};
    vector<int> result = modeOfArray(nums);

    if (areEqual(expected, result)) {
        cout << "Test 2 (multiple modes) passed!" << endl;
    } else {
        cout << "Test 2 (multiple modes) failed!" << endl;
    }
}

// Test 3: empty array
void testMode3() {
    vector<int> nums{};
    vector<int> expected = {}; // Convention for empty array
    vector<int> result = modeOfArray(nums);

    if (areEqual(expected, result)) {
        cout << "Test 3 (empty array) passed!" << endl;
    } else {
        cout << "Test 3 (empty array) failed!" << endl;
    }
}

int main() {
    testMode1();
    testMode2();
    testMode3();
    return 0;
}
