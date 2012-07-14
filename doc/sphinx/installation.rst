Installing PyQt
===============

Downloading SIP
---------------

SIP must be installed before building and using PyQt.  You can get the latest
release of the SIP source code from
http://www.riverbankcomputing.com/software/sip/download.

The SIP documentation can be found at
http://www.riverbankcomputing.com/static/Docs/sip4/index.html.


Downloading PyQt
----------------

You can get the latest release of the GPL version of the PyQt source code from
http://www.riverbankcomputing.com/software/pyqt/download.

If you are using the commercial version of PyQt then you should use the
download instructions which were sent to you when you made your purchase.  You
must also download your license file.


Configuring PyQt
----------------

After unpacking the source package (either a ``.tar.gz`` or a ``.zip`` file
depending on your platform) you should then check for any :file:`README` files
that relate to your platform.

If you are using the commercial version of PyQt then you must copy your
license file to the :file:`sip` directory.

You need to make sure your environment variables are set properly for your
development environment.  For example, if you are using a binary distribution
of Qt on Windows then make sure you have run the :file:`qtvars.bat` file.  For
other platforms it is normally enough to ensure that Qt's :file:`bin` directory
is on your :envvar:`PATH`.

Next you need to configure SIP by executing the :program:`configure.py` script.
For example::

    python configure.py

This assumes that the Python interpreter is on your path.  Something like the
following may be appropriate on Windows::

    c:\python32\python configure.py

If you have multiple versions of Python installed then make sure you use the
interpreter for which you wish to build PyQt for.

The full set of command line options is:

.. program:: configure.py

.. cmdoption:: --version

    Display the PyQt version number.

.. cmdoption:: -h, --help

    Display a help message.

.. cmdoption:: --confirm-license

    Using this confirms that you accept the terms of the PyQt license.

.. cmdoption:: -k, --static

    The PyQt modules will be built as static libraries.  This is useful when
    building a custom interpreter with the PyQt modules built in to the
    interpreter.

.. cmdoption:: --no-docstrings

    The PyQt modules will not contain automatically generated docstrings.

.. cmdoption:: -r, --trace

    The generated PyQt modules contain additional tracing code that is enabled
    using SIP's :func:`sip.settracemask` function.

.. cmdoption:: -u, --debug

    The PyQt modules will be built with debugging symbols.  On Windows this
    requires that a debug version of Python is installed.

.. cmdoption:: -w, --verbose

    Compiler commands and any output issued during configuration is displayed
    instead of being suppressed.  Use this if :program:`configure.py` is having
    problems to see what exactly is going wrong.

.. cmdoption:: -c, --concatenate

    The C++ source files for a Python module will be concatenated.  This
    results in significantly reduced compilation times.  Most, but not all,
    C++ compilers can handle the large files that result.  See also the
    :option:`--concatenate-split <-j>` option.

.. cmdoption:: -j <N>, --concatenate-split <N>

    If the :option:`--concatenate <-c>` option is used to concatenate the C++
    source files then this option determines how many files are created.  The
    default is 1.

.. cmdoption:: --assume-shared

    Normally Qt is checked to see if it has been built as shared libraries.
    Some Linux distributions configure their Qt builds to make this check
    unreliable.  This option ignores the result of the check and assumes that
    Qt has been built as shared libraries.

.. cmdoption:: -g, --consolidate

    Normally each PyQt module (except for the :mod:`~PyQt4.Qt` module) is
    linked against the corresponding Qt library.  This option creates a module
    called :mod:`~PyQt4._qt` which is linked against all the required Qt
    libraries and the other modules are stub modules that populate their module
    dictionaries from this one.  This is useful when linking against static Qt
    libraries to eliminate the need to distribute the Qt libraries while
    minimising the memory footprint of the PyQt modules.

.. cmdoption:: -e <MODULE>, --enable <MODULE>

    Normally all PyQt4 modules are enabled and are built if the corresponding
    Qt library can be found.  Using this option only those modules specifically
    enabled will be checked for and built.  The option may be specified any
    number of times.

.. cmdoption:: -t <PLUGIN>, --plugin <PLUGIN>

    If Qt has been built as static libraries then the static plugin
    ``<PLUGIN>`` will be linked with the appropriate PyQt module.  The option
    may be specified any number of times.

.. cmdoption:: -T, --no-timestamp

    Normally the header comments of each generated C/C++ source file includes
    a timestamp corresponding to when the file was generated.  This option
    suppresses the inclusion of the timestamp.

.. cmdoption:: -q <FILE>, --qmake <FILE>

    Qt's :program:`qmake` program is used to determine how your Qt installation
    is laid out.  Normally :program:`qmake` is found on your :envvar:`PATH`.
    This option can be used to specify a particular instance of
    :program:`qmake` to use.  This option is not available on Windows.

.. cmdoption:: -s <DIR>, --dbus <DIR>

    The :file:`dbus-python.h` header file of the dbus-python package can be
    found in the directory ``<DIR>/dbus``.

