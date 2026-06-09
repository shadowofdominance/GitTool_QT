#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GitManager.h"
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
    void updateFileTree(QString status);

private slots:
    void on_selectProjectBtn_clicked();

    void on_pushBtn_clicked();

    void on_commitBtn_clicked();

    void on_stageAllButton_clicked();

private:
    Ui::MainWindow *ui;
    QString currentProjectPath;

    GitManager gitManager;
};
#endif // MAINWINDOW_H
