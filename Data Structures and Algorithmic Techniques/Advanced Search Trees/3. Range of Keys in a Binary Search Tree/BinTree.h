//
//  BinTree.h
//
//  Implementation of binary trees (with node sharing)
//
//  Algorithmic Techniques in Software Engineering / Algorithm Design
//  Faculty of Computer Science
//  Complutense University of Madrid
//
//  Created by Alberto Verdejo on 30/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef BINTREE_H_
#define BINTREE_H_

#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>

template <typename T>
class BinTree {
public:
	BinTree() : root_(nullptr) {}
	BinTree(T const& e);
	BinTree(BinTree<T> const& l, T const& e, BinTree<T> const& r);
	BinTree(BinTree<T> const& other) : root_(other.root_) {}

	bool empty() const { return root_ == nullptr; }
	T const& root() const;
	BinTree left() const;
	BinTree right() const;

private:
	struct TreeNode;
	using Link = std::shared_ptr<TreeNode>;
	BinTree(Link const& r);
	Link root_;

public:
	// iterator that traverses the tree in inorder
	class Iterator {
	public:
		T const& operator*() const;

		bool operator==(Iterator const& other) const;
		bool operator!=(Iterator const& other) const;

		Iterator & operator++();
		Iterator operator++(int);

	private:
		friend class BinTree;
		Link ptr_;
		std::stack<Link> ancestors;
		void next();
		Iterator() : ptr_(nullptr) {}
		Iterator(Link act) { ptr_ = first(act); }
		Link first(Link act);
	};

	Iterator begin() const {
		return Iterator(root_);
	}
	Iterator end() const {
		return Iterator(nullptr);
	}

};


template <typename T>
struct BinTree<T>::TreeNode {
	TreeNode(Link const& l, T const& e, Link const& r) : left_(l), elem_(e), right_(r) {};
	T elem_;
	Link left_, right_;
};


template <typename T>
BinTree<T>::BinTree(BinTree<T> const& l, T const& e, BinTree<T> const& r) :
   root_(std::make_shared<TreeNode>(l.root_, e, r.root_)) {}

template <typename T>
BinTree<T>::BinTree(T const& e) :
    root_(std::make_shared<TreeNode>(nullptr, e, nullptr)) {}

template <typename T>
BinTree<T>::BinTree(Link const& r) : root_(r) {}

template <typename T>
T const& BinTree<T>::root() const {
	if (empty()) throw std::domain_error("An empty tree has no root.");
	else return root_->elem_;
}

template <typename T>
BinTree<T> BinTree<T>::left() const {
	if (empty()) throw std::domain_error("An empty tree has no left child.");
	else return BinTree<T>(root_->left_);
}

template <typename T>
BinTree<T> BinTree<T>::right() const {
	if (empty()) throw std::domain_error("An empty tree has no right child.");
	else return BinTree(root_->right_);
}

template <typename T>
T const& BinTree<T>::Iterator::operator*() const { return ptr_->elem_; }

template <typename T>
bool BinTree<T>::Iterator::operator==(Iterator const& other) const {
	return ptr_ == other.ptr_;
}

template <typename T>
bool BinTree<T>::Iterator::operator!=(Iterator const& other) const {
	return !(this->operator==(other));
}

template <typename T>
typename BinTree<T>::Iterator & BinTree<T>::Iterator::operator++() {
	next();
	return *this;
}

template <typename T>
typename BinTree<T>::Iterator BinTree<T>::Iterator::operator++(int) {
	Iterator ret(*this);
	operator++();
	return ret;
}

template <typename T>
void BinTree<T>::Iterator::next() {
	if (ptr_ == nullptr) {
		throw std::range_error("The iterator cannot advance");
	}
	else {
		if (ptr_->right_ != nullptr) {
			ptr_ = first(ptr_->right_);
		}
		else {
			if (ancestors.empty()) {
				ptr_ = nullptr;
			}
			else {
				ptr_ = ancestors.top();
				ancestors.pop();
			}
		}
	}
}

template <typename T>
typename BinTree<T>::Link BinTree<T>::Iterator::first(Link act) {
	if (act == nullptr) {
		return nullptr;
	}
	else {
		while (act->left_ != nullptr) {
			ancestors.push(act);
			act = act->left_;
		}
		return act;
	}
}


#endif /* BINTREE_H_ */
