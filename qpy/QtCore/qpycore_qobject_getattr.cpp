// This implements the helper for QObject.__getattr__().
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

#include <QByteArray>
#include <QHash>
#include <QMetaMethod>
#include <QObject>

#include "qpycore_pyqtboundsignal.h"
#include "qpycore_pyqtmethodproxy.h"
#include "qpycore_pyqtsignal.h"


// See if we can find an attribute in the Qt meta-type system.  This is
// primarily to support access to JavaScript (e.g. QDeclarativeItem) so we
// don't support overloads.
PyObject *qpycore_qobject_getattr(QObject *qobj, PyObject *py_qobj,
        const char *name)
{
    const QMetaObject *mo = qobj->metaObject();

    // Try and find a method with the name.
    QMetaMethod method;
    int method_index = -1;

    // Count down to allow overrides (assuming they are possible).
    for (int m = mo->methodCount() - 1; m >= 0; --m)
    {
        method = mo->method(m);

#if QT_VERSION >= 0x040500
        if (method.methodType() == QMetaMethod::Constructor)
            continue;
#endif

        // Get the method name.
        QByteArray mname(method.signature());
        int idx = mname.indexOf('(');

        if (idx >= 0)
            mname.truncate(idx);

        if (mname == name)
        {
            method_index = m;
            break;
        }
    }

    if (method_index < 0)
    {
        // Replicate the standard Python exception.
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%s'",
                Py_TYPE(py_qobj)->tp_name, name);

        return 0;
    }

    // Get the value to return.  Note that this is recreated each time.  We
    // could put a descriptor in the type dictionary to satisfy the request in
    // future but the typical use case is getting a value from a C++ proxy
    // (e.g. QDeclarativeItem) and we can't assume that what is being proxied
    // is the same each time.
    PyObject *value;

    if (method.methodType() == QMetaMethod::Signal)
    {
        // We need to keep explicit references to the unbound signals (because
        // we don't use the type dictionary to do so) because they own the
        // parsed signature which may be needed by a PyQtProxy at some point.
        typedef QHash<QByteArray, PyObject *> SignalHash;

        static SignalHash *sig_hash = 0;

        // For crappy compilers.
        if (!sig_hash)
            sig_hash = new SignalHash;

        PyObject *sig_obj;
        QByteArray sig_str(method.signature());
        SignalHash::const_iterator it = sig_hash->find(sig_str);

        if (it == sig_hash->end())
        {
            qpycore_pyqtSignal *sig = qpycore_pyqtSignal_New();

            if (!sig)
                return 0;

            qpycore_add_native_Qt_signal(sig, sig_str.constData(), 0);

            sig_obj = (PyObject *)sig;

            sig_hash->insert(sig_str, sig_obj);
        }
        else
        {
            sig_obj = it.value();
        }

        value = qpycore_pyqtBoundSignal_New(sig_obj, py_qobj, qobj, 0);
    }
    else
    {
        QByteArray py_name(Py_TYPE(py_qobj)->tp_name);
        py_name.append('.');
        py_name.append(name);

        value = qpycore_pyqtMethodProxy_New(qobj, method_index, py_name);
    }

    return value;
}
