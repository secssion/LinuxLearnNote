EXEC := avl_tree
CC := gcc

OBJS := $(patsubst %.c, %.o, $(wildcard *.c))

all:$(EXEC)
	echo 'compile ok.'

clean:
	@-rm -f *.o $(EXEC) 
#	@-rm -f $(ROMFS_PATH)/bin/$(EXEC)

$(EXEC): $(OBJS)
	$(CC)  -o $@ $(OBJS) $(LDFLAGS_UGW) $(LDFLAGS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)
