#ifndef __cplusplus
#include<cppstring.h>
#include<cpcds_unordered_map.h>
#include<istream.h>
define_cpcds_um(cpcjp_json_map,struct cppstring,struct __cpcjp_json_val*,str_equal_values,cpcds_hash_str)
enum cpcjp_val_types
{CPCJP_NULL,CPCJP_BOOL,CPCJP_NUM,CPCJP_STR,CPCJP_LIST,CPCJP_OBJ};
struct __cpcjp_json_val
{
	enum cpcjp_val_types type;
	void*dat;
};
struct __cpcjp_json_obj
{
	struct cpcds_um_cpcjp_json_map*objmp;
	size_t elem_cnt;
};
struct __cpcjp_json_iter
{
	struct cpcds_umiter_cpcjp_json_map*iter;
	struct cpcds_umiter_cpcjp_json_map*end;
};
struct __cpcjp_json_val*cpcjp_get_elem(struct __cpcjp_json_obj*__obj,struct cppstring __str)
{
	return cpcds_um_get_cpcjp_json_map(__obj->objmp,__str);
}
void cpcjp_set_elem(struct __cpcjp_json_obj*__obj,struct cppstring __str,struct __cpcjp_json_val*__v)
{
	cpcds_um_insert_cpcjp_json_map(__obj->objmp,__str,__v);
}
struct __cpcjp_json_iter*cpcjp_get_iter(struct __cpcjp_json_obj*__obj)
{
	struct __cpcjp_json_iter*__it__=(struct __cpcjp_json_iter*)malloc(sizeof(struct __cpcjp_json_iter*));
	__it__->iter=(struct cpcds_umiter_cpcjp_json_map*)malloc(sizeof(struct cpcds_umiter_cpcjp_json_map));
	__it__->end=(struct cpcds_umiter_cpcjp_json_map*)malloc(sizeof(struct cpcds_umiter_cpcjp_json_map));
	*__it__->iter=cpcds_um_iter_begin_cpcjp_json_map(__obj->objmp);
	*__it__->end=cpcds_um_iter_end_cpcjp_json_map(__obj->objmp);
	return __it__;
}
struct cppstring cpcjp_iter_key(struct __cpcjp_json_iter*__it__)
{
	return cpcds_um_iter_get_cpcjp_json_map(__it__->iter).key;
}
struct __cpcjp_json_val*cpcjp_iter_val(struct __cpcjp_json_iter*__it__)
{
	return cpcds_um_iter_get_cpcjp_json_map(__it__->iter).val;
}
void cpcjp_iter_next(struct __cpcjp_json_iter*__it__)
{
	cpcds_um_iter_next_cpcjp_json_map(__it__->iter);
}
bool cpcjp_iter_ended(struct __cpcjp_json_iter*__it__)
{
	return cpcds_um_iter_equal_cpcjp_json_map(*__it__->iter,*__it__->end);
}
void cpcjp_destr_iter(struct __cpcjp_json_iter*__it__)
{
	free(__it__->iter);
	free(__it__->end);
}
struct __cpcjp_json_obj*cpcjp_parse_stream(struct __istream*__is)
{
	struct __cpcjp_json_obj*__obj=(struct __cpcjp_json_obj*)malloc(sizeof(struct __cpcjp_json_obj));
	__obj->elem_cnt=0;
	__obj->objmp=(struct cpcds_um_cpcjp_json_map*)malloc(sizeof(struct cpcds_um_cpcjp_json_map));
	*__obj->objmp=cpcds_mk_um_empty_cpcjp_json_map();
	return __obj;
}
#endif
