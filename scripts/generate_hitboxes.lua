--[[
  This script is a port from `get_regions` method from
  `csv_tilemap` code of "irene" game framework, by André Luiz Alvares.
  https://github.com/Andre-LA/irene/blob/master/irene/utils/csv_tilemap.nelua

  Copyright (c) 2020-present André Luiz Alvares
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
]]

local TILE_SIZE = 8
local tiledfile = require 'res.tiled.objects'

local function get_matrix()
  local tilelayer = tiledfile.layers[1]

  local is_surface = {}
  for _, v in ipairs({9, 10, 11, 12, 13, 17, 18, 19, 20, 21, 22, 29, 30}) do
    is_surface[v] = true
  end

  for i, v in ipairs(tilelayer.data) do
    if not is_surface[v] then
      tilelayer.data[i] = 0
    end
  end
  
  local csv = tilelayer.data
  
  local matrix = {}

  for i = 1, tilelayer.height do
    table.insert(matrix, {})
    
    for j = 1, tilelayer.width do
      local idx = j + (i-1)*56
      table.insert(matrix[i], csv[idx] ~= 0)
    end
  end

  return matrix
end

local function print_matrix(matrix, x, y)
  x = x or -1
  y = y or -1

  for i, line in ipairs(matrix) do
    for j, tile in ipairs(line) do
      local n = ' '
      
      if i == y and j == x then
        n = '#'
      elseif tile then
        n = 'x'
      end
      
      io.write(n)
    end
    print(' --> ' .. tostring(i))
  end
end

local function matrix_to_regions(matrix)
  local function mtx_width()
    local first_line = matrix[1]
    return #first_line
  end

  local function mtx_height()
    return #matrix
  end

  local function new_region(x, y, w, h)
    assert(type(x) == 'number')
    assert(type(y) == 'number')
    assert(type(w) == 'number')
    assert(type(h) == 'number')
    return { x=x, y=y, w=w, h=h }
  end

  local function new_empty_region()    return new_region(0, 0, 0, 0) end
  local function new_unit_region(x, y) return new_region(x, y, 1, 1) end

  local regions = {}
  local current_region = new_empty_region()
  local prev_cell, next_cell = false, false

  local function reset_state()
    prev_cell = 0
    current_region = new_empty_region()
  end

  local function push_region()
    if current_region.w > 1 or current_region.h > 1 then
      table.insert(regions, current_region)
    end

    reset_state()
  end

  local function collect_body(x, y, direction)
    local growing_axis = direction == 'horizontal' and x or y
    local growing_dimension = direction == 'horizontal' and 'w' or 'h'

    local cell = matrix[y][x]
    local is_last_cell = x == mtx_width() and y == mtx_height()

    local is_first_column = growing_axis == 0
    if prev_cell and is_first_column then
      push_region()
    end

    if cell then
      if prev_cell then
        current_region[growing_dimension] = current_region[growing_dimension] + 1
        matrix[y][x] = false
      else
        current_region = new_region(x, y, 1, 1)
        if next_cell then
          matrix[y][x] = false
        end
      end

      if is_last_cell then
        push_region()
      end
    else
      if prev_cell then
        push_region()
      end
    end

    prev_cell = cell
  end

  for y = 1, mtx_height() do
    for x = 1, mtx_width() do
      next_cell = y < mtx_width() and matrix[y][x+1] or false
      collect_body(x, y, 'horizontal')
    end
  end

  reset_state()

  for x = 1, mtx_width() do
    for y = 1, mtx_height() do
      next_cell = y < mtx_height() and matrix[y+1][x] or false
      collect_body(x, y, 'vertical')
    end
  end

  for y = 1, mtx_height() do
    for x = 1, mtx_width() do
      if matrix[y][x] then
        table.insert(regions, new_unit_region(x, y))
      end
    end
  end

  return regions
end

local matrix = get_matrix()
local regions = matrix_to_regions(matrix)

local generated_src = {}
for i, region in ipairs(regions) do
  local entry = string.format(
    '  { .x = %d, .y = %d, .w = %d, .h = %d }, /* %d */',
    (region.x-1) * TILE_SIZE,
    (region.y-1) * TILE_SIZE,
    region.w * TILE_SIZE,
    region.h * TILE_SIZE, 
    i
  )
  table.insert(generated_src, entry)
end
generated_src = table.concat(generated_src, '\n')

local template_file <close> = io.open('scripts/templates/hitboxes_template.h')
local template = template_file:read('a')

local result = template:gsub('// HITBOXES ARRAY //', generated_src)
                       :gsub('// HB_COUNT //', '#define HB_COUNT ' .. tostring(#regions))

local out_file <close> = io.open('inc/hitboxes.h', 'w')
out_file:write(result)
