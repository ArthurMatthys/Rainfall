#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc,char **argv)

{
  int iVar1;
  char *local_20;
  __uid_t local_18;
  __gid_t local_14;
  
  iVar1 = atoi(argv[1]);
  if (iVar1 == 0x1a7) //== 423
  { 
    local_20 = strdup("/bin/sh");
    local_14 = getegid();
    local_18 = geteuid();
    setresgid(local_14,local_14,local_14);
    setresuid(local_18,local_18,local_18);
    execv("/bin/sh",&local_20);
  }
  else {
    fwrite("No !\n",1,5,(FILE *)stderr);
  }
  return 0;
}

