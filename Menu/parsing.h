#ifndef PARSING_H
#define PARSING_H
#include <QMainWindow>
#include <QTextStream>
#include <QDebug>

/*Varios tipos que criei para retornar os valores de maneira mais organizada*/
struct Date{
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int sec;
} typedef date_t;

struct Graf_year_t{
    int year;
    int type;//P-0 ou Q-1
    int actual_month;
    int data[2];
}typedef graf_year_t;

struct Graf_month_t{
    int month;
    int type;//P-0 ou Q-1
    int data[31];
}typedef graf_month_t;

struct Graf_day_t{
    int day;
    int type;//P-0 ou Q-1
    int data[24];
}typedef graf_day_t;

struct Graf_fault_last_t{
    date_t date;
    int data[108];
}typedef Graf_fault_last_t;

struct Graf_fault_counter_t{
    int sag;
    int swell;
}typedef Graf_fault_counter_t;

struct Graf_rt_t{
    int v;
    int i;
    int p;
}typedef Graf_rt_t;

/*  Definição das classes*/

class Send
{

public:
   QString PassWord();
   QString Date(date_t date);
   QString Graf_rt(bool enable);
   QString Light(bool enable);

};



class Recieve
{

public:

   QString Get_Content(QString mensage);//verifica se têm o s: no inicio e o :P no fim, retorna a mensagem sem o S: e sem o :P
   int Get_Type(QString content);// verfica o tipo da mensagem, retorna o tipo da mensagem(se é para o grafico do ano, se é para a palavra-passe, etc)
   graf_year_t Graf_Year_Data(QString content);//tipo 0
   graf_month_t Graf_Month_Data(QString content);//tipo 1
   graf_day_t Graf_Day_Data(QString content);//tipo 2
   Graf_fault_last_t Graf_fault_last(QString content);//tipo 3
   Graf_fault_counter_t Graf_fault_counter(QString content);//tipo 4
   Graf_rt_t Graf_rt(QString content);//tipo 5
   QString Password(QString content);//tipo 6

};

#endif // PARSING_H
