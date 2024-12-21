#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char **argv){
	
	if (argc < 3) {
		printf("недостаточно аргументов");
	}
	FILE* f;
	f = fopen(argv[1], "r");
	if (f == NULL) {
		printf("Указанный файл не найден");
		return -1;
	}

	regex_t regexReplace;
	regcomp(&regexReplace, "^s/.*/.*/$", REG_EXTENDED);

	regex_t regexDelete;
	regcomp(&regexDelete, "^/.*/d$", REG_EXTENDED);

	regex_t regexFront;
	regcomp(&regexFront, "^s/\\^/.*/$", REG_EXTENDED);

	regex_t regexBack;
	regcomp(&regexBack, "^s/\\$/.*/$", REG_EXTENDED);

	char** strings = NULL;
	int busyCount = 0;
	int totalLines = 3;

	strings = RL(f, &busyCount, &totalLines);
	fclose(f);

	f = fopen(argv[1], "w");
	
	if (check(argv[2], regexFront) == 1) {
		front(f, argv[2], busyCount, strings);
	}
	if (check(argv[2], regexBack) == 1) {
		back(f, argv[2], busyCount, strings);
	}

    	fclose(f);

    	return 0;
}
