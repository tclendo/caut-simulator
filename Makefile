compiler = g++
sources =  $(filter-out vis.cpp, $(wildcard *.cpp)) # use this to include Vis: $(wildcard *.cpp)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g
# uncomment for OpenGL Vis: flags = -g -lglfw -lglew -framework OpenGL



target = caut

$(target) : $(objects)
	$(compiler) -o $(target) $(objects) $(flags)

%.o : %.cc
	$(compiler) -c $(flags) $< -o $@ $^

clean:
	rm $(target) $(objects) curr_grid.out
