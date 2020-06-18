#ifndef __cplusplus
#ifndef Included_header_only_json_obj_parser_h
#define Included_header_only_json_obj_parser_h
#include<cpcds_vector.h>
#include<cpcds_unordered_map.h>
#include<fstream.h>
#include<sstream.h>
//#include<header_only_fstream.h>
//#include<header_only_sstream.h>
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
{CPCJP_NULL,CPCJP_BOOL,CPCJP_NUM,CPCJP_STR,CPCJP_LIST,CPCJP_OBJ};
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
	/*struct __cpcjp_json_val *cv = malloc(sizeof(struct __cpcjp_json_val));
	cv->name = "gay";
	cv->stuff = malloc(sizeof(union iocjv));
	cv->type = CPCJP_NUM;
	cv->stuff->num = 3;
	cppstring s = mk_from_cstr(cv->name);
	cpcds_um_insert_cpcjp_json_map(&val->stuff->obj,s,cv);*/
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
	val->type = CPCJP_LIST;

	val->stuff->str = mk_from_cstr(str);
	return val;
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
struct cppstring cpcjp_dump_obj(struct __cpcjp_json_val*__val)
{
	struct __ostream*__os=openoss();
	struct cpcds_vector_cpcjp_dump_helper stkv;
	struct cpcds_vector_cpcjp_dump_helper*stk=&stkv;
	stkv = cpcds_mk_vec_default_cpcjp_dump_helper();
	struct __cpcjp_dump_helper __tmp;

