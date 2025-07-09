BINNAME=csv-view
BINDIR=src
BINSRC=$(BINDIR)/main.c

INCDIR=include/

CCFLAGS=-Wall -Wextra -Wpedantic -ferror-limit=5 -march=native -g -O0 -I$(INCDIR)
LDFLAGS=

.PHONY: clean install

$(BINNAME): $(BINSRC)
	$(CC) $(CCFLAGS) $< -o $@

install:
	sudo install -m775 $(BINNAME) /usr/local/bin/$(BINNAME)

clean:
	rm -f *.o
	rm -f $(BINNAME)