//Dylan Taylor A* search
// I declare that all material in this assessment task is my work except where there is
// clear acknowledge- mentor reference to the work of others. I further declare that I have
// complied and agreed to the CMU Academic Integrity Policy at the University website.
// http://www.coloradomesa.edu/student-services/document
// Author’s Name: Dylan Taylor UID(700#): 700373571 Date: 11/16/21


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <climits>

using namespace std;
const int SIZE = 31;
int dijkstra(int graph[SIZE][SIZE], int src, int dst);
int minDistance(int dist[], bool sptSet[]);
int nodeHeuristics(int src, int dest);




int main(int argc, char **argv)
{ 
    //Reading input
    ifstream in("Adjacency matrix.txt");
    int arr[SIZE][SIZE];
    string line, word;
    int value = 0, row = 0;
    int h[SIZE][SIZE];
    
    while(getline(in,line)){
   
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
    //Reads heuristic data
    while(getline(in,line)){
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
    in.close();

    int dist[SIZE];
    bool visited[SIZE];
    int f[SIZE];
    //setup 
    // all dist = max
    // all f = max
    // because both are unknown to start
    // all visited = false
    for(int i = 0; i < SIZE; i++){
        dist[i] = INT_MAX; 
        f[i] = INT_MAX;
        visited[i] = false;
    }

    int src = stoi(argv[1]); 
    int dest = stoi(argv[2]);
    
    //setup for intial state
    dist[src] = 0;
    f[src] = 0 + h[src][dest];

    for(int i = 0; i < SIZE - 1; i++){

        int current = minDistance(f,visited);
        visited[current] = true;
        
        cout << "\t\t\tCurrent: " << current << endl;
        //break before going further.
        if(current == dest){

            cout << "\n\nArrived at: " << current << " with a total distance of: " << dist[current];
            
            break;
        } 
        //updates all distances and f values when there is a connection to those nodes.
        for(int check = 0; check < SIZE; check++){
            if((arr[current][check] != 0) && !visited[check] && (arr[current][check] + dist[current] < dist[check])){
                
                dist[check] = arr[current][check] + dist[current];
                f[check] = dist[check] + h[check][dest];
                cout << "Connected node #: " << check << " Distance to get there: "
                     << dist[check] << " Heurisitc: " << h[check][dest] << endl;
            }
        }
            

    } 
}

//Used as a psuedo priority queue used from dijkstra geeks for geeks
int minDistance(int dist[], bool sptSet[])
{

	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < SIZE; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

