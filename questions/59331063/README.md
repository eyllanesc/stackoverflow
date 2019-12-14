Tested on Ubuntu 18.04

## How to use it
You can **clone** this github repository and then run this command to check if it's working

**Run**
```
docker run -it \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -e DISPLAY=$DISPLAY \
    --device /dev/dri --device /dev/snd \
    --privileged \
    -v /run/dbus/:/run/dbus/ \
    --group-add $(getent group audio | cut -d: -f3) \
    so-59331063:latest
```

**Build**
```
docker build --tag=so-59331063 .
```
