#include "header.h"
extern regs_t memory;
extern char command_line[CMD_LINE_SIZE];
extern int data_base_fd;

void push_regs(){
    struct pollfd fds[1];  
    fds[0].fd = data_base_fd;  
    fds[0].events = POLLOUT;
    int timeout = 1000;
    int res = poll(fds, 1, timeout);
        if(res < 0){
            perror("push_regs poll error: ");
            exit(EXIT_FAILURE);
        }
        else if(!res){
            printf("push_regs poll timeout\n");
            return;
        }
        else if(res > 0){
                if (fds[0].revents & POLLOUT){
                lseek(data_base_fd, 0, SEEK_END);
                   if (write(data_base_fd, &memory, sizeof(regs_t)) < sizeof(regs_t)){
                        perror("push_regs write error: ");
                        exit(EXIT_FAILURE);
                    }
                }    
                fsync(data_base_fd);
            }
    return;        
}
void pop_regs(int index){
    int count = memory.RIP - index;
    if(count < 1){
        printf("invalid operand\n");
        return;
    }
    struct pollfd fds[1];  
    fds[0].fd = data_base_fd;  
    fds[0].events = POLLIN;
    int timeout = 1000;
    int res = poll(fds, 1, timeout);
        if(res < 0){
            perror("pop_regs poll error: ");
            exit(EXIT_FAILURE);
        }
        else if(!res){
            printf("pop_regs poll timeout\n");
            return;
        }
        else if(res > 0){
                if (fds[0].revents & POLLIN){
                ftruncate(data_base_fd, count * sizeof(regs_t));
                lseek(data_base_fd, -(sizeof(regs_t)) , SEEK_END);
                   if (read(data_base_fd, &memory, sizeof(regs_t)) < sizeof(regs_t)){
                        perror("pop_regs read error: ");
                        exit(EXIT_FAILURE);
                    }
                }    
                fsync(data_base_fd);
            }
    return;        
}


void wrong_cmd_msg(){
    printf("Invalid instruction\n");
    return;
}

int is_number(char * str){
    while (*str){
         if (*str < '0' || *str > '9'){
                return 0;
         }
         ++str;
    }
    return 1;
}