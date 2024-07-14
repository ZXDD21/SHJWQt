/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_IP;
    QWidget *centralwidget;
    QGridLayout *gridLayout_9;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QLabel *label_16;
    QPushButton *pushButton_13;
    QPushButton *pushButton_12;
    QLabel *label_17;
    QLabel *label_19;
    QPushButton *pushButton_11;
    QSplitter *splitter_2;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_8;
    QSpacerItem *horizontalSpacer;
    QPushButton *refresh_table;
    QTableWidget *tableWidget;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_9;
    QWidget *layoutWidget_9;
    QHBoxLayout *horizontalLayout_9;
    QRadioButton *radioButton_2;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_28;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *refresh_table_3;
    QTableWidget *tableWidget_5;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(815, 904);
        action = new QAction(MainWindow);
        action->setObjectName("action");
        action->setMenuRole(QAction::NoRole);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName("action_2");
        action_2->setMenuRole(QAction::NoRole);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName("action_3");
        action_3->setMenuRole(QAction::NoRole);
        action_IP = new QAction(MainWindow);
        action_IP->setObjectName("action_IP");
        action_IP->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_9 = new QGridLayout(centralwidget);
        gridLayout_9->setObjectName("gridLayout_9");
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName("splitter_3");
        splitter_3->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        groupBox_3 = new QGroupBox(splitter);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName("gridLayout_3");
        splitter->addWidget(groupBox_3);
        groupBox_4 = new QGroupBox(splitter);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName("gridLayout");
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName("label_16");

        gridLayout->addWidget(label_16, 0, 0, 1, 1);

        pushButton_13 = new QPushButton(groupBox_4);
        pushButton_13->setObjectName("pushButton_13");

        gridLayout->addWidget(pushButton_13, 2, 1, 1, 1);

        pushButton_12 = new QPushButton(groupBox_4);
        pushButton_12->setObjectName("pushButton_12");

        gridLayout->addWidget(pushButton_12, 1, 1, 1, 1);

        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName("label_17");

        gridLayout->addWidget(label_17, 1, 0, 1, 1);

        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName("label_19");

        gridLayout->addWidget(label_19, 2, 0, 1, 1);

        pushButton_11 = new QPushButton(groupBox_4);
        pushButton_11->setObjectName("pushButton_11");

        gridLayout->addWidget(pushButton_11, 0, 1, 1, 1);

        splitter->addWidget(groupBox_4);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Vertical);
        label = new QLabel(splitter_2);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        splitter_2->addWidget(label);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName("layoutWidget");
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(layoutWidget);
        radioButton->setObjectName("radioButton");

        horizontalLayout->addWidget(radioButton);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setPointSize(15);
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        pushButton_8 = new QPushButton(layoutWidget);
        pushButton_8->setObjectName("pushButton_8");

        horizontalLayout->addWidget(pushButton_8);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        refresh_table = new QPushButton(layoutWidget);
        refresh_table->setObjectName("refresh_table");

        horizontalLayout->addWidget(refresh_table);

        splitter_2->addWidget(layoutWidget);
        tableWidget = new QTableWidget(splitter_2);
        tableWidget->setObjectName("tableWidget");
        splitter_2->addWidget(tableWidget);
        layoutWidget_2 = new QWidget(splitter_2);
        layoutWidget_2->setObjectName("layoutWidget_2");
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget_2);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_9 = new QPushButton(layoutWidget_2);
        pushButton_9->setObjectName("pushButton_9");

        horizontalLayout_3->addWidget(pushButton_9);

        splitter_2->addWidget(layoutWidget_2);
        layoutWidget_9 = new QWidget(splitter_2);
        layoutWidget_9->setObjectName("layoutWidget_9");
        horizontalLayout_9 = new QHBoxLayout(layoutWidget_9);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        radioButton_2 = new QRadioButton(layoutWidget_9);
        radioButton_2->setObjectName("radioButton_2");

        horizontalLayout_9->addWidget(radioButton_2);

        label_9 = new QLabel(layoutWidget_9);
        label_9->setObjectName("label_9");
        label_9->setFont(font1);

        horizontalLayout_9->addWidget(label_9);

        lineEdit_5 = new QLineEdit(layoutWidget_9);
        lineEdit_5->setObjectName("lineEdit_5");

        horizontalLayout_9->addWidget(lineEdit_5);

        pushButton_28 = new QPushButton(layoutWidget_9);
        pushButton_28->setObjectName("pushButton_28");

        horizontalLayout_9->addWidget(pushButton_28);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        refresh_table_3 = new QPushButton(layoutWidget_9);
        refresh_table_3->setObjectName("refresh_table_3");

        horizontalLayout_9->addWidget(refresh_table_3);

        splitter_2->addWidget(layoutWidget_9);
        tableWidget_5 = new QTableWidget(splitter_2);
        tableWidget_5->setObjectName("tableWidget_5");
        splitter_2->addWidget(tableWidget_5);
        splitter_3->addWidget(splitter_2);

        gridLayout_9->addWidget(splitter_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 815, 17));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu_2->addAction(action);
        menu_2->addAction(action_2);
        menu_2->addAction(action_3);
        menu_2->addAction(action_IP);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\274\240\347\255\226\347\225\245", nullptr));
#if QT_CONFIG(tooltip)
        action->setToolTip(QCoreApplication::translate("MainWindow", "plase give a .txt file", nullptr));
#endif // QT_CONFIG(tooltip)
        action_2->setText(QCoreApplication::translate("MainWindow", "\344\270\213\350\275\275\350\277\220\350\241\214\346\227\266\347\255\226\347\225\245", nullptr));
#if QT_CONFIG(tooltip)
        action_2->setToolTip(QCoreApplication::translate("MainWindow", "\344\270\213\350\275\275\347\255\226\347\225\245\345\210\260\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        action_3->setText(QCoreApplication::translate("MainWindow", "\344\270\213\350\275\275\345\210\240\351\231\244\347\255\226\347\225\245", nullptr));
        action_IP->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\224\271IP", nullptr));
        groupBox_3->setTitle(QString());
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\345\242\236\345\212\240\347\255\226\347\225\245", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\346\250\241\346\235\277\344\270\200", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\346\250\241\346\235\277\344\272\214", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\346\250\241\346\235\277\344\270\211", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        label->setText(QString());
        radioButton->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214\347\255\226\347\225\245", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
        refresh_table->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\350\241\250\346\240\274", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\211\271\351\207\217\345\210\240\351\231\244", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\346\211\271\351\207\217\346\222\244\345\215\225", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\350\247\246\345\217\221\347\255\226\347\225\245", nullptr));
        pushButton_28->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
        refresh_table_3->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\350\241\250\346\240\274", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\255\226\347\225\245\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
