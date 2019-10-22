EXEC := libtest.so
OBJS := $(patsubst %.c, %.o, $(wildcard *.c))

all:$(EXEC)
	echo "ok"

$(EXEC):$(OBJS)
	gcc -fPIC  -shared -o $@ $^  
$(OBJS): %.o: %.c
	gcc -fPIC -shared  -c $< -o $@

clean:
	rm -rf ./*.o
	rm -rf ./*.so
