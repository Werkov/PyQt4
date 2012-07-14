.. _ref-deploy-commercial:

Deploying Commercial PyQt Applications
======================================

When deploying commercial PyQt applications it is necessary to discourage
users from accessing the underlying PyQt modules for themselves.  A user that
used the modules shipped with your application to develop new applications
would themselves be considered a developer and would need their own commercial
PyQt license.

One solution to this problem is the `VendorID
<http://www.riverbankcomputing.com/software/vendorid/>`__ package.  This allows
you to build Python extension modules that can only be imported by a digitally
signed custom interpreter.  The package enables you to create such an
interpreter with your application embedded within it.  The result is an
interpreter that can only run your application, and PyQt modules that can only
be imported by that interpreter.  You can use the package to similarly restrict
access to any extension module.

In order to build PyQt with support for the VendorID package, pass the
:option:`--vendorid <configure.py -i>` command line option to
:program:`configure.py`.
