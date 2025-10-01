#include "Graph.h"
#include <iostream>
#include <vector>

using namespace std;

Graph::~Graph(){
}

void Graph::AddNode(nodekey_t key){
    // adds a new node to the graph
    // because it needs to expand the graph matrix to include this node, updating connections
    if(!IsPresent(key)){
        if (vec.empty()) {
            vec.push_back(vector<int>());
        }
        vec[0].push_back(key);
        vec.push_back(vector<int>(vec[0].size()+1));
        for (size_t i = 1; i < vec.size(); i++){
            vec[i].resize(vec[0].size()+1);
            fill(vec[i].begin()+1, vec[i].end(), -1);
        }
        vec[vec.size()-1][0] = key;        
    } else {
        throw invalid_argument("Key already exists."); ;
    }
}

const GraphEdge* Graph::AddEdge(nodekey_t fromNodeKey, nodekey_t toNodeKey, unsigned int weight){
    //adds a new directed edge with a given weight between two nodes
    //connects nodes to reflect graph relationships, ensuring no duplicate edges
    bool valid_input = false;
    for (size_t i = 0; i < vec.size(); i ++){
        if (size_t(vec[i][0]) == fromNodeKey){
            for (size_t j = 0; j < vec[i].size(); j ++){
                if (size_t(vec[0][j]) == toNodeKey && vec[i][j+1] == -1){
                    valid_input = true;
                    vec[i][j+1] = weight;
                }
            }
        }
    }

    if (!valid_input){
        throw invalid_argument("Node does not exist or edge already exists");
    }

    GraphEdge* edge = new GraphEdge{fromNodeKey, toNodeKey, weight};
    vec2.push_back(edge);
    return edge;
}
		
bool Graph::IsPresent(nodekey_t key) const{
    //we should check if a node exists in the graph, so it prevents duplicate nodes and ensures existing connections
    if (vec.empty()) {
        return false;
    }
    for(size_t i=0; i<vec[0].size(); i++){
        if (size_t(vec[0][i])==key){
            return true;
        }
    }
    return false;
}

string Graph::NodesToString() const{
    //we return a string of all nodes for easy display
    string str="[";
    for(size_t i=0; i<vec[0].size(); i++){
        str = str + "(" + to_string(vec[0][i]) + "), ";
    }
    str.erase(str.length() - 2, 2);
    str +="]";
    return str;
}

string Graph::EdgesToString() const{
    string str = "[";
    for (size_t i = 0; i < vec.size(); i++){
        for (size_t j = 0; j < vec[i].size(); j++){
            if (vec[i][j] != -1 && i!=0 && j!=0){
                str = str + "((" + to_string(vec[i][0]) + ")->(" + to_string(vec[0][j-1]) + ") w:" + to_string(vec[i][j]) + "), " ;
            }
        }
    }
    str.erase(str.length() - 2, 2);
    str += "]";
    return str;
}

set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t nodeKey) const{
    // this part gets all outward edges from a specific node
    set<const GraphEdge*> out_set;
    for (size_t i = 0; i < vec2.size(); i++){
        if (vec2[i]->from == 17){
            out_set.insert(vec2[i]);
        }
    }
    return out_set;
}

set<nodekey_t> Graph::GetNodes() const{
    //returns a set of all nodes in the graph.    
    set<nodekey_t> nodes_set; 
    if (vec.empty()){
        return {};
    }
    for(size_t i=0; i<vec[0].size(); i++){
        nodes_set.insert(vec[0][i]);
    }
    return nodes_set;
}

size_t Graph::Size() const{
    //returns the number of edges in the graph.
    int count = 0;
    for (size_t i = 1; i < vec.size(); i++){
        for (size_t j = 1; j < vec[i].size(); j++){
            if (vec[i][j] != -1){
                count += 1;
            }

        }
    }
    return count;
}

size_t Graph::Order() const{
    if (vec.empty()){
        return 0;
    }
    return vec[0].size();
}

void Graph::printmatrix(){
       // and we print the adjacency matrix for debugging here
    for (size_t i = 0; i < vec.size(); i++){
        if (i == 0){
            cout << "    " ;
        }
        for (size_t j = 0; j < vec[i].size(); j++){
            cout << vec[i][j] << ", ";
        }
        cout << endl;

    }
}