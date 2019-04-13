#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QListWidgetItem>
#include <QBluetoothSocket>
#include <QBluetoothLocalDevice>

#include <QStringListModel>
#include <QObject>
#include <QtQml>


class Bluetooth : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringListModel *listDevice_model READ ReadListDevice_model NOTIFY listDeviceChanged)

    Q_PROPERTY(QString message READ message_return NOTIFY messageRecieved)



     QStringListModel *listDevice_model;

     struct {
            QString name;
            QString adress;
     }typedef StructOfDevices ;

public:
    explicit Bluetooth(QObject *parent = nullptr);

     QStringListModel *ReadListDevice_model();

     QString message_return();


    Q_INVOKABLE void find();

    Q_INVOKABLE void conectar(QString name);

    Q_INVOKABLE void send(QString mensage);



signals:

    void messageRecieved();
    void listDeviceChanged();


private slots:

    void deviceDiscovered(const QBluetoothDeviceInfo &device);


    void finishedSearch();

    void readData();


private:

    int index_devices=0;

    StructOfDevices structOfDevices[10] ;

    QBluetoothLocalDevice localDevice;

    QStringList listDevice;

    QBluetoothSocket *socket;

    QString message;

    QStringList detected;



};

#endif // BLUETOOTH_H
