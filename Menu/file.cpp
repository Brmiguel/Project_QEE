#include "file.h"

file::file()
{
    QFile file("Dados.txt");
}


bool file::readFile()
{
    QFile file("Dados.txt");
    if(!file.exists())
    {
        qDebug() << file.fileName() << " does not exists";
    }

    if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);

        qDebug() << " ----- Reading from file ------" ;
        textStream.seek(0);
        while (!textStream.atEnd()) {

            qDebug() << textStream.readLine() ; //textStream.readAll()

        }

        file.close();
        return true;
    }

    else {
        qDebug() << " Could not open the file" ;
        return false;
    }
}

bool file::writeFile()
{
    QFile file("Dados.txt");
    if(!file.exists())
    {
        qDebug() << file.fileName() << " does not exists";
    }

    if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);

        qDebug() << " ----- Writing to file ------" ;

        textStream << "The first Line\n";
        textStream << "The second Line\n";
        textStream << "Note that the >> perator does not appends a new line automatically at the end\n";

        file.close();
        return true;
    }

    else {
        qDebug() << " Could not open the file" ;
        return false;
    }
}
