#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;
//Graph class
class graph
{
private:
    int ver;
    int edg;
    vector<vector<int>> adj_list;

public:
    graph()
    {
        this->ver = 0;
        this->edg = 0;
        this->adj_list.resize(0);
    }
    graph(int val1, int val2)
    {
        this->ver = val1;
        this->edg = val2;
        this->adj_list.resize(val1); // resize the adj list to accomodate vertices = val1
    }
    // Create a graph
    void createGraph()
    {
        cout << "Enter the number of vertices in this graph: ";
        cin >> ver;
        cout << "Enter the number of edges in this graph: ";
        cin >> edg;

        adj_list.resize(ver); // resize to accomodate ver num. of vertices.
        cout << "Enter the edges (strt end):" << endl;
        for (int i = 0; i < edg; ++i)
        {
            int strt, end;
            cin >> strt >> end;
            adj_list[strt].push_back(end); // push vertex(end) to adj list whose start(strt)
        }
    }

    // Display the graph
    void displayGraph()
    {
        cout << "Adjacency List Representation of the Graph:" << endl;
        for (int i = 0; i < ver; ++i)
        {
            cout << "Vertex " << i << ": ";
            for (int j : adj_list[i])
            {
                cout << j << "->";
            }
            cout << endl;
        }
    }
    // Calculate the degree of each node
    void calculateDegree()
    {
        cout << "Degree of Each Node:" << endl;
        for (int i = 0; i < ver; ++i)
        {
            cout << "Vertex " << i << ": " << adj_list[i].size() << endl;
        }
    }
    // BFS Traversal
    void bfsTraversal(int startVertex)
    {
        vector<bool> visited(ver,false);
        cout << "Breadth-First Search Traversal: ";

        queue<int> q;
        q.push(startVertex);
        visited[startVertex] = true; // vertex as visited

        while (!q.empty())
        {
            int vtx = q.front(); // storing front of queue in variable vtx
            q.pop();
            cout << vtx << " ";

            for (int u : adj_list[vtx]) // traverse every vertex(u) adjacent to vertex(vtx)
            {
                if (!visited[u]) // If not visited then push to queue
                {
                    q.push(u);
                    visited[u] = true;
                }
            }
        }
        cout << "BFS completed" << endl;
        cout << endl;
    }
    // DFs traversal of graph
    void dfsTraversal(int startVertex)
    {
        vector<bool> visited(ver, false);
        cout << "Depth-First Search Traversal: ";

        stack<int> s;
        s.push(startVertex);
        visited[startVertex] = true;

        while (!s.empty())
        {
            int v = s.top();
            s.pop();
            cout << v << " ";

            for (int u : adj_list[v])
            {
                if (!visited[u])
                {
                    s.push(u);
                    visited[u] = true;
                }
            }
        }
        cout << endl;
        cout << "DFS completed" << endl;
    }
};
// Main func
int main()
{
    int strt, choice;
    graph obj;
    while (true)
    {
        cout << "-----------CHOICE----------" << endl;
        cout << "1.Create a ghraph" << endl;
        cout << "2.Display adjacency list/graph" << endl;
        cout << "3.Print degree of each node" << endl;
        cout << "4.Perform DFS and BFS traversal" << endl;
        cout << "5.Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            obj.createGraph();
            break;
        case 2:
            obj.displayGraph();
            break;
        case 3:
            obj.calculateDegree();
            break;
        case 4:
            int ver;
            cout << "Enter the starting vertex: ";
            cin >> ver;
            obj.bfsTraversal(ver);
            obj.dfsTraversal(ver);
            break;
        case 5:
            break;

        default:
            break;
        }
    }

    return 0;
}
