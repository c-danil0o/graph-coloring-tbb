#include <iostream>
#include "tbb/task_group.h"
#include "tbb/tick_count.h"
#include "tbb/parallel_invoke.h"
#include "Graph.h"



using namespace std;
using namespace tbb;

void start_serial() {
    Graph gs;
    gs.init_matrix();
    gs.generate_nodes();
    gs.parse_matrix();
    parallel_invoke([&] {gs.draw(); }, [&] { gs.color_bfs(0, 0); });
    //gs.color_bfs(0, 0);


}
void start_parallel() {
    Graph g;
    g.init_matrix();
    g.generate_nodes();
    g.parse_matrix();
    task_group gr;
    gr.run([&] {g.draw(); });
   /* gr.run([&] { g.color_bfs(0, 0); });
    gr.run([&] {g.color_bfs(COLUMN_NUMBER - 5, 1); });
    gr.run([&] {g.color_bfs(ROW_NUMBER * (COLUMN_NUMBER - 1) + 1, 2); });
    gr.run([&] {g.color_bfs(ROW_NUMBER * COLUMN_NUMBER - 5, 3); });*/
    gr.run([&] {g.color_bfs(COLUMN_NUMBER * ROW_NUMBER / 8, 0); });
    gr.run([&] {g.color_bfs(2*COLUMN_NUMBER * ROW_NUMBER / 8, 1); });
    gr.run([&] {g.color_bfs(3*COLUMN_NUMBER * ROW_NUMBER / 8, 2); });
    gr.run([&] {g.color_bfs(4*COLUMN_NUMBER * ROW_NUMBER / 8, 3); });
    gr.run([&] {g.color_bfs(5*COLUMN_NUMBER * ROW_NUMBER / 8, 4); });
    gr.run([&] {g.color_bfs(6 * COLUMN_NUMBER * ROW_NUMBER / 8, 5); });
    gr.run([&] {g.color_bfs(7 * COLUMN_NUMBER * ROW_NUMBER / 8, 6); });
    gr.run([&] {g.color_bfs(8*COLUMN_NUMBER * ROW_NUMBER / 8 - 5, 7); });
    gr.wait();

}

int main() {
    int opcija = 0;
    cout << "1. Serijski\n2. Paralelno\n3.Kraj\n";
    while (opcija != 3) {
        cout << "Unesite opciju> ";
        cin >> opcija;
        cout << endl;
        if (opcija == 1) {
            tick_count serial_begin = tick_count::now();
            start_serial();
            tick_count serial_end = tick_count::now();
            cout << "Serial time: " << (serial_end - serial_begin).seconds() << endl;
        }
        else if (opcija == 2) {
            tick_count parallel_begin = tick_count::now();
            start_parallel();
            tick_count parallel_end = tick_count::now();
            cout << "Parallel time: " << (parallel_end - parallel_begin).seconds() << endl;
        }
    }


}