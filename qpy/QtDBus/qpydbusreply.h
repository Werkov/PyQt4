// This is the definition of the QPyDBusReply class.
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


#ifndef _QPYDBUSREPLY_H
#define _QPYDBUSREPLY_H


#include <Python.h>

#include <QDBusError>
#include <QVariant>


class QDBusMessage;
class QDBusPendingCall;


class QPyDBusReply
{
public:
    QPyDBusReply(const QDBusMessage &reply);
    QPyDBusReply(const QDBusPendingCall &call);
    QPyDBusReply(const QDBusError &error = QDBusError());
    QPyDBusReply(const QPyDBusReply &other);
    QPyDBusReply(PyObject *q_value, bool q_is_valid, const QDBusError &q_error);
    ~QPyDBusReply();

    inline const QDBusError &error() const {return _q_error;}
    inline bool isValid() const {return _q_is_valid;}

    PyObject *value(PyObject *type) const;

    QPyDBusReply &operator=(const QDBusMessage &reply);
    QPyDBusReply &operator=(const QDBusPendingCall &call);

private:
    PyObject *_q_value;
    QVariant _q_value_variant;
    bool _q_is_valid;
    QDBusError _q_error;
};

#endif
