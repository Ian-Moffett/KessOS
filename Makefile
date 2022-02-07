all:	
	nasm -fbin src/x86/boot/bootloader.asm -o bin/bootloader.bin
	nasm -felf32 src/x86/kernel/kernel.asm -o objres/kentry.o 
	gcc -c -m32 src/x86/kernel/kmain.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/kmain.o
	gcc -c -m32 src/x86/kernel/kshell/main.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/kshell.o
	gcc -c -m32 src/x86/kernel/drivers/IO/IO.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/io.o
	gcc -c -m32 src/x86/kernel/util/strings/strings.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/strings.o
	gcc -c -m32 src/x86/kernel/drivers/VGA/VGA.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/vga.o
	gcc -c -m32 src/x86/kernel/interrupts/impl/IDT.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/idt.o
	gcc -c -m32 src/x86/kernel/interrupts/impl/exceptions.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/excp.o
	ld -melf_i386 -Tlink.ld objres/*.o  obj/*.o --oformat binary -o bin/kernel.bin
	cat bin/bootloader.bin bin/kernel.bin > bin/KessOS.bin
	@ # Prepare the image.
	sudo dd if=/dev/zero of=KessOS.img bs=1024 count=1440
	@ # Put the OS stuff in the image.
	sudo dd if=bin/KessOS.bin of=KessOS.img

burn_usb:
	sudo dd if=KessOS.img of=/dev/sdb

danger:
	make all burn_usb run


run:
	sudo qemu-system-x86_64 -hda /dev/sdb -monitor stdio -d int -no-reboot -D logfile.txt -M smm=off
