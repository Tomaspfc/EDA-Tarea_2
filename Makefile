code: main.cpp
	cd build && make  && cd ..
	cp build/code code

run:
	./code

mk:
	cd build && cmake .. && cd ..
