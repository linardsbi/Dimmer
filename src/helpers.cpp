#include <Arduino.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "helpers.hpp"

const char RED[] = "red";
const char GREEN[] = "green";
const char BLUE[] = "blue";

void pushNumber(char* arr, const char newChar, uchar queuedCount) {
	uchar length = LENGTH_VALUE; // strlen(arr) returns 0 on arduino nano for some reason, gcc on desktop works fine
	assert(length > queuedCount);
	
	while (queuedCount != 0) {
		arr[length - queuedCount - 1] = arr[length - queuedCount];
		queuedCount--;
	}
	
	arr[length - 1] = newChar;
}

bool isColor(const char* left, const char* right) {
	size_t leftLen = strlen(left);
	size_t rightLen = strlen(right);
	size_t i = 0;
	
	while ((left[i] != '0' || right[i] != '0') && (i < leftLen && i < rightLen)) {
		if (left[i] != right[i]) return false;
		i++;
	}
	
	return true;
}

void parseColors(const char* input, char* colors) {
	size_t inputLength = strlen(input);
	assert(inputLength < 256);
	
	char colorName[LENGTH_COLOR] = {0};
	char colorVal[LENGTH_VALUE] = {0};
	uchar nameLength = 0;
	uchar colorLength = 0;
	uchar commaCount = 0;
	
	for (uchar i = 0; i < inputLength; i++) {
		if (input[i] == ',') {
			char colorP = 0;
			
			if (isColor(colorName, RED)) {
				colorP = OFFSET_RED;
			} else if (isColor(colorName, GREEN)) {
				colorP = OFFSET_GREEN;
			} else if (isColor(colorName, BLUE)) {
				colorP = OFFSET_BLUE;
			} else if (commaCount == 0) {
				colorP = OFFSET_RED;
			} else if (commaCount == 1) {
				colorP = OFFSET_GREEN;
			} else if (commaCount == 2) {
				colorP = OFFSET_BLUE;
			}
			
			for (uchar j = 0; j < LENGTH_VALUE; j++) {
				colors[colorP + j] = isdigit(colorVal[j]) ? colorVal[j] : '0';
			}
			
			memset(colorName, '0', LENGTH_COLOR);
			memset(colorVal, '0', LENGTH_VALUE);
			
			nameLength = 0;
			colorLength = 0;
			
			commaCount++;
		} else if (input[i] == ':') {
			// skip
		} else if (isalpha(input[i])) {
			colorName[nameLength] = input[i];
			nameLength++;
		} else if (isDigit(input[i])) {
			pushNumber(colorVal, input[i], colorLength);
			colorLength++;
		}
	}
	
	//delete [] colorName;
	//delete [] colorVal;
}

/* for testing 
int main() {
	
	std::string ogStr = "1,2,3";
	for (auto& str: strSplit(ogStr, "3")) {
		for (int i = 0; i < str.length(); i++) {
			printf("%c", str[i]);
		}
		printf("_");
	}
	
	const char ogStr[] = "green:255,";
	uchar newStr[] = "000000000";
	
	size_t length = 0;
	
	parseColors(ogStr, newStr);
	
	for (size_t i = 0; i < 9; i++) {
		printf("%c", newStr[i]);
	}
	
	delete newStr;
}
*/