//
// Created by tairy on 2020/11/21.
//

#ifndef TJVMTEST_BI_TREE_H
#define TJVMTEST_BI_TREE_H

#include "stdlib.h"

#define BI_TREE_SIZE(tree) ((tree)->size)
#define BI_TREE_ROOT(tree) ((tree)->root)
#define BI_TREE_IS_EOB(node) ((node) == NULL)
#define BI_TREE_IS_LEAF(node) ((node)->left == NULL && (node)->right == NULL)
#define BI_TREE_DATA(node) ((node)->data)
#define BI_TREE_LEFT(node) ((node)->left)
#define BI_TREE_RIGHT(node) ((node)->right)

struct bi_tree_node {
    void *data;
    struct bi_tree_node *left;
    struct bi_tree_node *right;
};

struct bi_tree {

    u_int32_t size;

    u_int8_t (*compare)(const void *key1, const void *key2);

    void (*destroy)(void *data);

    struct bi_tree_node *root;
};


/**
 * bi_tree_init
 * O(1)
 * @param tree
 * @param destroy
 */
void bi_tree_init(struct bi_tree *tree, void (*destroy)(void *data));

/**
 * bi_tree_destroy
 * O(n)
 * @param tree
 */
void bi_tree_destroy(struct bi_tree *tree);

/**
 * bi_tree_ins_left
 * O(1)
 * @param tree
 * @param node
 * @param data
 * @return
 */
u_int8_t bi_tree_ins_left(struct bi_tree *tree, struct bi_tree_node *node, const void *data);

/**
 * bi_tree_ins_right
 * O(1)
 * @param tree
 * @param node
 * @param data
 * @return
 */
u_int8_t bi_tree_ins_right(struct bi_tree *tree, struct bi_tree_node *node, const void *data);

/**
 * bi_tree_rem_left
 * O(n)
 * @param tree
 * @param node
 */
void bi_tree_rem_left(struct bi_tree *tree, struct bi_tree_node *node);

/**
 * bi_tree_rem_right
 * O(n)
 * @param tree
 * @param node
 */
void bi_tree_rem_right(struct bi_tree *tree, struct bi_tree_node *node);

/**
 * bi_tree_merge
 * O(1)
 * @param merge
 * @param left
 * @param right
 * @param data
 * @return
 */
u_int8_t bi_tree_merge(struct bi_tree *merge, struct bi_tree *left, struct bi_tree *right, const void *data);

#endif //TJVMTEST_BI_TREE_H
