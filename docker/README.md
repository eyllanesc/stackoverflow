**Run**
```
docker run -it \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -e DISPLAY=$DISPLAY \
    --device /dev/dri --device /dev/snd \
    --privileged \
    -v /run/dbus/:/run/dbus/ \
    --group-add $(getent group audio | cut -d: -f3) \
    python-qt-ubuntu
```

**Build**
```
docker build --tag=python-qt-ubuntu.
```