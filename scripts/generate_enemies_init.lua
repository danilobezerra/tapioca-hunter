local c_template_file = io.open('scripts/templates/enemies_init_template.c')
local c_template = c_template_file:read('a')

local h_template_file = io.open('scripts/templates/enemies_init_template.h')
local h_template = h_template_file:read('a')

local h_result = io.open('inc/enemies_init.h', 'w')
h_result:write(h_template)

local c_result = io.open('src/enemies_init.c', 'w')
c_result:write(c_template)
