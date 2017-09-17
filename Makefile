OBJECTS= timer.o signals.o dynamic_memory_check.o ./bstr/bstrlib.o intertask_interface.o backtrace.o memory_pools.o
INCLUDE=-I ./ -I./inc/ -I ./utils/ -I ./common/ -I./utils/bstr 

demo : main.c $(OBJECTS)
	gcc -I ./inc  -o demo main.c timer.o signals.o dynamic_memory_check.o ./bstr/bstrlib.o intertask_interface.o backtrace.o memory_pools.o $(INCLUDE) -L ./lib -llfds611 -lpthread -lrt -w

timer.o: ./inc/timer.c
	gcc -c ./inc/timer.c $(INCLUDE) -w
signals.o: ./inc/signals.c
	gcc -c ./inc/signals.c $(INCLUDE) -w
dynamic_memory_check.o: ./utils/dynamic_memory_check.c
	gcc -c ./utils/dynamic_memory_check.c $(INCLUDE) -w
intertask_interface.o: ./inc/intertask_interface.c
	gcc -c ./inc/intertask_interface.c $(INCLUDE) -w
backtrace.o: ./inc/backtrace.c 
	gcc -c ./inc/backtrace.c -w $(INCLUDE)
memory_pools.o: ./inc/memory_pools.c
	gcc -c ./inc/memory_pools.c $(INCLUDE) -w
bstrlib.o: ./bstr/bstrlib.c
	gcc -c ./bstr/bstrlib.c -I./bstr



clean:
	rm demo $(OBJECTS)
