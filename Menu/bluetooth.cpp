#include "bluetooth.h"
#include <QtBluetooth>


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

bool Bluetooth::writeFile()
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

    QFile file("Dados.txt");



    p_P=600;
    p_Q=300;

    graf_year_Year=2018;

    graf_year_P[0]=100;
    graf_year_P[1]=300;
    graf_year_P[2]=600;
    graf_year_P[3]=400;
    graf_year_P[4]=500;
    graf_year_P[5]=230;
    graf_year_P[6]=345;
    graf_year_P[7]=474;
    graf_year_P[8]=346;
    graf_year_P[9]=577;
    graf_year_P[10]=544;
    graf_year_P[11]=345;

    graf_year_Q[0]=234;
    graf_year_Q[1]=124;
    graf_year_Q[2]=68;
    graf_year_Q[3]=33;
    graf_year_Q[4]=160;
    graf_year_Q[5]=35;
    graf_year_Q[6]=108;
    graf_year_Q[7]=123;
    graf_year_Q[8]=134;
    graf_year_Q[9]=167;
    graf_year_Q[10]=123;
    graf_year_Q[11]=123;


    graf_rt_P[0]=0;
    graf_rt_P[1]=1;
    graf_rt_P[2]=2;
    graf_rt_P[3]=3;
    graf_rt_P[4]=4;
    graf_rt_P[5]=5;
    graf_rt_P[6]=4;
    graf_rt_P[7]=3;
    graf_rt_P[8]=2;
    graf_rt_P[9]=1;
    graf_rt_P[10]=0;
    graf_rt_P[11]=1;
    graf_rt_P[12]=2;
    graf_rt_P[13]=3;
    graf_rt_P[14]=4;
    graf_rt_P[15]=5;
    graf_rt_P[16]=6;
    graf_rt_P[17]=7;
    graf_rt_P[18]=8;
    graf_rt_P[19]=9;
    graf_rt_P[20]=10;
    graf_rt_P[21]=11;
    graf_rt_P[22]=12;
    graf_rt_P[23]=13;
    graf_rt_P[24]=14;

    graf_rt_I[0]=0;
    graf_rt_I[1]=1;
    graf_rt_I[2]=2;
    graf_rt_I[3]=3;
    graf_rt_I[4]=4;
    graf_rt_I[5]=5;
    graf_rt_I[6]=4;
    graf_rt_I[7]=3;
    graf_rt_I[8]=2;
    graf_rt_I[9]=1;
    graf_rt_I[10]=0;
    graf_rt_I[11]=1;
    graf_rt_I[12]=2;
    graf_rt_I[13]=3;
    graf_rt_I[14]=4;
    graf_rt_I[15]=5;
    graf_rt_I[16]=6;
    graf_rt_I[17]=7;
    graf_rt_I[18]=8;
    graf_rt_I[19]=9;
    graf_rt_I[20]=10;
    graf_rt_I[21]=11;
    graf_rt_I[22]=12;
    graf_rt_I[23]=13;
    graf_rt_I[24]=18;

    graf_rt_V[0]=0;
    graf_rt_V[1]=1;
    graf_rt_V[2]=2;
    graf_rt_V[3]=3;
    graf_rt_V[4]=4;
    graf_rt_V[5]=5;
    graf_rt_V[6]=4;
    graf_rt_V[7]=3;
    graf_rt_V[8]=2;
    graf_rt_V[9]=1;
    graf_rt_V[10]=0;
    graf_rt_V[11]=1;
    graf_rt_V[12]=2;
    graf_rt_V[13]=3;
    graf_rt_V[14]=4;
    graf_rt_V[15]=5;
    graf_rt_V[16]=6;
    graf_rt_V[17]=7;
    graf_rt_V[18]=8;
    graf_rt_V[19]=9;
    graf_rt_V[20]=10;
    graf_rt_V[21]=11;
    graf_rt_V[22]=12;
    graf_rt_V[23]=13;
    graf_rt_V[24]=10;
    custoLuz = 5;

}

QStringListModel *Bluetooth::ReadListDevice_model()
{
    return listDevice_model;
}


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

QString Bluetooth::message_return()
{
    return message;

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

int Bluetooth::realTimeP()
{

    indexRTP--;
    if (indexRTP<0)
        indexRTP=25;
    return graf_rt_P[indexRTP];

}

int Bluetooth::realTimeI()
{

    indexRTI--;
    if (indexRTI<0)
        indexRTI=25;
    return graf_rt_I[indexRTI];

}

int Bluetooth::realTimeV()
{

    indexRTV--;
    if (indexRTV<0)
        indexRTV=25;
    return graf_rt_V[indexRTV];

}

QString Bluetooth::paymentFunc()
{
    return ( "Até ao momento o valor de luz que terá de pagar é de " + QString::number(graf_rt_P[24] * custoLuz) + " €");
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

void Bluetooth::send(QString mensage)
{
     QByteArray text = mensage.toUtf8() + '\n';
     socket->write(text);
}

void Bluetooth::readData()
{
    QByteArray recieved =  socket->readAll();

    message = QString::fromUtf8(recieved);
    qDebug()<<message;
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

