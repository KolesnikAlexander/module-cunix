#ifndef   ENV_H_
# define  ENV_H_

int env_validate(int argc, char** args);
int env_execute(int argc, char** args);
void new_var(char* key, char* value);
// char* get_val(char* key);
void init_env_table();
void free_env_table();

#endif