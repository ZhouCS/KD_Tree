#include "kdtreenode.h"
void KDTree::KDTreeNode::create(KDTreeNode *left_child,KDTreeNode *right_child,KDTreeNode *parent,
    int split_dim,_Examplar dom_elt,_HyperRectangle range_hr
)
{
    this->_left_child = left_child;
    this->_right_child = right_child;
    this->_parent = parent;
    this->_dom_elt = dom_elt;
    this->_range_hr = range_hr;
}

KDTree::KDTreeNode::KDTreeNode(const KDTreeNode& rhs)
{
    this->_left_child  = rhs._left_child;
    this->_right_child = rhs._right_child;
    this->_parent = rhs._parent;
    this->_dom_elt  = rhs._dom_elt;
    this->_range_hr  = rhs._range_hr;
}

KDTree::KDTreeNode& KDTree::KDTreeNode::operator =(const KDTreeNode &rhs)
{
    if (this == &rhs) {
        return *this;
    }
    this->_left_child  = rhs._left_child;
    this->_right_child = rhs._right_child;
    this->_parent = rhs._parent;
    this->_dom_elt  = rhs._dom_elt;
    this->_range_hr  = rhs._range_hr;
    return *this;
}
