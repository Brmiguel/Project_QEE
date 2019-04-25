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
}

Graf_year_t Recieve::Graf_Year_Data(QString content)
{
    QStringList imgName = content.split(";");
    Graf_year_t struct_recieve;
    struct_recieve.year=imgName[1].toInt();
    if(imgName[2]=="P"){
       struct_recieve.type=0;
    }
    else {
       struct_recieve.type=1;
    }
    imgName=imgName[3].split(":");
    struct_recieve.actual_month=imgName[0].toInt();
    imgName=imgName[1].split(",");
    qDebug()<<"parsing "<<imgName[0]<<" "<<imgName[1];
    struct_recieve.data[0]=imgName[0].toInt();
    struct_recieve.data[1]=imgName[1].toInt();

    return struct_recieve;
};

Graf_month_t Recieve::Graf_Month_Data(QString content)
{
    QStringList imgName = content.split(";");
    Graf_month_t struct_recieve;
    struct_recieve.month=imgName[1].toInt();
    if(imgName[2]=="P"){
       struct_recieve.type=0;
    }
    else {
       struct_recieve.type=1;
    }

    imgName=imgName[3].split(",");

    for (int i=0;i<imgName.size();i++) {
         struct_recieve.data[i]=imgName[i].toInt();
         qDebug()<<"parsing "<<imgName[i];
    }

    return struct_recieve;
};

Graf_day_t Recieve::Graf_Day_Data(QString content)
{
    QStringList imgName = content.split(";");
    Graf_day_t struct_recieve;
    struct_recieve.day=imgName[1].toInt();
    if(imgName[2]=="P"){
       struct_recieve.type=0;
    }
    else {
       struct_recieve.type=1;
    }

    imgName=imgName[3].split(",");

    for (int i=0;i<24;i++) {
         struct_recieve.data[i]=imgName[i].toInt();
         qDebug()<<"parsing "<<imgName[i];

    }

    return struct_recieve;
};

Graf_fault_last_t Recieve::Graf_fault_last(QString content){
    QStringList imgName = content.split(":");
    imgName=imgName[1].split(",");
    Graf_fault_last_t struct_recieve;
    struct_recieve.date.month =imgName[0].toInt();
    struct_recieve.date.day =imgName[1].toInt();
    struct_recieve.date.hour =imgName[2].toInt();
    struct_recieve.date.minute =imgName[3].toInt();
    struct_recieve.date.sec =imgName[4].toInt();

    for (int i=0;i<108;i++) {
         struct_recieve.data[i]=imgName[i+5].toInt();
    }

    return struct_recieve;

};

Graf_fault_counter_t Recieve::Graf_fault_counter(QString content){
    QStringList imgName = content.split(";");
    Graf_fault_counter_t struct_recieve;

    struct_recieve.sag=imgName[0].remove(0,4).toInt();
    struct_recieve.swell=imgName[1].remove(0,6).toInt();

    return struct_recieve;
};

Graf_rt_t Recieve::Graf_rt(QString content)
{
    QStringList imgName = content.split(";");
    Graf_rt_t struct_recieve;
    struct_recieve.v=imgName[1].toInt();
    struct_recieve.i=imgName[2].toInt();
    struct_recieve.p=imgName[3].toInt();

    return struct_recieve;

};

QString Recieve::Password(QString content){
    return content.remove(0,3);
};

