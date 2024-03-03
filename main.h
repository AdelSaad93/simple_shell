#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define out -3

extern char **environme;
char *name;
int histo;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dirctor: A dirctorory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dirctor;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **myargs);
} builtin_t;

/**
 * struct names - A new struct defining names.
 * @name: The name of the name.
 * @value: The value of the name.
 * @next: A pointer to another struct names.
 */
typedef struct names
{
	char *name;
	char *value;
	struct names *next;
} name_t;

name_t *names;

ssize_t getrange(char **rangeptr, size_t *m, FILE *flow);
void *reallocte(void *pointer, unsigned int oldsize, unsigned int newsize);
char **stringtoken(char *range, char *delimiter);
char *get_location(char *command);
list_t *getpathdirctorector(char *path);
int execute(char **myargs, char **forehead);
void freelist(list_t *head);
char *intostr(int number);

void handle_range(char **range, ssize_t read);
void myvariable_replacement(char **myargs, int *exe_myret);
char *get_myargs(char *range, int *exe_myret);
int call_myargs(char **myargs, char **forehead, int *exe_myret);
int run_myargs(char **myargs, char **forehead, int *exe_myret);
int handle_myargs(int *exe_myret);
int check_myargs(char **myargs);
void free_myargs(char **myargs, char **forehead);
char **replace_names(char **myargs);

int stringlength(const char *s);
char *stringconcatenate(char *dest, const char *src);
char *stringnconcatenate(char *dest, const char *src, size_t n);
char *stringcopy(char *dest, const char *src);
char *stringcharacter(char *s, char c);
int stringsubstring(char *s, char *accept);
int stringcompare(char *s1, char *s2);
int stringncompare(const char *s1, const char *s2, size_t n);

int (*get_builtin(char *command))(char **myargs, char **forehead);
int simpleshell_out(char **myargs, char **forehead);
int simpleshell_environme(char **myargs, char  **forehead);
int simpleshell_setenviro(char **myargs);
int simpleshell_unsetenviro(char **myargs);
int simpleshell_cd(char **myargs);
int simpleshell_name(char **myargs);
int simpleshell_aid(char **myargs);


char **_copyenviro(void);
void free_enviro(void);
char **getenviro(const char *myvar);

int create_fault(char **myargs, int fau);
char *fault_enviro(char **myargs);
char *fault_1(char **myargs);
char *fault_2_out(char **myargs);
char *fault_2_cd(char **myargs);
char *fault_2_syn(char **myargs);
char *fault_404(char **myargs);
char *fault_505(char **myargs);

name_t *addnameend_end(name_t **forehead, char *name, char *value);
void freenamelist(name_t *head);
list_t *addnodeend(list_t **forehead, char *dirctor);
void freelist(list_t *forehead);

void aid_all(void);
void aid_name(void);
void aid_cd(void);
void aid_out(void);
void aid_aid(void);
void aid_enviro(void);
void aid_setenviro(void);
void aid_unsetenviro(void);
void aid_histo(void);

int process_file_commands(char *file_path, int *exe_myret);

#endif

