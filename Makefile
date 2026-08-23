CXX      ?= g++
STD      ?= c++17
CXXFLAGS ?= -std=$(STD) -O2 -Wall -Wextra -I.
BUILD    ?= build

SRCS := $(wildcard *.cpp)
BINS := $(patsubst %.cpp,$(BUILD)/%,$(SRCS))

.PHONY: all clean list help test
.DEFAULT_GOAL := help

all: $(BINS)
	@echo "built $(words $(BINS)) programs"

$(BUILD)/%: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -o $@ $< || { echo "FAIL $<"; exit 1; }

# `make cpp_logger`
define program_alias
.PHONY: $(1)
$(1): $(BUILD)/$(1)
	@echo "$(BUILD)/$(1)"
endef
$(foreach s,$(SRCS),$(eval $(call program_alias,$(basename $(s)))))

# `make run P=cpp_logger` — add IN=file to pipe stdin
run:
	@test -n "$(P)" || { echo "usage: make run P=<program> [IN=<file>]"; exit 1; }
	@test -f "$(P).cpp" || { echo "no such program: $(P)"; exit 1; }
	@mkdir -p $(BUILD)
	@$(CXX) $(CXXFLAGS) -o $(BUILD)/$(P) $(P).cpp
	@infile="$(IN)"; \
	 if [ -n "$$infile" ]; then "$(BUILD)/$(P)" < "$$infile"; else "$(BUILD)/$(P)"; fi

TESTS := $(wildcard tests/*.cpp)

test: $(patsubst %.cpp,$(BUILD)/%,$(TESTS))
	@fail=0; for t in $^; do echo "$$t"; ./$$t || fail=1; done; exit $$fail

list:
	@printf '%s\n' $(sort $(basename $(SRCS)))

clean:
	@rm -rf $(BUILD)

help:
	@echo "make all            compile every program ($(words $(SRCS)) of them)"
	@echo "make <program>      compile one, e.g. make cpp_logger"
	@echo "make run P=<name>   compile and run  (IN=file to pipe stdin)"
	@echo "make list           list program names"
	@echo "make test           build and run the tests"
	@echo "make clean          remove $(BUILD)/"
