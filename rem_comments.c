#include<stdio.h>
#include<stdlib.h>
void rem_cmnts(char *input_file)
{
  FILE *fsrc,*fdest,*ftemp;
  int len,i=0,s_cmt=0,m_cmt=0;
  char *buf;

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  // open the source file and copy it to the buf
  fsrc=fopen(input_file,"r");
  fdest=fopen("out.i","w");
  ftemp=fopen("temp2.c","w+");
  fseek(fsrc,0,SEEK_END);
  len=ftell(fsrc);
  rewind(fsrc);
  buf=calloc(len,sizeof(char));
  fread(buf,len,1,fsrc);

  /////////////////////////////////////////////////////////////////////////////////////////////////

  // check character by character and only copy characters which are not in comments
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
  free(buf);

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  // copy the data from temporary file to destination file (out.i)
  fseek(ftemp,0,SEEK_END);
  len=ftell(ftemp);
  rewind(ftemp);
  buf=calloc(len,sizeof(char));
  fread(buf,len,1,ftemp);
  fwrite(buf,1,len,fdest);

  /////////////////////////////////////////////////////////////////////////////////////////////////

  // finally, close all the streams associated with the files
  fclose(fsrc);
  fclose(fdest);
  fclose(ftemp);
  remove(input_file);
  remove("temp2.c");
}
