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

    return btnName;
}



void Bluetooth::finishedSearch()
{
    //qDebug() << "acabei ";
    if(listDevice.size() == 0) listDevice << "Not Found";
    listDevice_model->setStringList(listDevice);
    emit listDeviceChanged();

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
int Bluetooth::get_graf_Total(int tipo){

    switch (tipo) {
        case 0:
            return p_P;
        case 1:
            return p_Q;
        case 2:
            return p_P+p_Q;
    }
   return -1;
};

int Bluetooth::get_graf_year(int tipo, int index ...){

    switch (tipo) {
        case 0:
            return graf_year_Year;
        case 1:
            return graf_year_P[index];
        case 2:
            return graf_year_Q[index];
    }
   return -1;
};

int Bluetooth::get_graf_month(int tipo, int index ...){
    switch (tipo) {
        case 0:
            return graf_month_Month;
        case 1:
            return graf_month_P[index];
        case 2:
            return graf_month_Q[index];
    }
    return -1;

};

int Bluetooth::get_graf_day(int tipo, int index ...){
    switch (tipo) {
        case 0:
            return graf_day_Day;
        case 1:
            return graf_day_P[index];
        case 2:
            return graf_day_Q[index];
    }
    return -1;

};

int Bluetooth::get_graf_fault(int tipo, int index ...){
    switch (tipo) {
        case 0:
            return graf_fault_V[index];
        case 1:
            return graf_fault_Sag;
        case 2:
            return graf_fault_Swell;
    }
    return -1;

};

QString Bluetooth::get_graf_fault_S(int tipo, int index ...){
    switch (tipo) {
        case 0:
            return graf_fault_last;
        case 1:
         return graf_fault_Time[index];
    }
    return "erro";
};






