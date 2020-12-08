
void p(char *param_1,char *param_2)

{
  char *pcVar1;
  char buff [4104];

  puts(param_2);
  read(0,buff,0x1000);
  pcVar1 = strchr(buff,10);
  *pcVar1 = 0;
  strncpy(param_1,buff,0x14);
  return;
}


void pp(char *str)

{
	char cVar1;
	unsigned int i;
	char *cpy;
	char bVar4;
	char p_str1 [20];
	char p_str2 [20];

	bVar4 = 0;
	p(p_str1, " - "); //&DAT_080486a0
	p(p_str2, " - ");
	strcpy(str, p_str1);
	i = 0xffffffff;
	cpy = str;
	while (cVar1 != 0)
	{
		if (i == 0) 
			break;
		i = i - 1;
		cVar1 = *cpy;
		cpy = cpy + (unsigned int)bVar4 * -2 + 1;
	}
	*(undefined2 *)(str + (~i - 1)) = 0x20;
	strcat(str, p_str2);
	return;
}

int main(void)

{
	char str [54];

	pp(str);
	puts(str);
	return 0;
}

