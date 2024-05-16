void test_case_2() {
//     // create a PRC object
//     PRC prc(5, 5);
//     // create a graph
//     prc.create_graph("samples/5/graph.txt");
//     prc.process_parcels("samples/5/bookings.txt");
//     prc.run_simulation(4);
//     assert(prc.all_parcels_delivered() == false);
//     std::vector<std::string> delivered_parcels = prc.get_delivered_parcels();
//     assert(std::find(delivered_parcels.begin(), delivered_parcels.end(), "P31") == delivered_parcels.end());
//     assert(prc.get_parcels_delivered_up_to_time_tick(4).size() == 25);
// }

// void test_case_3() {
//     // create a PRC object
//     PRC prc(2, 2);
//     // create a graph
//     prc.create_graph("samples/1/graph.txt");
//     prc.process_parcels("samples/1/bookings.txt");
//     prc.run_simulation(20);
//     assert(prc.time_tick < 20);
// }
