#ifndef GITMANAGER_H
#define GITMANAGER_H

#include <QString>

class GitManager{

public:
    bool isGitRepo(QString path);
    QString getStatus(QString path);
    void stageFile(QString file);
    bool commitChanges(QString path, QString message);
    void push();
    QString fileStatus(QString filestatus);
    bool stageAllFiles(QString path);
};

#endif // GITMANAGER_H
