void macro_replace(char*);
void rem_cmnts(char*);
void header_incl(char*);

int main(int argc,char **argv)
{
  //macro_replace(argv[1]);
  header_incl(argv[1]);
  rem_cmnts("temp1.c");
return 0;
}
