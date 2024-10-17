#include <iostream>
#include <vector>
#include <queue>
#include <utility> // cho pair
#include <climits> // cho INT32_MAX
#include "Function.h"
#include <fstream> 
using namespace std;

// Cấu trúc để lưu trữ thông tin của cạnh (đỉnh kề và trọng số)

int main() {
    int num_nodes;  // Số lượng đỉnh
    unordered_map<int, vector<pair<int, double>>> graph;  // Biểu diễn đồ thị
    int start = NULL;
    int goal = NULL;
    // Nhập dữ liệu
    docDuLieuTuFile("D:/UDC/AKT_AT_Algorithm/input_AT.txt", num_nodes, graph, start, goal);

    // Hàm trả về danh sách các đỉnh kề và trọng số
    auto get_neighbors = [&](int node) {
        return graph[node];
        };

    // Gọi hàm AT để tìm trạng thái đích
    vector<int> path = AT(start, goal, get_neighbors);

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
