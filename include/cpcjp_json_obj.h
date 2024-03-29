#ifndef __cplusplus
#ifndef Included_cpcjp_json_obj_h
#define Included_cpcjp_json_obj_h
#include<stdbool.h>
#include<stdio.h>
#include<cpcio_ostream.h>
struct cppstring;
enum cpcjp_val_types
{CPCJP_NULL,CPCJP_BOOL,CPCJP_LIST,CPCJP_NUM,CPCJP_OBJ,CPCJP_STR};
union iocjv;
struct cpcjp_json_val
{
	enum cpcjp_val_types type;
	union iocjv*stuff;
};
struct cpcjp_json_iter;
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
struct cpcjp_json_val*cpcjp_malloc(void);
struct cpcjp_json_val*cpcjp_init_obj(void);
struct cpcjp_json_val*cpcjp_init_bool(int);
struct cpcjp_json_val*cpcjp_init_num(double);
struct cpcjp_json_val*cpcjp_init_list(void);
struct cpcjp_json_val*cpcjp_init_str(const char*);
struct cppstring cpcjp_dump_obj(struct cpcjp_json_val*);
int cpcjp_dump_obj_into_file(FILE*,struct cpcjp_json_val*);
void cpcjp_dump_obj_into_stream(cpcio_ostream,struct cpcjp_json_val*);
void cpcjp_insert_str_into_obj(struct cpcjp_json_val*,const char*,const char*);
void cpcjp_insert_num_into_obj(struct cpcjp_json_val*,const char*,double);
void cpcjp_insert_bool_into_obj(struct cpcjp_json_val*,const char*,int);
void cpcjp_insert_val_into_obj(struct cpcjp_json_val*,const char*,struct cpcjp_json_val*);
void cpcjp_insert_null_into_obj(struct cpcjp_json_val*,const char*);
void cpcjp_insert_num_into_list(struct cpcjp_json_val*,size_t,double);
void cpcjp_insert_bool_into_list(struct cpcjp_json_val*,size_t,int);
void cpcjp_insert_str_into_list(struct cpcjp_json_val*,size_t,const char*);
void cpcjp_insert_val_into_list(struct cpcjp_json_val*,size_t,struct cpcjp_json_val*);
void cpcjp_insert_null_into_list(struct cpcjp_json_val*,size_t);
void cpcjp_erase_from_list(struct cpcjp_json_val*,size_t);
void cpcjp_erase_value_from_list(struct cpcjp_json_val*list,struct cpcjp_json_val*val);
void cpcjp_erase_from_obj(struct cpcjp_json_val*,const char*);
void cpcjp_erase_from_list_nofree(struct cpcjp_json_val*,size_t);
void cpcjp_erase_value_from_list_nofree(struct cpcjp_json_val*list,struct cpcjp_json_val*val);
void cpcjp_erase_from_obj_nofree(struct cpcjp_json_val*,const char*);
size_t cpcjp_val_size(struct cpcjp_json_val*);
struct cpcjp_json_val*cpcjp_list_get(struct cpcjp_json_val*,size_t);
int cpcjp_obj_has(struct cpcjp_json_val*,const char*);
struct cpcjp_json_val*cpcjp_obj_get(struct cpcjp_json_val*,const char*);
struct cpcjp_json_iter*cpcjp_obj_iter(struct cpcjp_json_val*);
int cpcjp_list_merge(struct cpcjp_json_val *to, struct cpcjp_json_val *val);
int cpcjp_obj_merge(struct cpcjp_json_val *to, struct cpcjp_json_val *val);
void cpcjp_list_clear(struct cpcjp_json_val*);
void cpcjp_obj_clear(struct cpcjp_json_val*);
int cpcjp_equals(struct cpcjp_json_val*,struct cpcjp_json_val*);
struct cpcjp_json_val*cpcjp_copy_val(struct cpcjp_json_val*);
#ifdef DEBUG
size_t cpcjp____tot_alloc(void);
size_t cpcjp____tot_dealloc(void);
#endif
void cpcjp_free_val(struct cpcjp_json_val*);
typedef struct cpcjp_json_val*cpcjp_json_val;
typedef struct cpcjp_json_iter*cpcjp_json_iter;
struct cpcjp_json_iter;
typedef struct cppstring cpcjp_json_str;
typedef double cpcjp_json_num;
typedef bool cpcjp_json_bool;
typedef struct cpcds_um_cpcjp_json_map cpcjp_json_obj;
typedef struct cpcds_vector_cpcjp_json_list cpcjp_json_list;
#endif
#endif
