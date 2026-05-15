#include "MusicGraph.h"

// =============================================================================
// PRIVATE HELPER METHODS
// =============================================================================

int MusicGraph::getSongIndex(const string& id) const {
    // TODO: Implement linear search to find the index of a song by its ID
    for (size_t i = 0; i < songsList.size(); i++) {
        if (songsList[i].id == id) {
            return (int)i;
        }
    }
    return -1;
}

bool MusicGraph::isVisited(const string& id, const vector<string>& visitedList) const {
    // TODO: Check if the given ID exists in the visitedList
    for (const string& vId : visitedList) {
        if (vId == id) return true;
    }
    return false;
}

// =============================================================================
// PUBLIC METHODS
// =============================================================================

void MusicGraph::addSong(const string& id, const string& title, const string& artist, const string& genre) {
    // TODO: Add a new song to the system and add its ID as a vertex in the graph
    if (getSongIndex(id) != -1) return;

    Song newSong = {id, title, artist, genre};
    SongEntry newEntry = {id, newSong};

    songsList.push_back(newEntry);
    this->addVertex(id);
}

void MusicGraph::printSongInfo(const string& id) const {
    // TODO: Print the song information in the required format
    int idx = getSongIndex(id);
    if (idx != -1) {
        cout << "[" << songsList[idx].data.id << "] " 
             << songsList[idx].data.title << " - "
             << songsList[idx].data.artist;
    }
}

// =============================================================================
// REQUIREMENT 1: Recommend related songs (BFS)
// =============================================================================
void MusicGraph::recommendRelatedSongs(const string& startId) const {
    if (!this->hasVertex(startId)) return;

    cout << "\n[1] SUGGEST RELATED SONGS FOR: ";
    printSongInfo(startId);
    cout << "\n-------------------------------------------------\n";

    // TODO: Implement Breadth-First Search (BFS) to recommend related songs
    vector<string> visited;
    vector<string> customQueue;
    int head = 0;

    visited.push_back(startId);
    customQueue.push_back(startId);

    while (head < (int)customQueue.size()) {
        string currentId = customQueue[head++];
        vector<Edge> neighbors = this->getNeighbors(currentId);

        for (const auto& edge : neighbors) {
            if (!isVisited(edge.target, visited)) {
                visited.push_back(edge.target);
                customQueue.push_back(edge.target);

                cout << "-> ";
                printSongInfo(edge.target);
                cout << endl;
            }
        }
    }
}

// =============================================================================
// REQUIREMENT 2: Create playlist by clusters (Connected Components using BFS)
// =============================================================================
void MusicGraph::generatePlaylistsByClusters() const {
    cout << "\n[2] CREATE PLAYLIST BY CLUSTERS (CONNECTED COMPONENTS)\n";
    cout << "-------------------------------------------------\n";

    // TODO: Find connected components and print each cluster as a playlist
    vector<string> globalVisited;
    int playlistCount = 0;

    for (const auto& node : this->adjList) {
        if (!isVisited(node.vertex, globalVisited)) {
            playlistCount++;

            cout << "=== Playlist " << playlistCount << " ===\n";

            vector<string> localQueue;
            int localHead = 0;

            localQueue.push_back(node.vertex);
            globalVisited.push_back(node.vertex);

            while (localHead < (int)localQueue.size()) {
                string currentId = localQueue[localHead++];
                cout << "  * ";
                printSongInfo(currentId);
                cout << endl;

                // Follow outgoing edges
                for (const auto& edge : this->getNeighbors(currentId)) {
                    if (!isVisited(edge.target, globalVisited)) {
                        globalVisited.push_back(edge.target);
                        localQueue.push_back(edge.target);
                    }
                }

                // Follow reverse edges (treat graph as undirected for components)
                for (int i = 0; i < (int)this->adjList.size(); i++) {
                    for (const auto& edge : this->adjList[i].neighbors) {
                        if (edge.target == currentId && !isVisited(this->adjList[i].vertex, globalVisited)) {
                            globalVisited.push_back(this->adjList[i].vertex);
                            localQueue.push_back(this->adjList[i].vertex);
                        }
                    }
                }
            }
        }
    }
}

