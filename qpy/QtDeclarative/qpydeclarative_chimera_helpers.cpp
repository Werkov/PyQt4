// This is the implementation of the various Chimera helpers.
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


#include "sipAPIQtDeclarative.h"

#include "qpydeclarative_chimera_helpers.h"

#include <QList>
#include <QMetaType>
#include <QObject>


// Forward declarations.
static int QList_QObject_metatype();
static bool to_QList_QObject(PyObject *obj, QList<QObject *>&cpp);


// Convert a QVariant to a Python object.
bool qpydeclarative_to_pyobject(const QVariant *varp, PyObject **objp)
{
    // Check we handle the meta-type.
    if (varp->userType() != QList_QObject_metatype())
        return false;

    const QList<QObject *> *cpp = reinterpret_cast<const QList<QObject *> *>(varp->data());

    PyObject *obj = PyList_New(cpp->count());

    if (obj)
    {
        for (int i = 0; i < cpp->count(); ++i)
        {
            PyObject *itm = sipConvertFromType(cpp->at(i), sipType_QObject, 0);

            if (!itm)
            {
                Py_DECREF(obj);
                obj = 0;
                break;
            }

            PyList_SET_ITEM(obj, i, itm);
        }
    }

    *objp = obj;

    return true;
}


// Convert a Python object to a QVariant.
bool qpydeclarative_to_qvariant(PyObject *obj, QVariant *varp, bool *okp)
{
    int metatype = QList_QObject_metatype();

    // Check the meta-type has been defined.
    if (metatype == 0)
        return false;

    QList<QObject *> qlo;

    // A failure to convert isn't an error, just the wrong type of Python
    // object.
    if (!to_QList_QObject(obj, qlo))
        return false;

    *varp = QVariant(metatype, &qlo);
    *okp = true;

    return true;
}


// Convert a Python object to QVariant data.
bool qpydeclarative_to_qvariant_data(PyObject *obj, void *data, int metatype, bool *okp)
{
    // Check we handle the meta-type.
    if (metatype != QList_QObject_metatype())
        return false;

    QList<QObject *> qlo;

    // A failure to convert isn't an error, just the wrong type of Python
    // object.
    if (!to_QList_QObject(obj, qlo))
        return false;

    *reinterpret_cast<QList<QObject *> *>(data) = qlo;
    *okp = true;

    return true;
}


// Get the metatype for QList<QObject *> or 0 if it hasn't been registered.
static int QList_QObject_metatype()
{
    static int lo_metatype = 0;

    // We look each time until we find it rather than rely on any particular
    // behaviour from QtDeclarative.
    if (lo_metatype == 0)
        lo_metatype = QMetaType::type("QList<QObject*>");

    return lo_metatype;
}


// Convert a Python list object to a QList<QObject*> and return true if the
// conversion was successful.
static bool to_QList_QObject(PyObject *obj, QList<QObject *>&cpp)
{
    if (!PyList_CheckExact(obj))
        return false;

    for (SIP_SSIZE_T i = 0; i < PyList_GET_SIZE(obj); ++i)
    {
        PyObject *val_obj = PyList_GET_ITEM(obj, i);

        if (!val_obj)
            return false;

        int iserr = 0;

        QObject *val = reinterpret_cast<QObject *>(sipForceConvertToType(
                val_obj, sipType_QObject, 0, SIP_NO_CONVERTORS, 0, &iserr));

        if (iserr)
            return false;

        cpp.append(val);
    }

    return true;
}
