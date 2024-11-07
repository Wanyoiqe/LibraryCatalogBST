class BST:
    class Node:
        def __init__(self, isbn, book_data):
            self.isbn = isbn
            self.book_data = book_data
            self.left = None
            self.right = None

    def __init__(self):
        self.root = None

    def insert(self, isbn, book_data):
        """Inserts a new book record into the BST."""
        self.root = self._insert(self.root, isbn, book_data)

    def _insert(self, node, isbn, book_data):
        if node is None:
            return self.Node(isbn, book_data)
        elif isbn < node.isbn:
            node.left = self._insert(node.left, isbn, book_data)
        elif isbn > node.isbn:
            node.right = self._insert(node.right, isbn, book_data)
        return node

    def search(self, isbn):
        """Searches for a book by its ISBN."""
        return self._search(self.root, isbn)

    def _search(self, node, isbn):
        if node is None:
            return None
        if isbn == node.isbn:
            return node.book_data
        elif isbn < node.isbn:
            return self._search(node.left, isbn)
        else:
            return self._search(node.right, isbn)

    def delete(self, isbn):
        """Deletes a book record by ISBN."""
        self.root = self._delete(self.root, isbn)

    def _delete(self, node, isbn):
        if node is None:
            return None
        if isbn < node.isbn:
            node.left = self._delete(node.left, isbn)
        elif isbn > node.isbn:
            node.right = self._delete(node.right, isbn)
        else:
            # Node with only one child or no child
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            # Node with two children: get the inorder successor
            min_larger_node = self._min_value_node(node.right)
            node.isbn, node.book_data = min_larger_node.isbn, min_larger_node.book_data
            node.right = self._delete(node.right, min_larger_node.isbn)
        return node

    def _min_value_node(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current
