//
// Created by tairy on 2020/11/20.
//
#include "stdio.h"
#include "util/hash_map.h"
#include "util/bi_tree.h"
#include "util/list.h"
#include "util/util.h"
#include "util/stack.h"

void test_has_map();

void test_bi_tree();

void test_list();

void test_stack();

void test_expression();

int main() {
    test_has_map();
    test_list();
    test_stack();
    test_expression();
    test_bi_tree();
    return 0;
}

void test_has_map() {
    struct hash_map *hash_map = create_hash_map(NULL, NULL);
    default_put_func(hash_map, "key", "value");
    default_put_func(hash_map, "key1", "value1");
    default_put_func(hash_map, "key2", "value2");
    default_put_func(hash_map, "key3", "value3");
    default_put_func(hash_map, "key4", "value4");
    default_put_func(hash_map, "key5", "value5");
    default_put_func(hash_map, "key6", "value6");
    default_put_func(hash_map, "key7", "value7");
    default_put_func(hash_map, "key8", "value8");
    default_put_func(hash_map, "key9", "value9");
    default_remove_func(hash_map, "key3");

    struct hash_map_iterator *iterator = create_hash_map_iterator(hash_map);

    for (int index = 0; has_next_hash_map_iterator(iterator) != 0; index++) {
        iterator = next_hash_map_iterator(iterator);
        printf("key:%s, value:%s, hash_code: %d\n", iterator->entry->key, iterator->entry->value,
               default_hash_func(hash_map, iterator->entry->key));
    }

    printf("result: %s, size: %d, list_size: %d\n", default_get_func(hash_map, "key"), hash_map->size,
           hash_map->list_size);

    free_hash_map_iterator(&iterator);
}

void test_list() {
    struct list *list = NEW(struct list);
    list_init(list, NULL);
    list_ins_next(list, NULL, 123);
    list_ins_next(list, list->head, 111);

    for (struct list_element *e = list->head; e != NULL; e = e->next) {
        printf("list_data: %d\n", e->data);
    }

    printf("list_tail_data: %d\n", list->tail->data);
    list_destroy(list);
}

void test_stack() {
    struct list *stack = NEW(struct list);
    STACK_INIT(stack, NULL);
    stack_push(stack, 123);
    stack_push(stack, 124);
    stack_push(stack, 125);
    stack_push(stack, 126);

    int len = stack->size;

    void *data;
    for (int i = 0; i < len; i++) {
        stack_pop(stack, &data);
        printf("i: %d, stack_pop: %d\n", i, data);
    }
    STACK_DESTROY(stack);
}

void test_bi_tree() {
    struct bi_tree *bi_tree = NEW(struct bi_tree);
    bi_tree_init(bi_tree, NULL);
}

void expression_translate(stack *stack, char *a, char *b) {
    char ch = NULL;
    char *element = NULL;
    int i = 0, j = 0;
    ch = a[i++];
    while (ch != '\0') {
        switch (ch) {
            case '(':
                // 左括号出现，右括号不出现，所有符号入栈
                stack_push(stack, ch);
                break;
            case ')':
                // 右括号出现，括号里面所有符号出栈
                while (stack->head->data != '(') {
                    stack_pop(stack, &element);
                    b[j++] = element;
                }
                stack_pop(stack, &element);
                break;
            case '+':
            case '-':
                // 加减优先级最低压入栈底
                while (stack->head->data != '(') {
                    stack_pop(stack, &element);
                    b[j++] = element;
                }
                stack_push(stack, ch);
                break;
            case '*':
            case '/':
                // 乘除优先级比加减高，遇到加减出栈，其他情况元素出栈再入栈
                while (stack->head->data == '/' || stack->head->data == '*' || stack->head->data == '^') {
                    stack_pop(stack, &element);
                    b[j++] = element;
                }
                stack_push(stack, ch);
                break;
            case '^':
                while (stack->head->data == '^') {
                    stack_pop(stack, &element);
                    b[j++] = element;
                }
                stack_push(stack, ch);
                break;
            case ' ':
                break;
            default:
                while (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9') {
                    b[j++] = ch;
                    ch = a[i++];
                }
                b[j++] = ' ';
                i--;
        }
        ch = a[i++];
    }

    while (stack->size > 0) {
        stack_pop(stack, &element);
        b[j++] = element;
    }

    b[j] = '\0';
}

struct bi_tree *build_bi_tree(stack *stack, char *b) {
    int i = 0;
    struct bi_tree *bi_tree = NEW(struct bi_tree);
    struct bi_tree_node *bi_tree_node, *root;
    // todo destroy function.
    bi_tree_init(bi_tree, NULL);
    while (b[i] != '\0') {
        printf("%c", b[i]);

        if (b[i] == '+' || b[i] == '-' || b[i] == '*' || b[i] == '/' || b[i] == '^') {
            bi_tree_node = NEW(struct bi_tree_node);
            bi_tree_node->data = b[i];
            stack_pop(stack, &bi_tree_node->right);
            stack_pop(stack, &bi_tree_node->left);
            stack_push(stack, bi_tree_node);
            bi_tree->size++;
        } else {
            bi_tree_node = NEW(struct bi_tree_node);
            char tmp[4] = {0};
            int j = 0;
            while (b[i] != ' ') {
                tmp[j++] = b[i];
                i++;
            }
            tmp[j] = '\0';
            bi_tree_node->data = tmp;
            bi_tree_node->left = NULL;
            bi_tree_node->right = NULL;
            stack_push(stack, bi_tree_node);
            bi_tree->size++;
        }
        i++;
    }

    stack_pop(stack, &root);
    bi_tree->root = root;
    return bi_tree;
}

void test_expression() {
    struct list *stack = NEW(struct list);
    STACK_INIT(stack, NULL);
    char *a = "((74-10)/32*(23+17))\0";
    char b[100];
    expression_translate(stack, a, b);
    printf("a: %s, b: %s\n", a, b);
    STACK_DESTROY(stack);

    struct list *stack1 = NEW(struct list);
    STACK_INIT(stack1, NULL);
    struct bi_tree *bi_tree = build_bi_tree(stack1, b);
    STACK_DESTROY(stack1);
}

/**
 * 前序遍历二叉树
 *
 * @return
 */
u_int8_t pre_order_iter_bi_tree(const struct bi_tree_node *node, struct list *list) {

}