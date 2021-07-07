prom = TestBench
obj = TestBench.o Profiling.o 

$(prom): $(obj)
	g++ $(obj) -o $(prom) -O2 -std=c++17

TestBench.o : TestBench.cpp Profiling.hpp
	g++ TestBench.cpp -O2 -c -std=c++17

Profiling.o : Profiling.cpp Profiling.hpp
	g++ Profiling.cpp -O2 -c -std=c++17

clean:
	rm -rf $(obj) $(prom)
