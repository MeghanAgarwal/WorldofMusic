
#include "Graph.h"

void Graph :: Clear() {
    mapa.clear();
    gps.clear();
}

Graph::Vertex* Graph::vertexAt(int val) {
    Vertex* result = nullptr;
    for (auto it = gps.begin(); it != gps.end(); it++) {
        for (int i = 0; i < gps[(*it).first].size(); i++) {
            if (gps[(*it).first].at(i).to == val) {
                result = &(gps[(*it).first].at(i));
            }
        }
    }
    return result;
}

vector<int> Graph::getVertices() {
    vector<int> verticesList;
    for (auto traverse = mapa.begin(); traverse != mapa.end(); traverse++) {
        verticesList.push_back((*traverse).first);
    }
    return verticesList;
}

int Graph::totalVertices() {
    return ((int)mapa.size());
}

map<int, vector<tuple<int, int, int>>> Graph::getMap() {
    return mapa;
}

map<int, vector<Graph::Vertex>> Graph::getNestedMap() {
    return gps;
}

void Graph::insertEdge(int& from, int& to, int& weight, Song& s) {
    vertices.insert(from);
    // Simply define a typle that consists of the pair (from, to) and the weight and push this to our map's vector at the key.
    bool hasAdjacent = false;
    mapa[from].push_back(make_tuple(from, to, weight));
    Vertex v(from, to, weight, s);
    gps[from].push_back(v);
    for (auto iter = mapa.begin(); iter != mapa.end(); iter++) {
        for (int i = 0; i < mapa[(*iter).first].size(); i++) {
            // If the "to" vertex is equal to a "from" vertex, then it is also a "from vertex"
            if (to == get<0>(mapa[(*iter).first].at(i))) {
                hasAdjacent = true;
            }
        }
    }
    // If hasAdjacent is still false, then the "to" vertex has no adjacent vertices.
    // A vertex that has no adjacent vertices has a "to" vertex = 0, and weight = 0;
    if (hasAdjacent == false) {
        mapa[to].push_back(make_tuple(to, 0, 0));
    }

}

bool Graph::isEdge(int& from, int& to) {
    for (auto iter = mapa.begin(); iter != mapa.end(); iter++) {
        for (unsigned int i = 0; i < mapa[(*iter).first].size(); i++) {
            if (get<0>(mapa[(*iter).first].at(i)) == from) {
                if (get<1>(mapa[(*iter).first].at(i)) == to) {
                    return true;
                }
            }
        }
    }
    return false;
}

int Graph::getWeight(int& from, int& to) {
    for (unsigned int i = 0; i < mapa[from].size(); i++) {
        if (get<1>(mapa[from].at(i)) == to) {
            return get<2>(mapa[from].at(i));
        }
    }
    return 0;
}

vector<int> Graph::getAdjacent(int& vertex) {
    // We define a temporary vector.
    vector<int> temp;
    // We iterate through the the vertex's vector.
    // Note that the second element in the 3-tuple is the vertex connected to the input vertex because we defined this to be the "to" vertex
    for (unsigned int i = 0; i < mapa[vertex].size(); i++) {
        // We push back any vertices that originate from the input vertex paramter.
        // Note get<element "i" in the tuple>(pair name) retrieves the ith element in the tuple.
        if (get<1>(mapa[vertex].at(i)) != 0 && get<2>(mapa[vertex].at(i)) != 0) {
            temp.push_back(get<1>(mapa[vertex].at(i)));
        }
    }
    // Finally we sort the temp vector to ensure that the adjacent vertices to the input are in order.
    sort(temp.begin(), temp.begin() + temp.size());
    return temp;
}

int Graph::getIndegree(int& vertex) {
    // How many vertices point to the parameter vertex.
    int count = 0;
    // We iterate through the entire map.
    for (auto iter = mapa.begin(); iter != mapa.end(); iter++) {
        int tempParameter = (*iter).first;
        for (int elemento : getAdjacent(tempParameter)) {
            if (elemento == vertex) {
                count++;
            }
        }
    }
    return count;
}

int Graph::getOutdegree(int& vertex) {
    // How many vertices originate from the parameter vertex
    // The number of vertices that the input vertex points to is simply the size of the vector of vertices for key input vertex.
    int result = getAdjacent(vertex).size();
    return result;
}

int Graph::costliestEdge() {
    // Define a temp vector that holds all vertices' edge costs.
    vector<int> costs;
    int max = 0;
    // We iterate through the entire map.
    for (auto iter = mapa.begin(); iter != mapa.end(); iter++) {
        // We check each key's corresponding vector.
        for (int i = 0; i < mapa[(*iter).first].size(); i++) {
            // We note that the third element in the 3-tuple is the respective cost of the ordered pair (the first two elements in the 3-tuple).
            // So we simply push back the 3rd element into our temp vactor.
            costs.push_back(get<2>(mapa[(*iter).first].at(i)));
        }
    }
    // We assign max to be the first element in the vector and will judge all subsequent moves on this.
    // We do this outside the for loop to account for if there is only one element in the graph since our for loop's condition does not.
    if (costs.size() > 0) {
        max = costs[0];
    }
    // Now we go through the temp vector.
    for (int i = 0; i < costs.size() - 1; i++) {
        // If the current max is less than the cost at the next index, then set the max to be the cost of the next index.
        if (costs[i + 1] > max) {
            max = costs[i + 1];
        }
    }
    // By here, we should have the greatest cost in the vector.
    return max;
}


