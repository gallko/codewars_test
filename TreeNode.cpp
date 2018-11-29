//
// Created by rus on 29.11.18.
//

#include "TreeNode.h"

TreeNode::TreeNode(int value)
        : m_value(value), m_left(nullptr), m_right(nullptr), m_parent(nullptr) {

}

TreeNode::TreeNode(int value, TreeNode *left, TreeNode *right)
        : m_value(value), m_left(left), m_right(right) {
    left->m_parent = this;
    right->m_parent = this;
}

bool TreeNode::operator==(const TreeNode &rhs) const {
    return this->m_value == rhs.m_value;
}

TreeNode *TreeNode::get_left() const {
    return m_left;
}

bool TreeNode::set_left(TreeNode *left) {
    if (TreeNode::m_left)
        return false;
    TreeNode::m_left = left;
    left->m_parent = this;
    return true;
}

TreeNode *TreeNode::get_right() const {
    return m_right;
}

bool TreeNode::set_right(TreeNode *right) {
    if (TreeNode::m_right)
        return false;
    TreeNode::m_right = right;
    right->m_parent = this;
    return true;
}

TreeNode::~TreeNode() {
    delete m_left;
    delete m_right;
}

TreeNode *TreeNode::get_parent() const {
    return m_parent;
}
