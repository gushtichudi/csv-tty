SRCDIR=src
BINSRC=$(SRCDIR)/main.c
BINNAME=csv-view

INCDIR=include/

CCFLAGS=-Wall -Wextra -Wpedantic -ferror-limit=5 -march=native -g -O0 -I$(INCDIR)
LDFLAGS=

.PHONY: clean install

OBJS=csv.o

$(BINNAME): csv.o $(BINSRC) 
	$(CC) $(CCFLAGS) $(BINSRC) -o $@ $(OBJS)

csv.o: $(SRCDIR)/csv.c
	$(CC) $(CCFLAGS) -c $< -o $@

install:
	sudo install -m775 $(BINNAME) /usr/local/bin/$(BINNAME)

clean:
	rm -f *.o
	rm -f $(BINNAME)