SUFFIX = .c
CC = gcc
CFLAGS = -g -Wall -Wextra -O3
LDFLGAS = -lm
INCLUDE = -I./
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:$(SUFFIX)=.o)))
OBJDIR  = ./objs
SRCDIR = ./
SOURCES = $(wildcard $(SRCDIR)/*$(SUFFIX))
TARGET = ./tsh

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%$(SUFFIX)
	-mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

.PHONY: tmpclean clean
tmpclean:
	$(RM) *~
clean: tmpclean
	$(RM) $(OBJDIR) $(TARGET)
