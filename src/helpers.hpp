typedef unsigned char uchar;

enum {
	OFFSET_RED = 0,
	OFFSET_GREEN = 3,
	OFFSET_BLUE = 6,
	LENGTH_COLOR = 5,
	LENGTH_VALUE = 3,
};

void parseColors(const char* input, char* colors);