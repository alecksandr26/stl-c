# For debuggin
.SUFFIXES:
%:: SCCS/s.%
%:: RCS/%
%:: RCS/%,v
%:: %,v
%:: s.%

C = cc
AR = ar cr

C_FLAGS = -ggdb -pedantic -Wall 
C_FLAGS_LIBS = -ltc
C_TEST_FLAGS = -lunittest -ltc

CF = clang-format -i

V = valgrind
V_FLAGS = --leak-check=full --track-origins=yes -s  --show-leak-kinds=all

P = gprof
P_FLAGS = --line --brief -B

OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test
TESTRUNNER = test.out
LIB_DIR = lib
INCLUDE_DIR = include
EXAMPLE_DIR = example

# To profile the code
TEST_PROFILE_DIR = $(addprefix $(TEST_DIR)/, profile)
BIN_EXAMPLE_DIR = $(addprefix $(EXAMPLE_DIR)/, bin)
PROFILES = $(addprefix $(TEST_PROFILE_DIR)/, profile_stack.out)

OBJS = $(addprefix $(OBJ_DIR)/, 	\
				stl.o   \
				mem.o   \
				queue.o \
				stack.o)

#				array.o)
#				list.o\


EXAMPLES = $(addprefix $(BIN_EXAMPLE_DIR)/, 	\
						example_stack.out\
						example_queue.out)
#						example_list.out\
#						example_array.out\

LIBS = $(addprefix $(LIB_DIR)/, libstl.a)

.PHONY: all clean format test
all: $(OBJ_DIR) $(LIB_DIR) $(TEST_PROFILE_DIR) $(OBJS) $(LIBS) $(TESTRUNNER) $(PROFILES) $(EXAMPLES)

$(OBJ_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(LIB_DIR):
	@echo Creating: $@
	@mkdir -p $@

# Create the profile folder
$(TEST_PROFILE_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(BIN_EXAMPLE_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo Compiling: $< -o $@
	@$(C) $(C_FLAGS) -c $< -o $@ $(C_FLAGS_LIBS)

# To create examples
$(BIN_EXAMPLE_DIR)/%.out: $(EXAMPLE_DIR)/%.c $(LIBS) | $(BIN_EXAMPLE_DIR)
	@echo Compiling: $^ -o $@
	@$(C) $(C_FLAGS) $^ -o $@ $(C_FLAGS_LIBS)

%.out: $(BIN_EXAMPLE_DIR)/%.out
	@echo Running: $<
	@$(V) $(V_FLAGS) ./$<

example: $(notdir $(EXAMPLES))

# Creates the library
$(LIB_DIR)/%.a: $(OBJS) | $(LIB_DIR)
	@echo Archiving: $@
	@$(AR) $@ $^
	@ranlib $@

# To compile and run the testrunner
$(TESTRUNNER): test.c $(LIBS)
	@echo Compiling: $< -o $@
	@$(C) $(C_FLAGS) $< -o $@ $(C_TEST_FLAGS)

test: $(TESTRUNNER)
	@echo Running: $<
	@./$<

# To do profiling

# Compile the profiling tests
$(TEST_PROFILE_DIR)/profile_%.out: $(TEST_DIR)/profile_%.c $(LIBS) | $(TEST_PROFILE_DIR)
	@echo Compiling: $^ -o $@
	@$(C) $(C_FLAGS) -pg $(filter-out $(TEST_PROFILE_DIR), $^) -o $@ $(C_FLAGS_LIBS)

profile_%.out: $(TEST_PROFILE_DIR)/profile_%.out
	@echo Running: $@
	@cd $(dir $<) && ./$@
	@echo Profinling: $@
	@cd $(dir $<) && $(P) $(P_FLAGS) ./$@

# To run the profinling
profile: $(notdir $(PROFILES))

clean_$(LIB_DIR)/%:
	@echo Removing: $(patsubst clean_%, %, $@)
	@rm $(patsubst clean_%, %, $@)

clean_$(OBJ_DIR)/%.o:
	@echo Removing: $(patsubst clean_%, %, $@)
	@rm $(patsubst clean_%, %, $@)

clean_$(TEST_PROFILE_DIR)/profile_%.out:
	@echo Removing: $(patsubst clean_%, %, $@)
	@rm $(patsubst clean_%, %, $@)

# Clean the profile archive generated
clean_$(TEST_PROFILE_DIR)/gmon.out:
	@echo Removing: $(patsubst clean_%, %, $@)
	@rm $(patsubst clean_%, %, $@)

clean:  $(addprefix clean_, $(wildcard $(LIB_DIR)/*.a)) \
	$(addprefix clean_, $(wildcard $(OBJ_DIR)/*.o)) \
	$(addprefix clean_, $(wildcard $(TEST_PROFILE_DIR)/*.out))

ifneq ("$(wildcard $(OBJ_DIR))", "")
	@echo Removing: $(OBJ_DIR)
	@rmdir $(OBJ_DIR)
endif

ifneq ("$(wildcard $(LIB_DIR))", "")
	@echo Removing: $(LIB_DIR)
	@rmdir $(LIB_DIR)
endif

ifneq ("$(wildcard $(TEST_PROFILE_DIR))", "")
	@echo Removing: $(TEST_PROFILE_DIR)
	@rmdir $(TEST_PROFILE_DIR)
endif

ifneq ("$(wildcard $(TESTRUNNER))", "")
	@echo Removing: $(TESTRUNNER)
	@rm $(TESTRUNNER)
endif

ifneq ("$(wildcard $(BIN_EXAMPLE_DIR))", "")
	@echo Removing: $(BIN_EXAMPLE_DIR)
	@rm -r $(BIN_EXAMPLE_DIR)
endif


format_$(SRC_DIR)/%.c:
	@echo Formatting: $(patsubst format_%, %, $@)
	@$(CF) $(patsubst format_%, %, $@)

format_$(INCLUDE_DIR)/%.h:
	@echo Formatting: $(patsubst format_%, %, $@)
	@$(CF) $(patsubst format_%, %, $@)

format_$(TEST_SRC_DIR)/%.c:
	@echo Formatting: $(patsubst format_%, %, $@)
	@$(CF) $(patsubst format_%, %, $@)

# To format all the code
format: $(addprefix format_, 	$(wildcard $(SRC_DIR)/*.c) \
				$(wildcard $(INCLUDE_DIR)/*.h) \
				$(wildcard $(TEST_SRC_DIR)/*.c))



