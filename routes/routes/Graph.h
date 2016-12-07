#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <queue>
#include <functional>
#define INF INT_MAX
#include "Vertex.h"
using namespace std;
class Graph
{
	unordered_map<int, Vertex> _vertices;

public:

	void addVertex(Vertex vertex)
	{
		_vertices[vertex.getId()] = vertex;
	}

	//MA #12 TODO: IMPLEMENT!
	unordered_map<Vertex, int> computeShortestPath(Vertex *start)
	{
		//holds known distances
		unordered_map<Vertex, int> distances;
		for (int i = 0; i < _vertices.size(); i++)
		{
			distances.insert({_vertices[i],INF});
		}
		//underlying heap
		priority_queue<Vertex, vector<Vertex>, PathWeightComparer> dijkstra_queue{};

		//reset start's path weight
		start->setPathWeight(0);

		//make sure that the starting vertex is in the graph
		if (_vertices.find(start->getId()) != _vertices.end())
			//push on starting vertex

		{
			dijkstra_queue.push(_vertices.at(start->getId()));
			distances[start->getId()] = 0;
		}
		//while queue not empty
		while (!dijkstra_queue.empty())

			//Top of heap not known (in distances)?

		{
			Vertex curV = dijkstra_queue.top();
			int curID = dijkstra_queue.top().getId();
			dijkstra_queue.pop();

			//make known
			unordered_map<Vertex *, int>e = curV.getEdges();
			for (auto edge: e)
			{
				int vNum = edge.first->getId();
				int cost = edge.second;
				//push on outgoing edges
				if (distances[vNum] > distances[curID] + cost)
				{
					distances[vNum] = distances[curID] + cost;
					dijkstra_queue.push(_vertices.at(vNum));
				}
			}
			
		}
		return distances;
	}
};

#endif
