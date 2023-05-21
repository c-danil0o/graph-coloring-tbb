#include <iostream>
#include "tbb/task_group.h"
#include "tbb/tick_count.h"
#include "tbb/parallel_invoke.h"
#include "Graph.h"



using namespace std;
using namespace tbb;

int main() {
	Graph gs;
	gs.init_matrix();
	gs.generate_nodes();
	gs.parse_matrix();
	tick_count serial_begin = tick_count::now();
	parallel_invoke([&] {gs.draw(); }, [&] { gs.color_bfs(0, 0); });
	//gs.color_bfs(0);
	tick_count serial_end = tick_count::now();
	cout << "Serial time: " << (serial_end - serial_begin).seconds()<<endl;
	//gs.~Graph();

	//Graph g;
	//g.init_matrix();
	//g.generate_nodes();
	//g.parse_matrix();
	//task_group gr;
	//tick_count parallel_begin = tick_count::now();
	//gr.run([&] {g.draw(); });
	//gr.run([&]{ g.color_bfs(0, 0); });
	//gr.run([&] {g.color_bfs(30, 1); });
	//gr.run([&] {g.color_bfs(1560, 2); });
	//gr.run([&] {g.color_bfs(1597, 3); });
	//gr.wait();
	//tick_count parallel_end = tick_count::now();
	//cout << "Parallel time: " << (parallel_end - parallel_begin).seconds() << endl;
	//parallel_invoke(
	//	[&] {g.draw(); },
	//	[&] {g.color_bfs(0, 500); },
	//	[&] {g.color_bfs(500, 1000); },
	//	[&] {g.color_bfs(1000, 1500); },
	//	[&] {g.color_bfs(1500, 2000); }
	//);
	//g.print_matrix(); 

	

	
}