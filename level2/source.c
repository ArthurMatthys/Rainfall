
void p(void)
{
  uint local_res0;
  char str [76];
  
  fflush(stdout);
  gets(str);
  if ((local_res0 & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n",local_res0);
                    /* WARNING: Subroutine does not return */
    _exit(1);
  }
  puts(local_50);
  strdup(local_50);
  return;
}

void main(void)
{
  p();
  return;
}
