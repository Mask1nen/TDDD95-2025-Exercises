#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct sentencePair {
    vector<string> sentence1;
    vector<string> sentence2;
};

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


bool attemptMapping(vector<string> sentence1, vector<string> sentence2, unordered_map<string, string> validplaceholders, unordered_map<string, vector<string>> placeholdervalues, int index) {

    for (auto entry: placeholdervalues) {
        if (entry.second.size() > 1) {

        }
    }
    
}

sentencePair applyPlaceholder(vector<string> sentence1, vector<string> sentence2, unordered_map<string,string> validplaceholders) {
    for (int i = 0; i < sentence1.size(); i++) {
        string word1 = sentence1[i];
        string word2 = sentence2[i];

        if(isPlaceholder(word1)) {
            sentence1[i] = validplaceholders[word1];
        }
        if(isPlaceholder(word2)) {
            sentence2[i] = validplaceholders[word2];
        }
        sentencePair sentences = {sentence1, sentence2};
        return sentences;
    }
}

int main() {
    ifstream inputFile("help_input.txt");  // Open the file for reading
    if (!inputFile) {
        cerr << "Error: Could not open input.txt!" << endl;
        return 1;
    }

    int testCases;
    inputFile >> testCases;
    inputFile.ignore();  // Ignore newline after testCases
    unordered_map<string, vector<string>> placeholdervalues;
    unordered_map<string, string> validplaceholders;

    //Fetch input
    while (testCases--) {
        string pattern1, pattern2;
        vector<string> sentence1, sentence2;
        getline(inputFile, pattern1);
        getline(inputFile, pattern2);
        sentence1 = splitSentence(pattern1);
        sentence2 = splitSentence(pattern2);

        //If pattern1 size does not match pattern2 size there cannot be a match
        if(sentence1.size() != sentence2.size()) {
            cout << "-" << endl; 
        }
        else {
            for (int i = 0; i < sentence1.size(); i++) {
                string word1 = sentence1[i];
                string word2 = sentence2[i];

                //If word1 is placeholder
                if(isPlaceholder(word1)) {
                    //If placeholder value has not been recorded and the second word is not a placeholder add value to candidate placeholders
                    if (placeholdervalues.count(word1) == 0 && !isPlaceholder(word2)) {
                        placeholdervalues[word1].push_back(sentence2[i]);
                    }
                }

                //If word1 is placeholder
                if(isPlaceholder(word2)) {
                    //If placeholder value has not been recorded and the first word is not a placeholder add value to candidate placeholders
                    if (placeholdervalues.count(word2) == 0 && !isPlaceholder(word1)) {
                        placeholdervalues[word2].push_back(sentence1[i]);
                    }
                }

            }


            
            if(sentence1 == sentence2) {
                for(int i = 0; i < sentence1.size(); i++) {
                    cout << sentence1[i] << " ";
                }
                cout << endl;
            }
            else {
                cout << "-" << endl;
            }
        }

    }


    inputFile.close();
    return 0;
}