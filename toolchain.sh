#!/bin/sh

set -e

BINUTILS_V=2.32
GCC_V=9.1.0

echo $BINUTILS_V $GCC_V

TOOLCHAIN="$PWD/toolchain"
HOST="i686-elf"

mkdir -p ${TOOLCHAIN}/src

cd ${TOOLCHAIN}/src
wget ftp://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_V}.tar.gz
tar -xf binutils-${BINUTILS_V}.tar.gz
mkdir build-binutils
cd build-binutils
../binutils-${BINUTILS_V}/configure --target=${HOST} --prefix=${TOOLCHAIN} --disable-nls --with-sysroot --disable-werror
make
make install

cd ${TOOLCHAIN}/src
wget https://ftp.gnu.org/gnu/gcc/gcc-${GCC_V}/gcc-${GCC_V}.tar.xz
tar -xf gcc-${GCC_V}.tar.xz
mkdir build-gcc
cd build-gcc
../gcc-${GCC_V}/configure --target=${HOST} --prefix=${TOOLCHAIN} --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
