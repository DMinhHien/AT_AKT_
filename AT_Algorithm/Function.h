#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <limits>
#include <functional>
#include <fstream> 
using namespace std;

// Cấu trúc để biểu diễn một trạng thái trong cây tìm kiếm
struct State {
    int id;    // Mã trạng thái
    double g;  // Chi phí từ trạng thái khởi đầu

    // So sánh để dùng trong hàng đợi ưu tiên
    bool operator<(const State& other) const {
        return g > other.g; // g nhỏ hơn sẽ được ưu tiên
    }
};

// Hàm AT (thuật toán tìm kiếm trên cây không dựa vào heuristic)
vector<int> AT(
    int start,                  // Trạng thái bắt đầu
    int goal,                   // Trạng thái đích
    function<vector<pair<int, double>>(int)> get_neighbors // Hàm trả về các trạng thái lân cận (neighbor, cost)
) {
    priority_queue<State> open;  // Hàng đợi ưu tiên cho các trạng thái OPEN
    unordered_map<int, double> g_map; // Lưu trữ chi phí tốt nhất đến mỗi trạng thái
    unordered_map<int, int> parent;   // Lưu trạng thái cha của mỗi trạng thái

    // Đưa trạng thái khởi đầu vào OPEN
    open.push({ start, 0 });
    g_map[start] = 0;
    parent[start] = -1; // Trạng thái bắt đầu không có cha

    while (!open.empty()) {
        // a. Chọn trạng thái Tmax có giá trị g nhỏ nhất và loại khỏi OPEN
        State Tmax = open.top();
        open.pop();

        // b. Nếu Tmax là trạng thái kết thúc, truy vết lại đường đi và trả về
        if (Tmax.id == goal) {
            vector<int> path;
            int current = goal;
            while (current != -1) {
                path.push_back(current); // Thêm trạng thái hiện tại vào đường đi
                current = parent[current]; // Truy ngược về trạng thái cha
            }
            reverse(path.begin(), path.end()); // Đảo ngược đường đi để từ start đến goal
            return path;
        }

        // c. Tạo ra các trạng thái kế tiếp từ Tmax
        vector<pair<int, double>> neighbors = get_neighbors(Tmax.id); // Lấy danh sách các trạng thái lân cận
        for (const auto& neighbor : neighbors) {
            int Tk = neighbor.first;  // Lấy trạng thái Tk
            if (parent[Tmax.id] != Tk) {
                double cost = neighbor.second; // Lấy chi phí cost(Tmax, Tk)

                double g_new = Tmax.g + cost;  // g(Tk) = g(Tmax) + cost(Tmax, Tk)

                // Nếu tìm thấy một đường đi tốt hơn đến Tk, cập nhật trạng thái Tk
                if (g_map.find(Tk) == g_map.end() || g_new <= g_map[Tk]) {
                    g_map[Tk] = g_new;

                    // Cập nhật trạng thái cha của Tk là Tmax.id
                    parent[Tk] = Tmax.id;

                    // Thêm Tk vào OPEN
                    open.push({ Tk, g_new });
                }
            }
        }
    }

    // Không tìm thấy trạng thái đích
    return {};
}


// Hàm chính để nhập dữ liệu
void docDuLieuTuFile(const string& filename, int& num_nodes, unordered_map<int, vector<pair<int, double>>>& graph, int& start, int& goal) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << filename << endl;
        return;
    }

    file >> num_nodes;  // Đọc số lượng đỉnh

    // Đọc danh sách heuristic cho từng đỉnh

    // Đọc trọng số giữa các đỉnh
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            double cost;
            file >> cost;
            if (cost > 0) {  // Giả sử trọng số 0 nghĩa là không có đường đi
                graph[i].push_back({ j, cost });
            }
        }
    }

    file >> start >> goal;  // Đọc đỉnh bắt đầu và đích
}
