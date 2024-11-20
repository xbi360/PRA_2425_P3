#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../P1/PRA_2425_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

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
				int num=(char)c;
				sum+=num;
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
       		 	for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            			if (it->key == key) {
                			return it->value;
            			}
        		}
        	throw std::runtime_error("Clave no encontrada.");
    		}

		  // Implementación del método insert de Dict
    		void insert(std::string key, V value) override {
        		int index = h(key);
        		TableEntry<V> newEntry(key, value);

        	// Verificar si la clave ya existe
        		for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            			if (it->key == key) {
                		it->value = value; // Actualizar el valor si la clave ya existe
                		return;
            			}
        		}

        		table[index].prepend(newEntry);
        		++n;
    		}

    		V search(std::string key) override {
        		int index = h(key);
        		for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            			if (it->key == key) {
                			return it->value;
            			}
        		}
        		throw std::runtime_error("Clave no encontrada.");
    		}

    		V remove(std::string key) override {
        		int index = h(key);
       			for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            			if (it->key == key) {
               			V value = it->value;
               			table[index].erase(it);
                		--n;
                		return value;
            			}
        		}
        		throw std::runtime_error("Clave no encontrada.");
    		}	

    		// Devuelve el número de elementos almacenados
    		int entries() override {
        		return n;
    		}
        
};

#endif
