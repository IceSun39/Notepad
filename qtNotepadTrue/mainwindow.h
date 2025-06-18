#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTextCursor>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionOpen_triggered();

    void on_actionWhite_view_triggered();

    void on_actionDark_view_triggered();

    void on_actionItalic_triggered();

    void on_actionBold_triggered();

    void save();

    void saveAs();

    void newFile();

    void openFile();

    void setDarkTheme();

    void setLightTheme();

    void setItalic();

    void setBold();

private:
    QString currentFilePath;
    bool isModified = false;

    bool maybeSave();

    void loadFile(const QString &fileName);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
