#include <iostream>
using namespace std;

// Структура узла дерева
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;
    
    // Вспомогательные рекурсивные функции
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        
        return node;
    }
    
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    Node* remove(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }
        
        // Поиск узла для удаления
        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // Узел найден
            // Случай 1: нет детей или только один ребенок
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            // Случай 2: два ребенка
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }
    
    bool search(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }
        
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }
    
    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    
    void preorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    
    void postorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
    
    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
public:
    BinaryTree() {
        root = nullptr;
    }
    
    ~BinaryTree() {
        clear(root);
    }
    
    // Публичные методы
    void insert(int value) {
        root = insert(root, value);
    }
    
    void remove(int value) {
        root = remove(root, value);
    }
    
    bool search(int value) {
        return search(root, value);
    }
    
    void printInorder() {
        cout << "Inorder traversal: ";
        inorder(root);
        cout << endl;
    }
    
    void printPreorder() {
        cout << "Preorder traversal: ";
        preorder(root);
        cout << endl;
    }
    
    void printPostorder() {
        cout << "Postorder traversal: ";
        postorder(root);
        cout << endl;
    }
};

// Пример использования
int main() {
    BinaryTree tree;
    
    // Добавление элементов
    cout << "Adding elements: 50, 30, 70, 20, 40, 60, 80" << endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    // Вывод дерева разными способами
    tree.printInorder();
    tree.printPreorder();
    tree.printPostorder();
    
    // Поиск элементов
    cout << "\nSearching for 40: " << (tree.search(40) ? "Found" : "Not found") << endl;
    cout << "Searching for 100: " << (tree.search(100) ? "Found" : "Not found") << endl;
    
    // Удаление элемента
    cout << "\nRemoving 30" << endl;
    tree.remove(30);
    tree.printInorder();
    
    cout << "\nRemoving 50" << endl;
    tree.remove(50);
    tree.printInorder();
    
    return 0;
}
