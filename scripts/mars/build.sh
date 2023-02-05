echo "BUILD: Cleaning build files"
make -f Makefile clean

echo "BUILD: Running code generators (requires lua)"
lua scripts/generate_hitboxes.lua
lua scripts/generate_enemies_init.lua

echo "BUILD: Running make"
make -f Makefile all