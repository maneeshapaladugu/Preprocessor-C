#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void header_incl(char *input_file)
{
  FILE *fsrc,*ftar,*fpath;
  int len,i,j;
  char buf1[1024],*buf2,header_name[100],header_path[1024];

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  // open the input file and check if it is existed or not
  fsrc=fopen(input_file,"r");
  if(fsrc==NULL)
  {
    printf("%s: No such file or directory\n",input_file);
    return;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  // open the target file to store the output of this function
  ftar=fopen("temp1.c","w");

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  // copy the each header file content to target file
  while(fgets(buf1,sizeof(buf1),fsrc) != NULL)
  {
    if(strstr(buf1,"#include")!=NULL)                      // if true, copy header file content
    {
      if(buf1[8]=='<')
      {
        i=9;
        j=0;
        bzero(header_name,100);
        while(buf1[i]!='>')
          header_name[j++]=buf1[i++];
        strcpy(header_path,"/usr/include/");
        strcat(header_path,header_name);
        fpath=fopen(header_path,"r");
        fseek(fpath,0,SEEK_END);
        len=ftell(fpath);
        rewind(fpath);
        buf2=calloc(len,sizeof(char));
        fread(buf2,len,1,fpath);
        fwrite(buf2,1,len,ftar);
        free(buf2);
      }
    }
    else                                                   // else, copy the source file line
    {
      fputs(buf1,ftar);
    }
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////

  // finally, close all the streams associated with the files
  fclose(fsrc);
  fclose(ftar);
  fclose(fpath);
}
