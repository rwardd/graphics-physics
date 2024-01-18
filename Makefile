all:
	cd build && cmake .. && $(MAKE)

clean:
	cd build && $(MAKE) clean

run:
	cd build && cmake .. && $(MAKE) && ./physics_engine

