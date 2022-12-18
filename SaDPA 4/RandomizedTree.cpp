#include "RandomizedTree.h"

RandomizedTree::RandomizedTree(){
    root = nullptr;
}


/// Метод получения значения поля size дерева с корнем p
int RandomizedTree::getSize(NodeRT* p) {
    if (!p) return 0;
    return p->size;
}

/// Метод установления корректного размера дерева с корнем p
void RandomizedTree::fixSize(NodeRT* p) {
    p->size = getSize(p->left) + getSize(p->right) + 1;
}

/// Метод удаления всех узлов дерева
void RandomizedTree::clear(NodeRT* p) {
    if (p != nullptr) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}

/// Метод левого поворота вокруг узла q
NodeRT* RandomizedTree::rotateLeft(NodeRT* q){
    NodeRT* p = q->right;
    if (!p) return q;
                              // Если узел, вокруг которого совершался
    if (q == root) root = p; // поворот был корнем всего дерева,
                            // поле корня меняется на правого сына
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixSize(q); // После поворота меняется поле
    return p;  // размера поддерева с корнем в данном узле
}

/// Метод правого поворота вокруг узла p
NodeRT* RandomizedTree::rotateRight(NodeRT* p) {
    NodeRT* q = p->left;
    if (!q) return p;
                              // Если узел, вокруг которого совершался
    if (p == root) root = q; // поворот был корнем всего дерева,
                            // поле корня меняется на левого сына
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixSize(p); // После поворота меняется поле
    return q;  // размера поддерева с корнем в данном узле
}

/// Метод вставки нового узла в дерево. С вероятностью 1/(n+1),
/// где n-размер дерева до вставки, выполняется вставка в корень
/// На вход принимает: p - корень дерева, в которое происходит вставка;
/// key, pos - значения полей key и positoin структуры Node соответственно
NodeRT* RandomizedTree::insert(NodeRT* p, int key, int pos) {
    if (!p) {                    // Если дерево пустое (не имеет корня), создается корень
        if (root == nullptr) {  // Иначе создается наследник подходящего узла
            root = new NodeRT(key, pos);
            return root;
        }
        return new NodeRT(key, pos);
    }
    
    if (rand()%(p->size+1)==0) // С вероятностью 1/(n+1), узел вставляется в корень
        return insertRoot(p, key, pos);
    
    if (key < p->key) {
        p->left = insert(p->left, key, pos);
    }
    else {
        p->right = insert(p->right, key, pos);
    }

    fixSize(p); // После вставки меняется поле размера поддерева с корнем p
    return p;
}

//int RandomizedTree::rotateCnt = 0;
/// Метод вставки нового узла в корень дерева.
/// На вход принимает: p - корень дерева, в которое происходит вставка;
/// key, pos - значения полей key и positoin структуры Node соответственно
NodeRT* RandomizedTree::insertRoot(NodeRT* p, int key, int pos) {
    if (!p) {
        if (root == nullptr) {
            root = new NodeRT(key, pos);
            return root;
        }
        return new NodeRT(key, pos);
    }
    
    // Рекурсивная вставка нового ключа в корень левого (правого) поддеревьев
    // и выполнение поворота, противоположного по направлению стороне вставки
//    rotateCnt++;
    if (key < p->key) {
        p->left = insertRoot(p->left, key, pos);
        return rotateRight(p);
    }
    else {
        p->right = insertRoot(p->right, key, pos);
        return rotateLeft(p);
    }
}


/// Метод удаления узла из дерева
/// Последовательно проходит по дереву в соответствии с алгоритмом
/// При совпадении ключа удаляемого узла с ключом рассматриваемого,
/// объединяем поддеревья его потомков и удаляем найденный узел
NodeRT* RandomizedTree::remove(NodeRT* p, int key) {
    if (!p) return nullptr;

    if (p->key == key) {
        NodeRT* q = merge(p->left, p->right);
        if (p == root) root = q;
        delete p;
        return q;
    }
    else if (key < p->key) {
        p->left = remove(p->left, key);
    }
    else {
        p->right = remove(p->right, key);
    }
    return p;
}

