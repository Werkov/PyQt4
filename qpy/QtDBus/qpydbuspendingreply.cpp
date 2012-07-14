// This is the implementation of the QPyDBusPendingReply class.
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

#include "sipAPIQtDBus.h"

#include "qpydbuspendingreply.h"


// Default ctor.
QPyDBusPendingReply::QPyDBusPendingReply() : QDBusPendingReply<void>()
{
}


// Copy a reply.
QPyDBusPendingReply::QPyDBusPendingReply(const QPyDBusPendingReply &other)
        : QDBusPendingReply<void>(other)
{
}


// Extract a reply from another pending call.
QPyDBusPendingReply::QPyDBusPendingReply(const QDBusPendingCall &call)
        : QDBusPendingReply<void>(call)
{
}


// Extract a reply from a message.
QPyDBusPendingReply::QPyDBusPendingReply(const QDBusMessage &reply)
        : QDBusPendingReply<void>(reply)
{
}


// Return the value of the reply.  The GIL should be held.
PyObject *QPyDBusPendingReply::value(PyObject *type) const
{
    QVariant val;

    // This will wait for the call to complete.
    Py_BEGIN_ALLOW_THREADS
    val = argumentAt(0);
    Py_END_ALLOW_THREADS

    return qpycore_qvariant_value(val, type);
}
