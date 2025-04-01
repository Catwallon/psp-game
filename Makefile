CC = psp-gcc
CFLAGS =
LDFLAGS = -L$(PSPDEV)/psp/sdk/lib
LDLIBS = -lm -lpspkernel -lpspdebug -lpspdisplay -lpspge -lpspuser -lpspgu -lpspgum -lpspctrl
CPPFLAGS = -I$(PSPDEV)/psp/sdk/include -Iinclude

TARGET = psp-game.elf

SRCDIR = src
ASSETDIR = asset
OBJDIR = obj
BINDIR = bin

SRC = $(shell find $(SRCDIR) -name '*.c')
ASSET = $(shell find $(ASSETDIR) -name '*.raw')

OBJ_SRC = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
OBJ_ASSET = $(patsubst $(ASSETDIR)/%.raw, $(OBJDIR)/%.o, $(ASSET))
OBJ = $(OBJ_SRC) $(OBJ_ASSET)

BIN = $(addprefix $(BINDIR)/, $(TARGET))

TITLE = "PSP game"
EMULATOR = PPSSPPSDL

all: $(BIN)

run: $(BINDIR)/EBOOT.PBP $(BINDIR)/PARAM.SFO
	$(EMULATOR) $(BINDIR)/EBOOT.PBP

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

$(OBJDIR)/%.o: $(ASSETDIR)/%.raw
	@mkdir -p $(dir $@)
	bin2o -i $< $@ $(basename $(notdir $<))

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(BINDIR)

re: fclean all

.PHONY: all clean fclean re