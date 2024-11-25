#ifndef BSTREE_H
#define BSTREE_H
#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
	private:
    		BSNode<T>* root;
    		int nelem;

    		// Métodos privados recursivos
    		BSNode<T>* search(BSNode<T>* n, T e) const {
        		if (!n) 
				throw std::runtime_error("Elemento no encontrado.");
       			if (e < n->elem) 
				return search(n->left, e);
        		else if (e > n->elem) 
				return search(n->right, e);
        		else
            			return n;
    		}

    		BSNode<T>* insert(BSNode<T>* n, T e) {
        		if (!n)
           			return new BSNode<T>(e);
        		if (e < n->elem)
				n->left = insert(n->left, e);
        		else if (e > n->elem)
            			n->right = insert(n->right, e);
        		else
            			throw std::runtime_error("Elemento duplicado.");
        		return n;
    		}

    		BSNode<T>* remove(BSNode<T>* n, T e) {
        		if (!n) 
				throw std::runtime_error("Elemento no encontrado.");
        		if (e < n->elem) 
				n->left = remove(n->left, e);
        		else if (e > n->elem) n->right = remove(n->right, e);
        		else {	
            			if (n->left && n->right) {
                			n->elem = max(n->left);
               				n->left = remove_max(n->left);
            			}else {
                			BSNode<T>* temp = n;
                			if (n->left)
						n = n->left;
					else
						n = n->right;

                			delete temp;
            			}
	   
	
        		}
        		return n;
    		}

    		T max(BSNode<T>* n) const {
        		if (!n) throw std::runtime_error("Árbol vacío.");
        		while (n->right){
            			n = n->right;
			}
        		return n->elem;
    		}

    		BSNode<T>* remove_max(BSNode<T>* n) {
        		if (!n->right){
            			return n->left;
			}
        		n->right = remove_max(n->right);
        		return n;
    		}

    		void print_inorder(std::ostream& out, BSNode<T>* n) const {
        		if (!n) return;
        			print_inorder(out, n->left);
        			out << n->elem << " ";
        			print_inorder(out, n->right);
    		}

   		 void delete_cascade(BSNode<T>* n) {
        		if (!n) return;
        			delete_cascade(n->left);
        			delete_cascade(n->right);
        			delete n;
    		}

	public:
    		
    		BSTree() : root(nullptr), nelem(0) {}
    		~BSTree() { delete_cascade(root); }

    		
    		int size() const { return nelem; }

    		T search(T e) const {
        		BSNode<T>* result = search(root, e);
        		return result->elem;
    		}

    		void insert(T e) {
        		root = insert(root, e);
        		++nelem;
    		}

    		void remove(T e) {
        		root = remove(root, e);
        		--nelem;
    		}

    		T operator[](T e) const {
        		return search(e);
    		}

    		friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        		bst.print_inorder(out, bst.root);
        		return out;
    		}
};
#endif

