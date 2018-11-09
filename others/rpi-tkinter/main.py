from tkinter import Tk,Label,Button
from tkinter import *
import sys
import time
import os
import RPi.GPIO as GPIO
GPIO.setwarnings(False)
GPIO.cleanup()
GPIO.setmode(GPIO.BCM)
GPIO.setup(21,GPIO.IN, pull_up_down =GPIO.PUD_DOWN)
top=Tk()
top.minsize(666,666)
top.maxsize(666,666)
######################################################################
class App:
	def __init__(self, master):
		####################################################################
		self.button = Button(top, text='START',command=self.convert0)
		self.button.place(x=50,y=50)
		self.label=Label(top,text='').grid(row=20, column=5)
		self.clock = Label(top, font=('times', 20, 'bold'), bg='green')
		self.clock.place(x=200,y=200)
		self.isRunning = False
		GPIO.add_event_detect(21, GPIO.BOTH, callback=self.callback)
		###################################################################
	def convert0 ( self,tog=[0]): 
		tog[0] = not tog[0]
		if tog[0]:
			#########################################
			self.button.config(text='START')
			self.button.configure(bg = "blue")
			self.button.configure(fg = "white")
			self.label=Label(top,text='OFF',bg="blue",fg="white").place(x=150,y=55)
			#########################################
		else:
			self.button.config(text='STOP')
			self.button.configure(bg ="red")
			self.button.configure(fg ="white")
			self.label=Label(top,text='OFF',bg="red",fg="red").place(x=150,y=55)
			self.label=Label(top,text='ON',bg="red",fg="white").place(x=150,y=55)
	#########################################
	def tick(self):
		# get the current local time from the PC
		time1 = time.strftime('%I:%M:%S')
		# if time string has changed, update it
		self.clock.config(text=time1)
		# calls itself every 200 milliseconds
		# to update the time display as needed
		# could use >200 ms, but display gets jerky
		if self.isRunning:
			self.clock.after(200,self.tick)
	###################################################################

	def start(self):
		self.isRunning = True
		self.clock.after(200,self.tick)

	def stop(self):
		self.isRunning = False

	def callback(self, channel):
		if self.isRunning:
			self.stop()
		else:
			self.start()


app = App(top)
top.mainloop()
