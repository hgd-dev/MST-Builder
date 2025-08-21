#include <iostream>
#include <map>
#include <deque>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
struct weighted_edge {
    int weight = 0;
    string node1;
    string node2;
};
int e_kruskal = 0;
map <string, set <string>> mst_graph_kruskal;
deque <weighted_edge> all_edges_kruskal, mst_edges_kruskal;
set <string> vertices_kruskal, mst_vertices_kruskal;
map <string, bool> visited_kruskal;
bool is_integer(string str) //Test if a given string is an integer
{
    if (str.empty()) return false;
    while (str.front() == ' ') {
        str = str.substr(1);
    }
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.size() == 1) return false;
        start = 1;
    }
    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
bool detect_component_cycle_kruskal(string node, string parent)
{
    visited_kruskal[node] = 1;
    for (string neighbor : mst_graph_kruskal[node]) {
        if (parent == neighbor) { continue; }
        if (visited_kruskal[neighbor] == 1) { return true; }
        if (detect_component_cycle_kruskal(neighbor, node)) { return true; }
    }
    return false;
}
bool detect_graph_cycle_kruskal()
{
    for (string str : vertices_kruskal) { visited_kruskal[str] = false; }
    for (string str : vertices_kruskal) {
        if (!visited_kruskal[str]) {
            if (detect_component_cycle_kruskal(str, "-1")) { return true; }
        }
    }
    return false;
}
void add_edge_kruskal(int index)
{
    mst_graph_kruskal[all_edges_kruskal[index].node1].insert(all_edges_kruskal[index].node2);
    mst_graph_kruskal[all_edges_kruskal[index].node2].insert(all_edges_kruskal[index].node1);
}
void remove_edge_kruskal(int index)
{
    mst_graph_kruskal[all_edges_kruskal[index].node1].erase(all_edges_kruskal[index].node2);
    mst_graph_kruskal[all_edges_kruskal[index].node2].erase(all_edges_kruskal[index].node1);
}
bool comp(weighted_edge a, weighted_edge b)
{ return (a.weight < b.weight); }
void perform_kruskal()
{
    int edge_index = 0;
    while (mst_vertices_kruskal.size() != vertices_kruskal.size()) {
        add_edge_kruskal(edge_index);
        if (detect_graph_cycle_kruskal()) {
            remove_edge_kruskal(edge_index);
        }
        else {
            mst_edges_kruskal.push_back(all_edges_kruskal[edge_index]);
            cout << "\nNew edge added between nodes { " << all_edges_kruskal[edge_index].node1 << ' ' << all_edges_kruskal[edge_index].node2 << " } of weight " << all_edges_kruskal[edge_index].weight << '\n';
            bool firstdisplay = false;
            if (mst_vertices_kruskal.find(all_edges_kruskal[edge_index].node1) == mst_vertices_kruskal.end()) {
                mst_vertices_kruskal.insert(all_edges_kruskal[edge_index].node1);
                cout << "along with new node " << all_edges_kruskal[edge_index].node1;
                firstdisplay = true;
            }
            if (mst_vertices_kruskal.find(all_edges_kruskal[edge_index].node2) == mst_vertices_kruskal.end()) {
                mst_vertices_kruskal.insert(all_edges_kruskal[edge_index].node2);
                if (firstdisplay) {
                    cout << " and new node " << all_edges_kruskal[edge_index].node2;
                }
                else {
                    cout << "along with new node " << all_edges_kruskal[edge_index].node2;
                }
            }
            cout << '\n';
        }
        ++edge_index;
    }
}
void aggregate_weight_kruskal() {
    int all_weight_kruskal = 0;
    for (weighted_edge b : mst_edges_kruskal) {
        all_weight_kruskal += b.weight;
    }
    cout << "\nAggregate Minimum Spanning Tree Weight: " << all_weight_kruskal << '\n';
}
int main()
{
    string temp;
    while (true) {
        cout << "Enter your graph's number of edges (ε(G)):\n"; //input size
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) > 0) {
            e_kruskal = stoi(temp);
            break;
        }
        else { cout << "Invalid size! Attempt aborted.\n\n"; }
    }
    all_edges_kruskal.resize(e_kruskal);
    for (int i = 0; i < e_kruskal; ++i) {
        while (true) {
            cout << "Input edge " << i + 1 << " in the form: node1 node2 weight\n";
            bool inputValid = true;
            getline(cin, temp);
            temp = temp + ' ';
            istringstream iss(temp);

            string token = "";
            while (token.empty()) {
                if (getline(iss, token, ' ')) {}
                else {
                    inputValid = false;
                    break;
                }
            }
            if (!inputValid) {
                cout << "Invalid edge! Attempt aborted.\n\n";
                continue;
            }
            else { all_edges_kruskal[i].node1 = token; }

            token = "";
            while (token.empty()) {
                if (getline(iss, token, ' ')) {}
                else {
                    inputValid = false;
                    break;
                }
            }
            if (!inputValid) {
                cout << "Invalid edge! Attempt aborted.\n\n";
                continue;
            }
            else { all_edges_kruskal[i].node2 = token; }

            token = "";
            while (token.empty()) {
                if (getline(iss, token, ' ')) {}
                else {
                    inputValid = false;
                    break;
                }
            }
            if (!inputValid) {
                cout << "Invalid edge! Attempt aborted.\n\n";
                continue;
            }
            else {
                if (is_integer(token)) {
                    all_edges_kruskal[i].weight = (stoi(token));
                }
                else { inputValid = false; }
            }
            if (!inputValid) {
                cout << "Invalid edge! Attempt aborted.\n\n";
                continue;
            }
            else { break; }
        }
    }
    for (weighted_edge x : all_edges_kruskal) {
        vertices_kruskal.insert(x.node1), vertices_kruskal.insert(x.node2);
    }
    sort(all_edges_kruskal.begin(), all_edges_kruskal.end(), comp);
    perform_kruskal();
    cout << "\n\nList of MST vertices:\n";
    for (string a : vertices_kruskal) {
        cout << a << ' ';
    }
    cout << "\n\nList of MST Edges:\n";
    for (weighted_edge b : mst_edges_kruskal) {
        cout << "  Nodes: { " << b.node1 << ' ' << b.node2 << " }, Weight: " << b.weight << '\n';
    }
    aggregate_weight_kruskal();
    return 0;
}
