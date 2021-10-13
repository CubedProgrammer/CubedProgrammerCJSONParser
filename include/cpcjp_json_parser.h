#ifndef __cplusplus
#ifndef Included_cpcjp_json_parser_h
#define Included_cpcjp_json_parser_h
#include<cpcio_istream.h>
#include"cpcjp_json_obj.h"
struct cpcjp_parse_helper*cpcjp_mk_helper(struct cpcjp_json_val*,struct cpcjp_parse_helper*);
struct cpcjp_json_val*cpcjp_parse_stream(struct cpcio____istream*);
struct cpcjp_json_val*cpcjp_parse_str(const struct cppstring);
struct cpcjp_json_val*cpcjp_parse_cstr(const char*);
struct cpcjp_json_val*cpcjp_parse_arr(const char*,size_t);
#endif
#endif
