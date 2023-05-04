all: clean compile test

BINARY=Project2

clean:
	rm -f cmake-build-debug/$(BINARY)

compile: FileChecker.cpp FileChecker.h FileCopier.cpp FileCopier.h FileModifyException.h main.cpp Project2MultiProcessModifier.cpp Project2MultiProcessModifier.h Util.cpp Util.h
	g++ -std=c++14 -I . -o cmake-build-debug/$(BINARY) FileChecker.cpp FileCopier.cpp main.cpp Project2MultiProcessModifier.cpp Util.cpp

test:
	cd cmake-build-debug && ./$(BINARY) R
