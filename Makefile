mpi:
	mpic++ main.cpp -o main
	mpirun -np 8 ./main
run: gen
	./main
gen:
	g++ -g  generate.cpp -o main
gdb: gen
	gdb main
clean:
	rm -f main
	