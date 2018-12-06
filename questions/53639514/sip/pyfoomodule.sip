%Module(name=PyFooModule, call_super_init=True, keyword_arguments="Optional")
%DefaultMetatype PyQt4.QtCore.pyqtWrapperType
%DefaultSupertype sip.simplewrapper
%Include base.sip
%Include derived.sip