	__cpcjp_make_cdh(__tmp,__val,DUMP_HELPER_PENDING);
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
		if(__tmp.stuff->name!=NULL)
		{
			cpcio_putc_os(__os, DQUOTE);
			cpcio_puts_os(__os,__tmp.stuff->name);
			cpcio_putc_os(__os, DQUOTE);
			cpcio_puts_os(__os," : ");
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
					// add the right square bracket
					cpcio_putc_os(__os,RSQRBR);
				}
				else
				{
					__tmpl = __tmp.stuff->stuff->list;
					__tmp.status = DUMP_HELPER_OPENED;
					cpcds_vec_append_single_cpcjp_dump_helper(stk, __tmp);

					printf("%u\n",__tmpl.size);
					fflush(stdout);
					for(size_t i = 0; i < __tmpl.size; ++i)
					{
						__cpcjp_make_cdh(__tmp, cpcds_vec_get_at_cpcjp_json_list(&__tmpl,i), DUMP_HELPER_PENDING);
						cpcds_vec_append_single_cpcjp_dump_helper(stk,__tmp);
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
				else
				{
					__tmpo = __tmp.stuff->stuff->obj;
					__tmp.status = DUMP_HELPER_OPENED;
					cpcds_vec_append_single_cpcjp_dump_helper(stk, __tmp);

					it = cpcds_um_iter_begin_cpcjp_json_map(&__tmpo);
					printf("%u %u\n",__tmpo.size,cpcds_um_iter_end_cpcjp_json_map(&__tmpo).dq);
					fflush(stdout);
					while(!cpcds_um_iter_equal_cpcjp_json_map(it, cpcds_um_iter_end_cpcjp_json_map(&__tmpo)))
					{
						__cpcjp_make_cdh(__tmp, cpcds_um_iter_get_cpcjp_json_map(&it).val, DUMP_HELPER_PENDING);
						cpcds_vec_append_single_cpcjp_dump_helper(stk, __tmp);
						cpcds_um_iter_next_cpcjp_json_map(&it);
						printf("test %u %u\n",it.dq,cpcds_um_iter_end_cpcjp_json_map(&__tmpo).dq);
						fflush(stdout);
					}

					// add the left brace
					cpcio_putc_os(__os,LBRACE);
					__comma = false;
				}
				break;
		}
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
	struct __cpcjp_parse_helper*__top=__cpcjp_mk_helper(__val,NULL);
	struct __ostream*__os=openoss();
	struct cppstring __curr_obj_dat;
	struct cppstring __curr_obj_name;
	char __ch=cpcio_getc_is(__is);
	bool last_char_slash=false;
	cpcjp_json_num*__tmpd=NULL;
	struct cpcds_vector_cpcjp_json_list*__tmpv=NULL;
	struct cpcds_um_cpcjp_json_map*__tmpmp=NULL;
	struct __cpcjp_json_val*__tmpj=NULL;
	struct __cpcjp_parse_helper*__tmph=NULL;
	struct cppstring*__tmps=NULL;
	while(__ch!=0xff)
	{
		switch(__ch)
		{
			case DQUOTE:
				__curr_obj_name=mk_empty_str();
				__ch=cpcio_getc_is(__is);
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
				do
				{
					__ch=cpcio_getc_is(__is);
				}
				while(__ch!=COLON&&__ch!=COMMA);
				if(__ch==COLON)
				{
					__curr_obj_name=__curr_obj_dat;
					__curr_obj_dat=mk_empty_str();
				}
				else
				{
					__tmpj=(struct __cpcjp_json_val*)malloc(sizeof(struct __cpcjp_json_val));
					__tmpj->stuff=malloc(sizeof(struct cppstring));
					__tmps=(struct cppstring*)__tmpj->stuff;
					*__tmps=__curr_obj_dat;
					if(__top->stuff->type==CPCJP_LIST)
					{
						cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)__top->stuff->stuff,__tmpj);
					}
					else if(__top->stuff->type==CPCJP_OBJ)
					{
						cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)__top->stuff->stuff,__curr_obj_name,__tmpj);
					}
				}
				break;
			case COLON:
				__curr_obj_name=mk_from_cstr(cpcio_oss_str(__os));
				closeos(__os);
				free(__os);
				__os=NULL;
				break;
			case COMMA:
				__curr_obj_dat=mk_from_cstr(cpcio_oss_str(__os));
				if(__top->stuff->type==CPCJP_LIST)
				{
				}
				else if(__top->stuff->type==CPCJP_OBJ)
				{
					__tmpmp=(struct cpcds_um_cpcjp_json_map*)__top->stuff->stuff;
				}
				break;
			case LSQRBR:
				__tmpv=(struct cpcds_vector_cpcjp_json_list*)malloc(sizeof(struct cpcds_vector_cpcjp_json_list));
				*__tmpv=cpcds_mk_vec_default_cpcjp_json_list();
				__tmpj=(struct __cpcjp_json_val*)malloc(sizeof(struct __cpcjp_json_val));
				__tmpj->stuff=__tmpv;
				__tmpj->type=CPCJP_LIST;
				__top=__cpcjp_mk_helper(__tmpj,__top);
				break;
			case RSQRBR:
				__tmph=__top;
				__top=__top->up;
				if(__top!=NULL)
				{
					if(__top->stuff->type==CPCJP_LIST)
					{
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
				break;
			case LBRACE:
				__tmpmp=(struct cpcds_um_cpcjp_json_map*)malloc(sizeof(struct cpcds_um_cpcjp_json_map));
				__tmpj=(struct __cpcjp_json_val*)malloc(sizeof(struct __cpcjp_json_val));
				__tmpj->stuff=__tmpmp;
				__tmpj->type=CPCJP_OBJ;
				__top=__cpcjp_mk_helper(__tmpj,__top);
				break;
			case RBRACE:
				__tmph=__top;
				__top=__top->up;
				if(__top!=NULL)
				{
					if(__top->stuff->type==CPCJP_LIST)
					{
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
				break;
			default:
				if(__os==NULL)
				{
					__os=openoss();
				}
				cpcio_putc_os(__os,__ch);
				__ch=cpcio_getc_is(__is);
				while(!__cpcjp_is_alphanumeric(__ch))
				{
					cpcio_putc_os(__os,__ch);
					__ch=cpcio_getc_is(__is);
				}
				__curr_obj_dat=mk_from_cstr(cpcio_oss_str(__os));
				__top=__cpcjp_mk_helper(NULL,__top);
				__top->stuff=(struct __cpcjp_json_val*)malloc(sizeof(struct __cpcjp_json_val));
				if(str_char_at(&__curr_obj_dat,0)>='0'&&str_char_at(&__curr_obj_dat,0)<='9'||str_char_at(&__curr_obj_dat,0)=='+'||str_char_at(&__curr_obj_dat,0)=='-')
				{
					__top->stuff->type=CPCJP_NUM;
					__top->stuff->stuff=malloc(sizeof(cpcjp_json_num));
					__tmpd=(cpcjp_json_num*)__top->stuff->stuff;
					*__tmpd=strtod(cstr(&__curr_obj_dat),NULL);
				}
				else if(str_equal_values(CPCJP_BOOL_TRUE,__curr_obj_dat))
				{
					__top->stuff->type=CPCJP_BOOL;
					__top->stuff->stuff=malloc(sizeof(cpcjp_json_bool));
					for(char*__it__=(char*)__top->stuff->stuff;__it__!=(char*)(__top->stuff->stuff+sizeof(cpcjp_json_bool));++__it__)
					{
						if(__it__+1==(char*)(__top->stuff->stuff+sizeof(cpcjp_json_bool)))
						{
							*__it__=1;
						}
						else
						{
							*__it__='\0';
						}
					}
				}
				else if(str_equal_values(CPCJP_BOOL_FALSE,__curr_obj_dat))
				{
					__top->stuff->type=CPCJP_BOOL;
					__top->stuff->stuff=malloc(sizeof(cpcjp_json_bool));
					for(char*__it__=(char*)__top->stuff->stuff;__it__!=(char*)(__top->stuff->stuff+sizeof(cpcjp_json_bool));++__it__)
					{
						*__it__='\0';
					}
				}
				else if(str_equal_values(CPCJP_NULL_STR,__curr_obj_dat))
				{
					__top->stuff->type=CPCJP_NULL;
					__top->stuff->stuff=NULL;
				}
				break;
		}
		__ch=cpcio_getc_is(__is);
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
