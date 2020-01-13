FROM elementary/docker:stable

MAINTAINER eyllanesc <e.yllanescucho@gmail.com>

RUN apt-get update && \
	apt-get autoclean

RUN apt-get update && apt-get install \
	-y --no-install-recommends \
	python3-pip \
	python3-setuptools

RUN python3 -m pip install pyqt5==5.14 pyqtchart==5.14

COPY main.py .
CMD ["python3", "main.py"]