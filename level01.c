#include <nusys.h>
#include "2dlibrary.h"
#include "2dmap.h"
#include "level_shared.h"
#include "main.h"
#include "castle.h"
#include "level01.h"
#include "assets/music/all.h"

void initLevel_01() {
	Tile* tile;
	MapColumn* column;
	MapRow* button;
	MapRow* key;
	MapRow* door;
	MapRow* bigdoorleft;
	MapRow* bigdoorright;
	MapRow* trap1;
	MapRow* trap2;
	MapRow* lever;
	MapRow* barrel;
	MapRow* levelcompleted;
	
	//setTexturesCastle();
	setTexturesDungeon();
	setTexturesShared();
	setTexturesCharacters();
	
	my2D_loadTexture(&splash_screen, (u32)_SplashLevel01SegmentRomStart, (u32)_SplashLevel01SegmentRomEnd, 512, 395);
	
	loadRAMLevel(&game.level->map, (u32)_Level01SegmentRomStart, (u32)_Level01SegmentRomEnd);
	initMap(&map, game.level->map.width, game.level->map.width * game.level->map.height * 2, 300, 64, 64);

	setTiles();
	loadMap(&map);
	
	key = nextMapRow(&map, 8, &map.tiles[43]);
	appendMapRow(findMapColumn(&map, 59), key);
	
	button = nextMapRow(&map, 4, &map.tiles[41]);
	appendMapRow(findMapColumn(&map, 1), button);

	door = nextMapRow(&map, 56, &map.tiles[42]);
	appendMapRow(findMapColumn(&map, 34), door);
	button->related_row = door;
	
	bigdoorleft = nextMapRow(&map, 2, &map.tiles[40]);
	appendMapRow(findMapColumn(&map, 35), bigdoorleft);
	bigdoorright = nextMapRow(&map, 2, &map.tiles[62]);
	appendMapRow(findMapColumn(&map, 36), bigdoorright);
	bigdoorleft->related_row = bigdoorright;
	bigdoorright->related_row = bigdoorleft;
	
	trap1 = nextMapRow(&map, 10, &map.tiles[45]);
	appendMapRow(findMapColumn(&map, 61), trap1);
	trap2 = nextMapRow(&map, 10, &map.tiles[45]);
	appendMapRow(findMapColumn(&map, 62), trap2);
	
	lever = nextMapRow(&map, 54, &map.tiles[44]);
	appendMapRow(findMapColumn(&map, 55), lever);
	lever->related_row = trap1;
	trap1->related_row = trap2;
	
	
	bigdoorleft = nextMapRow(&map, 60, &map.tiles[40]);
	appendMapRow(findMapColumn(&map, 10), bigdoorleft);
	bigdoorright = nextMapRow(&map, 60, &map.tiles[62]);
	appendMapRow(findMapColumn(&map, 11), bigdoorright);
	bigdoorleft->related_row = bigdoorright;
	bigdoorright->related_row = bigdoorleft;
	
	barrel = nextMapRow(&map, 57, &map.tiles[46]);
	barrel->action = setRowToKey;
	appendMapRow(findMapColumn(&map, 13), barrel);
	
	column = findMapColumn(&map, 35);
	levelcompleted = findMapRow(column->first_row, 1);
	levelcompleted->over = level01End;
	column = findMapColumn(&map, 36);
	levelcompleted = findMapRow(column->first_row, 1);
	levelcompleted->over = level01End;
	
	sortMap(&map);
	game.character.side   = &game.character.front;
	// normal start position
	initMainCharacter(128, 3712, 255);
	
	
	//initMainCharacter(3264, 3392, 255);
	
	// test end game
	//initMainCharacter(2240, 256, 255);
	game.character.keys = 1;
	
	game.character.animation.border_x = game.level->map.width * map.column_width;
	game.character.animation.border_y = game.level->map.height * map.row_height;
	game.character.next = &characters[0];
	

	characters[0].keys			= 0;
	characters[0].x				= 240;
	characters[0].y				= 284;
	characters[0].move_x		= 0;
	characters[0].move_y		= 0;
	characters[0].state			= CHARACTER_IDLE;
	characters[0].life			= 255;
	characters[0].next			= NULL;
	characters[0].previous		= &game.character;
	characters[0].collision		= testCollisionFeet;
	characters[0].back.dead    = (AnimatedSprite){&texture[82], 48, 64,  5, 1};
	characters[0].back.attack  = (AnimatedSprite){&texture[84], 48, 64,  5, 0};
	characters[0].back.defend  = (AnimatedSprite){&texture[84], 48, 64,  5, 1};
	characters[0].back.hurt    = (AnimatedSprite){&texture[84], 48, 64,  5, 1};
	characters[0].back.idle    = (AnimatedSprite){&texture[83], 48, 64,  5, 1};
	characters[0].back.walk    = (AnimatedSprite){&texture[84], 48, 64,  5, 1};
	characters[0].front.dead   = (AnimatedSprite){&texture[85], 64, 64,  5, 0};
	characters[0].front.attack = (AnimatedSprite){&texture[87], 64, 64,  5, 0};
	characters[0].front.defend = (AnimatedSprite){&texture[87], 64, 64,  5, 1};
	characters[0].front.hurt   = (AnimatedSprite){&texture[87], 64, 64,  5, 1};
	characters[0].front.idle   = (AnimatedSprite){&texture[86], 64, 64,  5, 1};
	characters[0].front.walk   = (AnimatedSprite){&texture[87], 64, 64,  5, 1};
	characters[0].left.dead    = (AnimatedSprite){&texture[88], 96, 38,  5, 0};
	characters[0].left.attack  = (AnimatedSprite){&texture[90], 96, 38,  5, 0};
	characters[0].left.defend  = (AnimatedSprite){&texture[90], 96, 38,  5, 1};
	characters[0].left.hurt    = (AnimatedSprite){&texture[90], 96, 38,  5, 1};
	characters[0].left.idle    = (AnimatedSprite){&texture[89], 96, 38,  5, 1};
	characters[0].left.walk    = (AnimatedSprite){&texture[90], 96, 38,  5, 1};
	characters[0].right.dead   = (AnimatedSprite){&texture[91], 96, 38,  5, 0};
	characters[0].right.attack = (AnimatedSprite){&texture[93], 96, 38,  5, 0};
	characters[0].right.defend = (AnimatedSprite){&texture[93], 96, 38,  5, 1};
	characters[0].right.hurt   = (AnimatedSprite){&texture[93], 96, 38,  5, 1};
	characters[0].right.idle   = (AnimatedSprite){&texture[92], 96, 38,  5, 1};
	characters[0].right.walk   = (AnimatedSprite){&texture[93], 96, 38,  5, 1};
	characters[0].side   = &characters[0].left;
	characters[0].animation.sprite       = &characters[0].left.walk;
	characters[0].animation.frame        = 0;
	characters[0].animation.x            = 0;
	characters[0].animation.y            = 0;
	characters[0].animation.is_character = 0;
	characters[0].back.collision         = NULL;
	characters[0].front.collision        = NULL;
	characters[0].left.collision         = ratCollisionLeft;
	characters[0].right.collision        = ratCollisionRight;
	characters[0].back.action            = NULL;
	characters[0].front.action           = NULL;
	characters[0].left.action            = NULL;
	characters[0].right.action           = NULL;
	characters[0].back.push            = NULL;
	characters[0].front.push           = NULL;
	characters[0].left.push            = NULL;
	characters[0].right.push           = NULL;
	
	loadAudio((u32)_MusicAllPtrSegmentRomStart, (u32)_MusicAllPtrSegmentRomEnd, (u32)_MusicAllSfxSegmentRomStart, (u32)_MusicAllSfxSegmentRomEnd, _MusicAllWbkSegmentRomStart);
	
	music_tracks[0] = (MusicTrack){FX_EVILMARC, 71, 0, &music_tracks[1]};
	music_tracks[1] = (MusicTrack){FX_DANGER, 58, 0, &music_tracks[2]};
	music_tracks[2] = (MusicTrack){FX_SUPERNAT, 52, 0, &music_tracks[0]};
	music_tracks[3] = (MusicTrack){FX_DISCOVER, 15, 0, NULL};
	current_music = &music_tracks[3];
}

void level01End(MapRow* row) {
	// back to start menu ?
	stopMusic();
	my2D_loadTexture(&splash_screen, (u32)_SplashEndSegmentRomStart, (u32)_SplashEndSegmentRomEnd, 512, 395);
	
	game.level->loadControls = NULL;
	game.level->drawScreen = drawSplash;
	current_music = &music_tracks[3];
	
	/*game.level = &levels[2];
	game.state = GAMESTATE_LOADING;*/
	freeMap(&map);
}
