all:
	g++ Main.cpp -o topddt -I$(ROOTSYS)/include `root-config --libs`
clean:
	rm -f *.cxx
	rm -f *.d
	rm -f *.so
	rm -f topddt
