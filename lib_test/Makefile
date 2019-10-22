dir += lib
EXEC := TEST
CFLAG += -I./lib
LDFLAGS += -L./lib/
LDFLAGS += -ltest
LIB := lib
OBJS := $(patsubst %.c, %.o, $(wildcard *.c))

.PHONY : all clean LIB

all:$(EXEC)
	echo "ok"

$(EXEC): $(OBJS) $(LIB) 
	gcc $(CFLAG) -o $@  $(OBJS) $(LDFLAGS)

$(OBJS): %.o: %.c
	gcc $(CFLAG) -c $< -o $@ $(LDFLAGS)

LIBMAKE:
	make -C lib all

$(LIB): LIBMAKE

clean:
	rm $(EXEC)
	rm -rf ./*.o
	make -C lib clean