// =============================================================================
// REQUIREMENT 3: Smooth song transition (Dijkstra's Algorithm)
// =============================================================================
void MusicGraph::findSmoothTransition(const string& startId, const string& endId) const {
    cout << "\n[3] SMOOTHEST TRANSITION (DIJKSTRA)\n";
    cout << "From: "; printSongInfo(startId); cout << "\n";
    cout << "To: "; printSongInfo(endId); cout << "\n";
    cout << "-------------------------------------------------\n";

    int n = (int)this->adjList.size();
    int startIdx = this->getVertexIndex(startId);
    int endIdx = this->getVertexIndex(endId);

    if (startIdx == -1 || endIdx == -1) {
        cout << "Error: Song not found!\n";
        return;
    }

    // TODO: Implement Dijkstra's algorithm to find the shortest path between startId and endId
    double INF = 999999999.0;
    vector<double> dist(n, INF);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    dist[startIdx] = 0;
    
    for (int i = 0; i < n; i++) {
        int u = -1;
        double minDist = INF;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;

        if (u == endIdx) break;

        string currentId = this->adjList[u].vertex;
        for (const auto& edge : this->getNeighbors(currentId)) {
            int v = this->getVertexIndex(edge.target);
            if (!visited[v] && dist[u] + edge.weight < dist[v]) {
                dist[v] = dist[u] + edge.weight;
                prev[v] = u;
            }
        }
    }

    if (dist[endIdx] == INF) {
        cout << "No transition path between these two songs.";
    } else {
        cout << "-> Total Deviation (Cost): " << dist[endIdx] << endl;
        cout << "-> Playback Order:\n";

        vector<int> path;
        for (int at = endIdx; at != -1; at = prev[at]) {
            path.push_back(at);
        }

        int step = 1;
        for (int i = (int)path.size() - 1; i >= 0; i--) {
            cout << "   " << step++ << ". ";
            printSongInfo(this->adjList[path[i]].vertex);
            cout << endl;
        }
    }
}

// =============================================================================
// REQUIREMENT 4: Find the network hub song (In-degree Calculation)
// =============================================================================
void MusicGraph::findMostPopularSong() const {
    cout << "\n[4] FIND NETWORK HUB SONG (IN-DEGREE)\n";
    cout << "-------------------------------------------------\n";

    // TODO: Calculate the in-degree of all vertices and find the one with the maximum value
    int n = (int)this->adjList.size();
    if (n == 0) return;

    vector<int> inDegree(n, 0);

    for (int i = 0; i < n; i++) {
        for (const auto& edge : this->adjList[i].neighbors) {
            int targetIdx = this->getVertexIndex(edge.target);
            if (targetIdx != -1) {
                inDegree[targetIdx]++; 
            }
        }
    }

    int maxIn = -1;
    int maxIdx = -1;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] >= maxIn) {
            maxIn = inDegree[i];
            maxIdx = i;
        }
    }

    if (maxIdx != -1) {
        cout << "-> Network Hub Song:\n   ";
        printSongInfo(this->adjList[maxIdx].vertex);
        cout << "\n   (In-degree: " << maxIn << ")";
    }
}

// =============================================================================
// REQUIREMENT 5: Detect music loop (DFS Cycle Detection)
// =============================================================================

// DFS recursive helper function
bool MusicGraph::dfsCycleHelper(int idx, vector<bool>& visited, vector<bool>& recursionStack,
                                 vector<int>& parent, bool& found) const {
    // TODO: Implement the recursive DFS logic to detect cycles
    if (found) return true;
    visited[idx] = true;
    recursionStack[idx] = true;

    for (const auto& edge : this->adjList[idx].neighbors) {
        int v = this->getVertexIndex(edge.target);
        if (!visited[v]) {
            parent[v] = idx;
            if (dfsCycleHelper(v, visited, recursionStack, parent, found)) return true;
        } else if (recursionStack[v]) {
            found = true;
            cout << "-> Music loop detected!\n-> Loop:\n";

            vector<int> cycle;
            cycle.push_back(v); 
            for (int curr = idx; curr != v && curr != -1; curr = parent[curr]) {
                cycle.push_back(curr);
            }
            cycle.push_back(v); 

            for (int i = (int)cycle.size() - 1; i >= 0; i--) {
                cout << "   "; 
                printSongInfo(this->adjList[cycle[i]].vertex);
                cout << endl;
            }
            return true;
        }
    }
    recursionStack[idx] = false;
    return false;
}

void MusicGraph::detectMusicLoop() const {
    cout << "\n[5] DETECT MUSIC LOOP (DFS CYCLE DETECTION)\n";
    cout << "-------------------------------------------------\n";

    // TODO: Initialize required arrays and start DFS to detect a music loop
    int n = (int)this->adjList.size();
    vector<bool> visited(n, false);
    vector<bool> recursiveStack(n, false);
    vector<int> parent(n, -1);
    bool found = false;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfsCycleHelper(i, visited, recursiveStack, parent, found)) return;
        }
    }

    if (!found) {
        cout << "No music loop detected.\n";
    }

}