#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GitManager.h"

#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fileChangesTreeWidget->setHeaderLabels(
        QStringList() << "Status" << "File"
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectProjectBtn_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(
        this,
        "Select Project Folder"
    );

    if(folderPath.isEmpty())
        return;

    currentProjectPath = folderPath;
    ui->projectPathLabel->setText("Path: " + folderPath);

    if(!gitManager.isGitRepo(folderPath)){
        qDebug() << "Not a git repo!";
        ui->projectPathLabel->setText("PATH NOT A GIT REPO!");
        return;
    }

    QString status = gitManager.getStatus(folderPath);

    updateFileTree(status);

    qDebug() << status;

}


void MainWindow::on_stageAllButton_clicked()
{
    if(currentProjectPath.isEmpty())
    {
        qDebug() << "No project selected";
        return;
    }

    bool success = gitManager.stageAllFiles(currentProjectPath);

    if(success){
        qDebug() << "All files staged successfully";

        QString status = gitManager.getStatus(currentProjectPath);
        updateFileTree(status);
    }
}

void MainWindow::on_commitBtn_clicked()
{
    if(currentProjectPath.isEmpty())
    {
        qDebug() << "No project selected";
        return;
    }

    QString commitMessage = ui->commitMessageLineEdit->text();

    if(commitMessage.isEmpty()){
        qDebug() << "Commit message cannot be empty";
        return;
    }

    bool success = gitManager.commitChanges(currentProjectPath, commitMessage);

    if(success){
        qDebug() << "Commmit Successful";

        QString status = gitManager.getStatus(currentProjectPath);

        updateFileTree(status);

        ui->commitMessageLineEdit->clear();
    }

}

void MainWindow::on_pushBtn_clicked()
{
    if(currentProjectPath.isEmpty())
    {
        qDebug() << "No project selected";
        return;
    }
    bool success = gitManager.pushChanges(currentProjectPath);

    if(success){
        qDebug() << "Push successful";
    }
}

void MainWindow::updateFileTree(QString status)
{
    ui->fileChangesTreeWidget->clear();
    QStringList lines = status.split("\n", Qt::SkipEmptyParts);

    for(const QString & line : std::as_const(lines)){

        if(line.isEmpty())
            continue;

        QString fileStatus = line.left(2).trimmed();

        QString fileName = line.mid(3).trimmed();

        QTreeWidgetItem* item = new QTreeWidgetItem;

        item->setText(0, fileStatus);
        item->setText(1, fileName);

        ui->fileChangesTreeWidget->addTopLevelItem(item);
    }
}



