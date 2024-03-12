CC=gcc
CFLAGS=-I./include -Wall
OBJDIR=obj
SRCDIR=.
EXE=calculator_app
OBJS=$(OBJDIR)/main.o $(OBJDIR)/calculator.o

all: build $(EXE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJS)
	$(CC) -o $@ $^

$(OBJDIR):
	mkdir -p $@

build:
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE)
