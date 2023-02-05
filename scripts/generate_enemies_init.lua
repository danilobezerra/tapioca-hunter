local tiledfile = require 'res.tiled.objects'

local ghosts = tiledfile.layers[2].objects or {}

if #ghosts == 0 then
  print("'WARN: couldn't get ghosts")
end

local function ghost_to_code(idx)
  local ghost = ghosts[idx]
  return string.format(
    "    GHOST_init(&ghosts[%d], &ghosts_sprites[%d], %d, %d);",
    idx-1, idx-1, ghost.x, ghost.y
  );
end

local c_code = {}
for i=1, #ghosts do
  table.insert(c_code, ghost_to_code(i))
end

local c_template_file = io.open('scripts/templates/enemies_init_template.c')
local c_template = c_template_file:read('a')

local h_template_file = io.open('scripts/templates/enemies_init_template.h')
local h_template = h_template_file:read('a')

local h_result = io.open('inc/enemies_init.h', 'w')
h_result:write( (h_template:gsub("// GHOST_COUNT //", "#define GHOST_COUNT " .. tostring(#ghosts))) )

local c_result = io.open('src/enemies_init.c', 'w')
c_result:write( (c_template:gsub("// GHOSTS INIT //", table.concat(c_code, "\n"))) )
