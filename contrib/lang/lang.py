#!/usr/bin/env python

# switch translations dynamically in a PyQt4 application
#
# PyQt version by Hans-Peter Jansen <hpj@urpla.net>
#
# Based on an example from jpn on July 17 2006 found here:
# 
# http://www.qtcentre.org/wiki/index.php?title=Dynamic_translation_in_Qt4_applications
#
# Since the original version didn't carry any license, 
# I've add this one:
#
# This program is free software. It comes without any warranty, to
# the extent permitted by applicable law. You can redistribute it
# and/or modify it under the terms of the Do What The Fuck You Want
# To Public License, Version 2, as published by Sam Hocevar. See
# http://sam.zoy.org/wtfpl/COPYING for more details. 

import sys
import sip
sip.setapi('QString', 2)
sip.setapi('QVariant', 2)

from PyQt4 import QtCore, QtGui

from ui_mainwindow import Ui_MainWindow

import lang_rc

class Application(QtGui.QApplication):

    translators = {}
    current = None

    def __init__(self, argv):
        super(Application, self).__init__(argv)

    def loadTranslations(self, folder):
        if not isinstance(folder, QtCore.QDir):
            folder = QtCore.QDir(folder)
        pattern = "*_*.qm"  # <language>_<country>.qm
        filters = QtCore.QDir.Files | QtCore.QDir.Readable
        sort = QtCore.QDir.SortFlags(QtCore.QDir.Name)
        for langFile in folder.entryInfoList([pattern], filters, sort):
            # pick country and language out of the file name
            language, country = langFile.baseName().split("_", 1)
            language = language.lower()
            country = country.upper()
            locale = language + "_" + country
            # only load translation, if it does not exist already
            if not locale in Application.translators:
                # create and load translator
                translator = QtCore.QTranslator(self.instance())
                if translator.load(langFile.absoluteFilePath()):
                    Application.translators[locale] = translator

    @staticmethod
    def availableLanguages():
        return sorted(Application.translators.keys())

    @staticmethod
    def setLanguage(locale):
        #print "Application.setLanguage(%s)" % locale
        if Application.current:
            Application.removeTranslator(Application.current)
        Application.current = Application.translators.get(locale, None)
        if Application.current is not None:
            Application.installTranslator(Application.current)


class MainWindow(QtGui.QMainWindow):
    def __init__(self, parent = None, flags = 0):
        super(MainWindow, self).__init__(parent, QtCore.Qt.WindowFlags(flags))
        self.languages = QtGui.QMenu()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.fillLanguages()
        self.retranslate()

    def changeEvent(self, event):
        if event.type() == QtCore.QEvent.LanguageChange:
            # all designed forms have a retranslateUi() method
            self.ui.retranslateUi(self)
            # retranslate other widgets which weren't added in the designer
            self.retranslate()
        super(MainWindow, self).changeEvent(event)

    @QtCore.pyqtSlot(QtGui.QAction)
    def setLanguage(self, action):
        Application.setLanguage(action.data())

    def fillLanguages(self):
        self.languages = self.menuBar().addMenu("")
        # make a group of language actions
        actions = QtGui.QActionGroup(self)
        actions.triggered.connect(self.setLanguage)
        system = QtCore.QLocale.system()
        default = None
        for lang in Application.availableLanguages():
            # figure out nice names for locales
            locale = QtCore.QLocale(lang)
            language = QtCore.QLocale.languageToString(locale.language())
            country = QtCore.QLocale.countryToString(locale.country())
            name = "%s (%s)" % (language, country)
            # create an action
            action = self.languages.addAction(name)
            action.setData(lang)
            action.setCheckable(True)
            if lang == system.name():
                # language match the current system
                action.setChecked(True)
                Application.setLanguage(lang)
                default = lang
            actions.addAction(action)
        if default is None:
            # no exact match found, try language only
            for lang in Application.availableLanguages():
                locale = QtCore.QLocale(lang)
                if locale.language() == system.language():
                    # at least a language match
                    for action in actions.actions():
                        if lang == action.data():
                            # use first entry of this language
                            action.setChecked(True)
                            Application.setLanguage(lang)
                            default = lang
                            break
                    if default is not None:
                        break
        return default

    def retranslate(self):
        self.languages.setTitle(self.tr("Language"))


if __name__ == "__main__":
    app = Application(sys.argv)
    app.loadTranslations(":/lang")
    mainWindow = MainWindow()
    mainWindow.show()
    app.lastWindowClosed.connect(app.quit)
    sys.exit(app.exec_())

