RELEASE=lab2
CPU=bin/lab2.cpu
GPU=bin/lab2.gpu
LDFLAGS = -lm

all: release 

bin: 
	mkdir -p $@

debug: $(CPU) $(GPU)

release: $(RELEASE)

$(RELEASE): src/main_gpu.cu
	nvcc -o $@ $< $(LDFLAGS) -DGRID_SIZE=256 -DBLOCK_SIZE=32

$(GPU): src/main_gpu.cu
	nvcc -o $@ $< $(LDFLAGS)

$(CPU): src/main_cpu.cpp
	g++ --std=c11 -o $@ $< $(LDFLAGS)

clean:
	rm -f $(RELEASE) $(CPU) $(GPU)
