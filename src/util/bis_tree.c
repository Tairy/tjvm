//
// Created by tairy on 2020/11/22.
//

#include "bis_tree.h"
#include "string.h"

static void destroy_right(struct bi_tree *tree, struct bi_tree_node *node);

static void rotate_left(struct bi_tree_node **node) {
    struct bi_tree_node *left, *grand_child;

    left = BI_TREE_LEFT(*node);

    if (((struct avl_node *) BI_TREE_RIGHT(left))->factor == AVL_LEFT_HEAVY) {
        BI_TREE_LEFT(*node) = BI_TREE_RIGHT(left);
        BI_TREE_RIGHT(*node) = *node;
        ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_BALANCED;
        ((struct avl_node *) BI_TREE_DATA(left))->factor = AVL_BALANCED;
        *node = left;
    } else {
        grand_child = BI_TREE_RIGHT(left);
        BI_TREE_RIGHT(left) = BI_TREE_LEFT(grand_child);
        BI_TREE_LEFT(grand_child) = left;
        BI_TREE_LEFT(*node) = BI_TREE_RIGHT(grand_child);
        BI_TREE_RIGHT(grand_child) = *node;

        switch (((struct avl_node *) BI_TREE_DATA(grand_child))->factor) {
            case AVL_LEFT_HEAVY:
                ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_RIGHT_HEAVY;
                ((struct avl_node *) BI_TREE_DATA(left))->factor = AVL_BALANCED;
                break;
            case AVL_BALANCED:
                ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_BALANCED;
                ((struct avl_node *) BI_TREE_DATA(left))->factor = AVL_BALANCED;
                break;
            case AVL_RIGHT_HEAVY:
                ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_BALANCED;
                ((struct avl_node *) BI_TREE_DATA(left))->factor = AVL_LEFT_HEAVY;
                break;
        }

        ((struct avl_node *) BI_TREE_DATA(grand_child))->factor = AVL_BALANCED;
        *node = grand_child;
    }
}

static void rotate_right(struct bi_tree_node **node) {
    struct bi_tree_node *right, *grand_child;

    right = BI_TREE_LEFT(*node);

    if (((struct avl_node *) BI_TREE_DATA(right))->factor == AVL_RIGHT_HEAVY) {
        BI_TREE_RIGHT(*node) = BI_TREE_LEFT(right);
        BI_TREE_LEFT(right) = *node;
        ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_BALANCED;
        ((struct avl_node *) BI_TREE_DATA(right))->factor = AVL_BALANCED;
    } else {
        grand_child = BI_TREE_LEFT(right);
        BI_TREE_LEFT(right) = BI_TREE_RIGHT(grand_child);
        BI_TREE_RIGHT(grand_child) = right;
        BI_TREE_RIGHT(*node) = BI_TREE_LEFT(grand_child);
        BI_TREE_LEFT(grand_child) = *node;

        switch (((struct avl_node *) BI_TREE_DATA(grand_child))->factor) {
            case AVL_LEFT_HEAVY:
                ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_BALANCED;
                ((struct avl_node *) BI_TREE_DATA(right))->factor = AVL_RIGHT_HEAVY;
                break;
            case AVL_BALANCED:
                ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_BALANCED;
                ((struct avl_node *) BI_TREE_DATA(right))->factor = AVL_BALANCED;
                break;
            case AVL_RIGHT_HEAVY:
                ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_LEFT_HEAVY;
                ((struct avl_node *) BI_TREE_DATA(right))->factor = AVL_BALANCED;
        }

        ((struct avl_node *) BI_TREE_DATA(grand_child))->factor = AVL_BALANCED;
        *node = grand_child;
    }
}

static void destroy_left(struct bi_tree *tree, struct bi_tree_node *node) {
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
        destroy_left(tree, *position);
        destroy_right(tree, *position);

        if (tree->destroy != NULL) {
            tree->destroy(((struct avl_node *) (*position)->data)->data);
        }

        free((*position)->data);
        free(*position);
        *position = NULL;

        tree->size--;
    }
}

static void destroy_right(struct bi_tree *tree, struct bi_tree_node *node) {
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
        destroy_left(tree, *position);
        destroy_right(tree, *position);

        if (tree->destroy != NULL) {
            tree->destroy(((struct avl_node *) (*position)->data)->data);
        }

        free((*position)->data);
        free(*position);
        *position = NULL;

        tree->size--;
    }
}

/**
 * 插入节点，插入节点后，更新节点的平衡因子。
 * 如果任何一个节点的平衡因子变成 ±2，就必须从这个节点往下重新平衡这棵树，这个重新平衡的过程中称为旋转。
 *
 * @param tree 树
 * @param node
 * @param data 待插入的节点
 * @param balanced 是否平衡
 * @return
 */
