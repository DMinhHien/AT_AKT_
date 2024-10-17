#include <iostream>
#include "Function.h"
using namespace std;

int main() {
    int num_nodes;  // Số lượng đỉnh
    vector<double> heuristics;  // Mảng chứa các giá trị heuristic
    unordered_map<int, vector<pair<int, double>>> graph;  // Biểu diễn đồ thị
    // Nhập dữ liệu
    int start = NULL;
    int goal=NULL;
    docDuLieuTuFile("D:/UDC/AKT_AT_Algorithm/input_AKT.txt", num_nodes, heuristics, graph, start, goal);

    // Nhập đỉnh bắt đầu và đích
    
   
    // Hàm trả về danh sách các đỉnh kề và trọng số
    auto get_neighbors = [&](int node) {
        return graph[node];
        };

    // Hàm ước lượng heuristic
    auto h = [&](int node) {
        return heuristics[node];
        };

    // Gọi hàm AKT để tìm trạng thái đích
    vector<int> path = AKT(start, goal, get_neighbors, h);

    if (!path.empty()) {
        cout << "Tim thay duong di: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "Khong tim thay duong di." << endl;
    }
    return 0;
}