compiler = g++

sources =  $(filter-out vis.cpp, $(wildcard *.cpp)) # use this to include Vis: $(wildcard *.cpp)
objects = $(addsuffix .o, $(basename $(sources)))

flags = -g -fopenmp
# uncomment for OpenGL Vis: flags += -lglfw -lglew -framework OpenGL

target = caut

all: $(target)

$(target) : $(objects)
	$(compiler) $(flags) -o $(target) $(objects)

%.o : %.cpp
	$(compiler) -c $(flags) $< -o $@

clean:
	rm -rf $(target) $(objects)
