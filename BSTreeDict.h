#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"
#include "BSNode.h"

template <typename V>
class BSTreeDict: public Dict<V> {

	private:
		BSTree<TableEntry<V>>* tree;

        // ...

    	public:
		BSTreeDict(){
			tree = new BSTree<TableEntry<V>>();
		}
		~BSTreeDict(){
			delete tree;
		}
		friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
			out<< *(bs.tree) <<" ";
			
			return out;
		}
		V operator[](std::string key){
			search(key);
		}
		void insert(std::string key, V value)override{
			tree->insert(TableEntry<V>(key,value));
		}
                V search(std::string key)override{
			TableEntry<V> n = tree->search(TableEntry<V>(key));
			return n.value;
		}
                V remove(std::string key)override{
			 TableEntry<V>entry(key);
			 TableEntry<V> result = tree->search(key);
			 tree->remove(entry);
			 return result.value;
		}
                int entries()override{
			return tree->size();
		}


        // ...
        
};

#endif
