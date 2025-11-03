TEMPLATE = app
TARGET = ComputerAlgebraSystem
CONFIG += c++17
CONFIG += qt
QT += widgets

SOURCES += $$files(src/*.cpp)
  
HEADERS += $$files(src/*.h)

DESTDIR = build
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc

INCLUDEPATH += src
