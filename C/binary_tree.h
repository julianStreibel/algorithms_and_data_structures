#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
    float data;
    tree_node *left;
    tree_node *rigth;
};

typedef struct
{
    tree_node *root;
} binary_tree;

binary_tree *binary_tree_create()
{
    binary_tree *new_tree = malloc(sizeof(binary_tree));
    new_tree->root = NULL;
    return new_tree;
}

tree_node *tree_node_create(float data)
{
    tree_node *new_node = malloc(sizeof(tree_node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->rigth = NULL;
    return new_node;
}

void binary_tree_insert_into_subtree(tree_node *sub_tree, float new_data)
{
    if (sub_tree->data > new_data)
    {
        if (sub_tree->left)
        {
            binary_tree_insert_into_subtree(sub_tree->left, new_data);
        }
        else
        {
            sub_tree->left = tree_node_create(new_data);
        }
    }
    else
    {
        if (sub_tree->rigth)
        {
            binary_tree_insert_into_subtree(sub_tree->rigth, new_data);
        }
        else
        {
            sub_tree->rigth = tree_node_create(new_data);
        }
    }
}

void binary_tree_insert(binary_tree *tree, float new_data)
{
    if (tree->root)
    {
        binary_tree_insert_into_subtree(tree->root, new_data);
    }
    else
    {
        tree->root = tree_node_create(new_data);
    }
}

void binary_tree_remove_item_in_subtree(tree_node *sub_tree, tree_node *parent, float data)
{
    if (sub_tree)
    {
        if (sub_tree->data == data)
        {
            if (sub_tree->left)
            {
                sub_tree->data = sub_tree->left->data;
                binary_tree_remove_item_in_subtree(sub_tree->left, sub_tree, sub_tree->data);
                return;
            }
            else if (sub_tree->rigth)
            {
                sub_tree->data = sub_tree->rigth->data;
                sub_tree->left = sub_tree->rigth->left;
                sub_tree->rigth->left = NULL;
                binary_tree_remove_item_in_subtree(sub_tree->rigth, sub_tree, sub_tree->data);
                return;
            }
            if (parent->left->data == data)
            {
                parent->left = NULL;
                free(sub_tree);
                return;
            }
            parent->rigth = NULL;
            free(sub_tree);
            return;
        }
        else if (sub_tree->data < data)
        {
            binary_tree_remove_item_in_subtree(sub_tree->rigth, sub_tree, data);
            return;
        }
        binary_tree_remove_item_in_subtree(sub_tree->left, sub_tree, data);
    }
    return;
}

void binary_tree_remove_item(binary_tree *tree, float data)
{
    if (tree->root)
    {
        binary_tree_remove_item_in_subtree(tree->root, NULL, data);
    }
}

void binary_tree_traverse_subtree(tree_node *subroot)
{
    if (subroot->left)
    {
        binary_tree_traverse_subtree(subroot->left);
    }
    printf("%f\n", subroot->data);
    if (subroot->rigth)
    {
        binary_tree_traverse_subtree(subroot->rigth);
    }
}

void binary_tree_traverse(binary_tree *tree)
{
    if (tree->root)
    {
        binary_tree_traverse_subtree(tree->root);
    }
}

void binary_tree_delete_subtree(tree_node *subroot)
{
    if (subroot->left)
    {
        binary_tree_delete_subtree(subroot->left);
    }
    if (subroot->rigth)
    {
        binary_tree_delete_subtree(subroot->rigth);
    }
    free(subroot);
}
