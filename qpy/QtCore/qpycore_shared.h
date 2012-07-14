// This defines the interfaces to various odd and ends that are used internally
// by this library and called from handwritten code.
//
// Copyright (c) 2011 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of PyQt.
// 
// This file may be used under the terms of the GNU General Public
// License versions 2.0 or 3.0 as published by the Free Software
// Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
// included in the packaging of this file.  Alternatively you may (at
// your option) use any later version of the GNU General Public
// License if such license has been publicly approved by Riverbank
// Computing Limited (or its successors, if any) and the KDE Free Qt
// Foundation. In addition, as a special exception, Riverbank gives you
// certain additional rights. These rights are described in the Riverbank
// GPL Exception version 1.1, which can be found in the file
// GPL_EXCEPTION.txt in this package.
// 
// If you are unsure which license is appropriate for your use, please
// contact the sales department at sales@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


#ifndef _QPYCORE_SHARED_H
#define _QPYCORE_SHARED_H


#include <Python.h>

#include <QtGlobal>
#include <QByteArray>

#include "qpycore_namespace.h"


QT_BEGIN_NAMESPACE
class QObject;
class QVariant;
QT_END_NAMESPACE


char **qpycore_ArgvToC(PyObject *argvlist, int &argc);
void qpycore_UpdatePyArgv(PyObject *argvlist, int argc, char **argv);

const char *qpycore_pyqtsignal_get_parts(PyObject *sig_obj, QObject **qtx);
QByteArray qpycore_pyqtslot_get_parts(PyObject *callable, QObject **qrx);

PyObject *qpycore_qvariant_value(QVariant &value, PyObject *type);

#endif
