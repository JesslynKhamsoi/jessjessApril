#ifndef GRAPH_H
#define GRAPH_H
#pragma once
#include <unordered_map>
#include <queue>
#include <functional>
#include <limits>
#include <limits.h>
#include "Vertex.h"
using namespace std;
#define INF INT_MAX
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

		//underlying heap
		priority_queue<Vertex, vector<Vertex>, PathWeightComparer> dijkstra_queue{};

		//reset start's path weight
		start->setPathWeight(0);

		//push on starting vertex
	   //  double inf = std::numeric_limits<double>::max();
		distances.insert({ *start,0 });
		distances.insert({ _vertices[1], INF });
		distances.insert({ _vertices[2], INF });
		distances.insert({ _vertices[3], INF });
		distances.insert({ _vertices[4], INF });
		//make sure that the starting vertex is in the graph
		for (auto & v : _vertices)
		{
			if (v.second == *start)
			{
				cout << "first vertex is in the graph.";
			}
			/*else
			{
				return distances;
			}*/

			//while queue not empty
			unordered_map<Vertex *, int>e = v.second.getEdges();
			for (auto & w : e)
			{
				if (w.second + distances.at(v.first)  < distances.at(w.first->getId()))//w.first->getId() - 1
	
				{
				distances.at(w.first->getId()) = w.second + distances.at(v.first);
				}
				

			}
		}
			//v.second.getEdgeWeight(&e);
			//&e[0].;
			//how do i get the number???

			
		
		//Top of heap not known (in distances)?

		//make known

		//push on outgoing edges

		return distances;
	}
};

#endif
