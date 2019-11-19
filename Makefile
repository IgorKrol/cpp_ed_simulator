#!make -f

# all: test
# 	./$<

test: Editor.cpp Document.cpp main.cpp
	g++ -std=c++11 Editor.cpp Document.cpp main.cpp -o test

clean:
	rm -f *.o demo test
