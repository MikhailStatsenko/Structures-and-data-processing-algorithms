#include <iostream>
using namespace std;

#include "Graph.h"

int main() {
    int num = 0, verticeCnt = 0;
    Graph* graph = nullptr;
    cout << "Введите номер графа, который вы хотите использовать.\nДоступны графы №6 и №7\n> ";
    while (num != 6 && num != 7) {
        cin >> num;
        if (num == 6){
            verticeCnt = 6;
            graph = new Graph(verticeCnt);
            graph->addEdge(1, 3, 4);
            graph->addEdge(1, 2, 8);
            graph->addEdge(2, 5, 3);
            graph->addEdge(2, 4, 6);
            graph->addEdge(3, 2, 3);
            graph->addEdge(3, 4, 2);
            graph->addEdge(3, 6, 10);
            graph->addEdge(4, 5, 3);
            graph->addEdge(4, 6, 1);
            graph->addEdge(5, 6, 4);
        } else if (num == 7) {
            verticeCnt = 10;
            graph = new Graph(verticeCnt);
            graph->addEdge(1, 4, 2);
            graph->addEdge(1, 3, 4);
            graph->addEdge(1, 2, 3);
            graph->addEdge(2, 6, 3);
            graph->addEdge(3, 6, 6);
            graph->addEdge(4, 5, 5);
            graph->addEdge(4, 6, 2);
            graph->addEdge(5, 7, 6);
            graph->addEdge(5, 9, 12);
            graph->addEdge(6, 5, 1);
            graph->addEdge(6, 7, 8);
            graph->addEdge(6, 8, 7);
            graph->addEdge(7, 10, 4);
            graph->addEdge(8, 10, 3);
            graph->addEdge(9, 8, 6);
            graph->addEdge(9, 10, 11);
        } else {
            cout << "Введен неверный номер графа. Попробуйте еще раз: " << endl;
        }
    }
    while (num != 0) {
        cout << "\nЧто нужно сделать?\n0 - Завершить работу программы\n1 - Напечатать список смежных вершин\n2 - Определить эксцентриситет вершины\n3 - Вывести кратчайший путь между вершинами, найденным методом Флойда\n4 - Добавить ребро\n> ";
        cin >> num;
        switch (num){
            case 0:
                cout << "\nРабота программы завершена" << endl << endl;
                break;
            case 1:
                graph->printList();
                break;
            case 2: {
                int vertice;
                cout << "\nВведите номер вершины\n> ";
                cin >> vertice;
                if (vertice > verticeCnt || vertice <= 0) {
                    cout << "\nВершина не принадлежит графу" << endl;
                } else {
                    cout << "\nЭксцентриситет вершины №" << vertice << " - " << graph->findEccentricity(vertice) << endl;
                }
                break;
            }
            case 3: {
                int verticeFrom, verticeTo;
                cout << "\nВведите номер начальной и конечной вершин через пробел\n> ";
                cin >> verticeFrom >> verticeTo;
                if (verticeFrom > verticeCnt || verticeFrom <= 0 || verticeTo > verticeCnt || verticeTo <= 0) {
                    cout << "\nВершина не принадлежит графу" << endl;
                } else {
                    cout << endl;
                    graph->floydAlgorithm(verticeFrom, verticeTo);
                }
                break;
            }
            case 4: {
                cout << "\nВведите через пробел: вершину, из которой выходит ребро, в которую приходит и вес ребра\n> ";
                int verticeFrom, verticeTo, weight;
                cin >> verticeFrom >> verticeTo >> weight;
                if (verticeFrom > verticeCnt || verticeFrom <= 0 || verticeTo > verticeCnt || verticeTo <= 0) {
                    cout << "\nВершина не принадлежит графу" << endl;
                } else {
                    graph->addEdge(verticeFrom, verticeTo, weight);
                }
                break;
            }
        }
    }
    return 0;
}
