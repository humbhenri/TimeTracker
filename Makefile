#############################################################################
# Makefile for building: TimeTracker.app/Contents/MacOS/TimeTracker
# Generated by qmake (2.01a) (Qt 4.7.2) on: qui nov 17 23:14:27 2011
# Project:  TimeTracker.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile TimeTracker.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_XML_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -gdwarf-2 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -gdwarf-2 -Wall -W $(DEFINES)
INCPATH       = -I/usr/local/Qt4.7/mkspecs/macx-g++ -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/Library/Frameworks/QtXml.framework/Versions/4/Headers -I/usr/include/QtXml -I/usr/include -I. -I. -F/Library/Frameworks
LINK          = g++
LFLAGS        = -headerpad_max_install_names
LIBS          = $(SUBLIBS) -F/Library/Frameworks -L/Library/Frameworks -framework QtXml -framework QtCore -framework QtGui 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		preferenceswidget.cpp \
		projectwidget.cpp \
		trayiconcommand.cpp \
		preferences.cpp \
		project.cpp \
		timespan.cpp \
		createprojectdialog.cpp \
		screenshot.cpp moc_mainwindow.cpp \
		moc_preferenceswidget.cpp \
		moc_projectwidget.cpp \
		moc_preferences.cpp \
		moc_project.cpp \
		moc_createprojectdialog.cpp \
		moc_screenshot.cpp \
		qrc_res.cpp
OBJECTS       = main.o \
		mainwindow.o \
		preferenceswidget.o \
		projectwidget.o \
		trayiconcommand.o \
		preferences.o \
		project.o \
		timespan.o \
		createprojectdialog.o \
		screenshot.o \
		moc_mainwindow.o \
		moc_preferenceswidget.o \
		moc_projectwidget.o \
		moc_preferences.o \
		moc_project.o \
		moc_createprojectdialog.o \
		moc_screenshot.o \
		qrc_res.o
DIST          = /usr/local/Qt4.7/mkspecs/common/unix.conf \
		/usr/local/Qt4.7/mkspecs/common/mac.conf \
		/usr/local/Qt4.7/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.7/mkspecs/qconfig.pri \
		/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Qt4.7/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.7/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.7/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.7/mkspecs/features/debug.prf \
		/usr/local/Qt4.7/mkspecs/features/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.7/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.7/mkspecs/features/qt.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.7/mkspecs/features/moc.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.7/mkspecs/features/resources.prf \
		/usr/local/Qt4.7/mkspecs/features/uic.prf \
		/usr/local/Qt4.7/mkspecs/features/yacc.prf \
		/usr/local/Qt4.7/mkspecs/features/lex.prf \
		/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf \
		TimeTracker.pro
QMAKE_TARGET  = TimeTracker
DESTDIR       = 
TARGET        = TimeTracker.app/Contents/MacOS/TimeTracker

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-gdwarf-2 \
		-Wall \
		-W


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile TimeTracker.app/Contents/PkgInfo TimeTracker.app/Contents/Resources/empty.lproj TimeTracker.app/Contents/Info.plist TimeTracker.app/Contents/Resources/timetracker.icns $(TARGET)

$(TARGET): ui_mainwindow.h ui_preferenceswidget.h ui_projectwidget.h ui_createprojectdialog.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) TimeTracker.app/Contents/MacOS/ || $(MKDIR) TimeTracker.app/Contents/MacOS/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: TimeTracker.pro  /usr/local/Qt4.7/mkspecs/macx-g++/qmake.conf /usr/local/Qt4.7/mkspecs/common/unix.conf \
		/usr/local/Qt4.7/mkspecs/common/mac.conf \
		/usr/local/Qt4.7/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.7/mkspecs/qconfig.pri \
		/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Qt4.7/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.7/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.7/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.7/mkspecs/features/debug.prf \
		/usr/local/Qt4.7/mkspecs/features/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.7/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.7/mkspecs/features/qt.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.7/mkspecs/features/moc.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.7/mkspecs/features/resources.prf \
		/usr/local/Qt4.7/mkspecs/features/uic.prf \
		/usr/local/Qt4.7/mkspecs/features/yacc.prf \
		/usr/local/Qt4.7/mkspecs/features/lex.prf \
		/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf \
		/Library/Frameworks/QtXml.framework/QtXml.prl \
		/Library/Frameworks/QtCore.framework/QtCore.prl \
		/Library/Frameworks/QtGui.framework/QtGui.prl
	$(QMAKE) -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile TimeTracker.pro
