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
}

MainWindow::~MainWindow()
{
    delete ui;
    ui->fileChangesTreeWidget->setHeaderLabels(
        QStringList() << "Status" << "File"
        );
}

void MainWindow::on_selectProjectBtn_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(
        this,
        "Select Project Folder"
    );

    if(folderPath.isEmpty())
        return;

    ui->projectPathLabel->setText("Path: " + folderPath);

    GitManager git;

    if(!git.isGitRepo(folderPath)){
        qDebug() << "Not a git repo!";
        ui->projectPathLabel->setText("PATH NOT A GIT REPO!");
        return;
    }

    QString status = git.getStatus(folderPath);

    updateFileTree(status);

    qDebug() << status;

}


void MainWindow::on_pushBtn_clicked()
{

}


void MainWindow::on_commitBtn_clicked()
{

}

void MainWindow::updateFileTree(QString status)
{
    ui->fileChangesTreeWidget->clear();
    QStringList lines = status.split("\n", Qt::SkipEmptyParts);

    for(const QString & line : lines){


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

