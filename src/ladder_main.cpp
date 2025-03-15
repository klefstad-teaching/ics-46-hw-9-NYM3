#include "ladder.h"

int main() {
    set<string> word_list;
   load_words(word_list, "../src/words.txt");

    cout << "Enter the start word: ";
    string start;
    cin >> start;
    cout << "Enter the end word: ";
    string end;
    cin >> end;

    for (auto &c : start) c = (char)tolower(c);
    for (auto &c : end)   c = (char)tolower(c);

    if (start == end) {
        error(start, end, "Start and end words are the same. Cannot continue.");
        return 1;
    }

    vector<string> ladder = generate_word_ladder(start, end, word_list);

    if (ladder.empty()) {
        cout << "No ladder found from " << start << " to " << end << "." << endl;
    } else {
        cout << "Ladder from " << start << " to " << end << ":" << endl;
        print_word_ladder(ladder);
    }

    return 0;
}
