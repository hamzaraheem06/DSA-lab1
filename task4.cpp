#include<iostream>

using namespace std;

int findPattern(string s, string p) {
    int m = s.length();
    int n = p.length();

    if (!m || !n) return -1; // if any is empty 

    if (n > m) return -1; // pattern string is larger than the string

    string w = s.substr(0, n); // first window
    
    if(w == p) return 0;

    for (int i = n; i < m; i++) {
        w.erase(0, 1);
        w.push_back(s[i]);
        if(w == p) return i - n + 1;
    }

    return -1;
}

// -------- Test Cases --------
void testPatternAtBeginning() {
    string text = "hello world";
    string pattern = "hello";
    int result = findPattern(text, pattern);
    cout << "Test Pattern At Beginning: " << result << " (expected 0)" << endl;
}

void testPatternAtEnd() {
    string text = "openai rocks";
    string pattern = "rocks";
    int result = findPattern(text, pattern);
    cout << "Test Pattern At End: " << result << " (expected 7)" << endl;
}

void testPatternNotPresent() {
    string text = "abcdef";
    string pattern = "gh";
    int result = findPattern(text, pattern);
    cout << "Test Pattern Not Present: " << result << " (expected -1)" << endl;
}

void testEmptyPattern() {
    string text = "anything";
    string pattern = "";
    int result = findPattern(text, pattern);
    cout << "Test Empty Pattern: " << result << " (expected -1)" << endl;
}

// -------- main --------
int main() {
    testPatternAtBeginning();
    testPatternAtEnd();
    testPatternNotPresent();
    testEmptyPattern();
    return 0;
}