// myasm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>

//labels should have : after the nam
// comments start with ;, everything after is comment

char* keyworkds[] = {
	//sort of directives
	"org",
	"define",
	"data",
	"code",

	// instructions
	"add",
	"store",
	"load",
	"jump",
	"jneg"
};

enum t_opcodes{
	en_add = 0,
	en_store = 1,
	en_load = 2,
	en_jump = 3,
	en_jneg = 4,
	en_out = 5,
};
struct t_coding{
	std::string name;
	t_opcodes val;
};

#define nrinstr	(6)
const t_coding mymachine[nrinstr] = {
	{"add",en_add},
	{"store",en_store},
	{"load",en_load},
	{"jump",en_jump},
	{"jneg",en_jneg},
	{"out",en_out},
};

enum t_state{
	en_init = 0,
	en_defines,
	en_data,
	en_code,
	en_comment,
	en_define_name,
	en_define_value,
	en_data_name,
	en_data_value,
	en_code_opcode,
	en_code_value,
	en_symbol,
	en_value,
	en_label,
};
struct t_data{
	int addr;
	int linenr;
	std::string name;
	std::string comment;
	int value;
};

struct t_code{
	int linenr;
	unsigned int address;
	t_opcodes opcode;
	std::string string_param;
	int int_param;
	std::string orig_code;
	std::string comment;
};

struct t_file{
	t_state last_state;
	t_state sub_state;
	std::vector<t_data> labels;
	std::vector<t_data> defines;
	std::vector<t_data> vars;
	std::vector<t_code> code;
};
int tmp_val;

t_file myfile;
int get_token(char *p, char *pout);
int int_token(char *p);

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *in;
	char tmp[256];
	char tmp2[256];
	char c, i,j;
	int tmp_addr = 0;

	t_data tmp_data;
	t_code tmp_code;

	if(argc!=2) goto error;
	in = fopen(argv[1],"rt");
	if(!in) goto error;
	int tk;
	
	

	//parse file
	while(!feof(in)){
		//read line
		{
			i = 0;
			while(1){
				c = fgetc(in);
				if(c!='\n' && c!='\r' && c!=0 && c!=-1){
					tmp[i++] = c;
				} else {
					tmp[i] = 0;
					break;
				}
			}
		}
		// now we have one line
		//printf("%s\n",tmp);

		// parse line
		i = 0;
		//printf("%s\n",tmp);
		while(1)
		{
			j= get_token(tmp+i,tmp2);
			i+=j;

			if(tmp2[0]!=' ' && tmp2[0]!=0 && tmp2[0]!='\t'){
				//printf(" t=%s",tmp2);
				switch(tk=int_token(tmp2))
				{
				case en_comment:
					//printf("// %s\n",tmp+i);
					goto l2;
					break;
				case en_defines:
					myfile.last_state = en_defines;
					printf("\n***** define seciton\n\n");
					break;
				case en_data:
					myfile.last_state = en_data;
					printf("\n***** data seciton\n\n");
					break;
				case en_code:
					myfile.last_state = en_code;
					printf("\n***** code seciton\n\n");
					break;
				case en_label:
					tmp2[strlen(tmp2)-1]=0;
					printf("%s:\n",tmp2);
					tmp_data.name = tmp2;
					tmp_data.addr = tmp_addr;
					myfile.labels.push_back(tmp_data);
					break;
				case en_value:
					//printf("value= %d\n",tmp_val);
					break;
				case en_symbol:
					//printf("symbol= %s\n",tmp2);
					break;
				}
				switch(myfile.last_state)
				{
				case en_defines:
					//expected symbol
					if(tk == en_symbol)
					{
						printf("#define %s (",tmp2);
						myfile.last_state = en_define_value;
						tmp_data.name = tmp2;
					}
					break;
				case en_define_value:
					//expected symbol
					if(tk == en_value)
					{
						printf("%d)\n",tmp_val);
						myfile.last_state = en_defines;
						tmp_data.value = tmp_val;
						myfile.defines.push_back(tmp_data);
					}
					break;

				case en_data:
					//expected symbol
					if(tk == en_symbol)
					{
						printf("int %s = ",tmp2);
						myfile.last_state = en_data_value;
						tmp_data.name = tmp2;
					}
					break;
				case en_data_value:
					//expected symbol
					if(tk == en_value)
					{
						printf(" %d;\n",tmp_val);
						myfile.last_state = en_data;
						tmp_data.value = tmp_val;
						myfile.vars.push_back(tmp_data);
					}
					break;
				case en_code:
					if(tk == en_symbol)
					{
						printf("\t\t%s\t",tmp2);
						myfile.last_state = en_code_value;
						tmp_code.orig_code = tmp2;
						// search for the code value
						std::string ttmp2 = tmp2;
						for(int i=0;i<nrinstr;i++){
							if(mymachine[i].name == ttmp2){
								tmp_code.opcode = mymachine[i].val;
								break;
							}
						}
					}
					break;
				case en_code_value:
					if(tk == en_symbol)
					{
						printf(" %s\n",tmp2);
						myfile.last_state = en_code;
						tmp_code.string_param = tmp2;
						tmp_code.int_param = -1;
					}			
					if(tk == en_value)
					{
						printf(" %d\n",tmp_val);
						myfile.last_state = en_code;
						tmp_code.int_param = tmp_val;
					}		
					tmp_code.address = tmp_addr;
					myfile.code.push_back(tmp_code);
					tmp_addr++;
					break;

				}
			}
			if(j==0) {
				//printf("<<<\n");
				break;
			}						
		}
l2: ;
	}

	fclose(in);
	char tmp_str[256];
	int tmp_val;

	printf("\n\n*** file process done ***\n\n");
	printf("\nextracted defines:\n");
	for(std::vector<t_data>::iterator i = myfile.defines.begin();i!=myfile.defines.end();++i)
	{
	
		printf("%s %d\n",i->name.c_str(),i->value);
	}

	printf("\nextracted variables:\n");
	int start_addr = myfile.code.at(myfile.code.size()-1).address+1;
	printf("variables start at %d\n",start_addr);
	for(std::vector<t_data>::iterator i = myfile.vars.begin();i!=myfile.vars.end();++i)
	{
		i->addr = start_addr++;
		printf("%d\t%s %d\n",i->addr,i->name.c_str(),i->value);
	}

	printf("\nextracted labels:\n");
	for(std::vector<t_data>::iterator i = myfile.labels.begin();i!=myfile.labels.end();++i)
	{
	
		printf("%s %d\n",i->name.c_str(),i->addr);
	}

	printf("\nresolving symbol names\n");
	for(std::vector<t_code>::iterator i = myfile.code.begin();i!=myfile.code.end();++i){

		if(i->int_param!=-1) continue;
		//search for label define or variable

		//search for label
		for(std::vector<t_data>::iterator j = myfile.labels.begin();j!=myfile.labels.end();++j)	{
			if(j->name == i->string_param){
				i->int_param = j->addr;
				break;
			}
		}
		//search for defines
		for(std::vector<t_data>::iterator j = myfile.defines.begin();j!=myfile.defines.end();++j)	{
			if(j->name == i->string_param){
				i->int_param = j->value;
				break;
			}
		}
		//search for variables
		for(std::vector<t_data>::iterator j = myfile.vars.begin();j!=myfile.vars.end();++j)	{
			if(j->name == i->string_param){
				i->int_param = j->addr;
				break;
			}
		}
	}

	printf("\nextracted code:\n");
	for(std::vector<t_code>::iterator i = myfile.code.begin();i!=myfile.code.end();++i)
	{
	
		printf("%d\t %02d %02d  %s %s\n",i->address,i->opcode,i->int_param, i->orig_code.c_str(),i->string_param.c_str());
	}

	printf("\n\n complete listing \n\n");

	printf("\n;define\n\n");
	for(std::vector<t_data>::iterator i = myfile.defines.begin();i!=myfile.defines.end();++i)
	{
	
		printf(";\t%s\t%d\n",i->name.c_str(),i->value);
	}
	
	printf("\n\n;data\n\n");
	for(std::vector<t_data>::iterator i = myfile.vars.begin();i!=myfile.vars.end();++i)
	{		
		printf(";\t%s\t%d\n",i->name.c_str(),i->value);
	}
