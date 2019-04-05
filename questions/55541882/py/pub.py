#!/usr/bin/python3

import time
import zmq
context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://127.0.0.1:5555")

# Allow clients to connect before sending data
time.sleep(3)
while True:
    socket.send_json({1:[1,2,3]})
    time.sleep(1)
