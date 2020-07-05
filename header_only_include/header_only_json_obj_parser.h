#ifndef __cplusplus
#ifndef Included_header_only_json_obj_parser_h
#define Included_header_only_json_obj_parser_h
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
/*struct __cpcjp_json_val*cpcjp_get_elem(struct __cpcjp_json_obj*__obj,struct cppstring __str)
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
}*/
/*struct cppstring cpcjp_iter_key(struct __cpcjp_json_iter*__it__)
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
}*/
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
		printf("before %d, %d\n",__tmp.status,__tmp.stuff->type);
		fflush(stdout);
		printf("stuff: %d\n",__tmp.stuff->name);
		fflush(stdout);
		if(stk->size>0&&__tmp.status==DUMP_HELPER_PENDING&&__tmp.stuff->name!=NULL)
		{
			cpcio_putc_os(__os, DQUOTE);
			cpcio_puts_os(__os,__tmp.stuff->name);
			cpcio_putc_os(__os, DQUOTE);
			cpcio_puts_os(__os," : ");
			printf(__tmp.stuff->name);
			printf(" %d %d",__tmp.stuff->type,__tmp.stuff);
			printf(" from name\n");
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
				printf("num: %f\n",__tmp.stuff->stuff->num);
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
					printf(__tmp.stuff->name);
					printf("type: %d\n",__tmp.status);
					fflush(stdout);
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

					if(__tmp.stuff->name)
					{
						printf(__tmp.stuff->name);
						printf("\n");
						fflush(stdout);
					}
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
		printf("after %d, %d\n",__tmp.status,__tmp.stuff->type);
		fflush(stdout);
	}
	cpcds_vec_destr_cpcjp_dump_helper(stk);
	struct cppstring __str=mk_from_cstr(cpcio_oss_str(__os));
	closeos(__os);
	return __str;
}
struct __cpcjp_parse_helper*__cpcjp_mk_helper(struct __cpcjp_json_val*stuff,struct __cpcjp_parse_helper*up)
{
	struct __cpcjp_parse_helper*x=(struct __cpcjp_parse_helper*)malloc(sizeof(struct __cpcjp_parse_helper));
	x->stuff=stuff;
	x->up=up;
	return x;
}
struct __cpcjp_json_val*cpcjp_parse_stream(struct __istream*__is)
{
	struct cppstring CPCJP_BOOL_TRUE=mk_from_cstr("true");
	struct cppstring CPCJP_BOOL_FALSE=mk_from_cstr("false");
	struct cppstring CPCJP_NULL_STR=mk_from_cstr("null");
	struct __cpcjp_json_val*__val=NULL;
	struct __cpcjp_parse_helper*__top=NULL;
	struct __ostream*__os=openoss();
	struct cppstring __curr_obj_dat;
	struct cppstring __curr_obj_name=mk_empty_str();
	char __ch=cpcio_getc_is(__is);
	bool last_char_slash=false;
	struct __cpcjp_json_val*__tmpj=NULL;
	struct __cpcjp_parse_helper*__tmph=NULL;
	while(__ch!=-1)
	{
		switch(__ch)
		{
			case DQUOTE:
				__ch=cpcio_getc_is(__is);
				if(__os == NULL)
				{
					__os = openoss();
				}
				while(__ch!=DQUOTE)
				{
					if(last_char_slash)
					{
						switch(__ch)
						{
							case BSLASH:
								cpcio_putc_os(__os,__ch);
								break;
							case'n':
								cpcio_putc_os(__os,'\n');
								break;
							case'r':
								cpcio_putc_os(__os,'\r');
								break;
							case'b':
								cpcio_putc_os(__os,'\b');
								break;
							case'a':
								cpcio_putc_os(__os,'\a');
								break;
							case'f':
								cpcio_putc_os(__os,'\f');
								break;
							case't':
								cpcio_putc_os(__os,'\t');
								break;
							case'v':
								cpcio_putc_os(__os,'\v');
								break;
							case'\'':
								cpcio_putc_os(__os,'\'');
								break;
							case DQUOTE:
								cpcio_putc_os(__os,DQUOTE);
								break;
							default:
								cpcio_putc_os(__os,__ch);
								break;
						}
					}
					else
					{
						if(__ch==BSLASH)
						{
							last_char_slash=true;
						}
						else
						{
							cpcio_putc_os(__os,__ch);
						}
					}
					__ch=cpcio_getc_is(__is);
					if(last_char_slash&&__ch==DQUOTE)
					{
						cpcio_putc_os(__os,DQUOTE);
						__ch=cpcio_getc_is(__is);
					}
				}
				__curr_obj_dat=mk_from_cstr(cpcio_oss_str(__os));
				closeos(__os);
				free(__os);
				__os = NULL;
				do
				{
					__ch=cpcio_getc_is(__is);
				}
				while(__ch=='\n'||__ch==' '||__ch=='\t');
				if(__ch==COLON)
				{
					__curr_obj_name=__curr_obj_dat;
					__curr_obj_dat=mk_empty_str();
					cpcds_stdprint_cppstr(__curr_obj_name);
					printf(" is __curr_obj_name\n");
				}
				else
				{
					__tmpj=(struct __cpcjp_json_val*)malloc(sizeof(struct __cpcjp_json_val));
					__tmpj->stuff=malloc(sizeof(union iocjv));
					__tmpj->stuff->str=__curr_obj_dat;
					__tmpj->type=CPCJP_STR;
					cpcds_stdprint_cppstr(__curr_obj_name);
					printf(" is __curr_obj_name\n");
					cpcds_stdprint_cppstr(__curr_obj_dat);
					printf(" is __curr_obj_dat\n");
					if(__top->stuff->type==CPCJP_LIST)
					{
						cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)__top->stuff->stuff,__tmpj);
						__tmpj->name=NULL;
					}
					else if(__top->stuff->type==CPCJP_OBJ)
					{
						cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)__top->stuff->stuff,__curr_obj_name,__tmpj);
						__tmpj->name=cstr(&__curr_obj_name);
					}
					cpcio_ungetc_is(__is);
				}
				break;
			case LSQRBR:
				__tmpj=(struct __cpcjp_json_val*)malloc(sizeof(struct __cpcjp_json_val));
				__tmpj->stuff=(union iocjv*)malloc(sizeof(union iocjv));
				__tmpj->stuff->list=cpcds_mk_vec_default_cpcjp_json_list();
				__tmpj->type=CPCJP_LIST;
				__tmpj->name=cstr(&__curr_obj_name);
				__top=__cpcjp_mk_helper(__tmpj,__top);
				break;
			case RSQRBR:
				__tmph=__top;
				__top=__top->up;
				if(__top!=NULL)
				{
					if(__top->stuff->type==CPCJP_LIST)
					{
						__tmph->stuff->name = NULL;
						cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)__top->stuff->stuff,__tmph->stuff);
					}
					else if(__top->stuff->type==CPCJP_OBJ)
					{
						cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)__top->stuff->stuff,__curr_obj_name,__tmph->stuff);
					}
				}
				else
				{
					__val=__tmph->stuff;
				}
				free(__tmph);
				cpcds_stdprint_cppstr(__curr_obj_name);
				printf("\n");
				fflush(stdout);
				break;
			case LBRACE:
				__tmpj=(struct __cpcjp_json_val*)malloc(sizeof(struct __cpcjp_json_val));
				__tmpj->stuff=(union iocjv*)malloc(sizeof(union iocjv));
				__tmpj->stuff->obj=cpcds_mk_um_empty_cpcjp_json_map();
				__tmpj->type=CPCJP_OBJ;
				__tmpj->name=cstr(&__curr_obj_name);
				__top=__cpcjp_mk_helper(__tmpj,__top);
				break;
			case RBRACE:
				__tmph=__top;
				__top=__top->up;
				if(__top!=NULL)
				{
					if(__top->stuff->type==CPCJP_LIST)
					{
						__tmph->stuff->name = NULL;
						cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)__top->stuff->stuff,__tmph->stuff);
					}
					else if(__top->stuff->type==CPCJP_OBJ)
					{
						cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)__top->stuff->stuff,__curr_obj_name,__tmph->stuff);
					}
				}
				else
				{
					__val=__tmph->stuff;
				}
				free(__tmph);
				cpcds_stdprint_cppstr(__curr_obj_name);
				printf(" curly\n");
				fflush(stdout);
				for(int i = 0; __is->cbuf[i] != -1; ++i)
				{
					printf("%c",__is->cbuf[i]);
				}
				printf("\n");
				break;
			case-1:
				break;
			default:
				if(__cpcjp_is_alphanumeric(__ch))
				{
					if(__os==NULL)
					{
						__os=openoss();
					}
					do
					{
						cpcio_putc_os(__os,__ch);
						__ch=cpcio_getc_is(__is);
					}
					while(__cpcjp_is_alphanumeric(__ch));
					cpcio_ungetc_is(__is);
					__curr_obj_dat=mk_from_cstr(cpcio_oss_str(__os));
					cpcds_stdprint_cppstr(__curr_obj_dat);
					printf(", %d\n", __ch);
					fflush(stdout);
					closeos(__os);
					free(__os);
					__os = NULL;
					if(__curr_obj_dat.len)
					{
						__top=__cpcjp_mk_helper(NULL,__top);
						__top->stuff=(struct __cpcjp_json_val*)malloc(sizeof(struct __cpcjp_json_val));
						if(str_char_at(&__curr_obj_dat,0)>='0'&&str_char_at(&__curr_obj_dat,0)<='9'||str_char_at(&__curr_obj_dat,0)=='+'||str_char_at(&__curr_obj_dat,0)=='-')
						{
							__top->stuff->type=CPCJP_NUM;
							__top->stuff->stuff=malloc(sizeof(union iocjv));
							__top->stuff->stuff->num=strtod(cstr(&__curr_obj_dat),NULL);
						}
						else if(str_equal_values(CPCJP_BOOL_TRUE,__curr_obj_dat))
						{
							__top->stuff->type=CPCJP_BOOL;
							__top->stuff->stuff=malloc(sizeof(union iocjv));
							__top->stuff->stuff->tof = true;
						}
						else if(str_equal_values(CPCJP_BOOL_FALSE,__curr_obj_dat))
						{
							__top->stuff->type=CPCJP_BOOL;
							__top->stuff->stuff=malloc(sizeof(union iocjv));
							__top->stuff->stuff->tof = false;
						}
						else if(str_equal_values(CPCJP_NULL_STR,__curr_obj_dat))
						{
							__top->stuff->type=CPCJP_NULL;
							__top->stuff->stuff=NULL;
						}
						else
						{
							cpcds_stdprint_cppstr(__curr_obj_dat);
							printf(" is fucking gay.\n");
						}
						__tmph = __top;
						__top = __top->up;
						if(__top!=NULL)
						{
							if(__top->stuff->type==CPCJP_LIST)
							{
								__tmph->stuff->name=NULL;
								cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)__top->stuff->stuff,__tmph->stuff);
							}
							else if(__top->stuff->type==CPCJP_OBJ)
							{
								__tmph->stuff->name=cstr(&__curr_obj_name);
								cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)__top->stuff->stuff,__curr_obj_name,__tmph->stuff);
							}
						}
						else
						{
							__val=__tmph->stuff;
						}
						free(__tmph);
					}
				}
				/*printf("just finished default case\n");
				fflush(stdout);*/
				break;
		}
		/*printf("__ch used to be %d or %c\n", __ch, __ch);
		fflush(stdout);*/
		__ch=cpcio_getc_is(__is);
		/*printf("__ch is %d or %c\n", __ch, __ch);
		fflush(stdout);*/
	}
	return __val;
}
struct __cpcjp_json_val*cpcjp_parse_str(const struct cppstring __s)
{
	struct __istream*__is=openiss(cstr(&__s));
	struct __cpcjp_json_val*__val=cpcjp_parse_stream(__is);
	closeis(__is);
	free(__is);
	return __val;
}
#endif
#endif
