all : main.c bootstrap.S
	riscv32-unknown-elf-gcc main.c bootstrap.S -o main -lm -nostartfiles -march=rv32ima -mabi=ilp32
	
sim: all
	$(EE6470)/riscv-vp/vp/build/bin/riscv-vp-dac-two-core --intercept-syscalls main
	
clean:
	rm -f main
