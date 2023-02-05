IMAGE splash "images/splash.png" FAST
IMAGE title "images/logo.png" FAST
TILESET game_tileset "tiled/game_ts.tsx"
PALETTE game_pal "tiled/tileset.png"
MAP gamemap "tiled/map.tmx" bg
MAP foremap "tiled/map.tmx" fg
SPRITE player_sprite "sprites/char_01.png" 2 2 BEST
SPRITE ghost_sprite "sprites/fantasma01.png" 2 2 BEST
SPRITE tapioca_sprite "sprites/tapioca01.png" 2 2 BEST
XGM main_menu_bgm "music/title.vgm" -1
XGM gameplay_bgm "music/play.vgm" -1
XGM ending_bgm "music/ending.vgm" -1
IMAGE lose_screen "images/game over.png" FAST
IMAGE win_screen "images/vencedor.png" FAST
WAV sfx_enter "sfx/enter.wav" 5
WAV sfx_attack "sfx/attack.wav" 5
WAV sfx_eat "sfx/eat.wav" 5
WAV sfx_jump "sfx/jump.wav" 5
WAV sfx_walk "sfx/walk.wav" 5
