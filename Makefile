# Makefile

TARGETS = shapeguide sin test wave

CFLAGS = -w
CLEANCMD = rm -f

ifdef MSYSTEM
	LDFLAGS = -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm
	EXECS = $(addsuffix .exe, $(TARGETS))
else
	LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm
	EXECS = $(TARGETS)
endif

all: $(TARGETS)

$(TARGETS): %: %.o
	$(CC) $< $(LDFLAGS) -o $@

.PHONY:	clean

clean:
	@$(CLEANCMD) $(EXECS) *.o
