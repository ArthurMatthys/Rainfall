int main(int argc, char **argv)
{
	int res;
	int iVar2;
	char local_98 [16];
	undefined local_57;
	char local_56 [66];
	FILE *local_14;

	local_14 = fopen("/home/user/end/.pass","r");
	if ((local_14 == (FILE *)0x0) || (argc != 2)) {
		res = 0xffffffff;
	}
	else {
		fread(local_98,1,0x42,local_14);
		local_57 = 0;
		iVar2 = atoi(argv[1]);
		*(undefined *)((int)local_98 + iVar2) = 0;
		fread(local_56,1,0x41,local_14);
		fclose(local_14);
		iVar2 = strcmp((char *)local_98,argv[1]);
		if (iVar2 == 0) {
			execl("/bin/sh","sh",0);
		}
		else {
			puts(local_56);
		}
		res = 0;
	}
	return res;
}

