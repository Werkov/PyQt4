// This is the SIP specification of the QPyDBusReply class.
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


class QPyDBusReply /PyName=QDBusReply/
{
%TypeHeaderCode
#include <qpydbusreply.h>
%End

public:
    QPyDBusReply(const QDBusMessage &reply) /HoldGIL/;
    QPyDBusReply(const QDBusPendingCall &call) /HoldGIL/;
    QPyDBusReply(const QDBusError &error);
    QPyDBusReply(const QPyDBusReply &other) /HoldGIL/;
    ~QPyDBusReply() /HoldGIL/;

    const QDBusError &error() const /HoldGIL/;
    bool isValid() const /HoldGIL/;
    SIP_PYOBJECT value(SIP_PYOBJECT type /DocValue="None"/ = 0) const /HoldGIL/;
};


template<TYPE>
%MappedType QDBusReply<TYPE> /DocType="QDBusReply"/
{
%TypeHeaderCode
#include <qdbusreply.h>
#include <qpydbusreply.h>
%End

%ConvertFromTypeCode
    PyObject *value_obj;

    if (sipCpp->isValid())
    {
        // Convert the value to a Python object.
        TYPE *value = new TYPE(sipCpp->value());

        if ((value_obj = sipConvertFromNewType(value, sipType_TYPE, NULL)) == NULL)
        {
            delete value;
            return NULL;
        }
    }
    else
    {
        value_obj = 0;
    }

    QPyDBusReply *reply = new QPyDBusReply(value_obj,
            sipCpp->isValid(), sipCpp->error());

    PyObject *reply_obj = sipConvertFromNewType(reply, sipType_QPyDBusReply, sipTransferObj);

    if (reply_obj == NULL)
    {
        delete reply;
        return NULL;
    }

    return reply_obj;
%End

%ConvertToTypeCode
    // We never create a QDBusReply from Python.
    return 0;
%End
};


%MappedType QDBusReply<void> /DocType="QDBusReply"/
{
%TypeHeaderCode
#include <qdbusreply.h>
#include <qpydbusreply.h>
%End

%ConvertFromTypeCode
    Py_INCREF(Py_None);
    QPyDBusReply *reply = new QPyDBusReply(Py_None,
            sipCpp->isValid(), sipCpp->error());

    PyObject *reply_obj = sipConvertFromNewType(reply, sipType_QPyDBusReply, sipTransferObj);

    if (reply_obj == NULL)
    {
        delete reply;
        return NULL;
    }

    return reply_obj;
%End

%ConvertToTypeCode
    // We never create a QDBusReply from Python.
    return 0;
%End
};


%MappedType QDBusReply<bool> /DocType="QDBusReply"/
{
%TypeHeaderCode
#include <qdbusreply.h>
#include <qpydbusreply.h>
%End

%ConvertFromTypeCode
    PyObject *value_obj;

    if (sipCpp->isValid())
    {
        if ((value_obj = PyBool_FromLong(sipCpp->value())) == NULL)
            return NULL;
    }
    else
    {
        value_obj = 0;
    }

    QPyDBusReply *reply = new QPyDBusReply(value_obj,
            sipCpp->isValid(), sipCpp->error());

    PyObject *reply_obj = sipConvertFromNewType(reply, sipType_QPyDBusReply, sipTransferObj);

    if (reply_obj == NULL)
    {
        delete reply;
        return NULL;
    }

    return reply_obj;
%End

%ConvertToTypeCode
    // We never create a QDBusReply from Python.
    return 0;
%End
};


%MappedType QDBusReply<unsigned> /DocType="QDBusReply"/
{
%TypeHeaderCode
#include <qdbusreply.h>
#include <qpydbusreply.h>
%End

%ConvertFromTypeCode
    PyObject *value_obj;

    if (sipCpp->isValid())
    {
        if ((value_obj = PyLong_FromUnsignedLong(sipCpp->value())) == NULL)
            return NULL;
    }
    else
    {
        value_obj = 0;
    }

    QPyDBusReply *reply = new QPyDBusReply(value_obj,
            sipCpp->isValid(), sipCpp->error());

    PyObject *reply_obj = sipConvertFromNewType(reply, sipType_QPyDBusReply, sipTransferObj);

    if (reply_obj == NULL)
    {
        delete reply;
        return NULL;
    }

    return reply_obj;
%End

%ConvertToTypeCode
    // We never create a QDBusReply from Python.
    return 0;
%End
};


%MappedType QDBusReply<QDBusConnectionInterface::RegisterServiceReply> /DocType="QDBusReply"/
{
%TypeHeaderCode
#include <qdbusreply.h>
#include <qpydbusreply.h>
%End

%ConvertFromTypeCode
    PyObject *value_obj;

    if (sipCpp->isValid())
    {
        if ((value_obj = sipConvertFromEnum(sipCpp->value(), sipType_QDBusConnectionInterface_RegisterServiceReply)) == NULL)
            return NULL;
    }
    else
    {
        value_obj = 0;
    }

    QPyDBusReply *reply = new QPyDBusReply(value_obj,
            sipCpp->isValid(), sipCpp->error());

    PyObject *reply_obj = sipConvertFromNewType(reply, sipType_QPyDBusReply, sipTransferObj);

    if (reply_obj == NULL)
    {
        delete reply;
        return NULL;
    }

    return reply_obj;
%End

%ConvertToTypeCode
    // We never create a QDBusReply from Python.
    return 0;
%End
};
