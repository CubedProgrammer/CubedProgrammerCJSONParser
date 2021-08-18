#ifndef cplusplus
#ifndef Included_cpcjp_json_obj_h
#define Included_cpcjp_json_obj_h
#include<stdbool.h>
struct cppstring;
enum cpcjp_val_types
{CPCJP_NULL,CPCJP_BOOL,CPCJP_LIST,CPCJP_NUM,CPCJP_OBJ,CPCJP_STR};
struct cpcjp_json_val;
struct cpcjp_json_iter;
union iocjv;
struct cpcjp_parse_helper;
struct cpcjp_dump_helper;
/*struct cpcjp_json_val*cpcjp_get_elem(struct cpcjp_json_obj*,struct cppstring name);
void cpcjp_set_elem(struct cpcjp_json_obj*,struct cppstring name,struct cpcjp_json_val*);
struct cpcjp_json_iter*cpcjp_get_iter(struct cpcjp_json_obj*);*/
struct cppstring cpcjp_iter_key(struct cpcjp_json_iter*);
struct cpcjp_json_val*cpcjp_iter_val(struct cpcjp_json_iter*);
void cpcjp_iter_next(struct cpcjp_json_iter*);
bool cpcjp_iter_ended(struct cpcjp_json_iter*);
void cpcjp_destr_iter(struct cpcjp_json_iter*);
struct cpcjp_json_val *cpcjp_init_obj(void);
struct cpcjp_json_val *cpcjp_init_bool(int);
struct cpcjp_json_val *cpcjp_init_num(double);
struct cpcjp_json_val *cpcjp_init_list(void);
struct cpcjp_json_val *cpcjp_init_str(const char*);
struct cpcjp_json_val *cpcjp_nullptr_val(void);
void cpcjp_insert_str_into_obj(struct cpcjp_json_val*,const char*,const char*);
struct cppstring cpcjp_dump_obj(struct cpcjp_json_val*);
typedef struct cpcjp_json_val*cpcjp_json_val;
typedef struct cpcjp_json_iter*cpcjp_json_iter;
typedef struct cppstring cpcjp_json_str;
typedef double cpcjp_json_num;
typedef bool cpcjp_json_bool;
typedef struct cpcds_um_cpcjp_json_map cpcjp_json_obj;
typedef struct cpcds_vector_cpcjp_json_list cpcjp_json_list;
#endif
#endif
