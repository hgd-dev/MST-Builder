#include <iostream>
#include <map>
#include <deque>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <random>
#include <time.h>
#include <iterator>
using namespace std;
struct weighted_edge {
    int weight = 0;
    string node1;
    string node2;
};
int e_prim = 0;
map <string, set <string>> all_graph_prim;
map <pair <string, string>, int> all_weights_prim;
deque <weighted_edge> all_edges_prim, mst_edges_prim;
set <string> absent_vertices_prim, mst_vertices_prim;
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

void add_edge_prim(weighted_edge new_edge)
{
    mst_vertices_prim.insert(new_edge.node1), mst_vertices_prim.insert(new_edge.node2);
    mst_edges_prim.push_back(new_edge);
    cout << "\nNew edge added between nodes { " << new_edge.node1 << ' ' << new_edge.node2 << " } of weight " << new_edge.weight << '\n';
    if (absent_vertices_prim.find(new_edge.node1) != absent_vertices_prim.end()) {
        absent_vertices_prim.erase(new_edge.node1);
        cout << "along with new node " << new_edge.node1 << '\n';
    }
    else if (absent_vertices_prim.find(new_edge.node2) != absent_vertices_prim.end()) {
        absent_vertices_prim.erase(new_edge.node2);
        cout << "along with new node " << new_edge.node2 << '\n';
    }
}
bool comp(weighted_edge a, weighted_edge b)
{ return (a.weight < b.weight); }
void perform_prim()
{
    while (!absent_vertices_prim.empty()) {
        weighted_edge to_add;
        deque <weighted_edge> valid_edges;
        for (string node : mst_vertices_prim) {
            for (string neighbor : all_graph_prim[node]) {
                if (absent_vertices_prim.find(neighbor) != absent_vertices_prim.end()) {
                    to_add.node1 = node, to_add.node2 = neighbor;
                    to_add.weight = all_weights_prim[make_pair(node, neighbor)];
                    valid_edges.push_back(to_add);
                }
            }
        }
        sort(valid_edges.begin(), valid_edges.end(), comp);
        add_edge_prim(valid_edges[0]);
    }
}
void aggregate_weight_prim() {
    int all_weight_prim = 0;
    for (weighted_edge b : mst_edges_prim) {
        all_weight_prim += b.weight;
    }
    cout << "\nAggregate Minimum Spanning Tree Weight: " << all_weight_prim << '\n';
}
int main()
{
    srand(time(0));
    string temp;
    while (true) {
        cout << "Enter your graph's number of edges (ε(G)):\n"; //input size
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) > 0) {
            e_prim = stoi(temp);
            break;
        }
        else { cout << "Invalid size! Attempt aborted.\n\n"; }
    }
    all_edges_prim.resize(e_prim);
    for (int i = 0; i < e_prim; ++i) {
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
            else { all_edges_prim[i].node1 = token; }

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
            else { all_edges_prim[i].node2 = token; }

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
                    all_edges_prim[i].weight = (stoi(token));
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
    for (weighted_edge x : all_edges_prim) {
        absent_vertices_prim.insert(x.node1), absent_vertices_prim.insert(x.node2);
        all_graph_prim[x.node1].insert(x.node2), all_graph_prim[x.node2].insert(x.node1);
        all_weights_prim[make_pair(x.node1, x.node2)] = x.weight;
        all_weights_prim[make_pair(x.node2, x.node1)] = x.weight;
    }
    while (true) {
        cout << "Enter any desired initial vertex, or \"rand\" for arbitrary choice:\n";
        getline(cin, temp);
        if (absent_vertices_prim.find(temp) != absent_vertices_prim.end()) {
            mst_vertices_prim.insert(temp);
            absent_vertices_prim.erase(temp);
            cout << "\nStarting MST at vertex " << temp << ":\n";
            break;
        }
        else if (temp == "rand") {
            int random_index = (rand() % absent_vertices_prim.size());
            set <string>::iterator it = absent_vertices_prim.begin();
            advance(it, random_index);
            temp = *it;
            mst_vertices_prim.insert(temp);
            absent_vertices_prim.erase(temp);
            cout << "\nStarting MST at vertex " << temp << ":\n";
            break;
        }
        else { cout << "Invalid start! Attempt aborted.\n\n"; }
    }
    perform_prim();
    cout << "\n\nList of MST Vertices:\n";
    for (string a : mst_vertices_prim) {
        cout << a << ' ';
    }
    cout << "\n\nList of MST Edges:\n";
    for (weighted_edge b : mst_edges_prim) {
        cout << "  Nodes: { " << b.node1 << ' ' << b.node2 << " }, Weight: " << b.weight << '\n';
    }
    aggregate_weight_prim();
    return 0;
}
