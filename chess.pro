QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    figure.cpp \
    main.cpp \
    game.cpp

HEADERS += \
    board.h \
    figure.h \
    game.h


QMAKE_EXTRA_COMPILERS += nasm
NASMEXTRAFLAGS = -f elf64 -g -F dwarf
OTHER_FILES += $$NASM_SOURCES
nasm.output = ${QMAKE_FILE_BASE}.o
nasm.commands = /usr/local/bin/nasm -fmacho64 -g -F dwarf -o ${QMAKE_FILE_BASE}.o ${QMAKE_FILE_NAME}
nasm.input = NASM_SOURCES

NASM_SOURCES += \
    king.asm \
    queen.asm \
    bishop.asm \
    knight.asm \
    rook.asm \
    white_pawn.asm \
    black_pawn.asm

FORMS += \
    game.ui



DISTFILES += \
    king.asm \
    queen.asm \
    bishop.asm \
    knight.asm \
    rook.asm \
    white_pawn.asm \
    black_pawn.asm

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
