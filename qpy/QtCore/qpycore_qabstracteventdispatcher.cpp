// This implements the helpers for QAbstractEventDispatcher.
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

#include <QAbstractEventDispatcher>

#include "qpycore_sip.h"


// A reference to the current Python event filter.
static PyObject *py_event_filter = 0;

// The dispatcher that the event filter is installed for.  Note that we only
// support one dispatcher (because, as usual, the C++ API for callbacks is
// badly designed) and this allows us to raise an exception if the user tries
// to set a filter for more than one (i.e. one from another thread).
static QAbstractEventDispatcher *dispatcher = 0;


// Forward declarations.
static bool event_filter(void *message);


// Implement QSettings.value() and allow the type of the returned object to be
// explicitly specified.
PyObject *qpycore_qabstracteventdispatcher_seteventfilter(
        QAbstractEventDispatcher *dist, PyObject *filter)
{
    // Check that this isn't a different dispatcher.
    if (dispatcher && dispatcher != dist)
    {
        PyErr_SetString(PyExc_ValueError,
                "PyQt only supports setting an event filter on a single "
                "QAbstractEventDispatcher");
        return 0;
    }

    // Make sure any previous filter has a corresponding Python object.
    PyObject *old_filter = py_event_filter;

    if (!old_filter)
    {
        old_filter = Py_None;
        Py_INCREF(old_filter);
    }

    if (filter == Py_None)
    {
        // Remove any existing filter.
        dist->setEventFilter(0);

        py_event_filter = 0;
        dispatcher = 0;
    }
    else
    {
        // Install the new filter.
        Py_INCREF(filter);
        py_event_filter = filter;
        dispatcher = dist;

        dist->setEventFilter(event_filter);
    }

    return old_filter;
}


// The event filter.
static bool event_filter(void *message)
{
    bool res = false, raised = true;

    SIP_BLOCK_THREADS

#if defined(Q_WS_WIN)
    PyObject *msg_obj = sipConvertFromType(reinterpret_cast<MSG *>(message),
            sipType_MSG, 0);
#else
    PyObject *msg_obj = sipConvertFromVoidPtr(message);
#endif

    if (msg_obj)
    {
        PyObject *res_obj = PyObject_CallFunctionObjArgs(py_event_filter,
                msg_obj, 0);

        Py_DECREF(msg_obj);

        if (res_obj)
        {
            if (PyBool_Check(res_obj))
            {
                if (res_obj == Py_True)
                    res = true;

                raised = false;
            }
            else
            {
                PyErr_Format(PyExc_TypeError,
                        "QAbstractEventDispatcher event filter returned a "
                        "'%s' instead of a 'bool'", Py_TYPE(res_obj)->tp_name);
            }

            Py_DECREF(res_obj);
        }
    }

    if (raised)
        PyErr_Print();

    SIP_UNBLOCK_THREADS

    return res;
}
