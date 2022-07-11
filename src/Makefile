<<<<<<< HEAD
# Output executable file path.
BINARY=bin
# Directories with source code of the project.
CODEDIRS=.
# Directories with definitions of custom libraries.
INCDIRS=$(CODEDIRS)

CC=gcc
OPT=-O0
DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -Werror -g $(foreach dir,$(INCDIRS),-I$(dir)) $(OPT) $(DEPFLAGS)

CFILES=$(foreach file,$(CODEDIRS),$(wildcard $(file)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))
=======
CC=gcc
CFLAGS=-Wall -Werror -Wextra
OBJECTS=graph.o
BINARY=../build/bin
>>>>>>> 55ef6f136a3c55c8d3bc921963e773bd546bfc9a

all: $(BINARY)

$(BINARY): $(OBJECTS)
<<<<<<< HEAD
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)
=======
	$(CC) -o $(BINARY) $(OBJECTS)

%.o: %.c:
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJECTS) $(BINARY)
>>>>>>> 55ef6f136a3c55c8d3bc921963e773bd546bfc9a
