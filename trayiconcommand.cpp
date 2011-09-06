#include "trayiconcommand.h"
#include "mainwindow.h"

TrayIconCommand::TrayIconCommand(MainWindow* obj, void(MainWindow:: *meth)())
    :method(meth), object(obj)
{
}

void TrayIconCommand::execute()
{
    (object->*method)();
}
