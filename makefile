SRCD = src
OBJD = obj
OBJS = $(patsubst $(SRCD)/%.c, $(OBJD)/%.o, $(wildcard $(SRCD)/*.c))

$(OBJD)/%.o: $(SRCD)/%.c
	$(CC) -c -o $@ $^

lpsearch: $(OBJS)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) lpsearch

