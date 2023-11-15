// objloader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <vector>

typedef struct txyz{
	float x,y,z;
};

typedef struct tuv{
	float u,v;
};
typedef struct tind{
	int iv[3], im[3];
};

typedef struct tobj{
	int no_vertices;	
	txyz *xyz;
	tuv *uv;
};

void load_obj(tobj *obj,char *name)
{
#define tmp_size (100)

	FILE *f;
	char tmp[tmp_size];
	std::vector<txyz> v_xyz;
	std::vector<tuv> v_uv;
	std::vector<tind> v_ind;

	txyz t_xyz;
	tuv t_uv;
	tind t_ind;

	f = fopen(name,"rt");
	if (!f) return;
	while(!feof(f))
	{
		//read line;
		fgets(tmp,tmp_size,f);
		switch(tmp[0])
		{
		case '#':
			// obj comment
			break;
		case 'v':
			// vertex data
			{
				switch(tmp[1])
				{
				case ' ':
					// xyz data								
					sscanf(tmp+1,"%g %g %g",&t_xyz.x,&t_xyz.y,&t_xyz.z);					
					//printf("x=%f y=%f z=%f\n\n",t_xyz.x,t_xyz.y,t_xyz.z);
					v_xyz.push_back(t_xyz);
					break; 
				case 't':
					// uv data
					sscanf(tmp+2,"%g %g",&t_uv.u,&t_uv.v);					
					//printf("u=%f v=%f\n\n",t_uv.u,t_uv.v);
					v_uv.push_back(t_uv);
					break;
				}
			}
			break;
		case 'f':
			// face data

			char *t = tmp+2;

			t+= 1 + sscanf(t,"%d",&t_ind.iv[0]); if(t_ind.iv[0]>99) t+=2; else if(t_ind.iv[0]>9) t+=1;
			t+= 2 + sscanf(t,"%d",&t_ind.im[0]);if(t_ind.im[0]>99) t+=2; else if(t_ind.im[0]>9) t+=1;

			t+= 1 + sscanf(t,"%d",&t_ind.iv[1]);if(t_ind.iv[1]>99) t+=2; else if(t_ind.iv[1]>9) t+=1;
			t+= 2 + sscanf(t,"%d",&t_ind.im[1]);if(t_ind.im[1]>99) t+=2; else if(t_ind.im[1]>9) t+=1;

			t+= 1 + sscanf(t,"%d",&t_ind.iv[2]);if(t_ind.iv[2]>99) t+=2; else if(t_ind.iv[2]>9) t+=1;
			t+= 2 + sscanf(t,"%d",&t_ind.im[2]);if(t_ind.im[2]>99) t+=2; else if(t_ind.im[2]>9) t+=1;

			v_ind.push_back(t_ind);
			
			break;
		}

	}
	fclose(f);
	if(!obj) return;
	obj->no_vertices = (v_ind.size())*3;
	obj->xyz = new txyz[obj->no_vertices];
	obj->uv = new tuv[obj->no_vertices];

	int j=0,k = 0;
	for(std::vector<tind>::iterator i = v_ind.begin();i!=v_ind.end();++i)
	{
		t_ind = *i;
		obj->xyz[j++] = v_xyz[i->iv[0]-1];
		obj->xyz[j++] = v_xyz[i->iv[1]-1];
		obj->xyz[j++] = v_xyz[i->iv[2]-1];		

		obj->uv[k++] = v_uv[i->im[0]-1];
		obj->uv[k++] = v_uv[i->im[1]-1];
		obj->uv[k++] = v_uv[i->im[2]-1];
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc!=2) return 1;
	printf("//file: %s\n",argv[1]);

	tobj myobj;

	load_obj(&myobj,argv[1]);

	//print obj
	printf("GLfloat vertices[] = {\n");
	int j=0;
	for(int i=0;i<myobj.no_vertices;i++)
	{
		printf("%f, %f, %f,\n",myobj.xyz[j].x,myobj.xyz[j].y,myobj.xyz[j].z);
		j++;
	}
	printf("};\n\n");

	printf("GLfloat uvmaps[] = {\n");
	j=0;
	for(int i=0;i<myobj.no_vertices;i++)
	{
		printf("%f, %f,\n",myobj.uv[j].u,myobj.uv[j].v);
		j++;
	}
	printf("};\n");
	

	return 0;
}

