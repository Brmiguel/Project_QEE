#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include "parsing.h"


#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QListWidgetItem>
#include <QBluetoothSocket>
#include <QBluetoothLocalDevice>

#include <QStringListModel>
#include <QObject>
#include <QtQml>
#include <QDir>
#include <QFile>

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))


class Bluetooth : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringListModel *listDevice_model READ ReadListDevice_model NOTIFY listDeviceChanged)

    Q_PROPERTY(QString message READ message_return NOTIFY messageRecieved)

    Q_PROPERTY(QString btnName READ btnNameRet NOTIFY btnChanged)

    Q_PROPERTY(bool ledConnec READ led_Connec NOTIFY ledChanged)

    Q_PROPERTY(int graf_rt_P READ realTimeP() NOTIFY pRTChanged)
    Q_PROPERTY(int graf_rt_I READ realTimeI() NOTIFY iRTChanged)
    Q_PROPERTY(int graf_rt_V READ realTimeV() NOTIFY vRTChanged)

    Q_PROPERTY(QString paymentText READ paymentFunc NOTIFY paymentChanged)

    Q_PROPERTY(int graf_P_P READ grafPP() NOTIFY PPChanged)
    Q_PROPERTY(int graf_P_Q READ grafPQ() NOTIFY PQChanged)

    Q_PROPERTY(int graf_year READ grafYear() NOTIFY GYChanged)
    Q_PROPERTY(int graf_year_P READ grafYearP() NOTIFY pGYChanged)
    Q_PROPERTY(int graf_year_Q READ grafYearQ() NOTIFY qGYChanged)

    Q_PROPERTY(int graf_month READ grafMonth() NOTIFY GMChanged)
    Q_PROPERTY(int graf_month_P READ grafMonthP() NOTIFY pGMChanged)
    Q_PROPERTY(int graf_month_Q READ grafMonthQ() NOTIFY qGMChanged)

    Q_PROPERTY(int graf_day READ grafDay() NOTIFY GDChanged)
    Q_PROPERTY(int graf_day_P READ grafDayP() NOTIFY pGDChanged)
    Q_PROPERTY(int graf_day_Q READ grafDayQ() NOTIFY qGDChanged)

    Q_PROPERTY(QString graf_fault_last READ grafFaultLast() NOTIFY GFLChanged)
    Q_PROPERTY(QString graf_fault_time READ grafFaultTime() NOTIFY timeGFChanged)
    Q_PROPERTY(int graf_fault_V READ grafFaultV() NOTIFY vGFChanged)
    Q_PROPERTY(int graf_fault_Sag READ grafFaultSag() NOTIFY sagGFChanged)
    Q_PROPERTY(int graf_fault_Swell READ grafFaultSwell() NOTIFY swellGFChanged)

    Q_PROPERTY(bool password READ Password_r() NOTIFY password_recieved)
    Q_PROPERTY(int password_index READ Password_index() NOTIFY password_recieved )



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

     /*check password*/
     void password_correct(QString password_correct);
     bool Password_r();
     int Password_index();


     bool led_Connec();

     int realTimeP();

     int realTimeI();

     int realTimeV();

     bool readFile();

     bool writeFile();

     QString paymentFunc();

     /*Funçoes Graficos*/
     int grafPP();
     int grafPQ();

     int grafYear();
     int grafYearP();
     int grafYearQ();

     int grafMonth();
     int grafMonthP();
     int grafMonthQ();

     int grafDay();
     int grafDayP();
     int grafDayQ();

     QString grafFaultLast();
     QString grafFaultTime();
     int grafFaultV();
     int grafFaultSag();
     int grafFaultSwell();

     void parsingFile(QString line , int index);

    Q_INVOKABLE void find();

    Q_INVOKABLE void conectar(QString name);

    Q_INVOKABLE void send(QString mensage,int tipo,bool enable);


signals:

    void password_recieved();

    void messageRecieved();
    void listDeviceChanged();
    void btnChanged();
    void ledChanged();
    void pRTChanged();
    void iRTChanged();
    void vRTChanged();
    void paymentChanged();

    void PPChanged();
    void PQChanged();

    void GYChanged();
    void pGYChanged();
    void qGYChanged();

    void GMChanged();
    void pGMChanged();
    void qGMChanged();

    void GDChanged();
    void pGDChanged();
    void qGDChanged();

    void GFLChanged();
    void timeGFChanged();
    void vGFChanged();
    void sagGFChanged();
    void swellGFChanged();



private slots:

    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    void connectedChanged();

    void finishedSearch();

    void readData();


private:

    int index_devices=0;
    int indexRTP=25;
    int indexRTI=25;
    int indexRTV=25;

    int indexGYP=12;
    int indexGYQ=12;

    int indexGMP=31;
    int indexGMQ=31;

    int indexGDP=24;
    int indexGDQ=24;

    int indexGFV=108;  

    StructOfDevices structOfDevices[10] ;

    QBluetoothLocalDevice localDevice;

    QStringList listDevice;

    QBluetoothSocket *socket;

    QString message;

    QString btnName;

    QStringList detected;

    bool ledConnec;

    int password_index;
    bool password_r;
    QString password_w;

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
    QString graf_fault_Time;//ver melhor isto
    int graf_fault_Sag;//counter dos sags
    int graf_fault_Swell;//counter dos swells


    /*Grafico Tempo Real*///mostra os ultimos 5 sec (mostrando a media de cada ciclo)
    int graf_rt_V[25];
    int graf_rt_I[25];
    int graf_rt_P[25];

    /*Custo da eletrecidade por W*/

    double custoLuz ;


};

#endif // BLUETOOTH_H
