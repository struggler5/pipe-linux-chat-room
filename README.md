# pipe-linux-chat-room
project for IPB course operating systems



![](assets/2025-12-30-14-36-08.png)
 
## Code

### Server 

```cpp
#define FIFO_PATH "/tmp/myfifo"
```
>Defining the path for the named pipe

```cpp
mkfifo(FIFO_PATH, 0666);

...

unlink(FIFO_PATH);
```

> Making and removing the named pipe after the process is done


### Writer 

```cpp
int fl = open(FIFO_PATH,O_WRONLY); 
```
> opening the named pipe


```cpp
write(fl,message,strlen(message));
```

> Writing to the named pipe

### Reader 

```cpp
while ((n = read(fl, buffer, sizeof(buffer) - 1)) > 0) {
    buffer[n] = '\0';
    printf("Received: %s", buffer);
}
```

>While the read string is valid, prints the message and adds the end string to the end of the bufffer

## Compiling

> The files are already compiled so they should be run in the folloing order

1. Server
2. Writer
3. Reader

*The order doesn't much matter as long as the server is ran first*



## Developers 

m323241 Vleju Dumitru Aurel


m323031 Baris Efe Turkmen
