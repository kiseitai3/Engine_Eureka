#ifndef CMD_UTILS_H_INCLUDED
#define CMD_UTILS_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


#define CMD_YES 1
#define CMD_NO 0

typedef unsigned int size_t;

size_t cmd_generate_hash(const char* arg, size_t size);
void cmd_init(const char* noarg_options, size_t strSize);
void cmd_process(int argc, char** argv);
size_t cmd_get_option();
size_t cmd_get_arg_size();
size_t cmd_get_argc();
const char* cmd_get_error();
const char* cmd_get_appname();
const char* cmd_get_fullpath();
const char* cmd_get_appdir();
const char* cmd_get_argument();
void cmd_next_arg();
void cmd_reset_cursor_beg();
void cmd_reset_cursor_end();

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // CMD_UTILS_H_INCLUDED
