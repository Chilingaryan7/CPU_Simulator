#ifndef HEADER 
#define HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <poll.h>
#include <sys/mman.h>

#define RAM_SIZE 64
#define REG_COUNT 7
#define CMD_LINE_SIZE 128
#define REGS_NAME_COUNT 9
#define CMD_PART_COUNT 4
#define CMD_PART_SIZE 16

typedef struct regs{
    int regs[REG_COUNT];
    int WSR;
    int RIP;
    int RAM[RAM_SIZE];
}regs_t;

typedef enum opr_status {VALID, INVALID} opr_stat;

void pop_regs(int);
void push_regs(void);
void wrong_cmd_msg(void);
int is_number(char *);
#endif