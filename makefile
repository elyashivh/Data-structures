# set FN=program_name
FN ?= foo
SRC = src/$(FN).c

UPPER_FN = $(shell echo $(FN) | tr 'a-z' 'A-Z')

# output
DEBUG = bin/debug
FULL_DEBUG = /home/elyashiv/git/ds/bin/debug
RELEASE = bin/release

TARGET = $(DEBUG)/$(FN).out

# main header
HEADER_DIR = include
HEADER = $(HEADER_DIR)/$(FN).h

# srcs dir
SRC_DIR = src

# other srcs dir
DS_SRC_DIR = /home/elyashiv/git/ds/src
DS_HEADER_DIR = /home/elyashiv/git/ds/include
PROJECTS_HEADER = /home/elyashiv/git/ds/include
PROJECTS_SRC_DIR = /home/elyashiv/git/ds/src

# tests and test objects
TESTS = test/test_$(FN).c
TEST_OBJS = $(TESTS:.c=.o)

DEPENDENCIES_TEST = $(shell gcc -I$(PROJECTS_HEADER) -MM $(TESTS))
EXTRACTED_UTILS = $(patsubst $(PROJECTS_HEADER)/%.h,$(PROJECTS_SRC_DIR)/%.c,$(filter %.h, $(DEPENDENCIES_TEST)))
DEPENDENCIES = $(shell gcc -I$(HEADER_DIR) -I$(DS_HEADER_DIR) -MM $(SRC))
EXTRACTED_SRCS1 = $(patsubst $(DS_HEADER_DIR)/%.h,$(DS_SRC_DIR)/%.c,$(filter %.h, $(DEPENDENCIES)))
EXTRACTED_SRCS2 = $(patsubst $(HEADER_DIR)/%.h,$(SRC_DIR)/%.c,$(filter %.h, $(DEPENDENCIES)))
EXTRACTED_SRCS = $(EXTRACTED_SRCS1) $(EXTRACTED_SRCS2) $(EXTRACTED_UTILS)
FILTERED_SRCS = $(SRC) $(filter-out $(SRC) %.h, $(EXTRACTED_SRCS))
SRCS_FILES_V1 = $(foreach src,$(FILTERED_SRCS),$(if $(wildcard $(src)), $(src)))

ALL_DEPENDENCIES = $(shell gcc -I$(HEADER_DIR) -I$(DS_HEADER_DIR) -MM $(SRCS_FILES_V1))
ALL_EXTRACTED_SRCS1 = $(patsubst $(DS_HEADER_DIR)/%.h,$(DS_SRC_DIR)/%.c,$(filter %.h, $(ALL_DEPENDENCIES)))
ALL_EXTRACTED_SRCS2 = $(patsubst $(HEADER_DIR)/%.h,$(SRC_DIR)/%.c,$(filter %.h, $(ALL_DEPENDENCIES)))
ALL_EXTRACTED_SRCS = $(ALL_EXTRACTED_SRCS1) $(ALL_EXTRACTED_SRCS2)
ALL_FILTERED_SRCS = $(SRC) $(filter-out $(SRC) %.h, $(ALL_EXTRACTED_SRCS))
SRCS_FILES_V2 = $(foreach src,$(ALL_FILTERED_SRCS),$(if $(wildcard $(src)), $(src)))
SRCS_FILES := 

define add_unique
$(if $(findstring $(1),$(SRCS_FILES)),,$(eval SRCS_FILES += $(1)))
endef
$(foreach word,$(SRCS_FILES_V2),$(eval $(call add_unique,$(word))))

#$(info $(SRCS_FILES))


# dependencies 
DEPS_DIR = deps
DEP = $(DEPS_DIR)/$(FN).d

# libraries
LIBS = $(patsubst %.c,-l%,$(notdir $(SRCS_FILES)))

# extra libraries
LIBS += -lm

# src objects
DEBUG_OBJS = $(patsubst %.c,$(DEBUG)/%.o,$(notdir $(SRCS_FILES)))
RELEASE_OBJS = $(patsubst %.c,$(RELEASE)/%.o,$(notdir $(SRCS_FILES)))

# shared objects
DEBUG_SO = $(patsubst %.c,$(DEBUG)/lib%.so,$(notdir $(SRCS_FILES)))
RELEASE_SO = $(patsubst %.c,$(RELEASE)/lib%.so,$(notdir $(SRCS_FILES)))

# preprocessor and compiler flags
CPPFLAGS = -I$(HEADER_DIR) -I$(DS_HEADER_DIR)
CC = gcc
PIC = -fPIC

# debug flags
GD = -ansi -pedantic-errors -Wall -Wextra -g
GC = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
CFLAGS = $(GD)

# linker flags
LDFLAGS = -L$(FULL_DEBUG) -Wl,-rpath,$(FULL_DEBUG)
LDSHARED = -shared


.PHONY: open create deps debug release test clean

default: deps debug test clean

all: debug release clean


deps: $(DEP)
-include $(DEP)

debug: $(DEBUG_OBJS) $(DEBUG_SO)
 
release: CFLAGS = $(GC)
release: $(RELEASE_OBJS) $(RELEASE_SO)

test: $(TEST_OBJS) $(TARGET)

clean:
	rm -rf $(DEBUG_OBJS) $(RELEASE_OBJS) $(TEST_OBJS) $(DEP)
	

# open all project files in gedit
open: 
	gedit $(HEADER) $(SRC) $(TESTS) & 


# init project files
create: $(SRC) $(TESTS) $(HEADER)

$(SRC) $(TESTS) $(HEADER): 
	touch $(SRC)
	echo "#include \"$(FN).h\"" >> $(SRC)
	touch $(TESTS)
	echo "#include \"$(FN).h\"" >> $(TESTS)
	touch $(HEADER)
	echo "#ifndef __$(UPPER_FN)_H__\n#define __$(UPPER_FN)_H__\n\n\n#endif" >> $(HEADER)


# create dependencies files
$(DEP): $(SRCS_FILES)
	$(CC) -MM $(CPPFLAGS) $^ > $@
	
	
# create .o files
$(DEBUG)/%.o: $(SRCS_FILES)
	$(CC) $(PIC) $(CFLAGS) $(CPPFLAGS) -c $(filter %/$(basename $(notdir $@)).c,$(SRCS_FILES)) -o $@

$(RELEASE)/%.o: $(SRCS_FILES)
	$(CC) $(PIC) $(CFLAGS) $(CPPFLAGS) -c $(filter %/$(basename $(notdir $@)).c,$(SRCS_FILES)) -o $@

$(TEST_OBJS): $(TESTS) $(HEADER)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	
	
# create .so files
$(DEBUG_SO): $(DEBUG)/lib%.so: $(DEBUG)/%.o
	$(CC) $(LDSHARED) $< -o $@

$(RELEASE_SO): $(RELEASE)/lib%.so: $(RELEASE)/%.o
	$(CC) $(LDSHARED) $< -o $@


# create executable
$(TARGET): $(TEST_OBJS) 
	$(CC) $^ -o $@ $(LDFLAGS) $(LIBS)

