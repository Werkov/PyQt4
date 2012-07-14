
PYUIC = pyuic4
PYRCC = pyrcc4

UIFILES = $(wildcard *.ui)
PYUIFILES = $(patsubst %.ui,ui_%.py,$(UIFILES))

RESOURCES = $(wildcard *.qrc)
PYRESOURCES = $(patsubst %.qrc,%_rc.py,$(RESOURCES))

ui_%.py: %.ui
	$(PYUIC) -x -o $@ $<

%_rc.py: %.qrc
	$(PYRCC) -o $@ $<

all: $(PYUIFILES) $(PYRESOURCES)

$(PYUIFILES): $(UIFILES)

$(PYRESOURCES): $(RESOURCES)

clean:
	rm -f *~ *_rc.py ui_*.py *.pyc *.pyo
