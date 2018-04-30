# Building Klosy Reloaded
This is a building guide for Klosy Reloaded

## Prerequisites
To build Klosy Reloaded you will need:

- A UNIX-like build environment (Linux is recommended)

- GNU Binutils and GNU GCC configured for target `i686-elf` with some special parameters, see below

- Klosy Reloaded source code (can be obtained from [GitHub](https://github.com/kodo-pp/klosy-reloaded))

- Xorriso, GNU GRUB and `grub-mkrescue` program (all of these are optional and
are required only to build an ISO image)

Kernel can be built without Xorriso, GNU GRUB and grub-mkrescue, but if you
want to build a bootable ISO image, you will need them.
Any other multiboot-capable bootloader should be OK, but scripts are provided
only for GRUB.

## Obtaining GCC and Binutils
Based on [this tutorial](https://wiki.osdev.org/GCC_Cross-Compiler).

If you have done this step earlier and you already have programs like
`i686-elf-as` and `i686-elf-gcc`, you can skip this step.
***WARNING***: to build Klosy Reloaded you can not use native GCC and Binutils,
which are commonly pre-installed in Linux distros like Ubuntu or which can
be downloaded in the binary form. You will need to configure them and then
build from source.

Building Binutils and GCC from source is quite a long process. On fast machines
it can take about 20-30 minutes (or may be a bit less), but on slow machines
the building process may last a couple of hours. Also, be ready that large amounts
of RAM and disk space will be consumed.

### Prerequisites for GNU GCC
#### TL;DR
Apt-based systems:
`$ sudo apt-get install libgmp3-dev libmpfr-dev libisl-dev libcloog-isl-dev libmpc-dev texinfo`

Cygwin:
package list:
`libgmp-devel`, `libmpfr-devel`, `libisl-devel`, `libcloog-isl-devel`, `libmpc-devel`, `texinfo`

#### More detailed description

Here are some libs required to build GCC. You can download them with your
favourite package manager such as apt, pacman or yum (for package names see
https://wiki.osdev.org/GCC_Cross-Compiler#Downloading_the_Source_Code)

### Downloading source code
I am using GCC 7.3.0 and Binutils 2.30.0, you can maybe use other versions,
but if you experience problems with them, try versions that I use.

Also, I'm downoading GCC sources from mirrors in Germany, you may prefer other mirrors.
[List of all possible mirrors](https://gcc.gnu.org/mirrors.html).

So, here we go,

Create a directory (e.g. ~/tools) where the sources will be downloaded
```
$ mkdir tools
$ cd tools
```

Download Binutils source code (download size: about 19 MiB)
```
$ wget --continue 'ftp://sourceware.org/pub/binutils/snapshots/binutils-2.30.0.tar.xz'
$ tar -xf binutils-2.30.0.tar.xz
```

Download Binutils source code (download size: about 107 MiB)
As it was said above, you may want to choose another mirror
```
$ wget  --continue 'ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-7.3.0/gcc-7.3.0.tar.gz'
$ tar -xf gcc-7.3.0.tar.gz
```

### Building Binutils

`$HOME/opt/cross` is path where to install Binutils ang GCC. You can specify
your own installation directory. If you install Binutils to `/some/directory`
be sure to include `/some/directory/bin` to `$PATH` before building GCC!
Also, if installing somewhere in `/usr/local` or something like that (**which is
not recommended!**), you may have to put `sudo` before `make install`.
```
$ mkdir -p build/binutils
$ cd build/binutils
$ ../../binutils-2.30.0/configure --prefix="$HOME/opt/cross" --target=i686-elf --with-sysroot --disable-nls --disable-werror
$ make -j8
$ make install
$ cd ../../
```

Don't forget to include the `$HOME/opt/cross/bin` to your $PATH (maybe you should
do it in your ~/.bashrc (or ~/.zshrc or ~/.whatever-shell-you-use-rc)) (Assuming
you installed Binutils in `$HOME/opt/cross/bin`)
```
$ echo 'export PATH="$HOME/opt/cross/bin:$PATH"' >> ~/.bashrc
$ source ~/.bashrc
```

### Building GCC

You should install GCC into the same directory, where you have installed Binutils
(`$HOME/opt/cross` is our example).

```
$ mkdir -p build/gcc
$ cd build/gcc
$ ../../gcc-7.3.0/configure --target=i686-elf --prefix="$HOME/opt/cross" --disable-nls --enable-languages=c,c++ --disable-werror --without-headers
$ make -j8 all-gcc
$ make -j8 all-target-libgcc
$ make -j8 install-gcc
$ make -j8 install-target-libgcc
```

Congratulations! You made it!
Binutils and GCC are successfully built and installed now, you can now build Klosy Reloaded

## Building
Everything is super-easy.

Build kernel: `./build.sh`

Create bootable ISO image with GRUB: `./iso.sh` or `./iso.sh -f` if you want to re-build kernel

Launck KR in qemu: `./qemu.sh` or `./qemu.sh -f` if you want to re-build kernel

Clean up: `./clean.sh` or `./clean.sh --no-keep-kernel` if you want to remove klosy-reloaded.elf

## Debugging

Debug kernel in qemu: `KR_DEBUG=yes ./qemu.sh -f`.

Then start GDB (in another terminal, but in the same directory): `gdb --symbols=klosy-reloaded.elf`.

Then type in GDB console: `target remote localhost:1234`.

Now you can debug the kernel.
