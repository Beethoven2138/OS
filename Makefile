GCCPARAMS = -std=gnu99 -ffreestanding  -static-libgcc -lgcc -Iinclude

objects = obj/boot.o \
	obj/gdt.o \
	obj/asm/gdt.o \
	obj/kernel.o \
	obj/common.o \
	obj/idt.o \
	obj/irq.o \
	obj/asm/idt.o \
	obj/timer.o \
	obj/keyboard.o \
	obj/mm/frames.o \
	obj/mm/paging.o \
	obj/mm/enable_paging.o \
	obj/mm/heap.o \
	obj/tasks/task.o \
	obj/tasks/switch.o \

obj/%.o: src/%.c
	mkdir -p $(@D)
	/opt/cross/bin/i686-elf-gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.asm
	mkdir -p $(@D)
	nasm -felf32 -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	/opt/cross/bin/i686-elf-gcc $(GCCPARAMS) -c -o $@ $<

os.bin: linker.ld $(objects)
	/opt/cross/bin/i686-elf-gcc -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib $(objects)

os.iso: os.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp mykernel.bin iso/boot/os.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/mykernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=os.iso iso
	rm -rf iso

clean:
	rm -rf obj *.bin
