CC = cc
CFLAGS = -Wall -Wextra -Wpedantic

INCLUDE_ROOT = include
INCLUDE_DIRS = -I$(INCLUDE_ROOT) \
               $(patsubst %/, -I%,$(sort $(dir $(wildcard $(INCLUDE_ROOT)/*/))))
CPPFLAGS = $(INCLUDE_DIRS)

TARGET = build/Emu386

SRC = $(sort $(shell grep -rl --include='*.c' '[^[:space:]]' src))
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

compile_commands.json: $(SRC) Makefile
	@awk -v dir="$(CURDIR)" -v cc="$(CC)" -v flags="$(CFLAGS) $(CPPFLAGS)" 'BEGIN { print "["; sep = "" } FNR == 1 { obj = "build/" substr(FILENAME, 5); sub(/[.]c$$/, ".o", obj); cmd = cc " " flags " -MMD -MP -c " FILENAME " -o " obj; printf "%s  {\n", sep; printf "    \"directory\": \"%s\",\n", dir; printf "    \"command\": \"%s\",\n", cmd; printf "    \"file\": \"%s/%s\"\n", dir, FILENAME; printf "  }"; sep = ",\n" } END { print "\n]" }' $(SRC) > $@.tmp
	@mv $@.tmp $@

clean:
	rm -rf build

.PHONY: all clean compile_commands.json
