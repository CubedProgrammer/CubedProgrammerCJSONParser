
#ifndef cplusplus
#ifndef Included_header_only_json_obj_parser_h
#define Included_header_only_json_obj_parser_h
#include<cpcds_vector.h>
#include<cpcds_unordered_map.h>
#include<fstream.h>
#include<sstream.h>
//#include<header_only_fstream.h>
//#include<header_only_sstream.h>
#include"../include/cpcjp_json_parser.h"
#define LBRACE '{'
#define RBRACE '}'
#define LSQRBR '['
#define RSQRBR ']'
#define DQUOTE '"'
#define BSLASH '\\'
#define COLON ':'
#define COMMA ','
#define cpcjp_is_alphanumeric(ch)(((ch)<='9'&&(ch)>='0')||((ch)<='Z'&&(ch)>='A')||((ch)<='z'&&(ch)>='a'))
#define cpcjp_is_whitespace(ch)((ch)=='\b'||(ch)=='\r'||(ch)==' '||(ch)=='\n'||(ch)=='\t')
#define cpcjp_make_cdh(helper,val,stat)do {  helper.stuff=val;helper.status=stat;  } while (0)
define_cpcds_um(cpcjp_json_map,struct cppstring,struct cpcjp_json_val*,str_equal_values,cpcds_hash_str)
define_cpcds_vector(cpcjp_json_list,cpcjp_json_val)
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
enum dump_helper_status
{DUMP_HELPER_PENDING,DUMP_HELPER_OPENED};
struct cpcjp_dump_helper
{
	struct cpcjp_json_val*stuff;
	enum dump_helper_status status;
};
define_cpcds_vector(cpcjp_dump_helper,struct cpcjp_dump_helper)
typedef struct cpcjp_json_val*cpcjp_json_val;
/*struct cpcjp_json_val*cpcjp_get_elem(struct cpcjp_json_obj*obj,struct cppstring str)
{
	return cpcds_um_get_cpcjp_json_map(obj->objmp,str);
}
void cpcjp_set_elem(struct cpcjp_json_obj*obj,struct cppstring str,struct cpcjp_json_val*v)
{
	cpcds_um_insert_cpcjp_json_map(obj->objmp,str,v);
}
struct cpcjp_json_iter*cpcjp_get_iter(struct cpcjp_json_obj*obj)
{
	struct cpcjp_json_iter*it=(struct cpcjp_json_iter*)malloc(sizeof(struct cpcjp_json_iter*));
	it->iter=(struct cpcds_umiter_cpcjp_json_map*)malloc(sizeof(struct cpcds_umiter_cpcjp_json_map));
	it->end=(struct cpcds_umiter_cpcjp_json_map*)malloc(sizeof(struct cpcds_umiter_cpcjp_json_map));
	*it->iter=cpcds_um_iter_begin_cpcjp_json_map(obj->objmp);
	*it->end=cpcds_um_iter_end_cpcjp_json_map(obj->objmp);
	return it;
}*/
/*struct cppstring cpcjp_iter_key(struct cpcjp_json_iter*it)
{
	return cpcds_um_iter_get_cpcjp_json_map(it->iter).key;
}
struct cpcjp_json_val*cpcjp_iter_val(struct cpcjp_json_iter*it)
{
	return cpcds_um_iter_get_cpcjp_json_map(it->iter).val;
}
void cpcjp_iter_next(struct cpcjp_json_iter*it)
{
	cpcds_um_iter_next_cpcjp_json_map(it->iter);
}
bool cpcjp_iter_ended(struct cpcjp_json_iter*it)
{
	return cpcds_um_iter_equal_cpcjp_json_map(*it->iter,*it->end);
}
void cpcjp_destr_iter(struct cpcjp_json_iter*it)
{
	free(it->iter);
	free(it->end);
}*/
struct cpcjp_json_val *cpcjp_init_obj(void)
{
	struct cpcjp_json_val *val = malloc(sizeof(struct cpcjp_json_val));
	val->name = NULL;
	val->stuff = malloc(sizeof(union iocjv));
	val->type = CPCJP_OBJ;

	val->stuff->obj = cpcds_mk_um_empty_cpcjp_json_map();
	/*struct cpcjp_json_val *cv = malloc(sizeof(struct cpcjp_json_val));
	cv->name = "gay";
	cv->stuff = malloc(sizeof(union iocjv));
	cv->type = CPCJP_NUM;
	cv->stuff->num = 3;
	cppstring s = mk_from_cstr(cv->name);
	cpcds_um_insert_cpcjp_json_map(&val->stuff->obj,s,cv);*/
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
struct cppstring cpcjp_dump_obj(struct cpcjp_json_val*val)
{
	struct cpcio____ostream*os=cpcio_open_osstream();
	struct cpcds_vector_cpcjp_dump_helper stkv;
	struct cpcds_vector_cpcjp_dump_helper*stk=&stkv;
	stkv = cpcds_mk_vec_default_cpcjp_dump_helper();
	struct cpcjp_dump_helper tmp;