/usr/local/Qt4.7/mkspecs/common/unix.conf:
/usr/local/Qt4.7/mkspecs/common/mac.conf:
/usr/local/Qt4.7/mkspecs/common/mac-g++.conf:
/usr/local/Qt4.7/mkspecs/qconfig.pri:
/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri:
/usr/local/Qt4.7/mkspecs/features/qt_functions.prf:
/usr/local/Qt4.7/mkspecs/features/qt_config.prf:
/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf:
/usr/local/Qt4.7/mkspecs/features/default_pre.prf:
/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf:
/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf:
/usr/local/Qt4.7/mkspecs/features/debug.prf:
/usr/local/Qt4.7/mkspecs/features/default_post.prf:
/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf:
/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf:
/usr/local/Qt4.7/mkspecs/features/warn_on.prf:
/usr/local/Qt4.7/mkspecs/features/qt.prf:
/usr/local/Qt4.7/mkspecs/features/unix/thread.prf:
/usr/local/Qt4.7/mkspecs/features/moc.prf:
/usr/local/Qt4.7/mkspecs/features/mac/rez.prf:
/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf:
/usr/local/Qt4.7/mkspecs/features/resources.prf:
/usr/local/Qt4.7/mkspecs/features/uic.prf:
/usr/local/Qt4.7/mkspecs/features/yacc.prf:
/usr/local/Qt4.7/mkspecs/features/lex.prf:
/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf:
/Library/Frameworks/QtXml.framework/QtXml.prl:
/Library/Frameworks/QtCore.framework/QtCore.prl:
/Library/Frameworks/QtGui.framework/QtGui.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile TimeTracker.pro

TimeTracker.app/Contents/PkgInfo: 
	@$(CHK_DIR_EXISTS) TimeTracker.app/Contents || $(MKDIR) TimeTracker.app/Contents 
	@$(DEL_FILE) TimeTracker.app/Contents/PkgInfo
	@echo "APPL????" >TimeTracker.app/Contents/PkgInfo
TimeTracker.app/Contents/Resources/empty.lproj: 
	@$(CHK_DIR_EXISTS) TimeTracker.app/Contents/Resources || $(MKDIR) TimeTracker.app/Contents/Resources 
	@touch TimeTracker.app/Contents/Resources/empty.lproj
	
TimeTracker.app/Contents/Info.plist: 
	@$(CHK_DIR_EXISTS) TimeTracker.app/Contents || $(MKDIR) TimeTracker.app/Contents 
	@$(DEL_FILE) TimeTracker.app/Contents/Info.plist
	@sed -e "s,@ICON@,timetracker.icns,g" -e "s,@EXECUTABLE@,TimeTracker,g" -e "s,@TYPEINFO@,????,g" /usr/local/Qt4.7/mkspecs/macx-g++/Info.plist.app >TimeTracker.app/Contents/Info.plist
TimeTracker.app/Contents/Resources/timetracker.icns: images/timetracker.icns
	@$(CHK_DIR_EXISTS) TimeTracker.app/Contents/Resources/ || $(MKDIR) TimeTracker.app/Contents/Resources/ 
	@$(DEL_FILE) TimeTracker.app/Contents/Resources/timetracker.icns
	@$(COPY_FILE) images/timetracker.icns TimeTracker.app/Contents/Resources/timetracker.icns
dist: 
	@$(CHK_DIR_EXISTS) .tmp/TimeTracker1.0.0 || $(MKDIR) .tmp/TimeTracker1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/TimeTracker1.0.0/ && $(COPY_FILE) --parents mainwindow.h preferenceswidget.h projectwidget.h trayiconcommand.h preferences.h project.h timespan.h createprojectdialog.h screenshot.h .tmp/TimeTracker1.0.0/ && $(COPY_FILE) --parents res.qrc .tmp/TimeTracker1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp preferenceswidget.cpp projectwidget.cpp trayiconcommand.cpp preferences.cpp project.cpp timespan.cpp createprojectdialog.cpp screenshot.cpp .tmp/TimeTracker1.0.0/ && $(COPY_FILE) --parents mainwindow.ui preferenceswidget.ui projectwidget.ui createprojectdialog.ui .tmp/TimeTracker1.0.0/ && (cd `dirname .tmp/TimeTracker1.0.0` && $(TAR) TimeTracker1.0.0.tar TimeTracker1.0.0 && $(COMPRESS) TimeTracker1.0.0.tar) && $(MOVE) `dirname .tmp/TimeTracker1.0.0`/TimeTracker1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/TimeTracker1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) -r TimeTracker.app
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_mainwindow.cpp moc_preferenceswidget.cpp moc_projectwidget.cpp moc_preferences.cpp moc_project.cpp moc_createprojectdialog.cpp moc_screenshot.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_preferenceswidget.cpp moc_projectwidget.cpp moc_preferences.cpp moc_project.cpp moc_createprojectdialog.cpp moc_screenshot.cpp
moc_mainwindow.cpp: mainwindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ mainwindow.h -o moc_mainwindow.cpp

