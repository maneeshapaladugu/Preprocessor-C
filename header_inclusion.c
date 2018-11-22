#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void header_incl(char *file)
{
	FILE *fsrc,*ftar,*fpath;
	int len,cur,prev=0,i,j;
	char *buf,header[100],path[1024],ch;

	fsrc=fopen(file,"r");if(fsrc==NULL){printf("%s: No such file or directory\n",file);return;}
	ftar=fopen("temp1.c","w");

	while((ch=fgetc(fsrc))!=EOF)
	{
	    if(ch=='\n')
	    {
		cur=ftell(fsrc);
		buf=calloc(1,cur+1);
		fseek(fsrc,-(cur-prev),SEEK_CUR);
		fread(buf,(cur-prev),1,fsrc);
		if(strstr(buf,"#include")!=NULL)
		{
		    if(buf[8]=='<')
		    {
			i=9;
			j=0;
			bzero(header,100);
			while(buf[i]!='>')
			    header[j++]=buf[i++];
			strcpy(path,"/usr/include/");
			strcat(path,header);
			fpath=fopen(path,"r");
			fseek(fpath,0,SEEK_END);
			len=ftell(fpath);
			rewind(fpath);
			buf=calloc(1,len+1);
			fread(buf,len,1,fpath);
			fputs(buf,ftar);
			free(buf);
		    }
		}
		else
		{
			fputs(buf,ftar);
			free(buf);
		}
		prev=cur;
	    }
	}

	fclose(fsrc);
	fclose(ftar);
	fclose(fpath);
	remove(file);
}
