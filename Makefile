CC ?= gcc
AR ?= ar
RM ?= rm -f

CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O2 -ffreestanding -fno-builtin
TEST_CFLAGS := $(CFLAGS) -Wno-format-truncation
CPPFLAGS += -Iinclude

BUILD_DIR := build
LIB_NAME := libzirvlibc.a

SRC := \
	src/string.c \
	src/ctype.c \
	src/stdio.c

OBJ := $(patsubst src/%.c,$(BUILD_DIR)/src/%.o,$(SRC))

TEST_BIN := $(BUILD_DIR)/test_libc

.PHONY: all clean test

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	$(AR) rcs $@ $^

$(BUILD_DIR)/src/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(TEST_BIN): tests/test_libc.c $(LIB_NAME)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(TEST_CFLAGS) -o $@ tests/test_libc.c $(LIB_NAME)

test: $(TEST_BIN)
	$(TEST_BIN)

clean:
	$(RM) $(LIB_NAME)
	$(RM) -r $(BUILD_DIR)
