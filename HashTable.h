#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../../P1/PRA_2425_P1/Node.h" 

#include "../../P1/PRA_2425_P1/ListLinked.h"  

template <typename V>
class HashTable: public Dict<V> {

	private:
		int n;
		int max;
		ListLinked<TableEntry<V>>* table;
		
		//función has -> obtener posición de la cubeta
		int h(std::string key){
			int sum=0;
			for(char c:key){
				sum += static_cast<int>(c);
				
			}
			return sum%max;
		}



        // ...
	public:
		//constructor tabla hash
		HashTable(int size):n(0),max(size){
			table=new ListLinked<TableEntry<V>>[max];
		};

		//Destructor 
		~HashTable(){
			delete [] table;
		}

		int capacity(){
			return max;
		}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			for (int i=0;i<th.max;i++){
				out<<"Cubeta"<<i<<": ";
				if(!th.table[i].empty()){
					out<<th.table[i];
				}else{
					out<<"vacía";
				}
				out<<std::endl;
			}
			return out;
		}		

		V operator[](std::string key) {
        		int index = h(key); //obtener el índice
			auto *nodo=table[index].get_first();
       		 	while(nodo!=nullptr){
				if(nodo->data.key==key) return nodo->data.value;
				nodo=nodo->next;
        		}
        	throw std::runtime_error("Clave no encontrada.");
    		}

		  // Implementación del método insert de Dict
    		void insert(std::string key, V value) override {
        		int index = h(key);
      			auto *nodo=table[index].get_first();
			while(nodo!=nullptr){
				if(nodo->data.key==key){
					nodo->data.value = value; //si la key ya existe, se actualiza
				
				}
				nodo=nodo->next;
			
    			}
			//inserta al frente de la lista.
			table[index].prepend(TableEntry<V>(key, value));
			n++;

		}

    		V search(std::string key) override {
        		int index = h(key);
        		auto *current = table[index].get_first();
			
			while(current !=nullptr){
				if(current->data.key==key){
					return current->data.value;
				}
				current=current->next;
			
    			}
			throw std::runtime_error("Clave no encuentrada.");
		}


    		V remove(std::string key) override {
        		int index = h(key);
			auto *current=table[index].get_first();
			Node <TableEntry<V>>*prev=nullptr;
			while(current !=nullptr){
				if(current->data.key==key){
					V value=current->data.value;
				if(prev==nullptr){
					table[index].remove_first();
				}else{
					prev->next=current->next;
					delete current;
				}
				n--;
				return value;
				}
			prev=current;
			current=current->next;
			}

        		throw std::runtime_error("Clave no encontrada.");
    		}	

    		// Devuelve el número de elementos almacenados
    		int entries() override {
        		return n;
    		}
        
};

#endif