void Graph::printGraph() {
    for (auto iter = mapa.begin(); iter != mapa.end(); iter++) {
        cout << (*iter).first << ":";
        for (int i = 0; i < mapa[(*iter).first].size(); i++) {
            // The adjacent pairs are printed so long as the "to" vertex and weight != 0, the default values
            // for a vertex with no adjacent vertices.
            if (get<1>(mapa[(*iter).first].at(i)) != 0 && get<2>(mapa[(*iter).first].at(i)) != 0) {
                // The second element in the 3-tuple we noted earlier to be the adjacent vertices of a vertex V.
                cout << " " << get<1>(mapa[(*iter).first].at(i));
                // Edge case: If there is only one tuple in the map
                /*if (mapa.size() == 1) {
                    cout << get<1>(mapa[(*iter).first].at(i)) << endl;
                    break;
                }*/
            }
        }
        cout << endl;
    }
}

/*
Dijkstra's Algo: (Pseudocode from lecture)
Initialize S with the start vertex, s, and V-S with the remaining vertices
for all v in V-S
    Set p[v] to s.
    if there is an edge(s, v)
        set d[v] to w(s,v)
    else
        set d[v] to inf
while V-S is not empty
    for all u in V-S
        find the smallest d[u]
    Remove u from V-S and u to S.
    for all v adjacent to u in V-S
        if d[u] + w(u,v) < d[v]
            d[v] = d[u] + w(u,v)
            p[v] = u
*/
void Dijkstra(Graph& g, int origin) {

    set<int> S;
    S.insert(origin);
    set<int> VminusS;
    int totalV = g.totalVertices();
    map<int, vector<tuple<int, int, int>>> m = g.getMap();
    vector<int> prev(totalV, -1);
    vector<int> dist(totalV, ~(1 << 31));
    dist[origin] = 0;
    for (auto iter = m.begin(); iter != m.end(); iter++) {
        if ((*iter).first != origin) {
            VminusS.insert((*iter).first);
        }
    }
    for (int vertex : VminusS) {
        if (g.isEdge(origin, vertex) == true) {
            dist[vertex] = g.getWeight(origin, vertex);
            prev[vertex] = origin;
        }
        else {
            dist[vertex] = ~(1 << 31);
            prev[vertex] = -1;
        }
    }
    while (!(VminusS.empty())) {
        int minDistance = ~(1 << 31);
        int minDistIndex = ~(1 << 31);
        int u;
        set<int>::iterator iterVS = VminusS.begin();
        while (iterVS != VminusS.end()) {
            if (dist[(*iterVS)] < minDistance) {
                minDistance = dist[(*iterVS)];
                minDistIndex = (*iterVS);
                u = minDistIndex;
            }
            iterVS++;
        }
        VminusS.erase(minDistIndex);
        S.insert(minDistIndex);
        vector<int> theGold = g.getAdjacent(u);
        for (int v : theGold) {
            if (dist[u] + g.getWeight(u, v) < dist[v]) {
                dist[v] = dist[u] + g.getWeight(u, v);
                prev[v] = u;
            }
        }
    }

}

// BFS Search (source: Prof. Aman's ppts)
void Graph::bfs(int origin) {
    int numVertices = totalVertices();
    vector<bool> visited(totalVertices());
    queue<int> q;
    visited[origin] = true;
    q.push(origin);
    while (!(q.empty())) {
        int u = q.front();
        if (vertexAt(u) != nullptr) {
            cout << vertexAt(u)->title << endl;
        }
        q.pop();
        for (int v : getAdjacent(u)) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// DFS Search (same as BFS but uses a stack instead, source: Prof. Aman's ppts)
void Graph::dfs(int origin) {
    int numVertices = totalVertices();
    vector<bool> visited(totalVertices());
    stack<int> s;
    visited[origin] = true;
    s.push(origin);
    while (!(s.empty())) {
        int u = s.top();
        if (vertexAt(u) != nullptr) {
            cout << vertexAt(u)->title << endl;
        }
        s.pop();
        for (int v : getAdjacent(u)) {
            if (!visited[v]) {
                visited[v] = true;
                s.push(v);
            }
        }
    }
}

// Recursive DFS to see if a node is reachable (source: Prof. Aman's ppts)
// 2 parts: DFS helper and DFS class
bool dfsHelper(Graph& g, int origin, int destination, vector<int>& visited) {
    visited[origin] = true;
    if (origin == destination) {
        return true;
    }
    for (int child : g.getAdjacent(origin)) {
        if (!visited[child]) {
            if (dfsHelper(g, child, destination, visited) == true) {
                return true;
            }
        }
    }
    return false;
}

bool isReachable(Graph& g, int origin, int destination) {
    // Visited vector
    vector<int> visited(g.totalVertices());
    return dfsHelper(g, origin, destination, visited);
}

void degreeHelper(Graph& g) {
    for (int vertex : g.getVertices()) {
        g.inDegreeList.push_back(g.getIndegree(vertex));
        g.outDegreeList.push_back(g.getOutdegree(vertex));
    }
}

// Topological Sort (source: Prof. Aman's ppt)
void topSort(Graph g){
    // Degree must be updated / happen before the actual topSort!
    degreeHelper(g);
    // Preliminary tests from me...
    vector<int> inList = g.inDegreeList;
    vector<int> outList = g.outDegreeList;
    // Prof. Aman's pseudocode work
    queue<int> q;
    int counter = 0;
    for (int temp : g.getVertices()) {
        if (inList[temp] == 0) {
            q.push(temp);
        }
    }
    while (!(q.empty())) {
        int vertix = q.front();
        q.pop();
        cout << vertix << " ";
        for (int adj : g.getAdjacent(vertix)) {
            if (--inList[adj] == 0) {
                q.push(adj);
            }
        }
    }
}