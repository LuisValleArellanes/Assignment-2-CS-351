all: pipefile

pipestrans:	pipefile.cpp
	g++ pipefile.cpp -o pipefile

clean:
	rm -rf pipefile file__recv
