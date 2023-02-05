echo "BUILD: Resetting out"
rm -rf out/
mkdir out/

echo "BUILD: Running code generators (requires lua)"
lua scripts/generate_hitboxes.lua
lua scripts/generate_enemies_init.lua

echo "BUILD: Running make"
make -f scripts/mars/Makefile

echo "BUILD: Copying files to out/"
cp out.bin out/out.bin

echo "BUILD: Cleaning build files outside of out/"
make -f scripts/mars/Makefile clean