#pragma once
#include <SFML/Graphics.hpp>
#include "tbb/concurrent_vector.h"
#include <list>


using namespace std;
constexpr auto COLUMN_NUMBER = 40;
constexpr auto ROW_NUMBER = 40;





class Graph {
	int V; // graph size
	int matrix[ROW_NUMBER][COLUMN_NUMBER];
	list <int>* adj; // list of lists for every node
	sf::RectangleShape cells[ROW_NUMBER][COLUMN_NUMBER];
	tbb::concurrent_vector<bool> colored;
	//bool colored[ROW_NUMBER * COLUMN_NUMBER];
	
	

public:
	
	Graph() {
		this->V = ROW_NUMBER * COLUMN_NUMBER; adj = new list<int>[ROW_NUMBER * COLUMN_NUMBER];
		colored.grow_by(V);
		for (int i = 0; i < V; i++) {
			colored[i] = false;
		}

	}

	~Graph() { delete[]adj; }
	void add_edge(int v, int w);
	void init_matrix();
	void generate_nodes();
	void print_matrix();
	void add_all_edges(int row, int col);
	void parse_matrix();
	void print_graph();
	void set_color(int color, int row, int col);
	bool can_set_color(int color, int vertex);
	int get_color(int vertex);
	void color_graph();
	int get_available_color(int vertex);
	void color_bfs(int startNode);
	void draw();
	void updateCellColors(int row, int col);
};
