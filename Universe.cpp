#include "Universe.h"

bool Location_In_Rect(Location m_location, MyRect m_rect)
{
	if (m_location.x<m_rect.left_bottom.x || m_location.x>m_rect.right_top.x || m_location.y<m_rect.left_bottom.y || m_location.y>m_rect.right_top.y)
		return false;
	else
		return true;
}

void ReadEntity(int &node_count, vector<Entity> &entity_vector, string filename)
{
	char *ch = (char *)filename.data();
	freopen(ch, "r", stdin);

	scanf("%d\n", &node_count);
	entity_vector.resize(node_count);
	for (int i = 0; i < node_count; i++)
	{
		int id, IsSpatial;
		scanf("%d,%d", &id, &IsSpatial);
		entity_vector[id].IsSpatial = IsSpatial;
		if (IsSpatial)
			scanf(",%lf,%lf\n", &(entity_vector[id].location.x), &(entity_vector[id].location.y));
	}
	fclose(stdin);
}

string getstring(const int i)
{
	stringstream newstr;
	newstr << i;
	return newstr.str();
}

int StringtoInt(string str)
{
	return atoi(str.c_str());
}

vector<string> split(string str, string pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

void write(string filepath, string content)
{
	ofstream os(filepath, ios::app);
	os << content;
	os.close();
}

// A recursive function used by topologicalSort
void TopologicalSortUtil(int v, vector<bool> &visited, queue<int> &queue, vector<vector<int>> &graph)
{
	// Mark the current node as visited.
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	for (int i = 0; i < graph[v].size(); i++)
		if (!visited[graph[v][i]])
			TopologicalSortUtil(graph[v][i], visited, queue, graph);

	// Push current vertex to stack which stores result
	queue.push(v);
}

// The function to do Topological Sort. It uses recursive topologicalSortUtil()
void TopologicalSort(vector<vector<int>> &graph, queue<int> &queue)
{
	// Mark all the vertices as not visited
	vector<bool> visited = vector<bool>(graph.size());

	for (int i = 0; i < graph.size(); i++)
		visited[i] = false;

	// Call the recursive helper function to store Topological Sort
	// starting from all vertices one by one
	for (int i = 0; i < graph.size(); i++)
		if (visited[i] == false)
			TopologicalSortUtil(i, visited, queue, graph);
}

void ReadGraph(vector<vector<int>> &graph, int &node_count, string graph_filepath)
{
	char *ch = (char *)graph_filepath.data();
	freopen(ch, "r", stdin);

	scanf("%d\n", &node_count);
	graph.resize(node_count);

	for (int i = 0; i < node_count; i++)
	{
		int id, count, outid;
		scanf("%d,%d", &id, &count);
		graph[i].resize(count);
		for (int j = 0; j < count; j++)
		{
			scanf(",%d", &outid);
			graph[i][j] = outid;
		}
	}
	fclose(stdin);
}

void WriteGraph(vector<set<int>> &graph, string filepath)
{
    char * ch = (char*) filepath.data();
    freopen(ch, "w", stdout);

    printf("%d\n", graph.size());
    for ( int i = 0; i < graph.size(); i++)
    {
        printf("%d,%d", i, graph[i].size());
        for ( int neighbor : graph[i])
            printf(",%d", neighbor);
        printf("\n");
    }
    fclose(stdout);
}

void GenerateInedgeGraph(vector<vector<int>> &graph, vector<vector<int>> &in_edge_graph)
{
	int node_count = graph.size();
	in_edge_graph.resize(node_count);
	for (int i = 0; i < node_count; i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			int neighbor = graph[i][j];
			in_edge_graph[neighbor].push_back(i);
		}
	}
}

void GenerateHopNeighbors(vector<vector<int>> &graph, string source_path, string output_path)
{
    vector<vector<int>> hopneighbor_graph;
    int node_count;
    ReadGraph(hopneighbor_graph, node_count, source_path);
//    vector<set<int>> output_neighbors = vector<set<int>>(node_count);
    set<int> next_neighbors;

    char * ch = (char *) output_path.data();
    freopen(ch, "w", stdout);
    printf("%d\n", node_count);

    for ( int i = 0; i < graph.size(); i++)
    {
        for ( int j = 0; j < graph[i].size(); j++)
        {
            int neighbor = graph[i][j];
            for (int k = 0; k < hopneighbor_graph[neighbor].size(); k++)
            {
                next_neighbors.insert(hopneighbor_graph[neighbor][k]);
            }
        }
        printf("%d,%d", i, next_neighbors.size());
        for ( int neighbor : next_neighbors)
        {
            printf(",%d", neighbor);
        }
        printf("\n");
        next_neighbors.clear();
    }
//    WriteGraph(output_neighbors, output_path);
    fclose(stdout);
}


