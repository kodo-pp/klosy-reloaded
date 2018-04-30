# klosy
See [klosy](https://github.com/kodo-pp/klosy)

*copied from klosy repo, may not be relevant to Klosy Reloaded*

Klosy is a lightweight operating system. I created this repo only because it's safe to store the source code on GitHub, not on my computer.

**Warning:** Klosy is in developement and it isn't ready for downloading.

**Notice:** some code was taken from https://gitlab.com/sortie/meaty-skeleton. For getting more information see http://wiki.osdev.org/Meaty_Skeleton

# klosy-reloaded

*This part is solely about Klosy Reloaded and has nothing to do with Klosy except for the fact that KR is
rewritten Klosy*

An attempt to rewrite Klosy from scracth due to its bugs and костыли. Yes, I have too much free time

Some bootstrap project structure was taken from [Bare Bones tutorial](https://wiki.osdev.org/Bare_bones)
on [OSDev Wiki](https://wiki.osdev.org).

## License

Klosy Reloaded is distributed under conditions of the [MIT License](https://mit-license.org), see LICENSE file.
This license only applies to Klosy Reloaded itself, not to any other programs or other files distributed along
with Klosy Reloaded. A complete list of programs, source code files or any other information which are somehow
included in this distribution and are not a part of Klosy Reloaded can be found in the *Used and Distributed
along with Klosy Reloaded* section.

## Building
See BUILDING.md

## Based on
Klosy Reloaded uses code from [Bare Bones tutorial](https://wiki.osdev.org/Bare_bones) on
[OSDev Wiki](https://wiki.osdev.org).

Also some code was taken from different tutorials and pages:

- [VGA cursor manipulations](https://wiki.osdev.org/Text_Mode_Cursor)

## Used and Distributed along with Klosy Reloaded
Here is a complete list of any data, source code, binary or in any other form, included in the distribution
and not being a part of Klosy Reloaded.

(list is empty for now, as nothing is distributed along with KR)

**WARNING**: This OS normally uses GNU GRUB, which is distributed under GNU GPL. Simply speaking, this
license requires me to publish the source code of GNU GRUB along with my OS source code. However, I am too
lazy to build GNU GRUB from its source code to make sure I publish the same GNU GRUB source code version that
is used in final ISO to boot. So, as long as I don't build GNU GRUB from source code, I won't publish the
ISO containing Klosy and GNU GRUB. *klosy-reloaded.elf* will be available, but ISO image won't. To make
the ISO you will need GNU GRUB binaries and *grub-mkrescue* program. You **can** build them from their
source code, but I **don't provide** it because I am not distributing these programs in any form.

However, you can use any bootloader supporting Multiboot. Configuration files and build scripts are
provided only for GNU GRUB, but if you want to, you can use any bootloader or even do not use it at all
(for example running kernel directly with QEMU).

Also, there is a script to run Klosy Reloaded in QEMU, but again, I do not distribute QEMU in any form,
binary or source code. QEMU can be downloaded from [here](https://www.qemu.org/download).