static u_int8_t insert(struct bi_tree *tree, struct bi_tree_node **node, const void *data, u_int8_t *balanced) {
    struct avl_node *avl_node;
    u_int8_t cmpval, retval;

    // 是否为节点
    if (BI_TREE_IS_EOB(*node)) {
        if ((avl_node = (struct avl_node *) malloc(sizeof(struct avl_node))) == NULL) {
            return -1;
        }

        avl_node->factor = AVL_BALANCED;
        avl_node->hidden = 0;
        avl_node->data = (void *) data;

        return bi_tree_ins_left(tree, *node, avl_node);
    } else {
        cmpval = tree->compare(data, ((struct avl_node *) BI_TREE_DATA(*node))->data);
        if (cmpval < 0) {
            if (BI_TREE_IS_EOB(BI_TREE_LEFT(*node))) {
                if ((avl_node = (struct avl_node *) malloc(sizeof(struct avl_node))) == NULL) {
                    return -1;
                }

                avl_node->factor = AVL_BALANCED;
                avl_node->hidden = 0;
                avl_node->data = (void *) data;

                if (bi_tree_ins_left(tree, *node, avl_node) != 0) {
                    return -1;
                }

                *balanced = 0;
            } else {
                if ((retval = insert(tree, &BI_TREE_LEFT(*node), data, balanced)) != 0) {
                    return retval;
                }
            }

            // 保持平衡
            if (!(*balanced)) {
                switch (((struct avl_node *) BI_TREE_DATA(*node))->factor) {
                    case AVL_LEFT_HEAVY:
                        rotate_left(node);
                        *balanced = 1;
                        break;
                    case AVL_BALANCED:
                        ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_LEFT_HEAVY;
                        break;
                    case AVL_RIGHT_HEAVY:
                        ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;
                }
            }
        } else if (cmpval > 0) {
            if (BI_TREE_IS_EOB(BI_TREE_RIGHT(*node))) {
                if ((avl_node = (struct avl_node *) malloc(sizeof(struct avl_node))) == NULL) {
                    return -1;
                }

                avl_node->factor = AVL_BALANCED;
                avl_node->hidden = 0;
                avl_node->data = (void *) data;

                if (bi_tree_ins_right(tree, *node, avl_node) != 0) {
                    return -1;
                }

                *balanced = 0;
            } else {
                if ((retval = insert(tree, &BI_TREE_RIGHT(*node), data, balanced)) != 0) {
                    return retval;
                }
            }

            if (!(*balanced)) {
                switch (((struct avl_node *) BI_TREE_DATA(*node))->factor) {
                    case AVL_LEFT_HEAVY:
                        ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                    case AVL_BALANCED:
                        ((struct avl_node *) BI_TREE_DATA(*node))->factor = AVL_RIGHT_HEAVY;
                        break;
                    case AVL_RIGHT_HEAVY:
                        rotate_right(node);
                        *balanced = 1;
                        break;
                }
            }
        } else {
            if (!((struct avl_node *) BI_TREE_DATA(*node))->hidden) {
                return 1;
            } else {
                if (tree->destroy != NULL) {
                    tree->destroy(((struct avl_node *) BI_TREE_DATA(*node))->data);
                }

                ((struct avl_node *) BI_TREE_DATA(*node))->data = (void *) data;
                ((struct avl_node *) BI_TREE_DATA(*node))->hidden = 0;
                *balanced = 1;
            }
        }
    }

    return 0;
}

static u_int8_t hide(struct bi_tree *tree, struct bi_tree_node *node, const void *data) {
    u_int8_t cmpval, retval;

    if (BI_TREE_IS_EOB(node)) {
        return -1;
    }

    cmpval = tree->compare(data, ((struct avl_node *) BI_TREE_DATA(node))->data);
    if (cmpval < 0) {
        retval = hide(tree, BI_TREE_LEFT(node), data);
    } else {
        ((struct avl_node *) BI_TREE_DATA(node))->hidden = 1;
        retval = 0;
    }

    return retval;
}

static u_int8_t lookup(struct bi_tree *tree, struct bi_tree_node *node, void **data) {
    u_int8_t cmpval, retval;

    if (BI_TREE_IS_EOB(node)) {
        return -1;
    }

    cmpval = tree->compare(*data, ((struct avl_node *) BI_TREE_DATA(node))->data);
    if (cmpval < 0) {
        retval = lookup(tree, BI_TREE_LEFT(node), data);
    } else if (cmpval > 0) {
        retval = lookup(tree, BI_TREE_RIGHT(node), data);
    } else {
        if (!((struct avl_node *) BI_TREE_DATA(node))->hidden) {
            *data = ((struct avl_node *) BI_TREE_DATA(node))->data;
            retval = 0;
        } else {
            return -1;
        }
    }

    return retval;
}

void bis_tree_init(struct bi_tree *tree, u_int8_t(*compare)(const void *key1, const void *key2),
                   void (*destroy)(void *data)) {
    bi_tree_init(tree, destroy);
    tree->compare = compare;
}

void bis_tree_destroy(struct bi_tree *tree) {
    destroy_left(tree, NULL);
    memset(tree, 0, sizeof(struct bi_tree));
}

/**
 * @param tree 树
 * @param data 待插入的节点
 * @return 如果插入成功，返回 0, 如果插入的节点已经在树中存在，返回 1, 否则返回 -1
 */
u_int8_t bis_tree_insert(struct bi_tree *tree, const void *data) {
    u_int8_t balanced = 0;

}

/**
 * 该操作只执行一次惰性删除操作，即该节点只是简单的标记为隐藏。
 *
 * @param tree 树
 * @param data 待删除的节点
 * @return
 */
u_int8_t bis_tree_remove(struct bi_tree *tree, const void *data) {
    return hide(tree, BI_TREE_ROOT(tree), data);
}

u_int8_t bis_tree_lookup(struct bi_tree *tree, void **data) {
    return lookup(tree, BI_TREE_ROOT(tree), data);
}

