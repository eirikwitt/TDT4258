# Example Makefile
#
# Exercise 2, TDT4258

#COMMANDER=/home/oskar/new/skole/digdat/SimplicityCommander-Linux/commander/commander

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-mcpu=cortex-m3 -mthumb -g -std=c99 -Wall
LDFLAGS=-mcpu=cortex-m3 -mthumb -g -lgcc -lc -lcs3 -lcs3unhosted -lefm32gg -Llib
#LDFLAGS=-mcpu=cortex-m3 -mthumb -g -lgcc -lc -lefm32gg -Llib
ASFLAGS=-mcpu=cortex-m3 -mthumb -g
LINKERSCRIPT=lib/efm32gg.ld

ex2.bin : ex2.elf
	${OBJCOPY} -O binary $< $@

ex2.elf : ex2.o timer.o dac.o gpio.o interrupt_handlers.o ahem_x.o nokia.o call_to_arms.o applause3.o bloop_x.o bad_disk_x.o air_raid.o bushj_liberty.o
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY : pretty
pretty :
	-indent *.c *.h

.PHONY : upload
upload :
	-eACommander.sh -r --address 0x00000000 -f "ex2.bin" -r
#	$(COMMANDER) flash ex2.bin

.PHONY : clean
clean :
	-rm -rf *.o *.elf *.bin *.hex

# extract raw pcm audio data from wav container
%.raw : %.wav
	ffmpeg -y -i $< -f s8 -acodec pcm_s8 -ar 11025 -ac 1 $*.raw

# create linkable object files from raw pcm audio data
%.o : %.raw
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm --rename-section .data=.rodata $*.raw $@
