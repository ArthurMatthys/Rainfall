int main(int argc, char **argv)

{
	int uVar1;
	char local_3c [40];
	int local_14;

	local_14 = atoi(*(char **)(argv[1]));
	if (local_14 < 10) {
		memcpy(local_3c,*(void **)(argv[2]),local_14 * 4);
		if (local_14 == 0x574f4c46) {
			execl("/bin/sh","sh",0);
		}
		uVar1 = 0;
	}
	else {
		uVar1 = 1;
	}
	return uVar1;
}

