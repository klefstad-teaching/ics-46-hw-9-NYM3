#include "gtest/gtest.h"
#include "ladder.h"
#include "dijkstras.h"

#include <set>
#include <vector>
#include <string>
using namespace std;

// Helper to load the dictionary from a relative path.
// Adjust the path as needed for your project structure.
void loadTestDictionary(set<string>& word_list) {
    // If you run tests from the build/ directory and your words.txt is in src/,
    // then this relative path should work:
    load_words(word_list, "../src/words.txt");
}

// ===== Word Ladder Tests =====

TEST(WordLadderTest, CatToDog) {
    set<string> word_list;
    loadTestDictionary(word_list);
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    // Expected ladder length is 4 (e.g., cat -> cot -> cog -> dog)
    EXPECT_EQ(ladder.size(), 4);
}

TEST(WordLadderTest, MartyToCurls) {
    set<string> word_list;
    loadTestDictionary(word_list);
    vector<string> ladder = generate_word_ladder("marty", "curls", word_list);
    // Expected ladder length is 6
    EXPECT_EQ(ladder.size(), 6);
}

TEST(WordLadderTest, CodeToData) {
    set<string> word_list;
    loadTestDictionary(word_list);
    vector<string> ladder = generate_word_ladder("code", "data", word_list);
    // Expected ladder length is 6
    EXPECT_EQ(ladder.size(), 6);
}

TEST(WordLadderTest, WorkToPlay) {
    set<string> word_list;
    loadTestDictionary(word_list);
    vector<string> ladder = generate_word_ladder("work", "play", word_list);
    // Expected ladder length is 6
    EXPECT_EQ(ladder.size(), 6);
}

TEST(WordLadderTest, SleepToAwake) {
    set<string> word_list;
    loadTestDictionary(word_list);
    vector<string> ladder = generate_word_ladder("sleep", "awake", word_list);
    // Expected ladder length is 8
    EXPECT_EQ(ladder.size(), 8);
}

TEST(WordLadderTest, CarToCheat) {
    set<string> word_list;
    loadTestDictionary(word_list);
    vector<string> ladder = generate_word_ladder("car", "cheat", word_list);
    // Expected ladder length is 4 (e.g., car -> cat -> chat -> cheat)
    EXPECT_EQ(ladder.size(), 4);
}

// ===== Dijkstra’s Algorithm Tests =====

TEST(DijkstrasTest, SimpleGraph) {
    // Construct a simple graph manually.
    // Graph: 4 vertices
    // Edges:
    //   0 -> 1 (weight 2), 0 -> 3 (weight 1)
    //   3 -> 1 (weight 2)
    //   1 -> 2 (weight 3)
    Graph G;
    G.numVertices = 4;
    G.resize(G.numVertices);
    
    // Add edges for vertex 0
    G[0].push_back(Edge(0, 1, 2));
    G[0].push_back(Edge(0, 3, 1));
    // Add edge for vertex 3
    G[3].push_back(Edge(3, 1, 2));
    // Add edge for vertex 1
    G[1].push_back(Edge(1, 2, 3));
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    // Verify distances from vertex 0:
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 3); // via 0 -> 3 -> 1 (1+2)
    EXPECT_EQ(distances[2], 6); // via 0 -> 3 -> 1 -> 2 (1+2+3)
    EXPECT_EQ(distances[3], 1); // direct from 0 -> 3

    // Test the extracted path to vertex 2: should be [0, 3, 1, 2]
    vector<int> path_to_2 = extract_shortest_path(distances, previous, 2);
    vector<int> expected_path = {0, 3, 1, 2};
    EXPECT_EQ(path_to_2, expected_path);
}
