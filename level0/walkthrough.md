Once we decompile the binary level0, we can see that if we give 423 as first argument, we will have a shell as user1.

```bash
./level0 423
```

Then, we juste have to go to `/home/user/level1`:

```bash
cd /home/user/level1; cat .pass
```

>$ cd /home/user/level1; cat .pass
>1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a

```bash
su level01
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
