#ifndef __cplusplus
#ifndef Included_header_only_cpcjp_json_obj_h
#define Included_header_only_cpcjp_json_obj_h
#include<cpcds_vector.h>
#include<cpcds_unordered_map.h>
#include<header_only_fstream.h>
#include<header_only_istream.h>
#include<header_only_ostream.h>
#include<header_only_sstream.h>
#include<cpcjp_json_parser.h>
#define LBRACE '{'
#define RBRACE '}'
#define LSQRBR '['
#define RSQRBR ']'
#define DQUOTE '"'
#define BSLASH '\\'
#define COLON ':'
#define COMMA ','
#define __cpcjp_is_alphanumeric(__ch__)(((__ch__)<='9'&&(__ch__)>='0')||((__ch__)<='Z'&&(__ch__)>='A')||((__ch__)<='z'&&(__ch__)>='a'))
#define __cpcjp_is_whitespace(__ch__)((__ch__)==' '||(__ch__)=='\n'||(__ch__)=='\t')
#define __cpcjp_make_cdh(__helper__,__val__,__status__)do {  __helper__.stuff=__val__;__helper__.status=__status__;  } while (0)
enum cpcjp_val_types
{CPCJP_NULL,CPCJP_BOOL,CPCJP_LIST,CPCJP_NUM,CPCJP_OBJ,CPCJP_STR};
define_cpcds_um(cpcjp_json_map,struct cppstring,struct __cpcjp_json_val*,str_equal_values,cpcds_hash_str)
define_cpcds_vector(cpcjp_json_list,cpcjp_json_val)
define_cpcds_deque(cpcjp_free_helper,cpcjp_json_val)
struct __cpcjp_json_val
{
	enum cpcjp_val_types type;
	union iocjv*stuff;
	const char*name;
};
struct __cpcjp_json_iter
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
struct __cpcjp_parse_helper
{
	struct __cpcjp_json_val*stuff;
	struct __cpcjp_parse_helper*up;
};
enum __dump_helper_status
{DUMP_HELPER_PENDING,DUMP_HELPER_OPENED};
struct __cpcjp_dump_helper
{
	struct __cpcjp_json_val*stuff;
	enum __dump_helper_status status;
	bool is_self_containing;
};
define_cpcds_vector(cpcjp_dump_helper,struct __cpcjp_dump_helper)
typedef struct __cpcjp_json_val*cpcjp_json_val;
void cpcjp_insert_num_into_obj(struct __cpcjp_json_val *val,const char *key,double n)
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
void cpcjp_insert_bool_into_obj(struct __cpcjp_json_val *val,const char *key,int n)
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
void cpcjp_insert_str_into_obj(struct __cpcjp_json_val *val, const char *key, const char *str)
{
	if(val->type != CPCJP_OBJ)
	{
		fprintf(stderr, "Error: Function cpcjp_insert_str_into_obj requires the value to be of object type!\n");
	}
	else
	{
		struct __cpcjp_json_val *new = malloc(sizeof(struct __cpcjp_json_val));
		new->name = key;
		new->stuff = malloc(sizeof(*new->stuff));
		new->stuff->str = mk_from_cstr(str);
		new->type = CPCJP_STR;

		cpcds_um_insert_cpcjp_json_map(&val->stuff->obj, mk_from_cstr(key), new);
	}
}
void cpcjp_insert_val_into_obj(struct __cpcjp_json_val *obj, const char *key, struct __cpcjp_json_val *val)
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
void cpcjp_insert_null_into_obj(struct __cpcjp_json_val *val, const char *key)
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
void cpcjp_insert_num_into_list(struct __cpcjp_json_val *list, double n)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_num_into_list requires the value to be of list type!\n");
	else
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, cpcjp_init_num(n));
}
void cpcjp_insert_bool_into_list(struct __cpcjp_json_val *list, int n)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_bool_into_list requires the value to be of list type!\n");
	else
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, cpcjp_init_bool(n));
}
void cpcjp_insert_str_into_list(struct __cpcjp_json_val *list, const char *str)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_str_into_list requires the value to be of list type!\n");
	else
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, cpcjp_init_str(str));
}
void cpcjp_insert_val_into_list(struct __cpcjp_json_val *list, struct __cpcjp_json_val *val)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_val_into_list requires the value to be of list type!\n");
	else
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, val);
}
void cpcjp_insert_null_into_list(struct __cpcjp_json_val *list)
{
	if(list->type != CPCJP_LIST)
		fprintf(stderr, "Error: Function cpcjp_insert_null_into_list requires the value to be of list type!\n");
	else
		cpcds_vec_append_single_cpcjp_json_list(&list->stuff->list, cpcjp_nullptr_val());
}
struct __cpcjp_json_val *cpcjp_init_obj(void)
{
	struct __cpcjp_json_val *val = malloc(sizeof(struct __cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_OBJ;

	val->stuff->obj = cpcds_mk_um_empty_cpcjp_json_map();
	return val;
}
struct __cpcjp_json_val *cpcjp_init_bool(int v)
{
	struct __cpcjp_json_val *val = malloc(sizeof(struct __cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_BOOL;

	val->stuff->tof = v & 0x00000001;
	return val;
}
struct __cpcjp_json_val *cpcjp_init_num(double v)
{
	struct __cpcjp_json_val *val = malloc(sizeof(struct __cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_NUM;

	val->stuff->num = v;
	return val;
}
struct __cpcjp_json_val *cpcjp_init_list(void)
{
	struct __cpcjp_json_val *val = malloc(sizeof(struct __cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_LIST;

	val->stuff->list = cpcds_mk_vec_default_cpcjp_json_list();
	return val;
}
struct __cpcjp_json_val *cpcjp_init_str(const char *str)
{
	struct __cpcjp_json_val *val = malloc(sizeof(struct __cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_STR;

	val->stuff->str = mk_from_cstr(str);
	return val;
}
struct __cpcjp_json_val *cpcjp_nullptr_val(void)
{
	struct __cpcjp_json_val *val = malloc(sizeof(struct __cpcjp_json_val));
	val->name = NULL;
	val->stuff = NULL;
	val->type = CPCJP_NULL;
	return val;
}
struct cppstring cpcjp_dump_obj(struct __cpcjp_json_val*__val)
{
	struct __ostream*__os=openoss();
	struct cpcds_vector_cpcjp_dump_helper stkv;
	struct cpcds_vector_cpcjp_dump_helper*stk=&stkv;
	stkv = cpcds_mk_vec_default_cpcjp_dump_helper();
	struct __cpcjp_dump_helper __tmp;

	__cpcjp_make_cdh(__tmp,__val,DUMP_HELPER_PENDING);
	__tmp.is_self_containing=false;
	cpcds_vec_append_single_cpcjp_dump_helper(stk,__tmp);
	bool __comma=false;
	struct cppstring __tmps;
	cpcjp_json_bool __tmpb;
	cpcjp_json_num __tmpn;
	cpcjp_json_list __tmpl;
	cpcjp_json_obj __tmpo;

	cpcds_umiter_cpcjp_json_map it;
	while(stk->size > 0)
	{
		__tmp=cpcds_vec_pop_end_cpcjp_dump_helper(stk);
		if(__comma&&__tmp.status == DUMP_HELPER_PENDING)
		{
			cpcio_putc_os(__os,COMMA);
			cpcio_putc_os(__os,' ');
		}
		else
		{
			__comma=true;
		}
		/*printf("before %d, %d\n",__tmp.status,__tmp.stuff->type);
		fflush(stdout);
		printf("stuff: %d\n",__tmp.stuff->name);
		fflush(stdout);*/
		if(stk->size>0&&__tmp.status==DUMP_HELPER_PENDING&&__tmp.stuff->name!=NULL)
		{
			cpcio_putc_os(__os, DQUOTE);
			cpcio_puts_os(__os,__tmp.stuff->name);
			cpcio_putc_os(__os, DQUOTE);
			cpcio_puts_os(__os," : ");
			/*printf(__tmp.stuff->name);
			printf(" %d %d",__tmp.stuff->type,__tmp.stuff);
			printf(" from name\n");*/
			fflush(stdout);
		}
		switch(__tmp.stuff->type)
		{
			case CPCJP_NULL:
				cpcio_puts_os(__os,"null");
				break;
			case CPCJP_BOOL:
				__tmpb = __tmp.stuff->stuff->tof;
				if(__tmpb)
				{
					cpcio_puts_os(__os,"true");
				}
				else
				{
					cpcio_puts_os(__os,"false");
				}
				break;
			case CPCJP_NUM:
				//printf("num: %f\n",__tmp.stuff->stuff->num);
				fflush(stdout);
				__tmpn=__tmp.stuff->stuff->num;
				cpcio_putd_os(__os,__tmpn);
				break;
			case CPCJP_STR:
				__tmps = __tmp.stuff->stuff->str;
				cpcio_putc_os(__os, DQUOTE);
				cpcio_puts_os(__os,cstr(&__tmps));
				cpcio_putc_os(__os, DQUOTE);
				break;
			case CPCJP_LIST:
				if(__tmp.status == DUMP_HELPER_OPENED)
				{
					/*printf(__tmp.stuff->name);
					printf("type: %d\n",__tmp.status);
					fflush(stdout);*/
					// add the right square bracket
					cpcio_putc_os(__os,RSQRBR);
				}
				else if(__tmp.is_self_containing)
				{
					cpcio_puts_os(__os, "[ ... ]");
				}
				else
				{
					__tmpl = __tmp.stuff->stuff->list;
					__tmp.status = DUMP_HELPER_OPENED;
					cpcds_vec_append_single_cpcjp_dump_helper(stk, __tmp);

					for(size_t i = 0; i < __tmpl.size; ++i)
					{
						__tmp.is_self_containing = false;
						__cpcjp_make_cdh(__tmp, cpcds_vec_get_at_cpcjp_json_list(&__tmpl,i), DUMP_HELPER_PENDING);
						for(size_t j = 0;j < stk->size;j++)
						{
							if(cpcds_vec_get_at_cpcjp_dump_helper(stk, j).stuff == __tmp.stuff)
								__tmp.is_self_containing = true;
						}
						cpcds_vec_append_single_cpcjp_dump_helper(stk,__tmp);
					}

					/*if(__tmp.stuff->name)
					{
						printf(__tmp.stuff->name);
						printf("\n");
						fflush(stdout);
					}*/
					// add the left square bracket
					cpcio_putc_os(__os,LSQRBR);
					__comma = false;
				}
				break;
			case CPCJP_OBJ:
				if(__tmp.status == DUMP_HELPER_OPENED)
				{
					// add the right brace
					cpcio_putc_os(__os,RBRACE);
				}
				else if(__tmp.is_self_containing)
				{
					cpcio_puts_os(__os, "{ ... }");
				}
				else
				{
					__tmpo = __tmp.stuff->stuff->obj;
					__tmp.status = DUMP_HELPER_OPENED;
					cpcds_vec_append_single_cpcjp_dump_helper(stk, __tmp);

					it = cpcds_um_iter_begin_cpcjp_json_map(&__tmpo);
					while(!cpcds_um_iter_equal_cpcjp_json_map(it, cpcds_um_iter_end_cpcjp_json_map(&__tmpo)))
					{
						__cpcjp_make_cdh(__tmp, cpcds_um_iter_get_cpcjp_json_map(&it).val, DUMP_HELPER_PENDING);
						__tmp.is_self_containing = false;
						for(size_t i = 0;i < stk->size;i++)
						{
							if(cpcds_vec_get_at_cpcjp_dump_helper(stk, i).stuff == __tmp.stuff)
								__tmp.is_self_containing = true;
						}

						cpcds_vec_append_single_cpcjp_dump_helper(stk, __tmp);

						cpcds_um_iter_next_cpcjp_json_map(&it);
						fflush(stdout);
					}

					// add the left brace
					cpcio_putc_os(__os,LBRACE);
					__comma = false;
				}
				break;
		}
		/*printf("after %d, %d\n",__tmp.status,__tmp.stuff->type);
		fflush(stdout);*/
	}
	cpcds_vec_destr_cpcjp_dump_helper(stk);
	struct cppstring __str=mk_from_cstr(cpcio_oss_str(__os));
	closeos(__os);
	return __str;
}
void cpcjp_free_val(struct __cpcjp_json_val *val)
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
				if(val->name)
					free((void*)val->name);
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
