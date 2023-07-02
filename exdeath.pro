
HEADERS   += src/exdeath.hh src/data.hh src/randodata.hh src/randomizer.hh src/fiesta.hh src/patch.hh
SOURCES   += src/exdeath.cc src/main.cc src/randomizer.cc src/fiesta.cc src/patch.cc
RESOURCES += patches.qrc

CONFIG += release

QT += gui widgets core
