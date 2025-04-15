CC=g++ -std=c++11
exe_file=task 

$(exe_file): test_linked_list.o 
	$(CC) test_linked_list.o -o $(exe_file) 

test_linked_list.o: test_linked_list.cpp linked_list.h node.h
	$(CC) -c test_linked_list.cpp

clean: 
	rm -f *.o $(exe_file)


.PHONY: clean