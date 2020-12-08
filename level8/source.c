#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef	unsigned char	byte;	/* 8-bit data */
typedef int 			bool;
#define true	1
#define false	1


int main(void)
{
	char		cVar1;
	char		*pcVar2;
	int			iVar3;
	uint32_t	uVar4;
	byte 		*pbVar5;
	byte 		*pbVar6;
	bool 		bVar7;
	bool 		bVar8;
	bool 		bVar9;
	byte 		bVar10;
	byte 		local_90 [5];
	char 		local_8b [2];
	char 		acStack137 [125];
	
	bVar10 = 0;
	while( true )
	{
		printf("%p, %p \n",auth,service);
		pcVar2 = fgets((char *)local_90,0x80,stdin);
		bVar7 = false;
		bVar9 = pcVar2 == (char *)0x0;
		if (bVar9) {
			return 0;
		}
		iVar3 = 5;
		pbVar5 = local_90;
		pbVar6 = (byte *)"auth ";
		while (bVar9){
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			bVar7 = *pbVar5 < *pbVar6;
			bVar9 = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (uint32_t)bVar10 * -2 + 1;
			pbVar6 = pbVar6 + (uint32_t)bVar10 * -2 + 1;
		} 
		bVar8 = false;
		bVar7 = (!bVar7 && !bVar9) == bVar7;
		if (bVar7) {
			auth = (undefined4 *)malloc(4);
			*auth = 0;
			uVar4 = 0xffffffff;
			pcVar2 = local_8b;
			while (cVar1 != 0)
			{
				if (uVar4 == 0)
					break;
				uVar4 = uVar4 - 1;
				cVar1 = *pcVar2;
				pcVar2 = pcVar2 + (uint32_t)bVar10 * -2 + 1;
			}
			uVar4 = ~uVar4 - 1;
			bVar8 = uVar4 < 0x1e;
			bVar7 = uVar4 == 0x1e;
			if (uVar4 < 0x1f) {
				strcpy((char *)auth,local_8b);
			}
		}
		iVar3 = 5;
		pbVar5 = local_90;
		pbVar6 = (byte *)"reset";
		while (bVar7)
		{
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			bVar8 = *pbVar5 < *pbVar6;
			bVar7 = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (uint32_t)bVar10 * -2 + 1;
			pbVar6 = pbVar6 + (uint32_t)bVar10 * -2 + 1;
		}
		bVar9 = false;
		bVar7 = (!bVar8 && !bVar7) == bVar8;
		if (bVar7) {
			free(auth);
		}
		iVar3 = 6;
		pbVa5 = local_90;
		pbVar6 = (byte *)"service";
		while (bVar7)
		{
			if (iVar3 == 0) break;
			iVar3 = iVar3 + -1;
			bVar9 = *pbVar5 < *pbVar6;
			bVar7 = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (uint32_t)bVar10 * -2 + 1;
			pbVar6 = pbVar6 + (uint32_t)bVar10 * -2 + 1;
		} 
		bVar8 = false;
		bVar7 = (!bVar9 && !bVar7) == bVar9;
		if (bVar7) {
			bVar8 = (byte *)0xfffffff8 < local_90;
			bVar7 = acStack137 == (char *)0x0;
			service = strdup(acStack137);
		}
		iVar3 = 5;
		pbVar5 = local_90;
		pbVar6 = (byte *)"login";
		while (bVar7)
		{
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			bVar8 = *pbVar5 < *pbVar6;
			bVar7 = *pbVar5 == *pbVar6;
			pbVar5 = pbVar5 + (uint32_t)bVar10 * -2 + 1;
			pbVar6 = pbVar6 + (uint32_t)bVar10 * -2 + 1;
		}
		if ((!bVar8 && !bVar7) == bVar8) {
			if (auth[8] == 0) {
				fwrite("Password:\n",1,10,stdout);
			}
			else {
				system("/bin/sh");
			}
		}
	} 
}
