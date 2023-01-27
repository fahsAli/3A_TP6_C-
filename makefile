compiler        = g++
files       = sudoku.cpp main.cpp

all: compile

compile: $(files)
	$(compiler) $(files) 

clean:
	rm -f a.out

exe:
	./a.out

