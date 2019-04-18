#ifndef FILE_H
#define FILE_H

#include <QtQml>
#include <QDir>
#include <QFile>

class file
{
public:

    bool readFile();

    bool writeFile();

    file();
};

#endif // FILE_H
