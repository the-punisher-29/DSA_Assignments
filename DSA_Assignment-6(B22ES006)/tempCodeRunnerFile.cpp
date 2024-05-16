void test_preorder(Lexicon* lexicon) {
    vector<HybridNode*> preorder_traversal = lexicon->getRedBlackTree().preOrderTraversal(lexicon->getRedBlackTree().getRoot(), 9);

    assert(preorder_traversal.size() == 234);
}