#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> splitSentence(string sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while(ss >> word) {
        words.push_back(word);
    }
    return words;
}

bool isPlaceholder(string word) {
    return !word.empty() && word.front() == '<' && word.back() == '>';
}

int main() {
    int testCases;
    cin >> testCases;
    cin.ignore();

    //Fetch input
    string match = "";
    vector<string> output;
    while (testCases--) {
        unordered_map<string, string> placeholdervalues1;
        unordered_map<string, string> placeholdervalues2;
        string pattern1, pattern2;
        vector<string> sentence1, sentence2;
        getline(cin, pattern1);
        getline(cin, pattern2);
        if (pattern1.empty() || pattern2.empty()) {
            continue; // Skip empty input lines
        }
        sentence1 = splitSentence(pattern1);
        sentence2 = splitSentence(pattern2);

        //Set match as false, changed by logic below if a match is found.
        match = "-";
        if(sentence1.size() == sentence2.size()) {
            bool updated = true;
            while(updated) {
                updated = false;
                for (int i = 0; i < sentence1.size(); i++) {
                    string word1 = sentence1[i];
                    string word2 = sentence2[i];

                    //If word1 is placeholder
                    if(isPlaceholder(word1)) {
                        //If placeholder value has not been recorded and the second word is not a placeholder add value to candidate placeholders
                        if (placeholdervalues1.count(word1) == 0 && !isPlaceholder(word2)) {
                            placeholdervalues1[word1] = word2;
                        }
                    }

                    //If word2 is placeholder
                    if(isPlaceholder(word2)) {
                        //If placeholder value has not been recorded and the first word is not a placeholder add value to candidate placeholders
                        if (placeholdervalues2.count(word2) == 0 && !isPlaceholder(word1)) {
                            placeholdervalues2[word2] = word1;
                        }
                    }

                }
            
                for (int i = 0; i < sentence1.size(); i++) {
                    string word1 = sentence1[i];
                    string word2 = sentence2[i];

                    //If placeholder exists in placeholder1 map as key, replace with value
                    if (placeholdervalues1.count(word1) > 0) {
                        updated = true;
                        sentence1[i] = placeholdervalues1[word1];
                    }

                    //If word exists in placeholder2 map, replace with value
                    if (placeholdervalues2.count(word2) > 0) {
                        updated = true;
                        sentence2[i] = placeholdervalues2[word2];
                    }
                }
            }
        
            //Recreate strings from vectors after placeholder handling
            string resultPhrase1 = "";
            string resultPhrase2 = "";

            for (int i = 0; i < sentence1.size(); i++) {
                string word1 = sentence1[i];
                string word2 = sentence2[i];

                if (!resultPhrase1.empty()) {
                    resultPhrase1 += " ";
                }
                if (!resultPhrase2.empty()) {
                    resultPhrase2 += " ";
                }
                if (isPlaceholder(word1)) {
                    resultPhrase1 += "random";
                }
                else {
                    resultPhrase1 += word1;
                }
                if (isPlaceholder(word2)) {
                    resultPhrase2 += "random";
                }
                else {
                    resultPhrase2 += word2;
                }
            }
            //cout << resultPhrase1 << endl;
            
            //cout << resultPhrase2 << endl;
            if(resultPhrase1 == resultPhrase2) {
                match = resultPhrase1;
            }
        }
        
        cout << match << endl;
    }
    return 0;
}