/*
for(std::vector<t_data>::iterator j = myfile.labels.begin();j!=myfile.labels.end();++j)	{
			if(j->name == i->string_param){
				i->int_param = j->addr;
				break;
			}
		}
		*/
	{
	std::vector<t_data>::iterator l = myfile.labels.begin();
	printf("\n\n;code\n\n");
	for(std::vector<t_code>::iterator i = myfile.code.begin();i!=myfile.code.end();++i)
	{
		if(l!=myfile.labels.end()){
		if(i->address == l->addr){			
			printf(";%s:\n",l->name.c_str());
			l++;
		}
		}
		printf("%02x\t %02x%02x\t; %s\t%s\n",i->address,i->opcode,i->int_param, i->orig_code.c_str(),i->string_param.c_str());
	}
	}
	
	printf(";vars\n");
	for(std::vector<t_data>::iterator i = myfile.vars.begin();i!=myfile.vars.end();++i)
	{		
		printf("%02x\t %04x\t; %s\n",i->addr,i->value,i->name.c_str());
	}

	return 0;

error:
	printf("usage: myasm.exe inputfile\n"); return -1;
}

int get_token(char *p, char *pout){
	int i = 0;
	while(1){

		i++;
		if(*p==' ' || *p=='\t'){
			p++;
			while(*p==' ' || *p=='\t') {i++;p++;}			
			break;
		}
		if(*p=='\t') break;
		if(*p=='\n') {
			i = 0;break;
		}

		*pout++ = *p;

		if(*p==0) {
			i = 0;
			break;
		}

		if(*p == ';') break;

		p++;

	}
	*pout++ =0;
	return i;
}
int int_token(char *p){
	if(*p==';') return 	en_comment;
	if(strcmp(p,"define")==0) return en_defines;
	if(strcmp(p,"data")==0) return en_data;
	if(strcmp(p,"code")==0) return en_code;
	if(p[strlen(p)-1]==':') return en_label;
	if(isdigit(*p)){
		int val = atoi(p);
		tmp_val = val;
		return en_value;
	}else
	{
		return en_symbol;
	}
	return en_init;
}

