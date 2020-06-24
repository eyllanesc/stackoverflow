
### Build

```console
docker build -t 62555286:latest "."
```

### Run

```console
$ docker run -it 62555286:latest
qt_user@fd38358636c3:~$ python main_pyqt5.py 
LINESTRING(11.333333 51, 11.666667 50)
qt_user@fd38358636c3:~$ rm foo.sqlite 
qt_user@fd38358636c3:~$ python main_pyside2.py 
LINESTRING(11.333333 51, 11.666667 50)
```