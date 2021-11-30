compiler = g++
sources =  $(filter-out vis.cpp, $(wildcard *.cpp)) # use this to include Vis: $(wildcard *.cpp)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -fopenmp
# uncomment for OpenGL Vis: flags = -g -lglfw -lglew -framework OpenGL

target = caut

$(target) : $(objects)
	$(compiler) $(flags) -o $(target) $(objects)

%.o : %.cc
	$(compiler) -c $(flags) $< -o $@ $^

clean:
	rm $(target) $(objects) curr_grid.out
