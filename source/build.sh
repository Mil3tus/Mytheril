#path
export PATH="$HOME/opt/cross/bin:$PATH"

#assemble boot.s file
as --32 bootloader.s -o ../distribution/bootloader.o

#compile kernel.c file
gcc -m32 -c kernel.c -o ../distribution/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#linking the kernel with kernel.o and boot.o files
ld -m elf_i386 -T linker.ld ../distribution/kernel.o ../distribution/bootloader.o -o ../distribution/mytheril.bin -nostdlib

#check MyOS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot ../distribution/mytheril.bin

#building the iso file
#mkdir -p isodir/boot/grub
#cp MyOS.bin isodir/boot/MyOS.bin
#cp grub.cfg isodir/boot/grub/grub.cfg
#grub-mkrescue -o MyOS.iso isodir

#run it in qemu
qemu-system-x86_64 -kernel ../distribution/mytheril.bin
