#pragma once
#include <stdio.h>
#include "Level.h"

//This is a loader for a custom file format - .catt
//It is a text file that consists of:
//player_starting_position={x, y};
//enemy_pos={x, y};
//enemy_sprite="enemy sprite location here";
//enemy_pattern={ chosen pattern };
//level_background="background sprite location here";

//Structure:
//keyword=value;

//player_starting_position, enemy_pos, enemy_pattern values
//need to be encased in curly braces {value} or {val1, val2}
 
//keywords: player_starting_position, enemy_pos, enemy_sprite, enemy_pattern, level_background
//x and y are given in pixels eg.
//player_starting_position={692, 530};
//Avaliable patterns: circle, complex, altsphere, custom1 (it's not limited to the "advanced enemies", there are 2 more, unused patterns) :)

class FileLoader{
public:
	FileLoader(const char* filename);
	~FileLoader();
	Vector<Vector<char*>> ParseFile();
	Level loadLevel();
private:
	void stripSpace(char* str);
	void stripWord(char* s);
	char* buffer;
	Vector<char*> splitWord(char* word, const char* delimiter);
};
