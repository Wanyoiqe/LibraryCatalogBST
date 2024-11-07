#include <iostream>
#include <string>

struct Node {
    std::string isbn;
    std::string bookData;
    Node* left;
    Node* right;
    
    Node(const std::string& isbn, const std::string& bookData)
        : isbn(isbn), bookData(bookData), left(nullptr), right(nullptr) {}
};

class BookBST {
public:
    BookBST() : root(nullptr) {}

    void insert(const std::string& isbn, const std::string& bookData) {
        root = insert(root, isbn, bookData);
    }

    std::string search(const std::string& isbn) {
        Node* node = search(root, isbn);
        return node ? node->bookData : "";
    }

    void deleteISBN(const std::string& isbn) {
        root = deleteNode(root, isbn);
    }

private:
    Node* root;

    Node* insert(Node* node, const std::string& isbn, const std::string& bookData) {
        if (node == nullptr) return new Node(isbn, bookData);
        if (isbn < node->isbn) node->left = insert(node->left, isbn, bookData);
        else if (isbn > node->isbn) node->right = insert(node->right, isbn, bookData);
        return node;
    }

    Node* search(Node* node, const std::string& isbn) {
        if (node == nullptr || node->isbn == isbn) return node;
        if (isbn < node->isbn) return search(node->left, isbn);
        return search(node->right, isbn);
    }

    Node* deleteNode(Node* node, const std::string& isbn) {
        if (node == nullptr) return node;
        if (isbn < node->isbn) node->left = deleteNode(node->left, isbn);
        else if (isbn > node->isbn) node->right = deleteNode(node->right, isbn);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->isbn = temp->isbn;
            node->bookData = temp->bookData;
            node->right = deleteNode(node->right, temp->isbn);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) current = current->left;
        return current;
    }
};
