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

bool comp(weighted_edge a, weighted_edge b)
{ return (a.weight < b.weight); }



int e_kruskal = 0;
map <string, set <string>> mst_graph_kruskal;
deque <weighted_edge> all_edges_kruskal, mst_edges_kruskal;
set <string> vertices_kruskal, mst_vertices_kruskal;
map <string, bool> visited_kruskal;

void clear_kruskal() {
    e_kruskal = 0;
    mst_graph_kruskal.clear();
    all_edges_kruskal.clear();
    mst_edges_kruskal.clear();
    vertices_kruskal.clear();
    mst_vertices_kruskal.clear();
    visited_kruskal.clear();
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
    cout << "\nAggregate Minimum Spanning Tree Weight: " << all_weight_kruskal << "\n\n\n";
}

void main_kruskal()
{
    cout << "\nPerforming Kruskal Algorithm:\n";
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
    cout << "\n\n";
}



int e_prim = 0;
map <string, set <string>> all_graph_prim;
map <pair <string, string>, int> all_weights_prim;
deque <weighted_edge> all_edges_prim, mst_edges_prim;
set <string> absent_vertices_prim, mst_vertices_prim;

void clear_prim() {
    e_prim = 0;
    all_graph_prim.clear();
    all_weights_prim.clear();
    all_edges_prim.clear();
    mst_edges_prim.clear();
    absent_vertices_prim.clear();
    mst_vertices_prim.clear();
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
    cout << "\nAggregate Minimum Spanning Tree Weight: " << all_weight_prim << "\n\n\n";
}

void main_prim()
{
    cout << "\nPerforming Prim Algorithm:\n";
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
    cout << "\n\n";
}



void double_main() {
    cout << "\nExecuting both algorithms:\n";
    string temp;
    int e;
    while (true) {
        cout << "Enter your graph's number of edges (ε(G)):\n"; //input size
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) > 0) {
            e_prim = stoi(temp);
            e_kruskal = stoi(temp);
            e = stoi(temp);
            break;
        }
        else { cout << "Invalid size! Attempt aborted.\n\n"; }
    }
    all_edges_prim.resize(e_prim);
    all_edges_kruskal.resize(e_kruskal);
    for (int i = 0; i < e; ++i) {
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
            else {
                all_edges_prim[i].node1 = token;
                all_edges_kruskal[i].node1 = token;
            }

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
                all_edges_prim[i].node2 = token;
                all_edges_kruskal[i].node2 = token;
            }

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
    for (weighted_edge x : all_edges_prim) {
        absent_vertices_prim.insert(x.node1), absent_vertices_prim.insert(x.node2);
        all_graph_prim[x.node1].insert(x.node2), all_graph_prim[x.node2].insert(x.node1);
        all_weights_prim[make_pair(x.node1, x.node2)] = x.weight;
        all_weights_prim[make_pair(x.node2, x.node1)] = x.weight;
    }
    for (weighted_edge x : all_edges_kruskal) {
        vertices_kruskal.insert(x.node1), vertices_kruskal.insert(x.node2);
    }
    sort(all_edges_kruskal.begin(), all_edges_kruskal.end(), comp);
    while (true) {
        cout << "For Prim Algorithm: Enter any desired initial vertex, or \"rand\" for arbitrary choice:\n";
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
            cout << "\nStarting Prim's MST Algorithm at vertex " << temp << ":\n";
            break;
        }
        else { cout << "Invalid start! Attempt aborted.\n\n"; }
    }
    cout << "\nPerforming Prim Algorithm:\n";
    perform_prim();
    cout << "\n\nPerforming Kruskal Algorithm:\n";
    perform_kruskal();
    cout << "\n\nList of MST Vertices:\n";
    for (string a : mst_vertices_prim) {
        cout << a << ' ';
    }
    cout << "\n\nList of MST Edges (Prim):\n";
    for (weighted_edge b : mst_edges_prim) {
        cout << "  Nodes: { " << b.node1 << ' ' << b.node2 << " }, Weight: " << b.weight << '\n';
    }
    cout << "\nList of MST Edges (Kruskal):\n";
    for (weighted_edge b : mst_edges_kruskal) {
        cout << "  Nodes: { " << b.node1 << ' ' << b.node2 << " }, Weight: " << b.weight << '\n';
    }
}


int main() {
    srand(time(0));
    cout << "\nWelcome to MST Builder!\n\n";
    while (true) {
        cout << "Select function from menu below to build a minimum spanning tree (MST):\n";
        cout << "  Enter k to execute Kruskal's MST Algorithm\n";
        cout << "  Enter p to execute Prim's MST Algorithm\n";
        cout << "  Enter b to execute both MST algorithms\n";
        cout << "  Enter e to exit this program\n";
        char key_entered = cin.get();
        cin.ignore(2147483647, '\n'); 
        switch (key_entered) {
        case 'k':
            cout << "\nKey enter \"" << key_entered << "\" detected.\n";
            clear_kruskal();
            main_kruskal();
            aggregate_weight_kruskal();
            break;
        case 'p':
            cout << "\nKey enter \"" << key_entered << "\" detected.\n";
            clear_prim();
            main_prim();
            aggregate_weight_prim();
            break;
        case 'b':
            cout << "\nKey enter \"" << key_entered << "\" detected.\n";
            clear_kruskal();
            clear_prim();
            double_main();
            aggregate_weight_kruskal();
            break;
        case 'e':
            return 0;
        default:
            cout << "\n\"" << key_entered << "\" is an invalid key enter! Attempt aborted.\n";
            break;
        }
    }
    return 0;
}
