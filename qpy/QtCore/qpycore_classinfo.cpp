// This contains the implementation of the Q_CLASSINFO support.
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


#include <Python.h>
#include <frameobject.h>

#include <QMultiHash>

#include "qpycore_classinfo.h"


static QMultiHash<const PyFrameObject *, ClassInfo> class_info_hash;


// Add the given name/value pair to the current class info hash.
PyObject *qpycore_ClassInfo(const char *name, const char *value)
{
    PyFrameObject *frame = PyEval_GetFrame();

    // We need the frame we were called from, not the current one.
    if (frame)
        frame = frame->f_back;

    if (!frame)
    {
        PyErr_SetString(PyExc_RuntimeError, "no current frame");
        return 0;
    }

    class_info_hash.insert(frame,
            ClassInfo(QByteArray(name), QByteArray(value)));

    Py_INCREF(Py_None);
    return Py_None;
}


// Return the current class info list.
QList<ClassInfo> qpycore_get_class_info_list()
{
    PyFrameObject *frame = PyEval_GetFrame();
    QList<ClassInfo> class_info_list = class_info_hash.values(frame);

    class_info_hash.remove(frame);

    return class_info_list;
}
