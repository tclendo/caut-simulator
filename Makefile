compiler = g++
sources = $(wildcard *.cpp)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g

target = caut

$(target) : $(objects)
	$(compiler) -o $(target) $(objects)

%.o : %.cc
	$(compiler) -c $(flags) $< -o $@ $^

clean:
	rm $(target) $(objects)
