#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QtCharts>
//#include <QtChartsVersion>
#include <string.h>
#include <string>
#include "client.h"
#include <fstream>//文件操作
#include "newwindow.h"
#include "strategy_1.h"
#include <QDate>
#include "strategy.h"
#include "log.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void createChart();
    //void creat();
    void recive(void*);//回调函数接受数据。
    void ClientRun();//开始运行服务器
    //回调函数
    void  InittableWidget(int choice);//初始化策略信息

private slots:
    void on_refresh_table_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_11_clicked();
    void on_action_triggered();
    void on_action_2_triggered();
    void on_refresh_table_3_clicked();
    void on_pushButton_28_clicked();

    void on_radioButton_clicked(bool checked);

    void on_action_3_triggered();

    void on_action_IP_triggered();

private:
    static std::string get_now_time();
    Ui::MainWindow *ui;
    Client CL;//服务器
    QChartView *chartView;//图表视图
    QChart *chart;//图表
    QLineSeries *series0;//折现A
    QLineSeries *series1;//折现B
    QValueAxis *axisX;//X轴
    QValueAxis *axisY0; //Y轴价格轴
    QValueAxis *axisY1;//Y1轴数量轴
    DailyLogger *logger;
    bool uiHasBeenDisplayed=false;
    const int size=100;//X轴长度显示
    const std::string FILE="test.txt";
    std::list<strategy>Strategy;//策略
    std::list<strategy>removeStrategy;//删除策略
    const int min_strategy_size=10;//前17个没法删除
    void getstrategy(json data);//获取策略信息
    void addstrategy(json data);//增加策略信息
    void removestategy(json data);//修改策略信息
    std::vector<strategy_*>Strategy_;//策略模板
    std::string geturl();
    void getFORMAL_ORDER_CANCELED(json event_to_send);
    void saveurl();
    void serializeStrategyToFile(const std::vector<strategy_*>& strategies, const std::string& filename);//写入文件
    std::vector<strategy_*> deserializeStrategyFromFile(const std::string& filename);//读取文件
    void addstrategy_(strategy_*);//增加新的策略
    void showstrategy_();//展示策略按钮
    void show_txt(strategy_*str);//展示策略按钮对应的文本信息
    void createTableRow(int x,strategy &s,int choice);//增加表格内容
    void createTableRow(std::unordered_map<std::string,std::vector<double>>&S,std::unordered_map<std::string,std::vector<std::string>>&S1);
    void createTableRow(std::unordered_map<std::string, std::vector<int> > &S,std::vector<int>choice);
    void createTableRow(std::unordered_map<std::string, std::vector<int> > &S,std::unordered_map<std::string,std::vector<std::string>>&S1,std::vector<int>choice);
    void setItem(int choice);//设置表格标题
    void getvolume(json event_to_send);

    void getSCOUT_ORDER_SUCCESS(json event_to_send);
    void getSCOUT_ORDER_CANCELED(json event_to_send);

    void getFORMAL_ORDER_SUCCESS(json event_to_send);

    void getSCOUT_CANCEL_SUCCESS(json event_to_send);

    void getFORMAL_CANCEL_SUCCESS(json event_to_send);

    void getSCOUT_ORDER_ERROR(json event_to_send);

    void getFORMAL_ORDER_ERROR(json event_to_send);

    void    getSCOUT_CANCEL_ERROR(json event_to_send);

    void    getFORMAL_CANCEL_ERROR(json event_to_send);

    void    getFORMAL_PART_TRADE(json event_to_send);

    void    getFORMAL_FULLY_TRADE(json event_to_send);

    void   getSCOUT_TRADE(json event_to_send);

};


#endif // MAINWINDOW_H
