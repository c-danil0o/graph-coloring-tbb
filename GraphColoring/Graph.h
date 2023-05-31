#pragma once
#include <SFML/Graphics.hpp>
#include "tbb/concurrent_vector.h"
#include <list>


using namespace std;
const int COLUMN_NUMBER = 100;
const int ROW_NUMBER = 100;
constexpr auto NUM_OF_TASKS = 4;


class Graph {
	int V; // graph size
	tbb::concurrent_vector<int> matrixC;
	list <int>* adj; // list of lists for every node
	sf::RectangleShape** cells;
	tbb::concurrent_vector<bool> colored;
	bool bfsDone[NUM_OF_TASKS];

public:
	
	Graph() {
		this->V = ROW_NUMBER * COLUMN_NUMBER; adj = new list<int>[ROW_NUMBER * COLUMN_NUMBER];

		for (int i = 0; i < V; i++) {
			colored.push_back(false);
		}
		for (int i = 0; i < NUM_OF_TASKS; i++) {
			bfsDone[i] = false;
		}
		
		cells = new sf::RectangleShape * [ROW_NUMBER];
		for (int i = 0; i < ROW_NUMBER; i++) {
			cells[i] = new sf::RectangleShape[COLUMN_NUMBER];
		}
	}

	~Graph() { delete[]adj; }
	void add_edge(int v, int w);
	void init_matrix();
	void generate_nodes();
	void print_matrix();
	void add_all_edges(int x);
	void parse_matrix();
	void print_colored();
	void print_graph();
	void set_color(int color, int row, int col);
	bool can_set_color(int color, int vertex);
	int get_color(int vertex);
	void color_graph();
	int get_available_color(int vertex);
	void color_bfs(int startNode, int thread);
	void draw();
	void updateCellColors(int row, int col);
};
