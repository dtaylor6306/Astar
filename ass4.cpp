#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>

using namespace std;
const int SIZE = 31;
int dijkstra(int graph[SIZE][SIZE], int src, int dst);
int minDistance(int dist[], bool sptSet[]);
int nodeHeuristics(int src, int dest);




int main(int argc, char **argv)
{ 
    ifstream in("Adjacency matrix.txt");
    // ifstream in("precomp.txt");
    int arr[SIZE][SIZE];
    string line, word;
    int value = 0, row = 0;
    int h[SIZE][SIZE];
    
    while(getline(in,line)){
        //cout << "This line:" << line << endl;
        stringstream ss(line);

        //gets each word
        int col = 0;
        while(ss >> word){
         
            if(isdigit(word[0])){
                value = stoi(word);
                arr[row][col] = value;
                col++;
            } 
        }
        row++;
    }
    in.close(); 
    in.open("precomp.txt");
    row =0;
    value = 0;
    
    while(getline(in,line)){
        //cout << "This line:" << line << endl;
        stringstream ss(line);

        //gets each word
        int col = 0;
        while(ss >> word){
         
            if(isdigit(word[0])){
                value = stoi(word);
                h[row][col] = value;
                col++;
            } 
        }
        row++;
    }
    

    // for(int i = 0; i < 31; i++){
    //     for(int j =0; j < 31; j++){
    //         cout << h[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int dist[SIZE];
    bool visited[SIZE];
    int f[SIZE];

    for(int i = 0; i < SIZE; i++){
        dist[i] == INT_MAX; 
        f[i] = INT_MAX;
        visited[i] = false;
    }

    int src = 0; 
    int dest = 28;
    
    
    dist[src] = 0;
    f[src] = 0 + h[src][dest];
    cout <<  h[src][dest] << "THIS IS THE START\n\n\n";
    // should go 0 > 30 > 11 > 12 > 13 >28 done

    for(int i = 0; i < SIZE - 1; i++){

        int current = minDistance(f,visited);
        visited[current] = true;
        cout << "\t\t\t" << current << endl;
        for(int check = 0; check < SIZE; check++){
            if(arr[current][check] != 0 && !visited[check] 
            && arr[current][check] + dist[current] < dist[check]){
                dist[check] = arr[current][check] + dist[current];
                f[check] = dist[check] + h[current][check];
                cout << check << " " << f[check] << endl;
            }
        }
        if(current == dest){
            cout << "Arrived at " << current << " " << dist[current];
            
            break;
        } 
            

    } 
    // if not 0 check it
    // f = g + h
    // g = distance thus far
    // h = heuristic
    // need priority queue
    // parent array
}

int minDistance(int dist[], bool sptSet[])
{

	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < SIZE; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}


int dijkstra(int graph[SIZE][SIZE], int src, int dst)
{
	int dist[SIZE]; // The output array. dist[i] will hold the shortest
	// distance from src to i

	bool sptSet[SIZE]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < SIZE; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < SIZE - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < SIZE; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

    return dist[dst];
}

int nodeHeuristics(int src, int dest){
    return abs(dest - src);
}
