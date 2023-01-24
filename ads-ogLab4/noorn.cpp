#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class DirectedGraph {
public:
    int vertex_count;
    unordered_map<int, unordered_set<int>> adj;

    void dfs_r(int curr, unordered_map<int, bool>& visited, set<int> res,list<int>& visitPath) {
        int temp = curr;
        visited[curr] = true;
        res.insert(curr);
        visitPath.emplace_back(curr);
        vector<int> sorted_adj;
        for (auto& e : adj[curr]) 
        {
            sorted_adj.push_back(e);
        }
        sort(sorted_adj.begin(), sorted_adj.end());
        for (auto& e : sorted_adj) 
        {
            if (!visited[e])
            {
                visitPath.emplace_back(curr);
                dfs_r(e, visited, res,visitPath);
            }
        }
    }

    void add_vertex(int n) {
        // already in the graph
        if (adj.find(n) != adj.end()) {
            cout << "Vertex " << n << " is already in the graph" << endl;
            return;
        }

        adj[n] = {};
        vertex_count++;
    }

    void add_edge(int n1, int n2) {
        // if any of the two vertices are missing
        if (adj.find(n1) == adj.end() || adj.find(n2) == adj.end()) {
            cout << "At least one of the passed vertices are missing" << endl;
            return;
        }
        // if already has this edge
        if (adj[n1].find(n2) != adj[n1].end()) {
            cout << "This edge already exists" << endl;
            return;
        }

        adj[n1].insert(n2);
    }

    void remove_edge(int n1, int n2) {
        // if any of the two nodes are missing
        if (adj.find(n1) == adj.end() || adj.find(n2) == adj.end()) {
            cout << "At least one of the passed vertices are missing" << endl;
            return;
        }
        // if does not have such an edge
        if (adj[n1].find(n2) == adj[n1].end()) {
            cout << "There is no such edge" << endl;
            return;
        }

        adj[n1].erase(n2);
    }

    void print() {
        for (const auto& a : adj) {
            auto base = a.first;
            auto outs = a.second;
            cout << base;
            for (const auto& v : outs) {
                cout << "->" << v;
            }
            cout << endl;
        }
    }

    list<int> dfs(int* start_at = nullptr) //modified to find spanning tree
    {
        list<int> visitPath;
        set<int> res;
        unordered_map<int, bool> visited;
        for (const auto& e : adj)
            visited[e.first] = false;

        // find minimal vertex
        int minimal = adj.begin()->first;
        for (auto& e : adj) {
            if (e.first < minimal) {
                minimal = e.first;
            }
        }

        // if start_at was passed, start there. Otherwise start at the minimal
        dfs_r(start_at == nullptr ? minimal : *start_at, visited, res,visitPath);
        return visitPath;
    }

    void spanningTrees() 
    {
        DirectedGraph g = *this;
        vector<vector<int>> vertices_visited;
        bool AnswerFound = false;
        int temp=0;
        while (g.adj.size() > 0&&AnswerFound!=true&&temp<=vertex_count) {

            auto initial_dfs = g.dfs();
            int first_ele = *initial_dfs.begin();
            vertices_visited.push_back({});

            for (auto e : initial_dfs) 
            {
                auto visitPath=g.dfs(&e);
                if (visitPath.size() >= vertex_count)
                {
                    AnswerFound = true;
                    cout << "Spanning tree found. it is: ";
                    for (auto& e : visitPath)
                    {
                        cout << e;
                        if (e != visitPath.back())
                        {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }
            }
            temp++;
        }
        if (AnswerFound != true)
        {
            cout << "No spanning tree found." << endl;
        }
    }
};

int main() {
    DirectedGraph g;
    g.vertex_count = 0;

    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);
    g.add_edge(1, 2);
    g.add_edge(2, 1);
    g.add_edge(1, 3);
    g.add_edge(3, 1);
    g.add_edge(2, 4);
    g.add_edge(4, 2);
    g.add_edge(1, 4);
    g.add_edge(4, 1);



    g.spanningTrees();


    return 0;
}