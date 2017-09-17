INCLUDE=-I ./ -I ../utils/ -I ../common/ -I../utils/bstr
intertask_interface.o: intertask_interface.c backtrace.c memory_pools.c  signals.c timer.c ../utils/dynamic_memory_check.c
	gcc -c intertask_interface.c backtrace.c memory_pools.c  signals.c timer.c ../utils/dynamic_memory_check.c $(INCLUDE) -w
clean:
	rm timer.o signals.o memory_pools.o backtrace.o intertask_interface.o dynamic_memory_check.o
