//
// Created by tairy on 2020/11/22.
//

#ifndef TJVMTEST_BIS_TREE_H
#define TJVMTEST_BIS_TREE_H

#include "stdlib.h"
#include "bi_tree.h"

// 节点平衡因子
#define AVL_LEFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RIGHT_HEAVY -1
#define BIS_TREE_SIZE(tree) ((tree)->size)

struct avl_node {
    void *data;
    int8_t hidden; // 标识该节点已经移除
    int8_t factor; // 平衡因子
};

// public interface
void bis_tree_init(struct bi_tree *tree, int8_t(*compare)(const void *key1, const void *key2),
                   void (*destroy)(void *data));

void bis_tree_destroy(struct bi_tree *tree);

int8_t bis_tree_insert(struct bi_tree *tree, const void *data);

int8_t bis_tree_remove(struct bi_tree *tree, const void *data);

int8_t bis_tree_lookup(struct bi_tree *tree, void **data);


#endif //TJVMTEST_BIS_TREE_H
