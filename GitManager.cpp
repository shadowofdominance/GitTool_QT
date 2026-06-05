#include "GitManager.h"
#include <QDir>
#include <QProcess>

bool GitManager::isGitRepo(QString path){
    QDir dir(path);
    return dir.exists(".git");
}

QString GitManager::getStatus(QString path){
    QProcess process;

    process.setWorkingDirectory(path);

    process.start("git", QStringList() << "status" << "--porcelain");

    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    if(!error.isEmpty()){
        return "Error: " + error;
    }

    return output;
}
QString GitManager::fileStatus(QString fileStatus){
    if(fileStatus == "M")
        return "Modified";
    if(fileStatus == "D")
        return "Deleted";
    if(fileStatus == "??")
        return "Untracked";

    return fileStatus;
}
