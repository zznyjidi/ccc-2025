#include <iostream>
using namespace std;

struct color_change {
    int type;
    int index;
    int value;

    color_change() {};

    color_change(int type, int index, int value) {
        this->type = type;
        this->index = index;
        this->value = value;
    }
};

struct pen {
    int color;
    int pretty;

    pen() {};

    pen(int color, int pretty) {
        this->color = color;
        this->pretty = pretty;
    }

    void apply_change(color_change change) {
        if (change.type == 1) {
            this->color = change.value;
        } else {
            this->pretty = change.value;
        }
    }
};

struct bst_node {
    int value;
    bst_node *left;
    bst_node *right;

    bst_node() {
        value = 0;
        left = NULL;
        right = NULL;
    }

    bst_node(int value) {
        this->value = value;
        left = NULL;
        right = NULL;
    }
};

bst_node* add_to_bst(bst_node *master_node, int value) {
    if (!master_node->value) {
        master_node->value = value;
    } else if (master_node->value < value) {
        if (master_node->right) {
            return add_to_bst(master_node->right, value);
        } else {
            master_node->right = new bst_node(value);
            return master_node;
        }
    } else if (master_node->value > value) {
        if (master_node->left) {
            return add_to_bst(master_node->left, value);
        } else {
            master_node->left = new bst_node(value);
            return master_node;
        }
    }
    return master_node;
}

bst_node* bst_max(bst_node* master_node) {
    if (master_node->right) {
        return bst_max(master_node->right);
    } else {
        return master_node;
    }
}

bst_node* bst_min(bst_node* master_node) {
    if (master_node->left) {
        return bst_max(master_node->left);
    } else {
        return master_node;
    }
}

int main() {
    // Read Input
    int pen_count, color_count, change_count;
    cin >> pen_count >> color_count >> change_count;

    pen pen_list[pen_count];
    for (int i = 0; i < pen_count; i++) {
        int pen_color, pen_pretty;
        cin >> pen_color >> pen_pretty;
        pen_list[i] = pen(pen_color - 1, pen_pretty);
    }

    color_change change_list[change_count];
    for (int i = 0; i < change_count; i++) {
        int change_type, change_index, change_value;
        cin >> change_type >> change_index >> change_value;
        change_list[i] = color_change(change_type, change_index - 1, change_value);
    }

    // Process Each Changes
    for (int change_index = 0; change_index <= change_count; change_index++) {
        // Apply Change
        if (change_index != 0) {
            color_change change = change_list[change_index - 1];
            pen_list[change.index].apply_change(change);
        }

        // Init color_max Array
        int color_max[color_count];
        for (int i = 0; i < color_count; i++) {
            color_max[i] = 0;
        }

        // Get max value for each color & create Binary Search Tree for unused Pens
        bst_node* color_unused_root = new bst_node();
        for (int i = 0; i < pen_count; i++) {
            pen current_pen = pen_list[i];
            if (current_pen.pretty > color_max[current_pen.color]) {
                if (color_max[current_pen.color]) {
                    add_to_bst(color_unused_root, color_max[current_pen.color]);
                }
                color_max[current_pen.color] = current_pen.pretty;
            } else {
                add_to_bst(color_unused_root, current_pen.pretty);
            }
        }

        // Iterate through color to find smallest pretty used
        int color_min_used = __INT_MAX__;
        int color_min_used_index = 0;
        for (int i = 0; i < color_count; i++) {
            int current_color = color_max[i];
            if (color_min_used > current_color) {
                color_min_used = current_color;
                color_min_used_index = i;
            }
        }
        
        // Apply Color Swap if needed
        int color_max_unused = bst_max(color_unused_root)->value;
        if (color_max_unused > color_min_used) {
            color_max[color_min_used_index] = color_max_unused;
        }

        // Calculate Sum
        int sum = 0;
        for (int i = 0; i < color_count; i++) {
            sum += color_max[i];
        }
        cout << sum << endl;
    }
}
