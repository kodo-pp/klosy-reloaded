EXECNAME?=main

CC=i686-elf-gcc
CFLAGS+=-Wall -Wextra -std=c99 -pedantic

LIBS+=
LDFLAGS+=
LD=i686-elf-ld

RM=rm

OBJS+=src/main.o

.PHONY: all clean run ee bee
# Warning: `ee' and `bee' targets are debug ones, do not use on production!

# Production .PHONY targets
all: $(EXECNAME)

clean:
	$(RM) -fv $(OBJS) $(EXECNAME)

run: $(EXECNAME)
	./$(EXECNAME)

# Debug .PHONY targets
ee: clean run
bee: clean all

# Not .PHONY targets
$(EXECNAME): $(OBJS)
	$(LD) $(LDFLAGS) $(LIBS) $(OBJS) -o $(EXECNAME)
