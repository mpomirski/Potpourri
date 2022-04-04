#include <string.h>
#include "FileLoader.h"
#include "vector.h"

//Loads file contents into this->buffer
FileLoader::FileLoader(const char* filename) {
	long lSize;
	char ch;
	FILE* file;
	size_t result;

	file = fopen(filename, "r");
	if (file == NULL) { fputs("File error", stderr); exit(1); }
	fseek(file, 0, SEEK_END);
	lSize = ftell(file);
	rewind(file);

	buffer = (char*)malloc(sizeof(char) * lSize);
	int i = 0;
	while ((ch = fgetc(file)) != EOF) {
		buffer[i] = ch;
		i++;
	}
	buffer[i] = '\0';
	fclose(file);
}

FileLoader::~FileLoader() {
	free(buffer);
}

Level FileLoader::loadLevel() {
	Vector2D player_position;
	Vector2D enemy_position;
	const char* enemy_pattern;
	const char* enemy_background;
	const char* level_background;

	Vector<Vector<char*>> word_list = ParseFile();
	for (int i = 0; i < word_list.getLength(); i++) {
		for (int j = 0; j < word_list[i].getLength(); j++) {
			if (!strcmp(word_list[i][j], "player_starting_position") || !strcmp(word_list[i][j], "\nplayer_starting_position")) {
				char* pos = word_list[i][j + 1];
				stripSpace(pos);
				stripWord(pos);
				Vector<char*> words = splitWord(pos, ",");
				float posx = atof(words[0]);
				float posy = atof(words[1]);
				player_position = { posx, posy };
			}
			else if (!strcmp(word_list[i][j], "\nenemy_pos") || !strcmp(word_list[i][j], "enemy_pos")) {
				char* pos = word_list[i][j + 1];
				stripSpace(pos);
				stripWord(pos);
				Vector<char*> words = splitWord(pos, ",");
				float posx = atof(words[0]);
				float posy = atof(words[1]);
				enemy_position = { posx, posy };
			}
			else if (!strcmp(word_list[i][j], "\nenemy_pattern") || !strcmp(word_list[i][j], "enemy_pattern")) {
				char* pattern = word_list[i][j + 1];
				stripSpace(pattern);
				stripWord(pattern);
				enemy_pattern = pattern;
			}
			else if (!strcmp(word_list[i][j], "\nlevel_background") || !strcmp(word_list[i][j], "level_background")) {
				char* bg = word_list[i][j + 1];
				stripSpace(bg);
				stripWord(bg);
				level_background = bg;
			}
			else if (!strcmp(word_list[i][j], "\nenemy_sprite") || !strcmp(word_list[i][j], "enemy_sprite")) {
				char* sp = word_list[i][j + 1];
				stripSpace(sp);
				stripWord(sp);
				enemy_background = sp;
			}
		}
	}
	Vector<Vector2D> enemypos;
	enemypos.push(enemy_position);

	Vector<const char *> enemypat;
	enemypat.push(enemy_pattern);

	Level* level = new Level(player_position, enemy_background, enemypos, level_background, enemypat);
	return *level;
}

//Removes all spaces from a given string(char array)
void FileLoader::stripSpace(char* str) {
	char* ret = str;
	do {
		if (*ret != ' ')
			*str++ = *ret;
	} while (*ret++ != '\0');
}

//Removes first and last letter from a given string(char array)
void FileLoader::stripWord(char* s) {
	memmove(s, s + 1, strlen(s + 1) + 1);
	s[strlen(s)-1] = '\0';
}

//Parses input file(.catt)
Vector<Vector<char*>> FileLoader::ParseFile() {
	Vector<Vector<char*>> return_vec;
	Vector<char*> lines;
	lines = splitWord(buffer, ";");
	for (int i = 0; i < lines.getLength(); i++) {
		Vector<char*> word_parts;
		word_parts = splitWord(lines[i], "=");
		return_vec.push(word_parts);
	}
	return return_vec;
}

//Splits a char array word by given delimiter, returns a Vector containing the subdivisions
Vector<char*> FileLoader::splitWord(char* word, const char* delimiter) {
	Vector<char*> words;
	char* token;
	if ((token = strtok(word, delimiter)) != NULL) {
		words.push(token);
		while ((token = strtok(NULL, delimiter)) != NULL) {
			words.push(token);
		}
	}
	return words;
}