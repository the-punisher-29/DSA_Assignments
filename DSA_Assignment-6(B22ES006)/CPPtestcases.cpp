#include <bits/stdc++.h>
#include "interface_template.cpp"
#include <cassert>
using namespace std;

int failed_tests = 0;

void test_index_entry1() {
    vector<IndexEntry> index_entry = lexicon.buildIndex();

    for (auto& entry : index_entry) {
        if (entry.getWord() == "he" && entry.getChapterWordCounts()[0].first == "Chapter1") {
            assert(entry.getChapterWordCounts()[1].second == 17);
        }
        if (entry.getWord() == "cave" && entry.getChapterWordCounts()[0].first == "Chapter1") {
            assert(entry.getChapterWordCounts()[1].second == 8);
        }
    }
}

void test_index_entry2() {
    vector<IndexEntry> index_entry = lexicon.buildIndex();

    for (auto& entry : index_entry) {
        if (entry.getWord() == "anyone" && entry.getChapterWordCounts()[0].first == "Chapter2") {
            assert(entry.getChapterWordCounts()[1].second == 1);
        }
        if (entry.getWord() == "emily" && entry.getChapterWordCounts()[0].first == "Chapter2") {
            assert(entry.getChapterWordCounts()[1].second == 3);
        }
    }
}

void test_index_entry3() {
    vector<IndexEntry> index_entry = lexicon.buildIndex();

    for (auto& entry : index_entry) {
        if (entry.getWord() == "heal" && entry.getChapterWordCounts()[0].first == "Chapter3") {
            assert(entry.getChapterWordCounts()[1].second == 1);
        }
        if (entry.getWord() == "from" && entry.getChapterWordCounts()[0].first == "Chapter3") {
            assert(entry.getChapterWordCounts()[1].second == 1);
        }
    }
}

void test_preorder() {
    vector<string> preorder_traversal = lexicon.getRedBlackTree().preOrderTraversal(lexicon.getRedBlackTree().getRoot(), 0);

    assert(preorder_traversal.size() == 251);
}

void test_black_height() {
    assert(lexicon.getRedBlackTree().blackheight(lexicon.getRedBlackTree().getRoot()) == 8);
}

void test_search() {
    HybridNode* node = lexicon.getRedBlackTree().search("he");
    assert(node->element == "he");  

    node = lexicon.getRedBlackTree().search("Machine");
    assert(node == nullptr);
}

void test_delete() {
    lexicon.getRedBlackTree().deleteNode("he");
    assert(lexicon.getRedBlackTree().search("he") == nullptr);    
}

int main() {
    std::vector<void(*)()> unit_tests_list = {
        test_index_entry1,
        test_index_entry2,
        test_index_entry3,
        test_preorder,
        test_black_height,
        test_search,
        test_delete
    };
    int total = unit_tests_list.size();

    for (int i = 0; i < total; ++i) {
        try {
            unit_tests_list[i]();
        } catch (const std::exception& e) {
            failed_tests++;
            std::cout << "Unit test " << i << " failure: " << e.what() << std::endl;
        }
    }

    if (failed_tests == 0) {
        std::cout << "All tests have passed successfully!" << std::endl;
    } else {
        std::cout << failed_tests << " tests failed!" << std::endl;
    }

    return failed_tests;
}
