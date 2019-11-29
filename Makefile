NAME := Ansiterm

.PHONY: all clean format

all: format

format:
	clang-format --style=file -i $(NAME).*

clean:
	rm *.o
