sources = $(wildcard *.cpp)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g

target = caut

$(target) : $(objects)
	g++ -o $(target) $(objects)

%.o : %.cc
	g++ -c $(flags) $< -o $@

clean:
	rm $(target) $(objects)
