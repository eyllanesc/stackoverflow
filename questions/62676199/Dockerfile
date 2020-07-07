FROM centos:7

RUN yum -y update && yum clean all

RUN yum -y install python3 python3-pip

RUN python3 -m pip install -vvv --default-timeout=10000 PySide2

RUN yum -y install libGL

RUN python3 -m pip install aqtinstall

RUN python3 -m aqt install 5.15.0 linux desktop --outputdir qt

RUN yum -y install git

RUN yum -y install libxcb libxcb-devel xcb-util xcb-util-devel xcb-util-*-devel libX11-devel libXrender-devel libxkbcommon-devel libxkbcommon-x11-devel libXi-devel libdrm-devel libXcursor-devel libXcomposite-devel
RUN yum -y install centos-release-scl
RUN yum -y install devtoolset-7-gcc*

RUN git clone -b 5.15.0 git://code.qt.io/qt/qtbase.git

RUN yum -y install mysql-devel
ENV PATH="/qt/5.15.0/gcc_64/bin:${PATH}"

RUN yum -y groupinstall 'Development Tools'
RUN sed -i 's/QMAKE_USE += mysql/# QMAKE_USE += mysql/g' qtbase/src/plugins/sqldrivers/mysql/mysql.pro
RUN echo "INCLUDEPATH += /usr/include/mysql" >> qtbase/src/plugins/sqldrivers/mysql/mysql.pro
RUN echo "QMAKE_LIBDIR += /usr/lib64/mysql" >> qtbase/src/plugins/sqldrivers/mysql/mysql.pro
RUN echo "LIBS += -lmysqlclient" >> qtbase/src/plugins/sqldrivers/mysql/mysql.pro

RUN source scl_source enable devtoolset-7 && \
    cd /qtbase/src/plugins/sqldrivers/mysql && \
    qmake && \
    make && \
    cp ../plugins/sqldrivers/libqsqlmysql.so /usr/local/lib64/python3.6/site-packages/PySide2/Qt/plugins/sqldrivers

COPY main.py main.py

RUN python3 main.py
