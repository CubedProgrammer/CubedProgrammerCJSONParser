#ifndef __cplusplus
#ifndef Included_header_only_cpcjp_json_obj_h
#define Included_header_only_cpcjp_json_obj_h
#include<cpcds_vector.h>
#include<cpcds_unordered_map.h>
#include<cpcio_fstream.h>
#include<cpcio_istream.h>
#include<cpcio_ostream.h>
#include<cpcio_sstream.h>
#include<cpcjp_json_obj.h>
#define LBRACE '{'
#define RBRACE '}'
#define LSQRBR '['
#define RSQRBR ']'
#define DQUOTE '"'
#define BSLASH '\\'
#define COLON ':'
#define COMMA ','
#define cpcjp_is_alphanumeric(__ch__)(((__ch__)<='9'&&(__ch__)>='0')||((__ch__)<='Z'&&(__ch__)>='A')||((__ch__)<='z'&&(__ch__)>='a'))
#define cpcjp_is_whitespace(__ch__)((__ch__)==' '||(__ch__)=='\n'||(__ch__)=='\t')
#define cpcjp_make_cdh(__helper__,val__,__status__)do {  __helper__.stuff=val__;__helper__.status=__status__;  } while (0)
define_cpcds_um(cpcjp_json_map,struct cppstring,struct cpcjp_json_val*,str_equal_values,cpcds_hash_str)
define_cpcds_vector(cpcjp_json_list,cpcjp_json_val)
define_cpcds_deque(cpcjp_free_helper,cpcjp_json_val)
struct cpcjp_json_val
{
	enum cpcjp_val_types type;
	union iocjv*stuff;
	const char*name;
};
struct cpcjp_json_iter
{
	struct cpcds_umiter_cpcjp_json_map*iter;
	struct cpcds_umiter_cpcjp_json_map*end;
};
union iocjv
{
	cpcjp_json_num num;
	cpcjp_json_str str;
	cpcjp_json_bool tof;
	cpcjp_json_obj obj;
	cpcjp_json_list list;
};
struct cpcjp_parse_helper
{
	struct cpcjp_json_val*stuff;
	struct cpcjp_parse_helper*up;
};
enum cpcjp____dump_helper_status
{DUMP_HELPER_PENDING,DUMP_HELPER_OPENED};
struct cpcjp_dump_helper
{
	struct cpcjp_json_val*stuff;
	enum cpcjp____dump_helper_status status;
	bool is_self_containing;
};
define_cpcds_vector(cpcjp_dump_helper,struct cpcjp_dump_helper)
typedef struct cpcjp_json_val*cpcjp_json_val;
void cpcjp_insert_num_into_obj(struct cpcjp_json_val *val,const char *key,double n)
{
	if(val->type != CPCJP_OBJ)
	{
		fprintf(stderr, "Error: Function cpcjp_insert_num_into_obj requires the value to be of object type!\n");
	}
	else
	{
		cpcds_um_insert_cpcjp_json_map(&val->stuff->obj, mk_from_cstr(key), cpcjp_init_num(n));
	}
}
void cpcjp_insert_bool_into_obj(struct cpcjp_json_val *val,const char *key,int n)
{
	if(val->type != CPCJP_OBJ)
	{
		fprintf(stderr, "Error: Function cpcjp_insert_bool_into_obj requires the value to be of object type!\n");
	}
	else
	{
		cpcds_um_insert_cpcjp_json_map(&val->stuff->obj, mk_from_cstr(key), cpcjp_init_bool(n));
	}
}
void cpcjp_insert_str_into_obj(struct cpcjp_json_val *val, const char *key, const char *str)
{
	if(val->type != CPCJP_OBJ)
	{
		fprintf(stderr, "Error: Function cpcjp_insert_str_into_obj requires the value to be of object type!\n");
	}
	else
	{
		struct cpcjp_json_val *new = malloc(sizeof(struct cpcjp_json_val));
		new->name = key;
		new->stuff = malloc(sizeof(*new->stuff));
		new->stuff->str = mk_from_cstr(str);
		new->type = CPCJP_STR;

		cpcds_um_insert_cpcjp_json_map(&val->stuff->obj, mk_from_cstr(key), new);
	}
}
void cpcjp_insert_val_into_obj(struct cpcjp_json_val *obj, const char *key, struct cpcjp_json_val *val)
{
	if(obj->type != CPCJP_OBJ)
	{
		fprintf(stderr, "Error: Function cpcjp_insert_val_into_obj requires the value to be of object type!\n");
	}
	else
	{
		val->name = key;
		cpcds_um_insert_cpcjp_json_map(&obj->stuff->obj, mk_from_cstr(key), val);
	}
}
void cpcjp_insert_null_into_obj(struct cpcjp_json_val *val, const char *key)
{
	if(val->type != CPCJP_OBJ)
	{
		fprintf(stderr, "Error: Function cpcjp_insert_null_into_obj requires the value to be of object type!\n");
	}
	else
	{
		cpcds_um_insert_cpcjp_json_map(&val->stuff->obj, mk_from_cstr(key), cpcjp_nullptr_val());
	}
}
void cpcjp_insert_num_into_list(struct cpcjp_json_val *list, size_t ind, double n)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_num_into_list requires the value to be of list type!\n");
	else if(ind == list->stuff->list.size)
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, cpcjp_init_num(n));
	else
		cpcds_vec_insert_single_cpcjp_json_list(&list->stuff->list, ind, cpcjp_init_num(n));
}
void cpcjp_insert_bool_into_list(struct cpcjp_json_val *list, size_t ind, int n)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_bool_into_list requires the value to be of list type!\n");
	else if(ind == list->stuff->list.size)
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, cpcjp_init_bool(n));
	else
		cpcds_vec_insert_single_cpcjp_json_list(&list->stuff->list, ind, cpcjp_init_bool(n));
}
void cpcjp_insert_str_into_list(struct cpcjp_json_val *list, size_t ind, const char *str)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_str_into_list requires the value to be of list type!\n");
	else if(ind == list->stuff->list.size)
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, cpcjp_init_str(str));
	else
		cpcds_vec_insert_single_cpcjp_json_list(&list->stuff->list, ind, cpcjp_init_str(str));
}
void cpcjp_insert_val_into_list(struct cpcjp_json_val *list, size_t ind, struct cpcjp_json_val *val)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_val_into_list requires the value to be of list type!\n");
	else if(ind == list->stuff->list.size)
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, val);
	else
		cpcds_vec_insert_single_cpcjp_json_list(&list->stuff->list, ind, val);
}
void cpcjp_insert_null_into_list(struct cpcjp_json_val *list, size_t ind)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_null_into_list requires the value to be of list type!\n");
	else if(ind == list->stuff->list.size)
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, cpcjp_nullptr_val());
	else
		cpcds_vec_insert_single_cpcjp_json_list(&list->stuff->list, ind, cpcjp_nullptr_val());
}
struct cpcjp_json_val *cpcjp_init_obj(void)
{
	struct cpcjp_json_val *val = malloc(sizeof(struct cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_OBJ;

	val->stuff->obj = cpcds_mk_um_empty_cpcjp_json_map();
	return val;
}
struct cpcjp_json_val *cpcjp_init_bool(int v)
{
	struct cpcjp_json_val *val = malloc(sizeof(struct cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_BOOL;

	val->stuff->tof = v & 0x00000001;
	return val;
}
struct cpcjp_json_val *cpcjp_init_num(double v)
{
	struct cpcjp_json_val *val = malloc(sizeof(struct cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_NUM;

	val->stuff->num = v;
	return val;
}
struct cpcjp_json_val *cpcjp_init_list(void)
{
	struct cpcjp_json_val *val = malloc(sizeof(struct cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_LIST;

	val->stuff->list = cpcds_mk_vec_default_cpcjp_json_list();
	return val;
}
struct cpcjp_json_val *cpcjp_init_str(const char *str)
{
	struct cpcjp_json_val *val = malloc(sizeof(struct cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_STR;

	val->stuff->str = mk_from_cstr(str);
	return val;
}
struct cpcjp_json_val *cpcjp_nullptr_val(void)
{
	struct cpcjp_json_val *val = malloc(sizeof(struct cpcjp_json_val));
	val->name = NULL;
	val->stuff = NULL;
	val->type = CPCJP_NULL;
	return val;
}
size_t cpcjp_val_size(struct cpcjp_json_val *val)
{
	if(val->type == CPCJP_STR)
		return val->stuff->str.len;
	else if(val->type == CPCJP_OBJ)
		return val->stuff->obj.size;
	else if(val->type == CPCJP_LIST)
		return val->stuff->list.size;
	else
		return-1;
}
struct cpcjp_json_val *cpcjp_list_get(struct cpcjp_json_val *list, size_t ind)
{
	if(list->type == CPCJP_LIST)
		return cpcds_vec_get_at_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)list->stuff, ind);
	else
		return NULL;
}
struct cpcjp_json_val *cpcjp_obj_get(struct cpcjp_json_val *obj, const char *n)
{
	cppstring ns = mk_from_cstr(n);
	struct cpcjp_json_val *v = cpcds_um_get_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)obj->stuff, ns);
	cpcds_destr_str(ns);
	return v;
}
void cpcjp_list_clear(struct cpcjp_json_val* list)
{
	for(size_t i = 0; i < list->stuff->list.size; ++i)
		cpcjp_free_val(cpcds_vec_get_at_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)list->stuff, i));
	cpcds_vec_clear_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)list->stuff);
}
void cpcjp_obj_clear(struct cpcjp_json_val*);
struct cppstring cpcjp_dump_obj(struct cpcjp_json_val*val)
{
	cpcio_ostream os=cpcio_open_osstream();
	struct cpcds_vector_cpcjp_dump_helper stkv;
	struct cpcds_vector_cpcjp_dump_helper*stk=&stkv;
	stkv = cpcds_mk_vec_default_cpcjp_dump_helper();
	struct cpcjp_dump_helper tmp;

	cpcjp_make_cdh(tmp,val,DUMP_HELPER_PENDING);
	tmp.is_self_containing=false;
	cpcds_vec_append_single_cpcjp_dump_helper(stk,tmp);
	bool __comma=false;
	struct cppstring tmps;
	cpcjp_json_bool tmpb;
	cpcjp_json_num tmpn;
	cpcjp_json_list tmpl;
	cpcjp_json_obj tmpo;

	cpcds_umiter_cpcjp_json_map it;
	while(stk->size > 0)
	{
		tmp=cpcds_vec_pop_end_cpcjp_dump_helper(stk);
		if(__comma&&tmp.status == DUMP_HELPER_PENDING)
		{
			cpcio_putc_os(os,COMMA);
			cpcio_putc_os(os,' ');
		}
		else
		{
			__comma=true;
		}
		/*printf("before %d, %d\n",tmp.status,tmp.stuff->type);
		fflush(stdout);
		printf("stuff: %d\n",tmp.stuff->name);
		fflush(stdout);*/
		if(stk->size>0&&tmp.status==DUMP_HELPER_PENDING&&tmp.stuff->name!=NULL)
		{
			cpcio_putc_os(os, DQUOTE);
			cpcio_puts_os(os,tmp.stuff->name);
			cpcio_putc_os(os, DQUOTE);
			cpcio_puts_os(os," : ");
			/*printf(tmp.stuff->name);
			printf(" %d %d",tmp.stuff->type,tmp.stuff);
			printf(" from name\n");*/
			fflush(stdout);
		}
		switch(tmp.stuff->type)
		{
			case CPCJP_NULL:
				cpcio_puts_os(os,"null");
				break;
			case CPCJP_BOOL:
				tmpb = tmp.stuff->stuff->tof;
				if(tmpb)
				{
					cpcio_puts_os(os,"true");
				}
				else
				{
					cpcio_puts_os(os,"false");
				}
				break;
			case CPCJP_NUM:
				//printf("num: %f\n",tmp.stuff->stuff->num);
				fflush(stdout);
				tmpn=tmp.stuff->stuff->num;
				cpcio_putd_os(os,tmpn);
				break;
			case CPCJP_STR:
				tmps = tmp.stuff->stuff->str;
				cpcio_putc_os(os, DQUOTE);
				cpcio_puts_os(os,cstr(&tmps));
				cpcio_putc_os(os, DQUOTE);
				break;
			case CPCJP_LIST:
				if(tmp.status == DUMP_HELPER_OPENED)
				{
					/*printf(tmp.stuff->name);
					printf("type: %d\n",tmp.status);
					fflush(stdout);*/
					// add the right square bracket
					cpcio_putc_os(os,RSQRBR);
				}
				else if(tmp.is_self_containing)
				{
					cpcio_puts_os(os, "[ ... ]");
				}
				else
				{
					tmpl = tmp.stuff->stuff->list;
					tmp.status = DUMP_HELPER_OPENED;
					cpcds_vec_append_single_cpcjp_dump_helper(stk, tmp);

					for(int64_t i = tmpl.size - 1; i >= 0; --i)
					{
						tmp.is_self_containing = false;
						cpcjp_make_cdh(tmp, cpcds_vec_get_at_cpcjp_json_list(&tmpl,i), DUMP_HELPER_PENDING);
						for(size_t j = 0;j < stk->size;j++)
						{
							if(cpcds_vec_get_at_cpcjp_dump_helper(stk, j).stuff == tmp.stuff)
								tmp.is_self_containing = true;
						}
						cpcds_vec_append_single_cpcjp_dump_helper(stk,tmp);
					}

					/*if(tmp.stuff->name)
					{
						printf(tmp.stuff->name);
						printf("\n");
						fflush(stdout);
					}*/
					// add the left square bracket
					cpcio_putc_os(os,LSQRBR);
					__comma = false;
				}
				break;
			case CPCJP_OBJ:
				if(tmp.status == DUMP_HELPER_OPENED)
				{
					// add the right brace
					cpcio_putc_os(os,RBRACE);
				}
				else if(tmp.is_self_containing)
				{
					cpcio_puts_os(os, "{ ... }");
				}
				else
				{
					tmpo = tmp.stuff->stuff->obj;
					tmp.status = DUMP_HELPER_OPENED;
					cpcds_vec_append_single_cpcjp_dump_helper(stk, tmp);

					it = cpcds_um_iter_begin_cpcjp_json_map(&tmpo);
					while(!cpcds_um_iter_equal_cpcjp_json_map(it, cpcds_um_iter_end_cpcjp_json_map(&tmpo)))
					{
						cpcjp_make_cdh(tmp, cpcds_um_iter_get_cpcjp_json_map(&it).val, DUMP_HELPER_PENDING);
						tmp.is_self_containing = false;
						for(size_t i = 0;i < stk->size;i++)
						{
							if(cpcds_vec_get_at_cpcjp_dump_helper(stk, i).stuff == tmp.stuff)
								tmp.is_self_containing = true;
						}

						cpcds_vec_append_single_cpcjp_dump_helper(stk, tmp);

						cpcds_um_iter_next_cpcjp_json_map(&it);
						fflush(stdout);
					}

					// add the left brace
					cpcio_putc_os(os,LBRACE);
					__comma = false;
				}
				break;
		}
		/*printf("after %d, %d\n",tmp.status,tmp.stuff->type);
		fflush(stdout);*/
	}
	cpcds_vec_destr_cpcjp_dump_helper(stk);
	struct cppstring str=mk_from_cstr(cpcio_oss_str(os));
	cpcio_close_ostream(os);
	return str;
}
void cpcjp_free_val(struct cpcjp_json_val *val)
{
	struct cpcds_deque_cpcjp_free_helper q = cpcds_mk_deque_empty_cpcjp_free_helper();
	switch(val->type)
	{
		case CPCJP_LIST:
			cpcds_deque_push_cpcjp_free_helper(&q, val);
			break;
		case CPCJP_OBJ:
			cpcds_deque_push_cpcjp_free_helper(&q, val);
			break;
		default:
			if(val->name)
				free((void*)val->name);
			if(val->stuff)
				free(val->stuff);
			free(val);
			break;
	}
	while(q.size)
	{
		val = cpcds_queue_poll_cpcjp_free_helper(&q);
		switch(val->type)
		{
			case CPCJP_LIST:
				for(size_t i = 0; i < val->stuff->list.size; ++i)
					cpcds_deque_push_cpcjp_free_helper(&q, cpcds_vec_get_at_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)val->stuff, i));
				cpcds_vec_destr_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)val->stuff);
				free(val->stuff);
				if(val->name)
					free((void*)val->name);
				free(val);
				break;
			case CPCJP_OBJ:
				for(cpcds_umiter_cpcjp_json_map it = cpcds_um_iter_begin_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)val->stuff); !cpcds_um_iter_equal_cpcjp_json_map(it, cpcds_um_iter_end_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)val->stuff)); cpcds_um_iter_next_cpcjp_json_map(&it))
					cpcds_deque_push_cpcjp_free_helper(&q, cpcds_um_iter_get_cpcjp_json_map(&it).val);
				free(val->stuff);
				if(val->name)
					free((void*)val->name);
				free(val);
				break;
			default:
				/*if(val->name)
					free((void*)val->name);*/
				if(val->stuff)
					free(val->stuff);
				free(val);
				break;
		}
	}
	cpcds_deque_clear_cpcjp_free_helper(&q);
}
#endif
#endif
