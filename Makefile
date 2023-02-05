CC = g++
FLAGS = -std=c++11 -lpthread
COMP_OBJ = $(CC) $(FLAGS)  $^
main: task_queue.o thread_pool.o main.cc
	$(COMP_OBJ)
	
task_queue.o: task_queue.cc 
	$(COMP_OBJ)

thread_pool.o: thread_pool.cc
	$(COMP_OBJ)


clean:
	rm main
	rm *.o