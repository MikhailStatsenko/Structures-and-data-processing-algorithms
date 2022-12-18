#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/// Метод удаления всех узлов дерева
void BinarySearchTree::clear(NodeBST* p) {
    if (p != nullptr) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}

/// Метод поиска приемника при удалении узла с двумя детьми
NodeBST* BinarySearchTree::findAssignee(NodeBST* p) {
    NodeBST* node = p;
    while (node && node->left != nullptr)
        node = node->left;
    return node;
}

/// Метод поиска узла по ключу в дереве
NodeBST* BinarySearchTree::find(NodeBST* p, int key) {
    if (!p)             // Дерево пустое
        return nullptr;
    if (key == p->key)  // Узел найден
        return p;
    if (key < p->key)   // Ключ искомого элемента меньше ключа текущего
        return find(p->left, key);
    else                // Ключ искомого элемента больше ключа текущего
        return find(p->right, key);
}

/// Метод удаления узла из дерева
NodeBST* BinarySearchTree::remove(NodeBST* p, int key) {
    if (!p) return nullptr;
    
    if (key < p->key) {
        p->left = remove(p->left, key);
    }
    else if (key > p->key) {
        p->right = remove(p->right, key);
    }
    else {
        // Если у узла не более одного ребенка,
        // можно просто вырезать удаляемый узел
        if (p->left == nullptr) {
            NodeBST* q = p->right;
            delete p;
            return q;
        }
        else if (p->right == nullptr) {
            NodeBST* q = p->left;
            delete p;
            return q;
        }
        // Если у узла два ребенка, необходимо найти
        // самого левого ребенка правого поддерева узла
        // и поставить его вместо удаляемого узла,
        NodeBST* q = findAssignee(p->right);
        p->key = q->key;
        p->position = q->position;
        // Удаление узла, заместившего удаленного
        p->right = remove(p->right, q->key);
    }
    return p;
}

/// Метод вставки нового узла в дерево
/// На вход принимает: p - корень дерева, в которое происходит вставка;
/// key, pos - значения полей key и positoin структуры Node соответственно
NodeBST* BinarySearchTree::insert(NodeBST* p, int key, int pos) {
    if (!p) {                    // Если дерево пустое (не имеет корня), создается корень
        if (root == nullptr) {  // Иначе создается наследник подходящего узла
            root = new NodeBST(key, pos);
            return root;
        }
        return new NodeBST(key, pos);
    }
    
    if (key < p->key)
        p->left = insert(p->left, key, pos);
    else
        p->right = insert(p->right, key, pos);
    return p;
}


/// Проходит по дереву p и находит длину максимального пути к листу
int BinarySearchTree::maxDepth(NodeBST* p) {
    if (!p) return 0;
    else
        return 1 + ((maxDepth(p->left) > maxDepth(p->right)) ?
                    maxDepth(p->left) : maxDepth(p->right));
}

/// Метод визуально простого вывода дерева
void BinarySearchTree::printTreeSimple(NodeBST* p, int depth) {
    if (!p) return;
    
    printTreeSimple(p->left, ++depth);
    for (int i = 0; i < depth; i++)
        cout << "|";
    cout << p->key << endl;
    depth--;
    printTreeSimple(p->right, ++depth);
}

/// Метод вывода дерева по уровням на экран
void BinarySearchTree::printTree(NodeBST* p, int depth, int maxDepth) {
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
void BinarySearchTree::drawTableLine(int colWidth, int colCount, string cornerStart, string columnConnect, string cornerEnd) {
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
int BinarySearchTree::getPos(int key) {
    int position = find(key)->position;
    return position;
}

///
/// Методы-обертки для удобного вызова методов дерева
/// без аргументов и соответсвия описанию в базовом классе
///

void BinarySearchTree::printSimple() {
    printTreeSimple(root, 0);
}

void BinarySearchTree::print() {
    int maxDepth = this->maxDepth((NodeBST*)root);

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

bool BinarySearchTree::remove(int key) {
    return remove(root, key);
}

NodeBST* BinarySearchTree::find(int key) {
    return find(root, key);
}

bool BinarySearchTree::insert(int key, int pos) {
    return insert(root, key, pos);
}

BinarySearchTree::~BinarySearchTree() {
    clear(root);
}
