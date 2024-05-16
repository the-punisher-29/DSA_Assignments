void test_searchkeyin_BST() {
    class TempBinaryTree : public BinarySearchTree {
    public:
        TempBinaryTree(BinaryTreeNode* root1) {
            this->root = root1;
        }
    };
    TravelDesk travelDesk;
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1000);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1400);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1300);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1200);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 900);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 800);
    travelDesk.addTrip("A1", 4, "LocationA", "LocationB", 1500);

    BinaryTreeNode* rootLocationA = travelDesk.getLocation("LocationA")->getServicePtr("LocationB")->getBSTHead();

    TempBinaryTree* temp1 = new TempBinaryTree(rootLocationA);

    BinaryTreeNode* node = temp1->searchNodeWithKey(1200);
    bool flag1=customAssert( node!=nullptr && node->getDepartureTime() == 1200 , "Node with key 1200 not found or has incorrect departure time.");

 
    BinaryTreeNode* node1 = temp1->searchNodeWithKey(1200);
    
    bool flag2=customAssert(node1 == nullptr , "Node is not a nullptr");
    if(flag1 && flag2)testCasesPassed++;
}