#ifndef _SHELL_INTERFACE_H_
#define _SHELL_INTERFACE_H_
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#define DECIPHER_BUF_EXTENT 1024
#define CRAFT_BUF_EXTENT 1024
#define BUF_PURGE -1

#define CLI_CUSTOM 0
#define CLI_OR 1
#define CLI_AND 2
#define CLI_LINK 3

#define TRANSPOSE_MINISCULE 1
#define TRANSPOSE_NON_NEGATIVE 2

#define HARNESS_FGETS 0
#define HARNESS_STRSEP 0

#define HIST_RECORD ".simple_shell_history"
#define HIST_PEAK 4096
extern char **environ;

/**
 *struct strandlist - linked list
 *@num: num field
 *@str: string
 *@next: pointer to next nexus
 */
typedef struct strandlist
{
	int num;
	struct strandlist *next;
	char *str;
} index_t;

/**
 *struct passdata - contains variables
 *@histcount: chronicle number count
 *@arg: argument
 *@readfd: file descriptor from which to read
 *@argv: argument vector
 *@cmd_buf_type: command type
 *@path: array of strings
 *@cmd_buf: pointer address
 *@argc: argument count
 *@status: return value of last command
 *@line_count: error count
 *@env_changed: on if environ was altered
 *@err_num: error code
 *@alias: alias nexus
 *@linecount_flag: count line if on
 *@history: chronicle nexus
 *@fname: app file name
 *@environ: modified copy of environ
 *@env: linked list
 */
typedef struct passdata
{
	char *arg;
	int histcount;
	char **argv;
	int readfd;
	char *path;
	int cmd_buf_type;
	char *fname;
	int status;
	char **cmd_buf;
	int argc;
	char **environ;
	int env_changed;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	index_t *history;
	index_t *env;
	index_t *alias;
} insight_t;
#define DATA_INIT \
{NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0, \
	NULL, NULL, NULL}
/**
 *struct embedded - contains builtin string
 *@type: cmd flag
 *@func: function
 */
typedef struct embedded
{
	int (*func)(insight_t);
	char *type;
} embedded_table;

/* shell_iteration.c */
int hash_table(insight_t *, char **);
int find_native(insight_t *);
void find_prompt(insight_t *);
void fork_prompt(insight_t *);

/* decoder.c */
int is_prompt(insight_t *, char *);
char *dup_glyphs(char *, int, int);
char *find_route(insight_t *, char *, char *);

/* flaws.c */
void _eprints(char *);
int _eputc(char);
int _depictfd(char, int);
int _depictsfd(char *, int);

/* character_sequence.c */
int strand_length(char *);
int strand_compare(char *, char *);
char *embarks_with(const char *, const char *);
char *strand_concat(char *, char *);

/* character_sequence1.c */
char *strand_copy(char *, char *);
char *strand_duplicate(const char *);
void output_string(char *);
int output_symbols(char);

/* cease.c */
char *_strandclone(char *, char *, int);
char *_strandcat(char *, char *, int);
char *_strandchar(char *, char);

/* lexical_analyzer */
char **segmentwords(char *, char *);
char **segmentwords2(char *, char);

/* resize.c */
char *_populate(char *, char, unsigned int);
void liberate_string(char **);
void *_reshape(void *, unsigned int, unsigned int);

/* storage.c */
int bcrisp(void **);

/* sscanf.c */
int responsive(insight_t *);
int is_divider(char, char *);
int is_letterset(int);
int parsefloat(char *);

/* flaws1.c */
int _errstrtol(char *);
void print_flaw(insight_t *, char *);
int output_d(int, int);
char *transpose_number(long int, int, int);
void oust_comments(char *);

/* native.c */
int _myleave(insight_t *);
int _myworkingdir(insight_t *);
int _mysupport(insight_t *);

/* native1.c */
int my_record(insight_t *);
int my_sobriquet(insight_t *);

/* strand.c */
ssize_t get_dataentry(insight_t *);
int _getstrand(insight_t *, char **, size_t *);
void interrupt_handler(int);

/* insight.c */
void clear_insight(insight_t *);
void set_insight(insight_t *, char **);
void free_insight(insight_t *, int);

/* context.c */
char *_getctxt(insight_t *, const char *);
int _myctxt(insight_t *);
int _mysetctxt(insight_t *);
int _myunsetctxt(insight_t *);
int inhabit_ctxt_list(insight_t *);

/* ambiance.c */
char **get_context(insight_t *);
int unset_ambiance(insight_t *, char *);
int set_ambiance(insight_t *, char *, char *);

/* record.c */
char *get_recordfile(insight_t *);
int write_record(insight_t *);
int decipher_record(insight_t *);
int fabricate_recordlist(insight_t *, char *, int);
int reorder_record(insight_t *);

/* catalog.c */
index_t *append_nexus(index_t **, const char *, int);
index_t *append_nexus_end(index_t **, const char *, int);
size_t output_catalog_str(const index_t *);
int eradicate_catalog_at_indicator(index_t **, unsigned int);
void free_catalog(index_t **);

/* catalog1.c */
size_t catalog_extent(const index_t *);
char **catalog_to_strands(index_t *);
size_t output_catalog(const index_t *);
index_t *nexus_commences_with(index_t *, char *, char);
ssize_t acquire_nexus_indicator(index_t *, index_t *);

/* attribute.c */
int is_link(insight_t *, char *, size_t *);
void validate_link(insight_t *, char *, size_t *, size_t, size_t);
int replace_sobriquet(insight_t *);
int replace_parameter(insight_t *);
int replace_strand(char **, char *);

#endif
