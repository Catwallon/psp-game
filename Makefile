CC = psp-gcc
CFLAGS = 
LDFLAGS = -L$(PSPDEV)/psp/sdk/lib
LDLIBS = -lpspkernel -lpspdebug -lpspdisplay -lpspge -lpspuser -lpspgu -lpspgum -lpspctrl
CPPFLAGS = -I$(PSPDEV)/psp/sdk/include -Iinclude

TARGET = psp-game.elf

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRC = $(shell find $(SRCDIR) -name '*.c')
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
BIN = $(addprefix $(BINDIR)/, $(TARGET))

TITLE = "PSP game"

all: $(BIN)

run: $(BINDIR)/EBOOT.PBP $(BINDIR)/PARAM.SFO
	PPSSPPSDL $(BINDIR)/EBOOT.PBP

$(BINDIR)/EBOOT.PBP $(BINDIR)/PARAM.SFO: $(BIN)
	mksfo $(TITLE) $(BINDIR)/PARAM.SFO
	pack-pbp $(BINDIR)/EBOOT.PBP $(BINDIR)/PARAM.SFO NULL NULL NULL NULL NULL $(BIN) NULL

$(BIN): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)
	psp-fixup-imports $(BIN)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(BINDIR)

re: fclean all

.PHONY: all clean fclean re