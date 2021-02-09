AS = lcc -c
CC = lcc -Wa-l -Wl-m

BIN = gbflappy.gb
OBJS = main.o
EXTRA = main.lst main.sym gbflappy.map

all: $(BIN)

%.s: %.ms
	maccer -o $@ $<

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

clean:
	rm -rf $(BIN) $(OBJS) $(EXTRA) *~
