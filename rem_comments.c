#include<stdio.h>
#include<stdlib.h>
void rem_cmnts(char *file)
{
	int len,i=0,s_cmt=0,m_cmt=0;
	char *buf,ch;
	FILE *fsrc,*fdest,*ftemp;

	fsrc=fopen(file,"r");
	fdest=fopen("out.i","w");
	ftemp=fopen("temp2.c","w+");
	fseek(fsrc,0,SEEK_END);
	len=ftell(fsrc);
	rewind(fsrc);
	buf=calloc(1,len+1);
	fread(buf,len,1,fsrc);

	for(i=0;buf[i];i++)
	{
	    // If single line comment flag is on, then check for end of it
	    if(s_cmt==1 && buf[i]=='\n')
	        s_cmt=0,i++;
	    // If multiple line comment is on, then check for end of it
	    else if(m_cmt==1 &&  buf[i]=='*' && buf[i+1]=='/')
		m_cmt=0,i++;
	    // If this character is in a comment, ignore it
	    else if(s_cmt || m_cmt)
		continue;
	    // Checks for beginning of comments
	    else if(buf[i]=='/' && buf[i+1]=='/')
		s_cmt=1,i++;
	    else if(buf[i]=='/' && buf[i+1]=='*')
		m_cmt=1,i++;
	    else
		fputc(buf[i],ftemp);
	}
	
	rewind(ftemp);
	while((ch=fgetc(ftemp))!=EOF)
	    fputc(ch,fdest);

	fclose(fsrc);
	fclose(fdest);
	fclose(ftemp);
	remove(file);
	remove("temp2.c");
}
