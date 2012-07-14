.. _ref-dbus:

The Legacy DBus Support Module
==============================

Note that There are no plans for the standard ``dbus-python`` language bindings
package to be ported to Python v3 and so it is recommended that new
applications use the :mod:`~PyQt4.QtDBus` module instead.

The DBus support module is installed as :mod:`dbus.mainloop.qt` and provides
support for the Qt event loop to ``dbus-python``.  The module's API is almost
identical to that of the :mod:`dbus.mainloop.glib` modules that provides
support for the GLib event loop.

The :mod:`dbus.mainloop.qt` module contains the following function.

.. function:: DBusQtMainLoop(set_as_default=False)

    Create a ``dbus.mainloop.NativeMainLoop`` object that uses the the Qt event
    loop.

    :param set_as_default:
        is optionally set to make the main loop instance the default for all
        new Connection and Bus instances.  It may only be specified as a
        keyword argument, and not as a positional argument.

The following code fragment is all that is normally needed to set up the
standard ``dbus-python`` language bindings package to be used with PyQt::

    from dbus.mainloop.qt import DBusQtMainLoop

    DBusQtMainLoop(set_as_default=True)
