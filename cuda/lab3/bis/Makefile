all: bindir bin/gpu bin/cpu 

bindir: 
	mkdir -p bin

bin/gpu: src/l3.cu
	nvcc src/l3.cu -o bin/gpu

bin/cpu: src/l3.cpp
	g++ src/l3.cpp -o bin/cpu

clean:
	rm bin/*
