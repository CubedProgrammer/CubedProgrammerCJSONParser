#ifndef __cplusplus
#ifndef Included_header_only_json_obj_parser_h
#define Included_header_only_json_obj_parser_h
#include<cpcjp_json_obj.h>
#include<cpcjp_json_parser.h>
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
struct cpcjp_parse_helper*cpcjp_mk_helper(struct cpcjp_json_val*stuff,struct cpcjp_parse_helper*up)
{
	struct cpcjp_parse_helper*x=(struct cpcjp_parse_helper*)malloc(sizeof(struct cpcjp_parse_helper));
	x->stuff=stuff;
	x->up=up;
	return x;
}
struct cpcjp_json_val*cpcjp_parse_stream(cpcio_istream is)
{
	struct cppstring CPCJP_BOOL_TRUE=mk_from_cstr("true");
	struct cppstring CPCJP_BOOL_FALSE=mk_from_cstr("false");
	struct cppstring CPCJP_NULL_STR=mk_from_cstr("null");
	struct cpcjp_json_val*val=NULL;
	struct cpcjp_parse_helper*top=NULL;
	cpcio_ostream os=cpcio_open_osstream();
	struct cppstring curr_obj_dat;
	struct cppstring curr_obj_name=mk_empty_str();
	//cpcjp_json_list*tmpl=NULL;
	//struct cpcjp_json_val*tmpv=NULL;
	char ch=cpcio_getc_is(is);
	bool last_char_slash=false;
	struct cpcjp_json_val*tmpj=NULL;
	struct cpcjp_parse_helper*tmph=NULL;
	while(ch!=-1)
	{
		switch(ch)
		{
			case DQUOTE:
				ch=cpcio_getc_is(is);
				if(os == NULL)
				{
					os = cpcio_open_osstream();
				}
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
				cpcio_close_ostream(os);
				free(os);
				os = NULL;
				do
				{
					ch=cpcio_getc_is(is);
				}
				while(ch=='\n'||ch==' '||ch=='\t');
				if(ch==COLON)
				{
					curr_obj_name=curr_obj_dat;
					curr_obj_dat=mk_empty_str();
					//cpcds_stdprint_cppstr(curr_obj_name);
					//printf(" is curr_obj_name\n");
				}
				else
				{
					tmpj=(struct cpcjp_json_val*)malloc(sizeof(struct cpcjp_json_val));
					tmpj->stuff=malloc(sizeof(union iocjv));
					tmpj->stuff->str=curr_obj_dat;
					tmpj->type=CPCJP_STR;
					//cpcds_stdprint_cppstr(curr_obj_name);
					//printf(" is curr_obj_name\n");
					//cpcds_stdprint_cppstr(curr_obj_dat);
					//printf(" is curr_obj_dat\n");
					if(top->stuff->type==CPCJP_LIST)
					{
						cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)top->stuff->stuff,tmpj);
						tmpj->name=NULL;
					}
					else if(top->stuff->type==CPCJP_OBJ)
					{
						cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)top->stuff->stuff,curr_obj_name,tmpj);
						tmpj->name=cstr(&curr_obj_name);
					}
					cpcio_ungetc_is(is);
				}
				break;
			case LSQRBR:
				tmpj=(struct cpcjp_json_val*)malloc(sizeof(struct cpcjp_json_val));
				tmpj->stuff=(union iocjv*)malloc(sizeof(union iocjv));
				tmpj->stuff->list=cpcds_mk_vec_default_cpcjp_json_list();
				tmpj->type=CPCJP_LIST;
				tmpj->name=cstr(&curr_obj_name);
				top=cpcjp_mk_helper(tmpj,top);
				break;
			case RSQRBR:
				tmph=top;
				top=top->up;
				/*tmpl=(struct cpcds_vector_cpcjp_json_list*)tmph->stuff->stuff;
				for(size_t i=0;i<tmpl->size/2;i++)
				{
					tmpv=cpcds_vec_get_at_cpcjp_json_list(tmpl,i);
					cpcds_vec_set_single_cpcjp_json_list(tmpl,i,cpcds_vec_get_at_cpcjp_json_list(tmpl,tmpl->size-i-1));
					cpcds_vec_set_single_cpcjp_json_list(tmpl,tmpl->size-i-1,tmpv);
				}*/
				if(top!=NULL)
				{
					if(top->stuff->type==CPCJP_LIST)
					{
						tmph->stuff->name = NULL;
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
				//cpcds_stdprint_cppstr(curr_obj_name);
				//printf("\n");
				//fflush(stdout);
				break;
			case LBRACE:
				tmpj=(struct cpcjp_json_val*)malloc(sizeof(struct cpcjp_json_val));
				tmpj->stuff=(union iocjv*)malloc(sizeof(union iocjv));
				tmpj->stuff->obj=cpcds_mk_um_empty_cpcjp_json_map();
				tmpj->type=CPCJP_OBJ;
				tmpj->name=cstr(&curr_obj_name);
				top=cpcjp_mk_helper(tmpj,top);
				break;
			case RBRACE:
				tmph=top;
				top=top->up;
				if(top!=NULL)
				{
					if(top->stuff->type==CPCJP_LIST)
					{
						tmph->stuff->name = NULL;
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
				//cpcds_stdprint_cppstr(curr_obj_name);
				//printf(" curly\n");
				//fflush(stdout);
				/*for(int i = 0; is->cbuf[i] != -1; ++i)
				{
					printf("%c",is->cbuf[i]);
				}*/
				//printf("\n");
				break;
			case-1:
				break;
			default:
				if(cpcjp_is_alphanumeric(ch))
				{
					if(os==NULL)
					{
						os=cpcio_open_osstream();
					}
					do
					{
						cpcio_putc_os(os,ch);
						ch=cpcio_getc_is(is);
					}
					while(ch=='.'||cpcjp_is_alphanumeric(ch));
					cpcio_ungetc_is(is);
					curr_obj_dat=mk_from_cstr(cpcio_oss_str(os));
					//cpcds_stdprint_cppstr(curr_obj_dat);
					//printf(", %d\n", ch);
					fflush(stdout);
					cpcio_close_ostream(os);
					free(os);
					os = NULL;
					if(curr_obj_dat.len)
					{
						top=cpcjp_mk_helper(NULL,top);
						top->stuff=(struct cpcjp_json_val*)malloc(sizeof(struct cpcjp_json_val));
						if(str_char_at(&curr_obj_dat,0)>='0'&&str_char_at(&curr_obj_dat,0)<='9'||str_char_at(&curr_obj_dat,0)=='+'||str_char_at(&curr_obj_dat,0)=='-')
						{
							top->stuff->type=CPCJP_NUM;
							top->stuff->stuff=malloc(sizeof(union iocjv));
							top->stuff->stuff->num=strtod(cstr(&curr_obj_dat),NULL);
						}
						else if(str_equal_values(CPCJP_BOOL_TRUE,curr_obj_dat))
						{
							top->stuff->type=CPCJP_BOOL;
							top->stuff->stuff=malloc(sizeof(union iocjv));
							top->stuff->stuff->tof = true;
						}
						else if(str_equal_values(CPCJP_BOOL_FALSE,curr_obj_dat))
						{
							top->stuff->type=CPCJP_BOOL;
							top->stuff->stuff=malloc(sizeof(union iocjv));
							top->stuff->stuff->tof = false;
						}
						else if(str_equal_values(CPCJP_NULL_STR,curr_obj_dat))
						{
							top->stuff->type=CPCJP_NULL;
							top->stuff->stuff=NULL;
						}
						else
						{
							//cpcds_stdprint_cppstr(curr_obj_dat);
						}
						tmph = top;
						top = top->up;
						if(top!=NULL)
						{
							if(top->stuff->type==CPCJP_LIST)
							{
								tmph->stuff->name=NULL;
								cpcds_vec_append_single_cpcjp_json_list((struct cpcds_vector_cpcjp_json_list*)top->stuff->stuff,tmph->stuff);
							}
							else if(top->stuff->type==CPCJP_OBJ)
							{
								tmph->stuff->name=cstr(&curr_obj_name);
								cpcds_um_insert_cpcjp_json_map((struct cpcds_um_cpcjp_json_map*)top->stuff->stuff,curr_obj_name,tmph->stuff);
							}
						}
						else
						{
							val=tmph->stuff;
						}
						free(tmph);
					}
				}
				/*printf("just finished default case\n");
				fflush(stdout);*/
				break;
		}
		/*printf("ch used to be %d or %c\n", ch, ch);
		fflush(stdout);*/
		ch=cpcio_getc_is(is);
		/*printf("ch is %d or %c\n", ch, ch);
		fflush(stdout);*/
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
