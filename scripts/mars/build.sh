rm -rf out/
mkdir out/
make -f scripts/mars/Makefile
cp out.bin out/out.bin
make -f scripts/mars/Makefile clean