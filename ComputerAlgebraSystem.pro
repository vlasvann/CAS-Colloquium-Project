TEMPLATE = app
TARGET = ComputerAlgebraSystem
CONFIG += c++17 static  # ← ДОБАВЬТЕ 'static' ЗДЕСЬ!
QT += widgets

QMAKE_LFLAGS += -static-libgcc -static-libstdc++

SOURCES += $$files(src/*.cpp)
HEADERS += $$files(src/*.h)

DESTDIR = build
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc

INCLUDEPATH += src
