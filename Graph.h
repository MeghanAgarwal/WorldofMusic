//
// Created by Meghan Agarwal on 12/7/21.
//

#ifndef MUSICPROJECT_GRAPH_H
#define MUSICPROJECT_GRAPH_H
#include "Song.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>
#include <set>
#include <stack>
#include <queue>


using std::string;
using std::vector;
using std::map;
using std::tuple;
using std::make_tuple;
using std::get;
using std::set;
using std::stack;
using std::queue;
using std::cin;
using std::cout;
using std::endl; // Either use this or "\n"
using std::getline;



//int inf = ~(1 << 31);
typedef tuple<int, int, int> triple;

class Graph {
public:
    struct Vertex {
        int from;
        int to;
        int weight;
        string title;
        string artist;
        Vertex(int from, int to, int weight, Song& music) {
            this->from = from;
            this->to = to;
            this->weight = weight;
            title = music.title;
            artist = music.artist;

        }
    };
    void insertEdge(int& from, int& to, int& weight, Song& s);
    bool isEdge(int& from, int& to);
    int getWeight(int& from, int& to);
    vector<int> getAdjacent(int& vertex);
    int getIndegree(int& vertex);
    int getOutdegree(int& vertex);
    int costliestEdge();
    void printGraph();
    int totalVertices();
    map<int, vector<triple>> getMap();
    map<int, vector<Vertex>> getNestedMap();
    vector<int> getVertices();
    vector<int> inDegreeList;
    vector<int> outDegreeList;
    Vertex* vertexAt(int val);
    void bfs(int origin);
    void dfs(int origin);
    void Clear();
private:
    // Graph ADJACENCY LIST data structure here
    // We have an unordered map whose key is the "from" vertex
    // and it is equal to a vector of 3-tuples of the form:
    // 1st element - ("from" vertex), 2nd element - ("to" vertex), 3rd element - (weight between "from" and "to" vertex).
    map<int, vector<triple>> mapa;
    /* An unoriginal name for a map that holds each song's info. Since this is isomorphic to mapa, we can use info from mapa and its functions
    to find the song we want in here*/
    map<int, vector<Vertex>> gps;
    set<int> vertices;
};


#endif //MUSICPROJECT_GRAPH_H