moc_preferenceswidget.cpp: preferenceswidget.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ preferenceswidget.h -o moc_preferenceswidget.cpp

moc_projectwidget.cpp: projectwidget.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ projectwidget.h -o moc_projectwidget.cpp

moc_preferences.cpp: preferences.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ preferences.h -o moc_preferences.cpp

moc_project.cpp: timespan.h \
		project.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ project.h -o moc_project.cpp

moc_createprojectdialog.cpp: createprojectdialog.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ createprojectdialog.h -o moc_createprojectdialog.cpp

moc_screenshot.cpp: screenshot.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ screenshot.h -o moc_screenshot.cpp

compiler_rcc_make_all: qrc_res.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_res.cpp
qrc_res.cpp: res.qrc \
		images/clock.png \
		images/clock-off.png
	/Developer/Tools/Qt/rcc -name res res.qrc -o qrc_res.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_preferenceswidget.h ui_projectwidget.h ui_createprojectdialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_preferenceswidget.h ui_projectwidget.h ui_createprojectdialog.h
ui_mainwindow.h: mainwindow.ui \
		preferenceswidget.h \
		projectwidget.h
	/Developer/Tools/Qt/uic mainwindow.ui -o ui_mainwindow.h

ui_preferenceswidget.h: preferenceswidget.ui
	/Developer/Tools/Qt/uic preferenceswidget.ui -o ui_preferenceswidget.h

ui_projectwidget.h: projectwidget.ui
	/Developer/Tools/Qt/uic projectwidget.ui -o ui_projectwidget.h

ui_createprojectdialog.h: createprojectdialog.ui
	/Developer/Tools/Qt/uic createprojectdialog.ui -o ui_createprojectdialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		ui_mainwindow.h \
		preferenceswidget.h \
		projectwidget.h \
		preferences.h \
		trayiconcommand.h \
		timespan.h \
		project.h \
		screenshot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

preferenceswidget.o: preferenceswidget.cpp preferenceswidget.h \
		ui_preferenceswidget.h \
		preferences.h \
		trayiconcommand.h \
		project.h \
		timespan.h \
		createprojectdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o preferenceswidget.o preferenceswidget.cpp

projectwidget.o: projectwidget.cpp projectwidget.h \
		ui_projectwidget.h \
		project.h \
		timespan.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o projectwidget.o projectwidget.cpp

trayiconcommand.o: trayiconcommand.cpp trayiconcommand.h \
		mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o trayiconcommand.o trayiconcommand.cpp

preferences.o: preferences.cpp preferences.h \
		trayiconcommand.h \
		project.h \
		timespan.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o preferences.o preferences.cpp

project.o: project.cpp project.h \
		timespan.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o project.o project.cpp

timespan.o: timespan.cpp timespan.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o timespan.o timespan.cpp

createprojectdialog.o: createprojectdialog.cpp createprojectdialog.h \
		ui_createprojectdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o createprojectdialog.o createprojectdialog.cpp

screenshot.o: screenshot.cpp screenshot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o screenshot.o screenshot.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_preferenceswidget.o: moc_preferenceswidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_preferenceswidget.o moc_preferenceswidget.cpp

moc_projectwidget.o: moc_projectwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_projectwidget.o moc_projectwidget.cpp

moc_preferences.o: moc_preferences.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_preferences.o moc_preferences.cpp

moc_project.o: moc_project.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_project.o moc_project.cpp

moc_createprojectdialog.o: moc_createprojectdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_createprojectdialog.o moc_createprojectdialog.cpp

moc_screenshot.o: moc_screenshot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_screenshot.o moc_screenshot.cpp

qrc_res.o: qrc_res.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_res.o qrc_res.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

