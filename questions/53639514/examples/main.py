from PyQt4 import QtCore
from PyFooModule import Base, Derived

class PyDerived(Base):
	def doStuff(self):
		return "PyDerived"

if __name__ == '__main__':
	print("==============================")
	b = Base()
	pd = PyDerived()
	d = Derived()
	print("b.doStuff(): ", b.doStuff())
	print("pd.doStuff(): ", pd.doStuff())
	print("d.doStuff(): ", d.doStuff())
	print("==============================")
	print("Base is subclass of QObject: ", issubclass(Base, QtCore.QObject))
	print("PyDerived is subclass of Base: ", issubclass(PyDerived, Base))
	print("Derived is subclass of Base: ", issubclass(Derived, Base))
	print("==============================")
