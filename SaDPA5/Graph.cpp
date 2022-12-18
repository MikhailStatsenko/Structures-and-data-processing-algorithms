#include "Graph.h"

Graph::Graph(int verticeCnt) {
    this->verticeCnt = verticeCnt;
    adjacencyList.resize(verticeCnt);
}

void Graph::printList() {
    for (int i = 0; i < verticeCnt; i++) {
        cout << i+1;
        if (!adjacencyList[i]) {
            cout << endl;
            continue;
        }
        for (auto vertice : *adjacencyList[i]){
            cout << " ---> " << vertice.first << " (" << vertice.second << ")";
        }
        cout << endl;
    }
}

bool Graph::addEdge(int from, int to, int weight) {
    pair<int, int> node = make_pair(to, weight);
    if (adjacencyList[from-1]) {
        for (auto elem : *adjacencyList[from-1]) {
            if (elem.first == to) {
                cout << "\nТакая связь уже есть" << endl;
                return false;
            }
        }
    }
    else {
        adjacencyList[from-1] = new forward_list<pair<int, int>>;
    }
    adjacencyList[from-1]->push_front(node);
    return true;
}

vector<vector<int>> Graph::listToMatrix() {
    vector<vector<int>> matrix(verticeCnt);
    
    for (int i = 0; i < verticeCnt; i++) {
        matrix[i].resize(verticeCnt, 0);
        
        if (!adjacencyList[i]) continue;
        for (auto vertice : *adjacencyList[i]){
            matrix[i][vertice.first-1] = vertice.second;
        }
    }
    return matrix;
}

// Функция вывода кратчайшего пути
void findPath(int i, int j, vector<vector<int>> p) {
    int k = p[i][j];
    if (k == 0) return;
    findPath(i, k, p);
    cout << k+1 << "-";
    findPath(k, j, p);
}

void Graph::floydAlgorithm(int from, int to) {
    // Исходная матрица смежности, построенная на базе списка смежности
    vector<vector<int>> matrix(listToMatrix());
    
    // Вспомогательный массив для вывода кратчайшего пути
    vector<vector<int>> path(verticeCnt);
    // Заполнение нулями массива кратчайшего пути
    for (auto elem = path.begin(); elem != path.end(); elem++) {
        (*elem).resize(verticeCnt, 0);
    }
    
    // Матрица смежности заполняется большими числами в местах
    // отсутствия связей, чтобы алгоритм их избегал
    for (int i = 0; i < verticeCnt; i++){
        for (int j = 0; j < verticeCnt; j++) {
            if (matrix[i][j] == 0 && i != j) {
                matrix[i][j] = 1000000000;
            }
        }
    }
    
    // Поиск кратчайшего пути методом Флойда
    for (int k = 0; k < verticeCnt; k++){
        for (int i = 0; i < verticeCnt; i++){
            for (int j = 0; j < verticeCnt; j++){
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    path[i][j] = k; // Добавление участка крартчайшего пути
                }
            }
        }
    }

    // Вывод последовательности шагов пути
    if (matrix[from-1][to-1] < 1000000000) {
        cout << from << "->" << to << ": " << from << "-";
        findPath(from-1, to-1, path);
        cout << to << " (" << matrix[from-1][to-1] << ")" << endl << endl;
    } else {
        cout << "\nПуть между вершинами не найден" << endl;
    }
}

int Graph::findEccentricity(int vertice, int length, vector<int>* visited) {
    if (!visited) visited = new vector<int>;
    visited->push_back(vertice);

    int maxLen = length;
    if (adjacencyList[vertice-1]){
        for (auto vert = adjacencyList[vertice-1]->begin();
             vert != adjacencyList[vertice-1]->end(); vert++){

            for (auto iter = visited->begin(); iter != visited->end(); iter++){
                if (*iter == (*vert).first) continue;
            }

            int tmpLen = findEccentricity((*vert).first, length+(*vert).second, visited);
            if (tmpLen > maxLen)
                maxLen = tmpLen;
        }
    }
    return maxLen;
}

