#include "parsing.h"


QString Send::PassWord(){//envia o comando para pedir a password

    return "s:PS:P";
};

QString Send::Graf_rt(bool enable){//envia o comando para desligar/ligar o rt
    if(enable)
        return "s:RT:S:P";
    else
        return "s:RT:P:P";
};

QString Send::Light(bool enable){//envia o comando para desligar/ligar a luz
    if(enable)
        return "s:RT:O:P";
    else
        return "s:RT:F:P";
};

QString Send::Date(date_t date){//envia o comando da data
    QString ret;
    QTextStream out(&ret);
    out << "s:T:"<<date.year<<","<<date.month<<","<<date.day<<","<<date.hour<<","<<date.minute<<","<<date.sec<<":P";

    return ret;
};


/*Função recieve*/

QString Recieve::Get_Content(QString mensage){//verifica se começa por s: e acaba por :P, se sim retorna o que esta no meio
    QString ret;
    QTextStream out(&ret);
    bool i=false;
    i= mensage.startsWith("s:",Qt::CaseSensitive) & mensage.endsWith(":P",Qt::CaseSensitive);

    if(i){
        mensage.chop(2);//remove os 2 ultimos
        return  mensage.remove(0,2);//remove os 2 primeiros
    }

    else{
        return "error";
    }
};

int Recieve::Get_Type(QString content){
    QString type= content.left(3);//pega nas 2 primeiras letras e verifica qual o tipo de comando

    if(type=="RT;"){//como é o tempo real quanto mais rapido passar pelos if's melhor
        return 5;
    }
    if(type=="GA;"){
        return 0;
    }
    if(type=="GM;"){
        return 1;
    }
    if(type=="GD;"){
        return 2;
    }
    if(type=="FT:"){
        return 3;
    }
    if(type=="PS:"){
        return 6;
    }
    if(content.left(5)=="FSAG:"){
        return 4;
    }
    else {
        return -1;
    }
};

QString Recieve::Password(QString content){
    return content.remove(0,3);
};

