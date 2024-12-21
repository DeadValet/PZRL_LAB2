#ifndef M_H
#define M_H
int check (const char* string, const regex_t reegex);
void various (FILE* f, char* string, size_t strCount, char** strings);
char** RL(FILE * f, int * busyLines, int* totallines);
int replace(FILE* f, char* string, size_t str_count, char** strings);
int dlt(FILE* f, char* string, size_t strCount, char** strings);
void front(FILE* f, char* string, size_t str_count, char** strings);
void back(FILE* f, char* string, size_t str_count, char** strings);

#endif
