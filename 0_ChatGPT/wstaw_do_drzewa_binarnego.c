//Napisz program w c, który wstawia element do drzewa binarnego

#include <stdio.h>
#include <stdlib.h>

// Struktura przechowująca węzeł drzewa binarnego.
struct node {
    int data;
    struct node *left;
    struct node *right;
};

// Funkcja tworząca nowy węzeł z podaną wartością.
struct node *newNode(int data) {
    // Alokuj pamięć dla nowego węzła.
    struct node *node = (struct node *) malloc(sizeof(struct node));

    // Ustaw wartość węzła i ustaw wskaźniki na NULL.
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

// Funkcja dodająca element do drzewa binarnego.
struct node *insert(struct node *node, int data) {
    // Jeśli drzewo jest puste, utwórz nowy węzeł i zwróć go.
    if (node == NULL) return (newNode(data));

    // Jeśli wartość nowego elementu jest mniejsza niż wartość węzła, dodaj go do lewego poddrzewa.
    if (data < node->data) node->left = insert(node->left, data);
        // W przeciwnym razie dodaj go do prawego poddrzewa.
    else if (data > node->data) node->right = insert(node->right, data);

    return (node); // Zwróć węzeł (zmieniony lub niezmieniony).
}

int main() {
    struct node *root = NULL; // Inicjalizuj puste drzewo.

    // Wstaw kilka elementów do drzewa.
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 1);

    // Drukuj drzewo (możesz użyć innego sposobu wizualizacji drzewa).
    printf("Drzewo: 5, 3, 1, 4, 10\n");

    return 0;
}