/// Метод объединения двух поддеревьев при удалении узла
/// Выбор между присоединением левого подподдерве к правому поддереву и наоборот
/// происходит случайно n/(m+n) и m/(m+n), где m и n размеры левого и правого поддеревьев
/// На вход принимает указатели на левое и правое поддеревья
NodeRT* RandomizedTree::merge(NodeRT* p, NodeRT* q) {
    if (!p) return q;
    if (!q) return p;
    
    if (rand()%(p->size+q->size) < p->size) {
        p->right = merge(p->right, q);
        fixSize(p);
        return p;
    }
    else {
        q->left = merge(p, q->left);
        fixSize(q);
        return q;
    }
}

/// Метод поиска узла по ключу в дереве
NodeRT* RandomizedTree::find(NodeRT* p, int key) {
    if (!p)             // Дерево пустое
        return nullptr;
    if (key == p->key)  // Узел найден
        return p;
    if (key < p->key)   // Ключ искомого элемента меньше ключа текущего
        return find(p->left, key);
    else                // Ключ искомого элемента больше ключа текущего
        return find(p->right, key);
}


/// Проходит по дереву p и находит длину максимального пути к листу
int RandomizedTree::maxDepth(NodeRT* p) {
    if (!p) return 0;
    else
        return 1 + ((maxDepth(p->left) > maxDepth(p->right)) ?
                    maxDepth(p->left) : maxDepth(p->right));
}

/// Метод визуально простого вывода дерева
void RandomizedTree::printTreeSimple(NodeRT* p, int depth) {
    if (!p) return;
    
    printTreeSimple(p->left, ++depth);
    for (int i = 0; i < depth; i++)
        cout << "|";
    cout << p->key << endl;
    depth--;
    printTreeSimple(p->right, ++depth);
}

/// Метод вывода дерева по уровням на экран
void RandomizedTree::printTree(NodeRT* p, int depth, int maxDepth) {
    if (!p) return;
    
    printTree(p->right, ++depth, maxDepth);
    cout << " \u2502";
    for (int i = 1; i < maxDepth+1; i++) {
        if (i == depth){
            cout << setw(9) << p->key << "\u2502";
        }
        else{
            cout << setw(12) << "\u2502";
        }
    }
    cout << endl;
    
    printTree(p->left, depth, maxDepth);
}

/// Вспомогательный метод для метода print( )
/// На вход принимает  ширину каждой колонки ( в символах), число колонок таблицы,
/// а также символ начала линии (левый угол), символ объединения линии с разделителем столбцов и сивол конца линии
void RandomizedTree::drawTableLine(int colWidth, int colCount, string cornerStart, string columnConnect, string cornerEnd) {
    cout << " " << cornerStart;
    for (int i = 0; i < colCount; i++) {
        int width = colWidth;
        if (i == 0)
            width = 9;
        for (int j = 0; j < width; j++) {
            if (i != 0 && j == 0)
                cout << columnConnect;
            else
                cout << "\u2500";
        }
    }
    cout << cornerEnd << "\n";
}


/// Метод получения поля position узла по ключу
int RandomizedTree::getPos(int key) {
    int position = find(key)->position;
    return position;
}


///
/// Методы-обертки для удобного вызова методов дерева
/// без аргументов и соответсвия описанию в базовом классе
///

void RandomizedTree::printSimple() {
    printTreeSimple(root, 0);
}

void RandomizedTree::print() {
    int maxDepth = this->maxDepth(root);
    
    drawTableLine(10, maxDepth, "┌", "┬", "┐");
    printTree(root, 0, maxDepth);
    drawTableLine(10, maxDepth, "├", "┼", "┤");
    
    cout << " \u2502"; // Вывод нумерации уровней дерева
    for (int i = 1; i < maxDepth+1; i++) {
        cout << setw(9) << i << "\u2502";
    }
    cout << endl;
    drawTableLine(10, maxDepth, "└", "┴", "┘");
    cout << endl;
    
}

bool RandomizedTree::remove(int key) {
    return remove(root, key);
}

NodeRT* RandomizedTree::find(int key) {
    return find(root, key);
}

bool RandomizedTree::insert(int key, int pos) {
    return insert(root, key, pos);
}

RandomizedTree::~RandomizedTree() {
    clear(root);
}
