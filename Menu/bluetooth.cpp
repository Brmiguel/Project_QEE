#include "bluetooth.h"
#include <QtBluetooth>




Bluetooth::Bluetooth(QObject *parent)
    : QObject(parent)
{

    listDevice_model = new QStringListModel(this);

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    if (localDevice.isValid()){

        localDevice.powerOn();

        // Make it visible to others
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent(this);


        connect(agent,SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this,SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
        connect(agent, SIGNAL(finished()), this, SLOT(finishedSearch()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(socket,SIGNAL(connected()),this, SLOT(connectedChanged()));

        agent->start();
    }



    password_index=0;

    p_P=600;
    p_Q=300;

    graf_year_Year=2018;


    graf_rt_P[0]=0;
    graf_rt_P[1]=0;
    graf_rt_P[2]=0;
    graf_rt_P[3]=0;
    graf_rt_P[4]=0;
    graf_rt_P[5]=0;
    graf_rt_P[6]=0;
    graf_rt_P[7]=0;
    graf_rt_P[8]=0;
    graf_rt_P[9]=0;
    graf_rt_P[10]=0;
    graf_rt_P[11]=0;
    graf_rt_P[12]=0;
    graf_rt_P[13]=0;
    graf_rt_P[14]=0;
    graf_rt_P[15]=0;
    graf_rt_P[16]=0;
    graf_rt_P[17]=0;
    graf_rt_P[18]=0;
    graf_rt_P[19]=0;
    graf_rt_P[20]=0;
    graf_rt_P[21]=0;
    graf_rt_P[22]=0;
    graf_rt_P[23]=0;
    graf_rt_P[24]=0;

    graf_rt_I[0]=0;
    graf_rt_I[1]=0;
    graf_rt_I[2]=0;
    graf_rt_I[3]=0;
    graf_rt_I[4]=0;
    graf_rt_I[5]=0;
    graf_rt_I[6]=0;
    graf_rt_I[7]=0;
    graf_rt_I[8]=0;
    graf_rt_I[9]=0;
    graf_rt_I[10]=0;
    graf_rt_I[11]=0;
    graf_rt_I[12]=0;
    graf_rt_I[13]=0;
    graf_rt_I[14]=0;
    graf_rt_I[15]=0;
    graf_rt_I[16]=0;
    graf_rt_I[17]=0;
    graf_rt_I[18]=0;
    graf_rt_I[19]=0;
    graf_rt_I[20]=0;
    graf_rt_I[21]=0;
    graf_rt_I[22]=0;
    graf_rt_I[23]=0;
    graf_rt_I[24]=0;

    graf_rt_V[0]=0;
    graf_rt_V[1]=0;
    graf_rt_V[2]=0;
    graf_rt_V[3]=0;
    graf_rt_V[4]=0;
    graf_rt_V[5]=0;
    graf_rt_V[6]=0;
    graf_rt_V[7]=0;
    graf_rt_V[8]=0;
    graf_rt_V[9]=0;
    graf_rt_V[10]=0;
    graf_rt_V[11]=0;
    graf_rt_V[12]=0;
    graf_rt_V[13]=0;
    graf_rt_V[14]=0;
    graf_rt_V[15]=0;
    graf_rt_V[16]=0;
    graf_rt_V[17]=0;
    graf_rt_V[18]=0;
    graf_rt_V[19]=0;
    graf_rt_V[20]=0;
    graf_rt_V[21]=0;
    graf_rt_V[22]=0;
    graf_rt_V[23]=0;
    graf_rt_V[24]=0;




    custoLuz = 5;

    password_r=false;
    //writeFile();
    readFile();
}

QStringListModel *Bluetooth::ReadListDevice_model()
{
    return listDevice_model;
}


QString Bluetooth::message_return()
{
    return message;

}

void Bluetooth::mudar_preco(double custo_Luz){

    custoLuz=custo_Luz;
}

/*Check Password*/
void Bluetooth::password_correct(QString password_correct)
{
    if(password_correct == password_w){
        password_r=true;
    }
    else {
        password_r=false;
    }
    qDebug()<<password_correct;
    qDebug()<<password_r;
    emit password_recieved();
}



bool Bluetooth::Password_r(){
    return password_r;
}

int Bluetooth::Password_index(){
    return password_index;
}



/*HOME PAGE*/
int Bluetooth::realTimeP()
{

    indexRTP--;
    if (indexRTP<0)
        indexRTP=24;
    return graf_rt_P[indexRTP];

}

int Bluetooth::realTimeI()
{

    indexRTI--;
    if (indexRTI<0)
        indexRTI=24;
    return graf_rt_I[indexRTI];

}

int Bluetooth::realTimeV()
{

    indexRTV--;
    if (indexRTV<0)
        indexRTV=24;
    return graf_rt_V[indexRTV];

}

QString Bluetooth::paymentFunc()
{
    paymentText ="Até ao momento o valor de luz que terá de pagar é de " + QString::number(graf_rt_P[24] * custoLuz) + " €";
    return paymentText;
}



/*Funçoes bluetooth*/

void Bluetooth::deviceDiscovered(const QBluetoothDeviceInfo &device)
{

    listDevice << device.name();
   // qDebug() << listDevice;
    structOfDevices[listDevice.size()].name= device.name() ;
    structOfDevices[listDevice.size()].adress= device.address().toString() ;
    listDevice_model->setStringList(listDevice);

    //qDebug() << listDevice_model;
    emit listDeviceChanged();
    //qDebug() << "Encontrei um device, index : " << index_devices << "  Device name: " << device.name() << "É cached"<< device.isValid();

}

void Bluetooth::connectedChanged()
{
    emit btnChanged();
}

QString Bluetooth::btnNameRet()
{
    if(socket->state() == QBluetoothSocket::ConnectingState ){  // state connected

        btnName = "Connecting ...";
    }
    if(socket->state() == QBluetoothSocket::ConnectedState ){  // state connected

        btnName = "Connected";
    }

    if(socket->state() == QBluetoothSocket::UnconnectedState ){
        btnName = "Find";
    }

    emit ledChanged();
    return btnName;
}



void Bluetooth::finishedSearch()
{
    //qDebug() << "acabei ";
    if(listDevice.size() == 0) listDevice << "Not Found";
    listDevice_model->setStringList(listDevice);
    emit listDeviceChanged();

}

bool Bluetooth::led_Connec()
{

    if(socket->state() == QBluetoothSocket::ConnectedState ){  // state connected
        ledConnec = true;
    }
    else {
        ledConnec = false;
    }

    return ledConnec;
}

void Bluetooth::find()
{

    if(localDevice.isValid()) {
        if(socket->state() == QBluetoothSocket::ConnectedState) {
            socket->close();
        }

        listDevice.clear();
        listDevice_model->setStringList(listDevice);
        emit listDeviceChanged();

        QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent(this);
        agent->stop();

        connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
        connect(agent, SIGNAL(finished()), this, SLOT(finishedSearch()));

        // Start a discovery
        agent->start();
        socket->abort();
     }


    else {
        qDebug() << "O BLUETOOTH TA TOFO FUDIDO" ;
    }

 emit btnChanged();


}

void Bluetooth::conectar(QString name)
{
    QString addr;
    //qDebug() << adress ;
    for (int i =0 ;i < 10;i++) {
        if (structOfDevices[i].name == name)
            addr=structOfDevices[i].adress;

    }

    static const QString serviceUuid("00001101-0000-1000-8000-00805F9B34FB");

    socket->connectToService(QBluetoothAddress(addr),QBluetoothUuid(serviceUuid),QIODevice::ReadWrite | QIODevice::Unbuffered);


    emit btnChanged();
}

void Bluetooth::send(QString mensage,int tipo,bool enable)
{
    QByteArray text;
    Send send;
    switch (tipo) {
    case 1:
        password_w=mensage;
        text=send.PassWord().toUtf8();
        qDebug()<<password_w;
        break;

    case 2:
        text =send.Light(enable).toUtf8();
        break;

    case 3:
        text =send.Graf_rt(enable).toUtf8();
        break;

    case 4://dd.MM.yyyy - hh:mm:ss
        date_t date;
        date.day=mensage.left(2).toInt();
        date.month=mensage.mid(3,2).toInt();
        date.year=mensage.mid(6,4).toInt();
        date.hour=mensage.mid(13,2).toInt();
        date.minute=mensage.mid(16,2).toInt();
        date.sec=mensage.right(2).toInt();
        text =send.Date(date).toUtf8();
        qDebug()<<mensage;
        qDebug()<<"-"<<date.year<<","<<date.month<<","<<date.day<<","<<date.hour<<","<<date.minute<<","<<date.sec;
        qDebug()<<text;
        break;

    default:
        text = mensage.toUtf8();
    }
    socket->write(text);

}

double Bluetooth::get_Rt_P(int index)
{
    //qDebug() << index<< " : " <<  graf_rt_P[index];
    return graf_rt_P[index];
}

double Bluetooth::get_Rt_V(int index)
{
   // qDebug() << index<< " : " <<  graf_rt_P[index];
    return graf_rt_V[index];
}

double Bluetooth::get_Rt_I(int index)
{
    return graf_rt_I[index];
}

void Bluetooth::readData()
{
    QByteArray recieved =  socket->readAll();
    message = QString::fromUtf8(recieved);

    Recieve recieve;

    QString content=recieve.Get_Content(message);

    switch (recieve.Get_Type(content)) {
    case 0:

        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:{
        Graf_rt_t struct_recieve = recieve.Graf_rt(content);
        for (int i=0; i < 24;++i) {
            graf_rt_V[i] = graf_rt_V[i+1];
            graf_rt_I[i] = graf_rt_I[i+1];
            graf_rt_P[i] = graf_rt_P[i+1];

        }
        graf_rt_V[24] = struct_recieve.v;
        graf_rt_I[24] = struct_recieve.i;
        graf_rt_P[24] = struct_recieve.p;

        break;
    }
    case 6:{//password
        password_index++;
        password_correct(recieve.Password(content));
        break;
    }
    }


    emit messageRecieved();
}


/*FUNÇOES DOS GRAFICOS*/


int Bluetooth::grafPP()
{
    return p_P;
}
int Bluetooth::grafPQ()
{
    return p_Q;
}

int Bluetooth::grafYear()
{
    return graf_year_Year;
}

int Bluetooth::grafYearP()
{

    indexGYP--;
    if (indexGYP<0)
        indexGYP=12;
    return graf_year_P[indexGYP];

}

int Bluetooth::grafYearQ()
{

    indexGYQ--;
    if (indexGYQ<0)
        indexGYQ=12;
    return graf_year_Q[indexGYQ];

}

int Bluetooth::grafMonth()
{
    return graf_month_Month;
}

int Bluetooth::grafMonthP()
{

    indexGMP--;
    if (indexGMP<0)
        indexGMP=31;
    return graf_month_P[indexGMP];

}

int Bluetooth::grafMonthQ()
{

    indexGMQ--;
    if (indexGMQ<0)
        indexGMQ=31;
    return graf_month_Q[indexGMQ];

}

int Bluetooth::grafDay()
{
    return graf_day_Day;
}

int Bluetooth::grafDayP()
{

    indexGDP--;
    if (indexGDP<0)
        indexGDP=24;
    return graf_day_P[indexGDP];

}

int Bluetooth::grafDayQ()
{

    indexGDQ--;
    if (indexGDQ<0)
        indexGDQ=24;
    return graf_day_Q[indexGDQ];

}

QString Bluetooth::grafFaultLast()
{
    return graf_fault_last;
}
QString Bluetooth::grafFaultTime()
{
    return graf_fault_Time;
}

int Bluetooth::grafFaultV()
{

    indexGFV--;
    if (indexGFV<0)
        indexGFV=108;
    return graf_fault_V[indexGFV];

}

int Bluetooth::grafFaultSag()
{
    return graf_fault_Sag;
}

int Bluetooth::grafFaultSwell()
{
    return graf_fault_Swell;
}

void Bluetooth::parsingFile(QString line , int index)
{
    QStringList imgName = line.split(",");

    switch (index){

    case 0:{
        if (imgName[0] == "s" && imgName[1] == "GA" && imgName[3] == "P" )
        {

            for (int i=0; i<  ARRAY_SIZE(graf_year_P) ;++i) {
                graf_year_P[i] = imgName[i+4].toInt();

            }
        }
        break;

    }
    case 1:{
        if (imgName[0] == "s" && imgName[1] == "GA" && imgName[3] == "Q" )
        {
            for (int i=0; i<=  ARRAY_SIZE(graf_year_Q);++i) {
                graf_year_Q[i] = imgName[i+4].toInt();
            }
        }
        break;
    }
    case 2:{
        if (imgName[0] == "s" && imgName[1] == "GM" && imgName[3] == "P" )
        {
            for (int i=0; i<  ARRAY_SIZE(graf_month_P);++i) {
                graf_month_P[i] = imgName[i+4].toInt();
            }
        }
        break;
    }
    case 3:{
        if (imgName[0] == "s" && imgName[1] == "GM" && imgName[3] == "Q" )
        {
            for (int i=0; i<  ARRAY_SIZE(graf_month_Q);++i) {
                graf_month_Q[i] = imgName[i+4].toInt();
            }
        }
        break;
    }
    case 4:{
        if (imgName[0] == "s" && imgName[1] == "GD" && imgName[3] == "P" )
        {
            for (int i=0; i<  ARRAY_SIZE(graf_day_P);++i) {
                graf_day_P[i] = imgName[i+4].toInt();
            }
        }
        break;
    }
    case 5:{
        if (imgName[0] == "s" && imgName[1] == "GD" && imgName[3] == "Q" )
        {
            for (int i=0; i<  ARRAY_SIZE(graf_day_Q);++i) {
                graf_day_Q[i] = imgName[i+4].toInt();
            }
        }
        break;
    }
    case 6:{
        if (imgName[0] == "s" && imgName[1] == "C" && imgName[3] == "P" )
        {
            custoLuz = imgName[2].toDouble();
        }
        break;
    }

    default:{
        qDebug() << "Erro";
        break;
    }

    }
}


bool Bluetooth::readFile()
{
    QFile file("Dados.txt");
    if(!file.exists())
    {
        qDebug() << file.fileName() << " does not exists";
    }

    if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        QString line[7];
        int iterator =0;
        qDebug() << " ----- Reading from file ------" ;
        textStream.seek(0);
        while (!textStream.atEnd()) {

            line[iterator] = textStream.readLine() ; //textStream.readAll()
            parsingFile(line[iterator] ,iterator);
            iterator++;
        }

        file.close();



        return true;
    }

    else {
        qDebug() << " Could not open the file" ;
        return false;
    }
}

bool Bluetooth::writeFile()
{
    QFile file("Dados.txt");


    if(!file.exists())
    {
        qDebug() << file.fileName() << " does not exists";
    }

    if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream textStream(&file);

        qDebug() << " ----- Writing to file ------" ;
        /****************************** YEAR DATA SAVING *****************/
                        /****************   P  *************/

        textStream << "s,GA,2019,P,";

        for (unsigned long i = 0; i < ARRAY_SIZE(graf_year_P) -1;++i) {
            textStream << QString::number(graf_year_P[i]) + ",";
        }
        textStream << QString::number(graf_year_P[11]) + ",P\n";

                            /****************   Q  *************/

        textStream << "s,GA,2019,Q,";

        for (unsigned long i = 0; i < ARRAY_SIZE(graf_year_Q) -1;++i) {
            textStream << QString::number(graf_year_Q[i]) + ",";
        }
        textStream << QString::number(graf_year_Q[11]) + ",P\n";

        /****************************** MONTH DATA SAVING *****************/
                             /****************   P  *************/
        textStream << "s,GM,1,P,";

        for (unsigned long i = 0; i < ARRAY_SIZE(graf_month_P) -1;++i) {
            textStream << QString::number(graf_month_P[i]) + ",";
        }
        textStream << QString::number(graf_month_P[ARRAY_SIZE(graf_month_P)-1]) + ",P\n";

                            /****************   Q  *************/

        textStream << "s,GM,1,Q,";

        for (unsigned long i = 0; i < ARRAY_SIZE(graf_month_Q) -1;++i) {
            textStream << QString::number(graf_month_Q[i]) + ",";
        }
        textStream << QString::number(graf_month_Q[ARRAY_SIZE(graf_month_Q)-1]) + ",P\n";

        /****************************** DAY DATA SAVING *****************/
                             /****************   P  *************/
        textStream << "s,GD,1,P,";

        for (unsigned long i = 0; i < ARRAY_SIZE(graf_day_P) -1;++i) {
            textStream << QString::number(graf_day_P[i]) + ",";
        }
        textStream << QString::number(graf_day_P[ARRAY_SIZE(graf_day_P)-1]) + ",P\n";

                            /****************   Q  *************/

        textStream << "s,GD,1,Q,";

        for (unsigned long i = 0; i < ARRAY_SIZE(graf_day_Q) -1;++i) {
            textStream << QString::number(graf_day_Q[i]) + ",";
        }
        textStream << QString::number(graf_day_Q[ARRAY_SIZE(graf_day_Q)-1]) + ",P\n";



        /****************************** ELECTRICITY COST SAVING *****************/

        textStream << "s,C," + QString::number(custoLuz) + ",P\n";




        file.close();
        return true;
    }

    else {
        qDebug() << " Could not open the file" ;
        return false;
    }
}

