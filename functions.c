#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <regex.h>

int check (const char* string, const regex_t reegex) {
	
	int value;
	value = regexec(&reegex, string, 0, NULL, 0);

	if (value == 0) {
		return 1;
	}
	else if (value == REG_NOMATCH) { 
		return 0;
	}
	else {

		return 0;
	}
}

char ** RL(FILE * f, int* busyLines, int* totalLines) {

        char* buffer = NULL;
        size_t buflen = 0;
        int busyCount = 0;
        int allocCount = *totalLines;

	char ** strings = (char**) calloc(sizeof(char*), allocCount);
    	for (int i = 0; i < allocCount; i++) {
		strings[i] = NULL;
	}

        while (!feof(f)) {
                int cnt = getline(&buffer, &buflen, f);
                if (cnt < 0) {
                        free(buffer);
			break;
                }
                if (busyCount == allocCount) {
                        allocCount = allocCount * 2;
                        strings = (char**) realloc(strings, sizeof(char*) * allocCount);
                        for (int i = busyCount; i < allocCount; i++) {
                                strings[i] = NULL;
                        }
                }
                strings[busyCount] = strdup(buffer);
                busyCount++;
		free(buffer);
        	buflen = 0;
        	buffer = NULL;
        }
	*busyLines = busyCount;
	*totalLines = allocCount;
	return strings;
}

int replace(FILE* f, char* string, size_t strCount, char** strings) {
	return 0;
}

int dlt(FILE* f, char* string, size_t strCount, char** strings) {
        
	int flag = -1;
	
	regex_t reegex;
        regcomp(&reegex, "^/[^/]+/", REG_EXTENDED);
        regmatch_t pmatch[1];
        regexec(&reegex, string, 1, pmatch, 0);
        char* toDel = (char*) calloc(sizeof(char), (pmatch[0].rm_eo - pmatch[0].rm_so - 2));
        int index = 0;
        for (int i = pmatch[0].rm_so + 1; i < pmatch[0].rm_eo - 1; ++i) {
                toDel[index] = string[i];
                ++index;
        }
	
	pmatch[0].rm_so = 0;
	pmatch[0].rm_eo = 0;
        regex_t reegex1;
        regcomp(&reegex1, toDel, REG_EXTENDED);

	for (size_t i = 0; i < strCount; ++i) {	
		if (regexec(&reegex1, strings[i], 1, pmatch, 0) == 0) {
			flag = 0;
			for (int j = 0; j < pmatch[0].rm_so; ++j) {
				fprintf(f, "%c", strings[i][j]);
			}
			for (int j = pmatch[0].rm_eo + 1; j < strlen(strings[i]); ++j) {
				fprintf(f, "%c", strings[i][j]);
			}
		}
		else {
			fprintf(f, "%s", strings[i]);
		}
	}
	return 0;
}

void front(FILE* f, char* string, size_t strCount, char** strings) {
        regex_t reegex;
        regcomp(&reegex, "/[^/]+/$", REG_EXTENDED);
        regmatch_t pmatch[1];
        regexec(&reegex, string, 1, pmatch, 0);
        char* new_text = (char*) calloc(sizeof(char), (pmatch[0].rm_eo - pmatch[0].rm_so - 2));
        int index = 0;
        for (int i = pmatch[0].rm_so + 1; i < pmatch[0].rm_eo - 1; ++i) {
                new_text[index] = string[i];
                ++index;
        }
	for (size_t i = 0; i < strCount; ++i) {
		fprintf(f, "%s%s", new_text, strings[i]);
	}
}

void back(FILE* f, char* string, size_t strCount, char** strings) {
        regex_t reegex;
        regcomp(&reegex, "/[^/]+/$", REG_EXTENDED);
        regmatch_t pmatch[1];
        regexec(&reegex, string, 1, pmatch, 0);
        char* new_text = (char*) calloc(sizeof(char), (pmatch[0].rm_eo - pmatch[0].rm_so - 2));
        int index = 0;
        for (int i = pmatch[0].rm_so + 1; i < pmatch[0].rm_eo - 1; ++i) {
                new_text[index] = string[i];
                ++index;
        }
        for (size_t i = 0; i < strCount; ++i) {
		strings[i][strlen(strings[i]) - 1] = '\0';
                fprintf(f, "%s%s\n", strings[i], new_text);
        }
}

void various(FILE* f, char* string, size_t strCount, char** strings) {
        regex_t regexReplace;
        regcomp(&regexReplace, "^s/[^/\\^]+/[^/]+/$", REG_EXTENDED);

        regex_t regexDelete;
        regcomp(&regexDelete, "^/[^/]+/d$", REG_EXTENDED);

        regex_t regexFront;
        regcomp(&regexFront, "^s/\\^/[^/]+/$", REG_EXTENDED);

        regex_t regexBack;
        regcomp(&regexBack, "^s/\\$/[^]+/$", REG_EXTENDED);


        if (check(string, regexReplace) == 1) {
                printf("replace");
        }
        else if (check(string, regexDelete) == 1) {
                int dlt(FILE* f, char* string, size_t strCount, char** strings);
        }
        else if (check(string, regexFront) == 1) {
                void front(FILE* f, char* string, size_t strCount, char** strings);
        }
        else if (check(string, regexBack) == 1) {
                void back(FILE* f, char* string, size_t strCount, char** strings);
        }
        else {
                printf("Неизвестная команда");
        }
}
