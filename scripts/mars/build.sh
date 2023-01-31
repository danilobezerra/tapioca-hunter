rm -rf out/
mkdir out/
make -f scripts/mars/Makefile
cp out.bin out/out.bin
cp out.ram out/out.ram
make -f scripts/mars/Makefile clean