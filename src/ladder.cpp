#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error processing \"" << word1 << "\" -> \"" 
         << word2 << "\": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = (int)str1.size();
    int len2 = (int)str2.size();
    int diff = abs(len1 - len2);
    if (diff > 1) return false;

    if (len1 == len2) {
        int mismatchCount = 0;
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) {
                mismatchCount++;
                if (mismatchCount > d) return false;
            }
        }
        return (mismatchCount == d);
    }
    else {
        const string& longer = (len1 > len2) ? str1 : str2;
        const string& shorter = (len1 > len2) ? str2 : str1;

        int i = 0, j = 0;
        int mismatchCount = 0;
        while (i < (int)longer.size() && j < (int)shorter.size()) {
            if (longer[i] != shorter[j]) {
                mismatchCount++;
                if (mismatchCount > 1) return false;
                i++; 
            } else {
                i++;
                j++;
            }
        }
        mismatchCount += ( (int)longer.size() - i );
        return (mismatchCount == 1);
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word,
                                    const string& end_word,
                                    const set<string>& word_list)
{
    if (begin_word == end_word) {
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({ begin_word });

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();

        const string& last_word = current_ladder.back();

        if (last_word == end_word) {
            return current_ladder;  // BFS ensures this is one of the shortest
        }

        for (auto& candidate : word_list) {
            if (visited.find(candidate) == visited.end()) {
                if (is_adjacent(last_word, candidate)) {
                    visited.insert(candidate);
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(candidate);
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        cerr << "Error: Cannot open file " << file_name << endl;
        return;
    }
    string w;
    while (in >> w) {
        for (auto &c : w) c = (char)tolower(c);
        word_list.insert(w);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
        return;
    }
    for (int i = 0; i < (int)ladder.size(); i++) {
        cout << ladder[i];
        if (i < (int)ladder.size() - 1) cout << " -> ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");

    auto test1 = generate_word_ladder("cat", "dog", word_list);
    cout << "cat -> dog ladder length = " << test1.size() << endl;

    auto test2 = generate_word_ladder("marty", "curls", word_list);
    cout << "marty -> curls ladder length = " << test2.size() << endl;
}
