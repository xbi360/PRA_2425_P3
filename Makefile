bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

clean:
	rm -rf *.o *.gch bin

bin/testHashTable: testHashTable.cpp TableEntry.h HashTable.h Dict.h
	mkdir -p bin
	g++ -o bin/testHashTable testTableEntry.cpp

clean:
	rm -rf *.o *.gch bin
