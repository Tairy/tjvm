//
// Created by tairy on 2020/11/21.
//

#include "string.h"
#include "util.h"
#include "bi_tree.h"

void bi_tree_init(struct bi_tree *tree, void (*destroy)(void *data)) {
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
}

void bi_tree_destroy(struct bi_tree *tree) {
    bi_tree_rem_left(tree, NULL);
    memset(tree, 0, sizeof(struct bi_tree));
}

u_int8_t bi_tree_ins_left(struct bi_tree *tree, struct bi_tree_node *node, const void *data) {
    struct bi_tree_node *new_node, **position;

    if (node == NULL) {
        if (BI_TREE_SIZE(tree) > 0) {
            return -1;
        }
        position = &tree->root;
    } else {
        if (BI_TREE_LEFT(node) != NULL) {
            return -1;
        }
        position = &node->left;
    }

    new_node = NEW(struct bi_tree_node);
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = (void *) data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}

u_int8_t bi_tree_ins_right(struct bi_tree *tree, struct bi_tree_node *node, const void *data) {
    struct bi_tree_node *new_node, **position;
    if (node == NULL) {
        if (BI_TREE_SIZE(tree) > 0) {
            return -1;
        }

        position = &tree->root;
    } else {
        if (BI_TREE_RIGHT(node) != NULL) {
            return -1;
        }
        position = &node->right;
    }

    new_node = NEW(struct bi_tree_node);
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = (void *) data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;
    tree->size++;
    return 0;
}

void bi_tree_rem_left(struct bi_tree *tree, struct bi_tree_node *node) {
    struct bi_tree_node **position;
    if (BI_TREE_SIZE(tree) == 0) {
        return;
    }

    if (node == NULL) {
        position = &tree->root;
    } else {
        position = &node->left;
    }

    if (*position != NULL) {
        bi_tree_rem_left(tree, *position);
        bi_tree_rem_right(tree, *position);

        if (tree->destroy != NULL) {
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        tree->size--;
    }
}

void bi_tree_rem_right(struct bi_tree *tree, struct bi_tree_node *node) {
    struct bi_tree_node **position;
    if (BI_TREE_SIZE(tree) == 0) {
        return;
    }

    if (node == NULL) {
        position = &tree->root;
    } else {
        position = &node->right;
    }

    if (*position != NULL) {
        bi_tree_rem_left(tree, *position);
        bi_tree_rem_right(tree, *position);

        if (tree->destroy != NULL) {
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;
        tree->size--;
    }
}

u_int8_t bi_tree_merge(struct bi_tree *merge, struct bi_tree *left, struct bi_tree *right, const void *data) {
    bi_tree_init(merge, left->destroy);

    if (bi_tree_ins_left(merge, NULL, data) != 0) {
        bi_tree_destroy(merge);
        return -1;
    }

    BI_TREE_ROOT(merge)->left = BI_TREE_ROOT(left);
    BI_TREE_ROOT(merge)->right = BI_TREE_ROOT(right);
    merge->size = merge->size + BI_TREE_SIZE(left) + BI_TREE_SIZE(right);
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;
    return 0;
}