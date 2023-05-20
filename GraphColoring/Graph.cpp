#include <list>

#include <random>
#include <iostream>
#include "Graph.h"
#include "Windows.h"



using namespace std;

const int row_operation[8] = { -1,0, 1, -1, 1, -1, 0, 1 };
const int column_operation[8] = { -1, -1, -1, 0, 0,1,1,1 };

random_device rd; // obtain a random number from hardware
mt19937 gen(rd()); // seed the generator
uniform_int_distribution<> distr(0, 7); // define the range

int available_colors = 5;

void Graph::add_edge(int v, int w) {
	adj[v].push_back(w);
	adj[w].push_back(v);
}

void Graph::init_matrix() {
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			matrix[i][j] = -1;
		}
	}
}

void Graph::generate_nodes() {
	int random_number = 0;
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			while (true) {
				random_number = distr(gen);
				if ((i + row_operation[random_number] == -1) || (j + column_operation[random_number] == -1)) {
					continue;
				}
				if ((i + row_operation[random_number] == ROW_NUMBER) || (j + column_operation[random_number] == COLUMN_NUMBER)) {
					continue;
				}

				matrix[i + row_operation[random_number]][j + column_operation[random_number]] = 0;
				break;
			}

		}
	}

}

void Graph::print_matrix() {
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			if (matrix[i][j] == -1) {
				cout << " |";
			}
			else {
				cout << matrix[i][j] << "|";
			}
			if (j == COLUMN_NUMBER - 1)
				cout << endl;

		}
	}
}

void Graph::print_graph() {
	for (int i = 0; i < V; i++) {
		list<int>::iterator it;
		cout << i << "is connected with: ";
		for (it = adj[i].begin(); it != adj[i].end(); it++) {
			cout << *it << "|";
		}
		cout << endl;

	}
}

void Graph::add_all_edges(int row, int col) {
	for (int i = 4; i < 8; i++) {
		if ((row + row_operation[i] == -1) || (col + column_operation[i] == -1)) {
			continue;
		}
		if ((row + row_operation[i] == ROW_NUMBER) || (col + column_operation[i] == COLUMN_NUMBER)) {
			continue;
		}
		if (matrix[row + row_operation[i]][col + column_operation[i]] == 0) {
			add_edge((row * COLUMN_NUMBER + col), ((row + row_operation[i]) * COLUMN_NUMBER + col + column_operation[i]));
		}
	}
}

void Graph::parse_matrix() {
	for (int i = 0; i < ROW_NUMBER; i++) {
		for (int j = 0; j < COLUMN_NUMBER; j++) {
			if (matrix[i][j] == 0) {
				add_all_edges(i, j);
			}
		}
	}
}

void Graph::set_color(int color, int row, int col) {
	matrix[row][col] = color;
}

int Graph::get_color(int vertex) {
	return matrix[vertex / COLUMN_NUMBER][vertex % COLUMN_NUMBER];

}
bool Graph::can_set_color(int color, int vertex)
{
	list<int>::iterator i;
	for (i = adj[vertex].begin(); i != adj[vertex].end(); ++i) {
		if (get_color(*i) == color)
			return false;
	}
	return true;
}

int Graph::get_available_color(int vertex) {
	for (int i = 1; i < available_colors + 1; i++) {
		if (can_set_color(i, vertex)) {
			return i;
		}
	}
	return 0;
}

void Graph::color_graph() {
	for (int i = 0; i < V; i++) {
		if (matrix[i / COLUMN_NUMBER][i % COLUMN_NUMBER] == 0) {
			system("cls");
			
			set_color(get_available_color(i), i / COLUMN_NUMBER, i % COLUMN_NUMBER);
			print_matrix();
			Sleep(200);
		}
	}
}

void Graph::color_bfs(int startNode) {
	Sleep(1000);
	int v = startNode;
	for (int i = v; i < V; i++) {
		if (matrix[i / COLUMN_NUMBER][i % COLUMN_NUMBER] == 0) {
			v = i;
			break;
		}
	}

	int queue[ROW_NUMBER * COLUMN_NUMBER];
	int front = 0, rear = 0;
	colored[v] = true;
	queue[rear++] = v;
	while (front != rear) {
		v = queue[front++];
		//system("cls");
		int row = v / COLUMN_NUMBER;
		int col = v % COLUMN_NUMBER;
		set_color(get_available_color(v),row, col);
		updateCellColors(row, col);
		//print_matrix();
		Sleep(50);
		


		list<int>::iterator it = adj[v].begin();
		for (it; it != adj[v].end(); it++) {
			if (!colored[*it]) {
				colored[*it] = true;
				queue[rear++] = *it;
			}
		}
		
	}

}

void Graph::draw() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Matrix Drawing");
	float cellWidth = window.getSize().x / float(ROW_NUMBER);
	float cellHeight = window.getSize().y / float(COLUMN_NUMBER);
	

	for (int i = 0; i < ROW_NUMBER; i++)
	{
		for (int j = 0; j < COLUMN_NUMBER; j++)
		{
			cells[i][j].setSize(sf::Vector2f(cellWidth, cellHeight));
			cells[i][j].setPosition(i * cellWidth, j * cellHeight);
			if (matrix[i][j] == -1) {
				cells[i][j].setFillColor(sf::Color::White);
			}
			else {
				cells[i][j].setFillColor(sf::Color::Black);
			}
			
		}
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		

		// Draw the matrix
		for (int i = 0; i < ROW_NUMBER; i++)
		{
			for (int j = 0; j < COLUMN_NUMBER; j++)
			{
				window.draw(cells[i][j]);
			}
		}

		window.display();

		//updateCellColors(cells, matrix);
	}
}

void Graph::updateCellColors(int row, int col)
{
            switch (matrix[row][col])
            {
                case 1:
                    cells[row][col].setFillColor(sf::Color::Red);
                    break;
                case 2:
                    cells[row][col].setFillColor(sf::Color::Green);
                    break;
                case 3:
                    cells[row][col].setFillColor(sf::Color::Blue);
                    break;
                case 4:
                    cells[row][col].setFillColor(sf::Color::Yellow);
                    break;
                case 5:
                    cells[row][col].setFillColor(sf::Color::Magenta);
                    break;
                default:
                    cells[row][col].setFillColor(sf::Color::White);
            }


        
    
}
