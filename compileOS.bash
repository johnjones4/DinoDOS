#! /bin/bash

# This script compiles dinoDOS. Roar.
# Created by: John Jones and Russell Toris

# Create a fresh disk
rm floppya.img
dd if=/dev/zero of=floppya.img bs=512 count=2880 2>/dev/null
dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc 2>/dev/null
dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc 2>/dev/null

# Reassemble the bootloader
nasm bootload.asm
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc seek=0 2>/dev/null

# Compile the user libraries
bcc -ansi -c -o math.o usr/lib/math.c
bcc -ansi -c -o string.o usr/lib/string.c
bcc -ansi -c -o stdio.o usr/lib/stdio.c
bcc -ansi -c -o stdlib.o usr/lib/stdlib.c
bcc -ansi -c -o sys.o usr/lib/sys.c
bcc -ansi -c -o vga.o usr/lib/vga.c

# Compile and assembles the main kernel and puts a copy on the disk
bcc -ansi -c -o system.o system.c  # the system library for the kernel
bcc -ansi -c -o proc.o proc.c
bcc -ansi -c -o kernel.o kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o system.o kernel_asm.o string.o math.o proc.o
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3 2>/dev/null

# Compile user programs
as86 lib.asm -o lib.o
bcc -ansi -c -o shell_list.o usr/shell_list.c # used for the up/down arrows
bcc -ansi -c -o shell_man.o usr/shell_man.c #definitions for the man command
bcc -ansi -c -o shell_users.o usr/shell_users.c #definitions for shell users/passwords
bcc -ansi -c -o shell.o usr/shell.c
ld86 -o shell -d shell.o lib.o string.o stdio.o sys.o shell_list.o shell_man.o math.o stdlib.o shell_users.o
bcc -ansi -c -o videmo.o usr/videmo.c
ld86 -o videmo -d videmo.o lib.o stdio.o sys.o vga.o
bcc -ansi -c -o ttt.o usr/ttt.c
ld86 -o ttt -d ttt.o lib.o stdio.o string.o vga.o sys.o
bcc -ansi -c -o dedit.o usr/dedit.c
ld86 -o dedit -d dedit.o lib.o stdio.o sys.o string.o
bcc -ansi -c -o multi.o usr/multi.c
ld86 -o multi -d multi.o lib.o stdio.o sys.o
bcc -ansi -c -o sleep.o usr/sleep.c
ld86 -o sleep -d sleep.o lib.o stdio.o sys.o
bcc -ansi -c -o ddump.o usr/ddump.c
ld86 -o ddump -d ddump.o lib.o stdio.o sys.o string.o
bcc -ansi -c -o dbasic.o usr/dbasic.c
ld86 -o dbasic -d dbasic.o lib.o stdio.o sys.o string.o stdlib.o math.o vga.o

# Mark executable programs
gcc -o markExecutable markExecutable.c
./markExecutable shell
./markExecutable videmo
./markExecutable ttt
./markExecutable dedit
./markExecutable ddump
./markExecutable multi
./markExecutable sleep
./markExecutable dbasic

# Convert the line endings of the dinoBASIC programs
javac LineConverter.java
java LineConverter dbasicprogs/prog1 prog1
java LineConverter dbasicprogs/namep namep
java LineConverter dbasicprogs/graph graph
java LineConverter dbasicprogs/loops loops

# Load files onto the disk
gcc -o loadFile loadFile.c
./loadFile shell
./loadFile videmo
./loadFile ttt
./loadFile dedit
./loadFile message.txt
./loadFile script
./loadFile ddump
./loadFile multi
./loadFile sleep
./loadFile dbasic
./loadFile usrs
./loadFile prog1
./loadFile namep
./loadFile graph
./loadFile loops

# Do some cleanup
rm *.o
rm loadFile
rm markExecutable
rm bootload
rm kernel
rm shell
rm videmo
rm ttt
rm dedit
rm ddump
rm multi
rm dbasic
rm sleep
rm prog1
rm namep
rm graph
rm loops
rm LineConverter.class