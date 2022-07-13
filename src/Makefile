# Output executable file path.
BINARY=bin
# Directories with source code of the project.
CODEDIRS=. ./algorithms ./data_io ./data_structures ./rpn ./token 
# Directories with definitions of custom libraries.
INCDIRS=$(CODEDIRS)

CC=gcc
OPT=-O0
DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -Werror -g $(foreach dir,$(INCDIRS),-I$(dir)) $(OPT) $(DEPFLAGS)

CFILES=$(foreach file,$(CODEDIRS),$(wildcard $(file)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $@ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)