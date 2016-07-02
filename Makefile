cc = gcc
cc_args = -lpthread -lm

src = ./headers/14041_counter1_nonsafe.h
src += ./headers/14041_counter2_safe.h
src += ./headers/14041_Pthread.h
src += ./src/14041_stp.c
src += ./src/14041_mtp_c1.c
src += ./src/14041_mtp_c2.c
src += ./src/14041_mtp_c1_sem.c
src += ./src/14041_repeater.c

obj = ./exec/14041_stp.out
obj += ./exec/14041_mtp_c1.out
obj += ./exec/14041_mtp_c2.out
obj += ./exec/14041_mtp_c1_sem.out
obj += ./exec/14041_repeater.out

run_all: run1 run2 run3 run4

run1: $(obj)
	./exec/14041_repeater.out 1 50 14041_stp.txt

run2: $(obj)
	./exec/14041_repeater.out 2 50 14041_mtp_c1.txt

run3: $(obj)
	./exec/14041_repeater.out 3 50 14041_mtp_c2.txt

run4: $(obj)
	./exec/14041_repeater.out 4 50 14041_mtp_c1_sem.txt

$(obj): $(src)
	make compile

$(src):
	make compile

compile:
	$(cc) -o ./exec/14041_stp.out ./src/14041_stp.c $(cc_args)
	$(cc) -o ./exec/14041_mtp_c1.out ./src/14041_mtp_c1.c $(cc_args)
	$(cc) -o ./exec/14041_mtp_c2.out ./src/14041_mtp_c2.c $(cc_args)
	$(cc) -o ./exec/14041_mtp_c1_sem.out ./src/14041_mtp_c1_sem.c $(cc_args)
	$(cc) -o ./exec/14041_repeater.out ./src/14041_repeater.c $(cc_args)

## clean_all will erase all data collected by executing the Programs.. 
## Only execute if you know what you are doing

clean_all: clean
	rm -rf ./Statistics/*.txt

clean:
	rm -rf ./exec/*.out
