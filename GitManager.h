#ifndef GITMANAGER_H
#define GITMANAGER_H

#include <QString>

class GitManager{

public:
    bool isGitRepo(QString path);
    QString getStatus(QString path);
    void stageFile(QString file);
    void commit(QString message);
    void push();
    QString fileStatus(QString filestatus);
};

#endif // GITMANAGER_H