.. cmdoption:: -b <DIR>, --bindir <DIR>

    The :program:`pyuic4`, :program:`pyrcc4` and :program:`pylupdate4`
    utilities will be installed in the directory ``<DIR>``.

.. cmdoption:: -d <DIR>, --destdir <DIR>

    The PyQt Python package will be installed in the directory ``<DIR>``.  The
    default is the Python installation's :file:`site-packages` directory.  If
    you use this option then the :envvar:`PYTHONPATH` environment variable must
    include ``<DIR>``.

.. cmdoption:: -p <DIR>, --plugin-destdir <DIR>

    The Qt Designer plugin that manages plugins implemented in Python will be
    installed in the :file:`designer` subdirectory of the directory ``<DIR>``.

.. cmdoption:: --no-designer-plugin

    The Qt Designer plugin will not be built.

.. cmdoption:: --no-sip-files

    The ``.sip`` files for the PyQt modules will not be installed.

.. cmdoption:: -v <DIR>, --sipdir <DIR>

    The ``.sip`` files for the PyQt modules will be installed in the directory
    ``<DIR>``.

.. cmdoption:: --use-arch <ARCH>

    When :program:`pyuic4` calls the Python interpreter on MacOS it will be run
    using the architecture ``<ARCH>``.  See the section :ref:`ref-macos`.

.. cmdoption:: --protected-is-public

    On certain platforms the size of PyQt modules can be significantly reduced
    by redefining the C++ ``protected`` keyword as ``public`` during
    compilation.  This option enables this behaviour and is the default on
    Linux and MacOS/X.

.. cmdoption:: --protected-not-public

    The default redefinition of ``protected`` to ``public`` during compilation
    on Linux and MacOS/X is disabled.

.. cmdoption:: -i, --vendorid

    The checking of signed Python interpreters using the `VendorID
    <http://www.riverbankcomputing.com/software/vendorid/>`__ package is
    enabled.  See also the :option:`--vendorid-incdir <-l>` and
    :option:`--vendorid-libdir <-m>` options and :ref:`ref-deploy-commercial`.

.. cmdoption:: -l <DIR>, --vendorid-incdir <DIR>

    The header file of the VendorID package can be found in the directory
    ``<DIR>``.

.. cmdoption:: -m <DIR>, --vendorid-libdir <DIR>

    The library of the VendorID package can be found in the directory
    ``<DIR>``.

.. cmdoption:: -a, --qsci-api

    The :file:`PyQt4.api` QScintilla API file is installed even if QScintilla
    does not appear to be installed.  This option is implied if the
    :option:`--qsci-api-destdir <-n>` option is specified.

.. cmdoption:: --no-qsci-api

    The :file:`PyQt4.api` QScintilla API file is not installed even if
    QScintilla does appear to be installed.

.. cmdoption:: -n <DIR>, --qsci-api-destdir <DIR>

    The QScintilla API file will be installed in the :file:`python`
    subdirectory of the :file:`api` subdirectory of the directory ``<DIR>``.


.. _ref-macos:

Configuring SIP and PyQt for MacOS
----------------------------------

Building applications for MacOS can be a complex process.  Typically the
following need to be taken into account:

- the architectures (i.e. i386, x86_64, ppc) that you want to support

- the earliest version of MacOS you want to support (i.e. the deployment
  target)

- the version of the SDK you want to use.

If you are using a binary installer for Python and/or Qt then you also need to
consider how they have been built regarding the above, and what bugs they have.

SIP's and PyQt's :program:`configure.py` scripts provide the necessary command
line options to allow the correct configurations to be specified - the trick is
to work out which options to use depending on the versions of Python and Qt you
have installed.

SIP provides the following command line options to its :program:`configure.py`
script.

- ``--arch <ARCH>`` specifies the target architecture and may be specified a
  number of times.

- ``--universal`` is a shortcut for ``--arch i386 --arch ppc``.

- ``--deployment-target <VERSION>`` specifies the earliest version of MacOS you
  want to support.  This sets the :envvar:`MACOSX_DEPLOYMENT_TARGET`
  environment variable and should be used rather than setting the environment
  variable in the shell (to work around bugs in some versions of Python).

- ``--sdk <SDK>`` specifies the SDK to use.

PyQt provides the :option:`--use-arch <configure.py --use-arch>` option that
specifies which architecture certain PyQt tools (actually only
:program:`pyuic4` at the moment) will use when running Python.  For example, if
your Qt installation is 32 bits, and your Python installation is 32 bits and
64 bits then you will need to specify ``--use-arch i386`` to ensure that
:program:`pyuic4` runs the 32 bit version of Python.


Building PyQt
-------------

The next step is to build PyQt by running your platform's :program:`make`
command.  For example::

    make

The final step is to install PyQt by running the following command::

    make install

(Depending on your system you may require root or administrator privileges.)

This will install the various PyQt components.
