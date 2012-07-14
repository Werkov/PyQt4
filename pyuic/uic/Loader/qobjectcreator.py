#############################################################################
##
## Copyright (C) 2011 Riverbank Computing Limited.
## Copyright (C) 2006 Thorsten Marek.
## All right reserved.
##
## This file is part of PyQt.
##
## You may use this file under the terms of the GPL v2 or the revised BSD
## license as follows:
##
## "Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are
## met:
##   * Redistributions of source code must retain the above copyright
##     notice, this list of conditions and the following disclaimer.
##   * Redistributions in binary form must reproduce the above copyright
##     notice, this list of conditions and the following disclaimer in
##     the documentation and/or other materials provided with the
##     distribution.
##   * Neither the name of the Riverbank Computing Limited nor the names
##     of its contributors may be used to endorse or promote products
##     derived from this software without specific prior written
##     permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
## "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
## LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
## A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
## OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
## SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
## LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
## DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
## THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
## OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
##
#############################################################################


import sys

from PyQt4 import QtGui


class _QtGuiWrapper(object):
    def search(cls):
        return getattr(QtGui, cls, None)
    search = staticmethod(search)


class _ModuleWrapper(object):
    def __init__(self, moduleName, classes):
        self._moduleName = moduleName
        self._module = None
        self._classes = classes

    def search(self, cls):
        if cls in self._classes:
            if self._module is None:
                self._module = __import__(self._moduleName, {}, {}, self._classes)
            # Allow for namespaces.
            obj = self._module
            for attr in cls.split('.'):
                obj = getattr(obj, attr)

            return obj
        else:
            return None


class _CustomWidgetLoader(object):
    def __init__(self):
        # should it stay this way?
        sys.path.append(".")
        self._widgets = {}
        self._modules = {}
        
    def addCustomWidget(self, widgetClass, baseClass, module):
        assert widgetClass not in self._widgets
        self._widgets[widgetClass] = module
    
    def search(self, cls):
        try:
            module = self._widgets[cls]
            if module not in self._modules:
                self._modules[module] = __import__(module, {}, {}, (cls,))
            
            return getattr(self._modules[module], cls)
        except KeyError:
            pass
        return None


class LoaderCreatorPolicy(object):
    def createQtGuiWrapper(self):
        return _QtGuiWrapper
    
    def createModuleWrapper(self, moduleName, classes):
        return _ModuleWrapper(moduleName, classes)
    
    def createCustomWidgetLoader(self):
        return _CustomWidgetLoader()

    def instantiate(self, clsObject, objectName, ctor_args, is_attribute=True):
        return clsObject(*ctor_args)

    def invoke(self, rname, method, args):
        return method(*args)

    def getSlot(self, object, slotname):
        # Rename slots that correspond to Python keyword arguments.
        if slotname == 'raise':
            slotname += '_'

        return getattr(object, slotname)
