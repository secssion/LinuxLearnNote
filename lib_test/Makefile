dir += lib
EXEC := test
CFLAG += -I/home/xiedongsheng/project/temp_test/lib
LDFLAGS += -L/home/xiedongsheng/project/temp_test/lib/
LDFLAGS += -ltest
OBJS := $(patsubst %.c, %.o, $(wildcard *.c))

all:$(EXEC)
	echo "ok"

$(EXEC): $(OBJS)
	gcc $(CFLAG) -o $@ $(LDFLAGS) $^ 

$(OBJS): %.o: %.c
	gcc $(CFLAG) -c $< -o $@ $(LDFLAGS)
	
clean:
	rm -rf ./*.o
