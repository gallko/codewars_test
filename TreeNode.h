//
// Created by rus on 29.11.18.
//

#ifndef PTHREADS_TREENODE_H
#define PTHREADS_TREENODE_H


class TreeNode {
private:
    int m_value;
    TreeNode *m_left, *m_right, *m_parent;

public:
    explicit TreeNode(int value);
    TreeNode(int value, TreeNode* left, TreeNode* right);
    virtual ~TreeNode();

    bool operator==(const TreeNode& rhs) const;

    bool set_right(TreeNode *right);
    bool set_left(TreeNode *left);
    TreeNode *get_left() const;
    TreeNode *get_right() const;
    TreeNode *get_parent() const;
};


#endif //PTHREADS_TREENODE_H
