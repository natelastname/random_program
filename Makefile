NAME = gf2_poly
SOURCEDIR = src
SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJFILES := $(patsubst %.c,%.o,$(SOURCES))
LIBS := -ldl -lSDL2
OPTS := --std=gnu++11

%.o: %.cpp
	g++ $(OPTS) $< $(LIBS)

$(NAME): $(OBJFILES)
	g++ $(OPTS) $(SOURCES) $(LIBS)

all: $(NAME)

clean:
	rm -r *.o
