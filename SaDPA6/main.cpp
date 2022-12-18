#include <vector>
#include <random>
#include <iostream>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> generateMatrix(const int n, const int m) {
    vector<int> row;
    vector<vector<int>> generatedMatrix;
    for (int i = 0; i < n; i++){
        row.clear();
        for (int j = 0; j < m; j++) {
            row.push_back(rand()%100);
        }
        generatedMatrix.push_back(row);
    }
    return generatedMatrix;
}

vector<vector<int>> zeroMatrix(const int n, const int m) {
    vector<vector<int>> matrix(n, vector<int> (m));
    return matrix;
}

long long cntBruteForce = 0;
int shortPathBruteForce(const vector<vector<int>>& matrix, int i = 0, int j = 0) {
    cntBruteForce++;
    if (i == matrix.size()-1 && j == matrix[i].size()-1) { // Если дошли до последней ячейки, возвращаем ее значение
        return matrix[i][j];
    } else if (i == matrix.size() || j == matrix[i].size()) { // При выходе за границу массива,
        return 10000000;                                     // возвращаем большое число, которое никогда не будет минимальным
    } else { // В других ситуациях перебираем все возможные пути из данной ячейки и выбираем путь с минимальной длиной
        return matrix[i][j] + min(shortPathBruteForce(matrix, i+1, j), min(shortPathBruteForce(matrix, i+1, j+1), shortPathBruteForce(matrix, i, j+1)));
    }
}

int cntDynamic = 0;
int shortPathDynamicProg(const vector<vector<int>>& matrix, vector<vector<int>>& pathMatrix, int i = 0, int j = 0) {
    cntDynamic++;
    if (i==0 && j==0) {
        pathMatrix[i][j] = matrix[i][j];
    } else if (i == 0) {
        pathMatrix[i][j] = matrix[i][j] + pathMatrix[i][j-1];
    } else if (j == 0) {
        pathMatrix[i][j] = matrix[i][j] + pathMatrix[i-1][j];
    } else {
        pathMatrix[i][j] = matrix[i][j] + min(pathMatrix[i-1][j-1], min(pathMatrix[i][j-1], pathMatrix[i-1][j]));
    }
    
    if (j < matrix[i].size()-1) {
        shortPathDynamicProg(matrix, pathMatrix, i, j+1);
    } else if (i < matrix.size()-1){
        shortPathDynamicProg(matrix, pathMatrix, i+1, 0);
    }
    return pathMatrix[matrix.size()-1][matrix[i].size()-1];
}

int main(int argc, const char * argv[]) {
    srand(time(0));
    
    int rowCnt, colCnt;
    
    cout << "Введите число строк и столбцов: ";
    cin >> rowCnt >> colCnt;
    
    vector<vector<int>> matrix = generateMatrix(rowCnt, colCnt);
    vector<vector<int>> pathMatrix = zeroMatrix(rowCnt, colCnt);
    
    cout << "\nИсходная матрица: " << endl;
    printMatrix(matrix);
    
    
//    printMatrix(pathMatrix);
    
    cout << "Результат метода грубой силы: " << shortPathBruteForce(matrix)
    << "\nРезультат метода динамического программирования: " << shortPathDynamicProg(matrix, pathMatrix)
    << "\n\nЧисло шагов в методе грубой силы: " << cntBruteForce
    << "\nЧисло шагов в методе динамического программирования: " << cntDynamic << endl << endl;
    return 0;
}
