#ifndef NEWWINDOW_H
#define NEWWINDOW_H
#include <QMainWindow>
#include <QDate>
#include <QtCharts/QtCharts>
//#include <QtChartsVersion>
#include "strategy_.h"
#include "strategy_1.h"
#include "strategy.h"
#include "client.h"
#include <functional>
QT_BEGIN_NAMESPACE
class NewWindow : public QWidget {
    Q_OBJECT

public:
    NewWindow();
    NewWindow(QWidget *parent);
    ~NewWindow();
    void show_one(QStringList &headerText);
    void show_newwindows(QStringList &headerText, std::vector<strategy_*>&Strategy_,std::function<void(void)>it);
    void show_table();
    void show_warn(std::vector<std::string>&S,std::function<void(void)>it);
    void  setItem(QTableWidget *tableWidget);//设置表格标题
    void show_table(std::vector<strategy_*>&S,Client&CL);
    void create_table(QTableWidget *tableWidget,int x,strategy_1&s);
private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *layout;
};
#endif // NEWWINDOW_H
