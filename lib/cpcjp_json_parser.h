#ifndef __cplusplus
#ifndef Included_cpcjp_json_parser_h
#define Included_cpcjp_json_parser_h
#include<istream.h>
#include"cpcjp_json_obj.h"
struct __cpcjp_json_val*cpcjp_parse_stream(struct __istream*);
struct __cpcjp_json_val*cpcjp_parse_str(const struct cppstring);
#endif
#endif
