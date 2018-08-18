SRCS		:=
OBJS		:=
DEPS		:=
TMPS		:=
LIBS		:=
PROGRAMS	:=
TESTS		:=
#======================================================================
# MODULES
MODULES		:= src/buffer src/system src/json
# LIBS
MODULES		+= lib/
# APP
MODULES 	+= JsonCompression

INCLUDE_DIRS	:= include
vpath %.h $(INCLUDE_DIRS)
#======================================================================
# select which tools to use as compiler, 
# librarian and linker
#======================================================================
CFLAGS		+= -Wall -O2
CFLAGS		+= $(addprefix -I , $(INCLUDE_DIRS))
#======================================================================
# select which tools to use as compiler, librarian and linker
#======================================================================
AR = ar
ARFLAGS = rv
#======================================================================
# Enviroment
#======================================================================
MKDIR		:= mkdir -p
RM		:= rm -f
MV		:= mf -f
#======================================================================
# Common modules
include $(patsubst %, ./%/xmodule.mk, $(MODULES))
# Current program

# Unit test
# JSON
include ./unitTest/TEST_JSON/TEST_JSON_CODER_DECODER/xmodule.mk
#======================================================================
.PHONY: default build run all clean

default: all

all: $(OBJS) $(PROGRAMS) $(TESTS)

run: $(PROGRAMS)
	@$<
#======================================================================
# unitTest
test: $(OBJS) $(TMPS) $(TESTS)

TEST_JSON_CODER_DECODER_EXE:
	@./unitTest/TEST_JSON/TEST_JSON_CODER_DECODER/TEST_JSON_CODER_DECODER_EXE

# TEST MEM	
mem_prog: $(PROGRAMS) $(TESTS)
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no $(PROGRAMS)

# TEST MEM	
mem_test: $(PROGRAMS) $(TESTS)
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no ./unitTest/TEST_JSON/TEST_JSON_CODER_DECODER/TEST_JSON_CODER_DECODER_EXE

clean:
	$(RM) $(OBJS) $(DEPS) $(PROGRAMS) $(TMPS)
	

