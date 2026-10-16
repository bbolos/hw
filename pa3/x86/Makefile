# tools
AS := as
LD := ld
RM := rm -f

# flags
ASFLAGS := -g --32
LDFLAGS := -m elf_i386

default: all

all: echo.s
	$(AS) $(ASFLAGS) -o echo.o echo.s
	$(LD) -m elf_i386 -o echo echo.o

clean:
	$(RM) echo *.o