	cpcjp_make_cdh(tmp,val,DUMP_HELPER_PENDING);
	cpcds_vec_append_single_cpcjp_dump_helper(stk,tmp);
	bool comma=false;
	struct cppstring tmps;
	cpcjp_json_bool tmpb;
	cpcjp_json_num tmpn;
	cpcjp_json_list tmpl;
	cpcjp_json_obj tmpo;

	cpcds_umiter_cpcjp_json_map it;
	while(stk->size > 0)
	{
		tmp=cpcds_vec_pop_end_cpcjp_dump_helper(stk);
		if(comma&&tmp.status == DUMP_HELPER_PENDING)
		{
			cpcio_putc_os(os,COMMA);
			cpcio_putc_os(os,' ');
		}
		else
		{
			comma=true;
		}
		if(tmp.stuff->name!=NULL)
		{
			cpcio_putc_os(os, DQUOTE);
			cpcio_puts_os(os,tmp.stuff->name);
			cpcio_putc_os(os, DQUOTE);
			cpcio_puts_os(os," : ");
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
					// add the right square bracket
					cpcio_putc_os(os,RSQRBR);
				}
				else
				{
					tmpl = tmp.stuff->stuff->list;
					tmp.status = DUMP_HELPER_OPENED;
					cpcds_vec_append_single_cpcjp_dump_helper(stk, tmp);

					printf("%u\n",tmpl.size);
					fflush(stdout);
					for(size_t i = 0; i < tmpl.size; ++i)
					{
						cpcjp_make_cdh(tmp, cpcds_vec_get_at_cpcjp_json_list(&tmpl,i), DUMP_HELPER_PENDING);
						cpcds_vec_append_single_cpcjp_dump_helper(stk,tmp);
					}

					// add the left square bracket
					cpcio_putc_os(os,LSQRBR);
					comma = false;
				}
				break;
			case CPCJP_OBJ:
				if(tmp.status == DUMP_HELPER_OPENED)
				{
					// add the right brace
					cpcio_putc_os(os,RBRACE);
				}
				else
				{
					tmpo = tmp.stuff->stuff->obj;
					tmp.status = DUMP_HELPER_OPENED;
					cpcds_vec_append_single_cpcjp_dump_helper(stk, tmp);

					it = cpcds_um_iter_begin_cpcjp_json_map(&tmpo);
					printf("%u %u\n",tmpo.size,cpcds_um_iter_end_cpcjp_json_map(&tmpo).dq);
					fflush(stdout);
					while(!cpcds_um_iter_equal_cpcjp_json_map(it, cpcds_um_iter_end_cpcjp_json_map(&tmpo)))
					{
						cpcjp_make_cdh(tmp, cpcds_um_iter_get_cpcjp_json_map(&it).val, DUMP_HELPER_PENDING);
						cpcds_vec_append_single_cpcjp_dump_helper(stk, tmp);
						cpcds_um_iter_next_cpcjp_json_map(&it);
						printf("test %u %u\n",it.dq,cpcds_um_iter_end_cpcjp_json_map(&tmpo).dq);
						fflush(stdout);
					}

					// add the left brace
					cpcio_putc_os(os,LBRACE);
					comma = false;
				}
				break;
		}
	}
	cpcds_vec_destr_cpcjp_dump_helper(stk);
	struct cppstring str=mk_from_cstr(cpcio_oss_str(os));
	cpcio_close_ostream(os);
	return str;
}
struct cpcjp_parse_helper*cpcjp_mk_helper(struct cpcjp_json_val*stuff,struct cpcjp_parse_helper*up)
{
	struct cpcjp_parse_helper*x=(struct cpcjp_parse_helper*)malloc(sizeof(struct cpcjp_parse_helper));
	x->stuff=stuff;
	x->up=up;
	return x;
}
struct cpcjp_json_val*cpcjp_parse_stream(struct cpcio____istream*is)
{
	struct cppstring CPCJP_BOOL_TRUE=mk_from_cstr("true");
	struct cppstring CPCJP_BOOL_FALSE=mk_from_cstr("false");
	struct cppstring CPCJP_NULL_STR=mk_from_cstr("null");
	struct cpcjp_json_val*val=NULL;
	struct cpcjp_parse_helper*top=cpcjp_mk_helper(val,NULL);
	struct cpcio____ostream*os=cpcio_open_osstream();
	struct cppstring curr_obj_dat;
	struct cppstring curr_obj_name;
	char ch=cpcio_getc_is(is);
	bool last_char_slash=false;
	cpcjp_json_num*tmpd=NULL;
	struct cpcds_vector_cpcjp_json_list*tmpv=NULL;
	struct cpcds_um_cpcjp_json_map*tmpmp=NULL;
	struct cpcjp_json_val*tmpj=NULL;
	struct cpcjp_parse_helper*tmph=NULL;
	struct cppstring*tmps=NULL;
	while(ch!=-1)
	{
		switch(ch)
		{
			case DQUOTE:
				curr_obj_name=mk_empty_str();
				ch=cpcio_getc_is(is);
				while(ch!=DQUOTE)
				{
					if(last_char_slash)
					{
						switch(ch)
						{
							case BSLASH:
								cpcio_putc_os(os,ch);
								break;
							case'n':
								cpcio_putc_os(os,'\n');
								break;
							case'r':
								cpcio_putc_os(os,'\r');
								break;
							case'b':
								cpcio_putc_os(os,'\b');
								break;
							case'a':
								cpcio_putc_os(os,'\a');
								break;
							case'f':
								cpcio_putc_os(os,'\f');
								break;
							case't':
								cpcio_putc_os(os,'\t');
								break;
							case'v':
								cpcio_putc_os(os,'\v');
								break;
							case'\'':
								cpcio_putc_os(os,'\'');
								break;
							case DQUOTE:
								cpcio_putc_os(os,DQUOTE);
								break;
							default:
								cpcio_putc_os(os,ch);
								break;
						}
					}
					else
					{
						if(ch==BSLASH)
						{
							last_char_slash=true;
						}
						else
						{
							/*if(ch == -1)
								printf("%lu\n", strlen(cpcio_oss_str(os)));*/
							cpcio_putc_os(os,ch);
						}
					}
					ch=cpcio_getc_is(is);
					if(last_char_slash&&ch==DQUOTE)
					{
						cpcio_putc_os(os,DQUOTE);
						ch=cpcio_getc_is(is);
					}
				}
				curr_obj_dat=mk_from_cstr(cpcio_oss_str(os));
				do
				{
					ch=cpcio_getc_is(is);
				}
				while(ch!=COLON&&ch!=COMMA);
				if(ch==COLON)
				{
					curr_obj_name=curr_obj_dat;
					curr_obj_dat=mk_empty_str();
				}
				else
				{
					tmpj=(struct cpcjp_json_val*)malloc(sizeof(struct cpcjp_json_val));
					tmpj->stuff=malloc(sizeof(struct cppstring));
					tmps=(struct cppstring*)tmpj->stuff;
					*tmps=curr_obj_dat;
					if(top->stuff->type==CPCJP_LIST)
					{
						cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)top->stuff->stuff,tmpj);
					}
					else if(top->stuff->type==CPCJP_OBJ)
					{
						cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)top->stuff->stuff,curr_obj_name,tmpj);
					}
				}
				break;
			case COLON:
				curr_obj_name=mk_from_cstr(cpcio_oss_str(os));
				cpcio_close_ostream(os);
				free(os);
				os=NULL;
				break;
			case COMMA:
				curr_obj_dat=mk_from_cstr(cpcio_oss_str(os));
				if(top->stuff->type==CPCJP_LIST)
				{
				}
				else if(top->stuff->type==CPCJP_OBJ)
				{
					tmpmp=(struct cpcds_um_cpcjp_json_map*)top->stuff->stuff;
				}
				break;
			case LSQRBR:
				tmpv=(struct cpcds_vector_cpcjp_json_list*)malloc(sizeof(struct cpcds_vector_cpcjp_json_list));
				*tmpv=cpcds_mk_vec_default_cpcjp_json_list();
				tmpj=(struct cpcjp_json_val*)malloc(sizeof(struct cpcjp_json_val));
				tmpj->stuff=(union iocjv*)tmpv;
				tmpj->type=CPCJP_LIST;
				top=cpcjp_mk_helper(tmpj,top);
				break;
			case RSQRBR:
				tmph=top;
				top=top->up;
				if(top!=NULL)
				{
					if(top->stuff->type==CPCJP_LIST)
					{
						cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)top->stuff->stuff,tmph->stuff);
					}
					else if(top->stuff->type==CPCJP_OBJ)
					{
						cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)top->stuff->stuff,curr_obj_name,tmph->stuff);
					}
				}
				else
				{
					val=tmph->stuff;
				}
				free(tmph);
				break;
			case LBRACE:
				tmpmp=(struct cpcds_um_cpcjp_json_map*)malloc(sizeof(struct cpcds_um_cpcjp_json_map));
				*tmpmp=cpcds_mk_um_empty_cpcjp_json_map();
				tmpj=(struct cpcjp_json_val*)malloc(sizeof(struct cpcjp_json_val));
				tmpj->stuff=(union iocjv*)tmpmp;
				tmpj->type=CPCJP_OBJ;
				if(top->up==NULL)
				{
					val=tmpj;
					top->stuff = val;
				}
				else
				{
					top=cpcjp_mk_helper(tmpj,top);
				}
				break;
			case RBRACE:
				tmph=top;
				top=top->up;
				if(top!=NULL)
				{
					if(top->stuff->type==CPCJP_LIST)
					{
						cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)top->stuff->stuff,tmph->stuff);
					}
					else if(top->stuff->type==CPCJP_OBJ)
					{
						cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)top->stuff->stuff,curr_obj_name,tmph->stuff);
					}
				}
				else
				{
					val=tmph->stuff;
				}
				free(tmph);
				break;
			default:
				if(os==NULL)
				{
					os=cpcio_open_osstream();
				}
				cpcio_putc_os(os,ch);
				ch=cpcio_getc_is(is);
				while(cpcjp_is_whitespace(ch))
				{
					//cpcio_putc_os(os,ch);
					ch=cpcio_getc_is(is);
				}
				if(cpcjp_is_alphanumeric(ch))
				{
					curr_obj_dat=mk_from_cstr(cpcio_oss_str(os));
					top=cpcjp_mk_helper(NULL,top);
					top->stuff=(struct cpcjp_json_val*)malloc(sizeof(struct cpcjp_json_val));
					if(str_char_at(&curr_obj_dat,0)>='0'&&str_char_at(&curr_obj_dat,0)<='9'||str_char_at(&curr_obj_dat,0)=='+'||str_char_at(&curr_obj_dat,0)=='-')
					{
						top->stuff->type=CPCJP_NUM;
						top->stuff->stuff=malloc(sizeof(cpcjp_json_num));
						tmpd=(cpcjp_json_num*)top->stuff->stuff;
						*tmpd=strtod(cstr(&curr_obj_dat),NULL);
					}
					else if(str_equal_values(CPCJP_BOOL_TRUE,curr_obj_dat))
					{
						top->stuff->type=CPCJP_BOOL;
						top->stuff->stuff=malloc(sizeof(cpcjp_json_bool));
						for(char*it=(char*)top->stuff->stuff;it!=(char*)(top->stuff->stuff+sizeof(cpcjp_json_bool));++it)
						{
							if(it+1==(char*)(top->stuff->stuff+sizeof(cpcjp_json_bool)))
							{
								*it=1;
							}
							else
							{
								*it='\0';
							}
						}
					}
					else if(str_equal_values(CPCJP_BOOL_FALSE,curr_obj_dat))
					{
						top->stuff->type=CPCJP_BOOL;
						top->stuff->stuff=malloc(sizeof(cpcjp_json_bool));
						for(char*it=(char*)top->stuff->stuff;it!=(char*)(top->stuff->stuff+sizeof(cpcjp_json_bool));++it)
						{
							*it='\0';
						}
					}
					else if(str_equal_values(CPCJP_NULL_STR,curr_obj_dat))
					{
						top->stuff->type=CPCJP_NULL;
						top->stuff->stuff=NULL;
					}
				}
				else
				{
					cpcio_ungetc_is(is);
				}
				break;
		}
		ch=cpcio_getc_is(is);
		printf("%d\n", (int)ch);
	}
	return val;
}
struct cpcjp_json_val*cpcjp_parse_str(const struct cppstring s)
{
	return cpcjp_parse_cstr(cstr(&s));
}
struct cpcjp_json_val*cpcjp_parse_cstr(const char*str)
{
	struct cpcio____istream*is=cpcio_open_isstream(str);
	struct cpcjp_json_val*val=cpcjp_parse_stream(is);
	cpcio_close_istream(is);
	free(is);
	return val;
}
struct cpcjp_json_val*cpcjp_parse_arr(const char*arr,size_t sz)
{
	char*new=malloc(sz+1);
	memcpy(new,arr,sz);
	new[sz]='\0';
	struct cpcjp_json_val*val=cpcjp_parse_cstr(new);
	free(new);
	return val;
}
#endif
#endif
