#ifndef __cplusplus
#ifndef Included_header_only_json_obj_parser_h
#define Included_header_only_json_obj_parser_h
#include<header_only_cpcjp_json_obj.h>
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
