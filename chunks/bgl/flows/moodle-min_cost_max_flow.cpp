// Example using the different MinCostMaxFlow algorithms
// in BGL to implement the 'fruit delivery' example from the slides.

#include <iostream>
#include <cstdlib>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor,
                property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator


struct EdgeAdder {
    EdgeAdder(Graph & G, EdgeCapacityMap &capacity, EdgeWeightMap &weight, ReverseEdgeMap &rev_edge) 
        : G(G), capacity(capacity), weight(weight), rev_edge(rev_edge) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacity[e] = c;
        weight[e] = w;
        capacity[reverseE] = 0;
        weight[reverseE] = -w;
        rev_edge[e] = reverseE; 
        rev_edge[reverseE] = e; 
    }
    Graph &G;
    EdgeCapacityMap &capacity;
    EdgeWeightMap &weight;
    ReverseEdgeMap  &rev_edge;
};

int main() {
    const int N=7;
    const int v_source = 0;
    const int v_farm1 = 1;
    const int v_farm2 = 2;
    const int v_farm3 = 3;
    const int v_shop1 = 4;
    const int v_shop2 = 5;
    const int v_target = 6;

    // Create Graph and Maps
    Graph G(N);
    EdgeCapacityMap capacity = get(edge_capacity, G);
    EdgeWeightMap weight = get(edge_weight, G);
    ReverseEdgeMap rev_edge = get(edge_reverse, G);
    ResCapacityMap res_capacity = get(edge_residual_capacity, G);
    EdgeAdder ea(G, capacity, weight, rev_edge);
    
    // Add the edges
    ea.addEdge(v_source,v_farm1,3,0);
    ea.addEdge(v_source,v_farm2,1,0);
    ea.addEdge(v_source,v_farm3,2,0);

    ea.addEdge(v_farm1,v_shop1,1,1);
    ea.addEdge(v_farm1,v_shop2,1,5);
    ea.addEdge(v_farm2,v_shop1,1,2);
    ea.addEdge(v_farm2,v_shop2,1,2);
    ea.addEdge(v_farm3,v_shop1,1,3);
    ea.addEdge(v_farm3,v_shop2,2,2);

    ea.addEdge(v_shop1,v_target,3,0);
    ea.addEdge(v_shop2,v_target,3,0);

    // Run the algorithm

    // Option 1: Min Cost Max Flow with cycle_canceling
    int flow1 = push_relabel_max_flow(G, v_source, v_target);
    cycle_canceling(G);
    int cost1 = find_flow_cost(G);
    cout << "-----------------------" << endl;
    cout << "Minimum Cost Maximum Flow with cycle_canceling()" << endl;
    cout << "flow " << flow1 << endl; // 5
    cout << "cost " << cost1 << endl; // 12

    // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights
    successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost2 = find_flow_cost(G);
    int flow2 = 0;
    // Iterate over all edges leaving the source
    OutEdgeIt e, eend;
    for(tie(e, eend) = out_edges(vertex(v_source,G), G); e != eend; ++e) {
        flow2 += capacity[*e] - res_capacity[*e];
    }
    cout << "-----------------------" << endl;
    cout << "Minimum Cost Maximum Flow with successive_shortest_path_nonnegative_weights()" << endl;
    cout << "flow " << flow2 << endl; // 5
    cout << "cost " << cost2 << endl; // 12
    cout << "-----------------------" << endl;

}
