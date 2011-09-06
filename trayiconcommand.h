#ifndef TRAYICONCOMMAND_H
#define TRAYICONCOMMAND_H

class MainWindow;

class TrayIconCommand
{
public:
    TrayIconCommand(MainWindow* obj, void(MainWindow:: *meth)());
    void execute();
private:
    void(MainWindow:: *method)();
    MainWindow *object;
};

#endif // TRAYICONCOMMAND_H
