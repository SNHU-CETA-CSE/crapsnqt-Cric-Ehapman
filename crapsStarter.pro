QT += widgets
requires(qtConfig(combobox))

HEADERS     = die.h \
              craps.h
SOURCES     = crapsGame.cpp die.cpp craps.cpp
FORMS       = CrapsMainWindow.ui
RESOURCES   = crapsResources.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/layouts/crapsnqt-Cric-Ehapman2
INSTALLS += target
