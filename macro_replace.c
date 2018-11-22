#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void macro_replace(char *file)
{
	char buf[1000],*ptr,macro_name[100],expansion[100];
	int i,j;
	FILE *fsrc,*ftar;
	fsrc=fopen(file,"r");
	ftar=fopen("temp.c","w+");
	
	//extract macro_name and expansion from file
	while(fscanf(fsrc,"%s",buf)==1)
	{
	    if(strstr(buf,"#define"))
	    {
	        fscanf(fsrc,"%s",macro_name);
		fscanf(fsrc,"%s",expansion);
		break;
	    }
	}
	rewind(fsrc);

	//find and replace macro_name with expansion
	while(fgets(buf,sizeof(buf),fsrc)!=NULL)
	{
	    if(strstr(buf,"#define"))
	        continue;
	    if(!strstr(buf,"printf"))
	    {
		if((ptr=strstr(buf,macro_name)))
		{
		    for(i=0;i<ptr-buf;i++)
		        fputc(buf[i],ftar);
		    for(j=0;j<strlen(expansion);j++)
			fputc(expansion[j],ftar);
		    for(i=ptr-buf+strlen(macro_name);i<strlen(buf);i++)
			fputc(buf[i],ftar);
		}
		else
		    for(i=0;i<strlen(buf);i++)
			fputc(buf[i],ftar);
	    }
	    else
		for(i=0;i<strlen(buf);i++)
		    fputc(buf[i],ftar);
	}

	fclose(fsrc);
	fclose(ftar);
}
