compiler = g++
sources = $(wildcard *.cpp)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -lglfw -lglew -framework OpenGL



target = caut

$(target) : $(objects)
	$(compiler) -o $(target) $(objects) $(flags)

%.o : %.cc
	$(compiler) -c $(flags) $< -o $@ $^

clean:
	rm $(target) $(objects)
