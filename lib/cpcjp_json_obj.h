#ifndef __cplusplus
#ifndef Included_cpcjp_json_obj_h
#define Included_cpcjp_json_obj_h
#include<cppstring.h>
#include<cpcds_unordered_map.h>
enum cpcjp_val_types;
struct __cpcjp_json_val;
struct __cpcjp_json_obj;
struct __cpcjp_json_iter;
struct __cpcjp_json_val*cpcjp_get_elem(struct __cpcjp_json_obj*,struct cppstring name);
void cpcjp_set_elem(struct __cpcjp_json_obj*,struct cppstring name,struct __cpcjp_json_val*);
struct __cpcjp_json_iter*cpcjp_get_iter(struct __cpcjp_json_obj*);
struct cppstring cpcjp_iter_key(struct __cpcjp_json_iter*);
struct __cpcjp_json_val*cpcjp_iter_val(struct __cpcjp_json_iter*);
void cpcjp_iter_next(struct __cpcjp_json_iter*);
bool cpcjp_iter_ended(struct __cpcjp_json_iter*);
void cpcjp_destr_iter(struct __cpcjp_json_iter*);
typedef struct __cpcjp_json_val*cpcjp_json_val;
typedef struct __cpcjp_json_obj*cpcjp_json_obj;
typedef struct __cpcjp_json_iter*cpcjp_json_iter;
#endif
#endif
