CXX = g++
ECHO = echo
RM = rm -f

CXXFLAGS = -std=c++11 -Wall -Werror -ggdb3 -funroll-loops

LDFLAGS = ../lib/parbegin/libparbegin.a

BIN = rw_monitor_ex
OBJS = main.o rw_monitor.o

all: $(BIN) etags

$(BIN): $(OBJS)
	@$(ECHO) Linking $@
	@$(CXX) $^ -o $@ $(LDFLAGS)

-include $(OBJS:.o=.d)

%.o: %.cpp
	@$(ECHO) Compiling $<
	@$(CXX) $(CXXFLAGS) -MMD -MF $*.d -c $<

.PHONY: all clean clobber etags

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o $(BIN) *.d TAGS core vgcore.* gmon.out

etags:
	@$(ECHO) Updating TAGS
	@etags *.h *.cpp