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

    Q_PROPERTY(QString btnName READ btnNameRet NOTIFY btnChanged)




     QStringListModel *listDevice_model;

     struct {
            QString name;
            QString adress;
     }typedef StructOfDevices ;

public:
    explicit Bluetooth(QObject *parent = nullptr);

     QStringListModel *ReadListDevice_model();

     QString message_return();

     QString btnNameRet();

    Q_INVOKABLE void find();

    Q_INVOKABLE void conectar(QString name);

    Q_INVOKABLE void send(QString mensage);

    /*Funçoes Graficos*/
    Q_INVOKABLE int get_graf_Total(int tipo);

    Q_INVOKABLE int get_graf_year(int tipo, int index ...);

    Q_INVOKABLE int get_graf_month(int tipo, int index ...);

    Q_INVOKABLE int get_graf_day(int tipo, int index ...);

    Q_INVOKABLE int get_graf_fault(int tipo, int index ...);

    Q_INVOKABLE QString get_graf_fault_S(int tipo, int index ...);


signals:

    void messageRecieved();
    void listDeviceChanged();
    void btnChanged();



private slots:

    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    void connectedChanged();

    void finishedSearch();

    void readData();


private:

    int index_devices=0;

    StructOfDevices structOfDevices[10] ;

    QBluetoothLocalDevice localDevice;

    QStringList listDevice;

    QBluetoothSocket *socket;

    QString message;

    QString btnName;

    QStringList detected;

    /*Grafico Potencia geral*/
    int p_P;
    int p_Q;
    //int p_S: p_P+p_Q;

    /*Grafico ano*/
    int graf_year_Year;
    int graf_year_P[12];
    int graf_year_Q[12];

    /*Grafico mês*/
    int graf_month_Month;
    int graf_month_P[31];
    int graf_month_Q[31];

    /*Grafico dia*/
    int graf_day_Day;
    int graf_day_P[24];
    int graf_day_Q[24];

    /*Grafico Falha*///Guarda os 3 ultimos ciclos da falha (de 10º em 10º)
    QString graf_fault_last;
    int graf_fault_V[108];
    QString graf_fault_Time[108];//ver melhor isto
    int graf_fault_Sag;//counter dos sags
    int graf_fault_Swell;//counter dos swells


    /*Grafico Tempo Real*///mostra os ultimos 5 sec (mostrando a media de cada ciclo)
    int graf_rt_V[25];
    int graf_rt_I[25];
    int graf_rt_P[25];
    QString graf_rt_Time[25];



};

#endif // BLUETOOTH_H
