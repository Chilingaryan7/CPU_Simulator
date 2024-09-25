#include "header.h"

regs_t memory;
char command_line[CMD_LINE_SIZE] = {0};
int data_base_fd = 0;

int main(){
    char command_parts[CMD_PART_COUNT][CMD_PART_SIZE];
    const  char * regs_name[REGS_NAME_COUNT] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "WSR", "RIP",};
    data_base_fd = open("data_base.txt", O_CREAT | O_RDWR | O_TRUNC | O_SYNC, 0644);
        if (data_base_fd < 0) {
            perror("open error: ");
            exit(EXIT_FAILURE);
        }
    while(1){
        fflush(stdin);
        scanf("%s", command_line);
        if(!strcmp(command_line, "START") || !strcmp(command_line, "start")){
            memory.WSR = 1;
            memory.RIP = 1;
            push_regs();
            break;
        }
        else {
            printf("Enter START\n");
        }
    }
    fflush(stdin);
    printf("Hello this is CPU simulator, you hane this commands: ADD, SUB, MOV, LOAD, STORE, START, EXIT, DISC, LAYO\n");
    while(1){
        opr_stat opr1 = INVALID;
        opr_stat opr2 = INVALID;
        opr_stat opr3 = INVALID;

        int opr1_reg_ind = -1;
        int opr2_reg_ind = -1;
        int opr3_reg_ind = -1;
        for(int i = 0; i < CMD_PART_COUNT; ++i){
            memset(command_parts[i],0,CMD_PART_SIZE);
        }
        int tokens_count = 0;
        fgets(command_line, CMD_LINE_SIZE - 2, stdin); // -2 for /n and /o
        command_line[strlen(command_line) - 1] = '\0';
        fflush(stdin);
        char * token = strtok(command_line, " ,");
        while(token){
            strncpy(command_parts[tokens_count++], token, CMD_PART_SIZE - 1); // -1 for /0
            token = strtok(NULL, " ,");
            fflush(stdout);
        }

                if(!strcmp(command_parts[0], "MOV") || !strcmp(command_parts[0], "mov")){
                    if(tokens_count != 3){
                       wrong_cmd_msg();
                        continue; 
                    }
                        for(int i = 0; i < REG_COUNT; ++i){
                                if(!strcmp(command_parts[1],regs_name[i])){
                                    opr1 = VALID;
                                    opr1_reg_ind = i;
                                    break;
                                }
                            } 
                           
                if(opr1 == INVALID){
                    wrong_cmd_msg();
                    continue;
                }
                    if (is_number(command_parts[2])){
                                    memory.regs[opr1_reg_ind] = atoi(command_parts[2]);
                                    opr2 = VALID;
                                }
                        else {     
                            for(int i = 0; i < REG_COUNT; ++i){
                                    if(!strcmp(command_parts[2],regs_name[i])){
                                        opr2 = VALID;
                                        memory.regs[opr1_reg_ind] = memory.regs[i];
                                        break;
                                    }
                                }                   
                            }
                            
                 if(opr2 == INVALID){
                    wrong_cmd_msg();
                    continue;
                }
                memory.RIP++;
                push_regs();
                }

                else if(!strcmp(command_parts[0], "ADD") || !strcmp(command_parts[0], "add")){
                    if(tokens_count < 4){
                        wrong_cmd_msg();
                        continue;
                    }
                        for(int i = 0; i < REG_COUNT; ++i){
                                if(!strcmp(command_parts[1],regs_name[i])){
                                    opr1 = VALID;
                                    opr1_reg_ind = i;
                                    break;
                                }
                            }           
                        
                if(opr1 == INVALID){
                    wrong_cmd_msg();
                    continue;
                }
  
                        for(int i = 0; i < REG_COUNT; ++i){
                            if(!strcmp(command_parts[2],regs_name[i])){
                                opr2 = VALID;
                                opr2_reg_ind = i;
                                    break;
                                }
                            }                   
                            
                 if(opr2 == INVALID){
                    wrong_cmd_msg();
                    continue;
                }

                 if (is_number(command_parts[3])){
                                    memory.regs[opr1_reg_ind] =  memory.regs[opr2_reg_ind] + atoi(command_parts[3]);
                                    opr3 = VALID;
                                }
                       else {     
                            for(int i = 0; i < REG_COUNT; ++i){
                                    if(!strcmp(command_parts[3],regs_name[i])){
                                        opr3 = VALID;
                                        memory.regs[opr1_reg_ind] =  memory.regs[opr2_reg_ind] + memory.regs[i];
                                        break;
                                    }
                                }                   
                            }
                    if(opr3 == INVALID){
                        wrong_cmd_msg();
                        continue;
                    }  
                memory.RIP++;      
                push_regs();
                }
                else if(!strcmp(command_parts[0], "SUB") || !strcmp(command_parts[0], "sub")){
                    if(tokens_count < 4){
                        wrong_cmd_msg();
                        continue;
                    }                    
                        for(int i = 0; i < REG_COUNT; ++i){
                                if(!strcmp(command_parts[1],regs_name[i])){
                                    opr1 = VALID;
                                    opr1_reg_ind = i;
                                    break;
                                }
                            }           
                        
                if(opr1 == INVALID){
                    wrong_cmd_msg();
                    continue;
                }
  
                        for(int i = 0; i < REG_COUNT; ++i){
                            if(!strcmp(command_parts[2],regs_name[i])){
                                opr2 = VALID;
                                opr2_reg_ind = i;
                                    break;
                                }
                            }                   
                            
                 if(opr2 == INVALID){
                    wrong_cmd_msg();
                    continue;
                }

                 if (is_number(command_parts[3])){
                                    memory.regs[opr1_reg_ind] =  memory.regs[opr2_reg_ind] - atoi(command_parts[3]);
                                    opr3 = VALID;
                                }
                       else {     
                            for(int i = 0; i < REG_COUNT; ++i){
                                    if(!strcmp(command_parts[3],regs_name[i])){
                                        opr3 = VALID;
                                        memory.regs[opr1_reg_ind] = memory.regs[opr2_reg_ind] -  memory.regs[i];
                                        break;
                                    }
                                }                   
                            }
                    if(opr3 == INVALID){
                        wrong_cmd_msg();
                        continue;
                    }
                memory.RIP++;        
                push_regs();
                }                
                
                else if(!strcmp(command_parts[0], "LOAD") || !strcmp(command_parts[0], "load")){
                    if(tokens_count != 3){
                        wrong_cmd_msg();
                        continue;
                    }

                    for(int i = 0; i < REG_COUNT; ++i){
                                if(!strcmp(command_parts[1],regs_name[i])){
                                    opr1 = VALID;
                                    opr1_reg_ind = i;
                                    break;
                                }
                            }           
                        
                if(opr1 == INVALID){
                    wrong_cmd_msg();
                    continue;
                }

                if(!is_number(command_parts[2])){
                    wrong_cmd_msg();
                    continue;
                }
                else{
                    int index = atoi(command_parts[2]);
                    if(index < 0 || index >= RAM_SIZE){
                        wrong_cmd_msg();
                        continue;
                    }
                    memory.regs[opr1_reg_ind] = memory.RAM[index];
                }
                    
                memory.RIP++;        
                push_regs();
                }
                else if(!strcmp(command_parts[0], "STORE") || !strcmp(command_parts[0], "store")){
                            if(tokens_count != 3){
                            wrong_cmd_msg();
                                continue;
                            }

                     for(int i = 0; i < REG_COUNT; ++i){
                                if(!strcmp(command_parts[1],regs_name[i])){
                                    opr1 = VALID;
                                    opr1_reg_ind = i;
                                    break;
                                }
                            }           
                            
                    if(opr1 == INVALID){
                        wrong_cmd_msg();
                        continue;
                    }

                    if(!is_number(command_parts[2])){
                        wrong_cmd_msg();
                        continue;
                    }
                    else{
                        int index = atoi(command_parts[2]);
                        if(index < 0 || index >= RAM_SIZE){
                            wrong_cmd_msg();
                            continue;
                        }
                        memory.RAM[index] = memory.regs[opr1_reg_ind];
                    }
                        
                    memory.RIP++;        
                    push_regs();

                }
                else if(!strcmp(command_parts[0], "EXIT") || !strcmp(command_parts[0], "exit")){
                        if(tokens_count != 1){
                            wrong_cmd_msg();
                            continue;
                        }
                        if(!memory.WSR){
                            break;
                        }
                        else {
                            memory.WSR = 0;
                            memory.RIP = 0;
                            memset(memory.RAM, 0, sizeof(memory.RAM));
                            memset(memory.regs, 0, sizeof(memory.regs));
                            ftruncate(data_base_fd, 0);
                        }

                    memory.RIP++;        
                    push_regs();   
                }

                else if(!strcmp(command_parts[0], "DISC") || !strcmp(command_parts[0], "disc")){
                        if(tokens_count == 1){
                            strcpy(command_parts[1], "1");
                        }

                        if(tokens_count > 2){
                            wrong_cmd_msg();
                            continue;
                        }

                        if(!is_number(command_parts[1])){
                            wrong_cmd_msg();
                            continue;
                        }
                        else {
                                int index = atoi(command_parts[1]);
                                    if(index < 0  ||  index >= RAM_SIZE){
                                     wrong_cmd_msg();
                                        continue;
                                    }
                                pop_regs(index);
                            }   
                        }

                 else if(!strcmp(command_parts[0], "LAYO") || !strcmp(command_parts[0], "layo")){
                        if(tokens_count > 1){
                            wrong_cmd_msg();
                            continue;
                        }
                        for(int i = 0; i < REG_COUNT; ++i){
                            printf("%s : %d, ", regs_name[i], memory.regs[i]);
                        }

                        printf("%s : %d, ", regs_name[7], memory.WSR);
                        printf("%s : %d, ", regs_name[8], memory.RIP);
                        putchar('\n');
                        for(int i = 0; i < RAM_SIZE; ++i){
                            printf("%#x : %d ,", i, memory.RAM[i]);
                        }
                        putchar('\n');
                 }
                 else {
                    printf("No cuch command\n");
                 }        
        }  
    printf("Good bye\n");
    close(data_base_fd);
    return 0;
    }

