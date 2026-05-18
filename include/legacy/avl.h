//
// Created by Chenluo Deng on 5/18/26.
//

#ifndef MY_STL_AVL_H
#define MY_STL_AVL_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace DS {
class AVL {
private:
	struct TreeNode {
		int value{};
		int dep{1};
		TreeNode *left = nullptr;
		TreeNode *right = nullptr;
		TreeNode *parent = nullptr;
	};

	TreeNode *root;
	void mtv(TreeNode *rt, void (*fn)(TreeNode*)) {
		if (rt==nullptr) {
			return;
		}
		if (rt->left != nullptr) mtv(rt->left, fn);
		fn(rt);
		if (rt->right != nullptr) mtv(rt->right, fn);
	}
	void btv(TreeNode *rt, void (*fn)(TreeNode*)) {
		if (rt==nullptr) {
			return;
		}
		if (rt->left != nullptr) btv(rt->left, fn);
		if (rt->right != nullptr) btv(rt->right, fn);
		fn(rt);
	}
	void ftv(TreeNode *rt, void (*fn)(TreeNode*)) {
		if (rt==nullptr) {
			return;
		}
		fn(rt);
		if (rt->left != nullptr) ftv(rt->left, fn);
		if (rt->right != nullptr) ftv(rt->right, fn);
	}
	static void prt(TreeNode *t) {
		std::cout << t->value << std::endl;
	}
	static void del(TreeNode *t) {
		delete t;
	}

	TreeNode* getNode(int value) {
		TreeNode* x = root;
		while (x!=nullptr) {
			if (x->value == value) {
				return x;
			}
			if (x->value < value) {
				x = x->right;
			} else {
				x = x->left;
			}
		}
		delete x;
		return nullptr;
	}

	TreeNode* findMin(TreeNode* node) {
		while (node && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	int height(TreeNode* t) {
		return t == nullptr ? 0 : t->dep;
	}

	void updateHeight(TreeNode* t) {
		if (t != nullptr) {
			t->dep = std::max(height(t->left), height(t->right)) + 1;
		}
	}

	TreeNode* rotateLeft(TreeNode* D) {
		TreeNode* B = D->right;
		TreeNode* C = B->left;

		D->right = C;
		B->left = D;

		if (C!=nullptr) C->parent = D;

		if (D->parent!=nullptr) {
			if (D->parent->left == D) {
				D->parent->left = B;
			} else {
				D->parent->right = B;
			}
		} else {
			// Remember to update the root when D was the root
			root = B;
		}
		B->parent = D->parent;
		D->parent = B;

		updateHeight(D);
		updateHeight(B);

		return B;
	}

	TreeNode* rotateRight(TreeNode* D) {
		TreeNode* B = D->left;
		TreeNode* C = B->right;

		D->left = C;
		B->right = D;

		if (C!=nullptr) C->parent = D;

		if (D->parent!=nullptr) {
			if (D->parent->left == D) {
				D->parent->left = B;
			} else {
				D->parent->right = B;
			}
		} else {
			root = B;
		}
		B->parent = D->parent;
		D->parent = B;

		// Always update heights
		updateHeight(D);
		updateHeight(B);

		return B;
	}

	// Return the new root for updating
	TreeNode* rebalanceFrom(TreeNode* t) {
		int lb = height(t->left);
		int rb = height(t->right);
		if (lb-rb <= 1 && lb-rb >= -1) {
			return t;
		}
		if (lb - rb > 1) {
			if (height(t->left->left) >= height(t->left->right)) {
				return rotateRight(t);
			} else {
				rotateLeft(t->left);
				return rotateRight(t);
			}
		} else {
			if (height(t->right->right) >= height(t->right->left)) {
				return rotateLeft(t);
			} else {
				rotateRight(t->right);
				return rotateLeft(t);
			}
		}
	}

	int balance(TreeNode* t) {
		return height(t->left) - height(t->right);
	}

	// While removing, the roots of subtrees might change, so we need to update these nodes recursively.
	TreeNode* removeNode(int value, TreeNode *t) {
		if (t==nullptr) {
			return nullptr;
		}

		if (value < t->value) {
			t->left = removeNode(value, t->left);
		} else if (value > t->value) {
			t->right = removeNode(value, t->right);
		} else {
			if (t->left == nullptr) {
				TreeNode* tmp = t->right;
				if (tmp) tmp->parent = t->parent;
				delete t;
				return tmp;
			}
			if (t->right == nullptr) {
				TreeNode* tmp = t->left;
				if (tmp) tmp->parent = t->parent;
				delete t;
				return tmp;
			}

			// Find the smallest element in the right sub-tree, so that it can correctly be placed at the position of t.
			// Then we delete that element succ in the right sub-tree.
			TreeNode* succ = findMin(t->right);
			t->value = succ->value;
			t->right = removeNode(succ->value, t->right);
		}

		updateHeight(t);
		return rebalanceFrom(t);
	}

public:
	AVL() {
		root = nullptr;
	}

	~AVL() {
		btv(root, del);
	}

	void traverse() {
		mtv(root, prt);
	}

	void insert(int value) {
		auto *t = new TreeNode;
		t->value = value;
		t->dep = 1;
		t->right = nullptr;
		t->left = nullptr;
		TreeNode* x = root;
		TreeNode* y = nullptr;
		while (x!=nullptr) {
			y = x;
			if (t->value < x->value) {
				x = x->left;
			} else if (t->value > x->value) {
				x = x->right;
			} else {
				delete t;
				return;
			}
		}
		if (y==nullptr) {
			root = t;
		} else if (t->value < y->value) {
			y->left = t;
		} else {
			y->right = t;
		}
		t->parent = y;

		// Trace back to update heights and rebalance the tree
		while (t!=nullptr) {
			updateHeight(t);
			t = rebalanceFrom(t);
			t = t->parent;
		}
	}

	bool search(int value) const {
		TreeNode* x = root;
		while (x!=nullptr) {
			if (x->value == value) {
				return true;
			}
			if (x->value < value) {
				x = x->right;
			} else {
				x = x->left;
			}
		}
		delete x;
		return false;
	}

	void remove(int value) {
		root = removeNode(value, root);
	}

	int getMax() const {
		TreeNode* x = root;
		if (x==nullptr) {
			throw std::out_of_range("No such node");
		}
		while (x->right!=nullptr) {
			x = x->right;
		}
		return x->value;
	}

	int getMin() const {
		TreeNode* x = root;
		if (x==nullptr) {
			throw std::out_of_range("No such node");
		}
		while (x->left!=nullptr) {
			x = x->left;
		}
		return x->value;
	}
};}

#endif //MY_STL_AVL_H
