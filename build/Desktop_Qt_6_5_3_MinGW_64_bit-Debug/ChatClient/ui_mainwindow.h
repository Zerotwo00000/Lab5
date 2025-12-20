/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QLabel *title;
    QLabel *nickname;
    QStackedWidget *stackedWidget;
    QWidget *chatPage;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *roomTextEdit;
    QListWidget *userListWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *sayLineEdit;
    QPushButton *sayBtn;
    QPushButton *logoutBtn;
    QWidget *loginPage;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QFrame *loginFrame;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *ServerEdit;
    QLabel *label_3;
    QLineEdit *UserNameEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(895, 546);
        MainWindow->setStyleSheet(QString::fromUtf8("#title {\n"
"    color: white;\n"
"    font-size: 24px;\n"
"    text-align: center;\n"
"    padding: 5px;\n"
"    background: white;\n"
"    border: none;\n"
"	border-bottom: 1px solid black;\n"
"	background-color: #2a5caa;\n"
"}\n"
"\n"
"#nickname {\n"
"    color: white;\n"
"    font-size: 24px;\n"
"    text-align: center;\n"
"    padding: 5px;\n"
"    background: white;\n"
"    border: none;\n"
"	border-bottom: 1px solid black;\n"
"	background-color: #2a5caa;\n"
"}\n"
"\n"
"#loginFrame {\n"
"    background-color: #e6f7ff;\n"
"    border-radius: 20px;\n"
"    padding: 10px;\n"
"    border: 1px solid gray;\n"
"}\n"
"\n"
"#loginButton {\n"
"    background-color: #2a5caa;\n"
"    color: white; /* \347\231\275\350\211\262\346\226\207\345\255\227 */\n"
"    border: 2px solid #000000; /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 6px;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        title = new QLabel(centralwidget);
        title->setObjectName("title");
        QFont font;
        title->setFont(font);
        title->setStyleSheet(QString::fromUtf8(""));
        title->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(title, 0, 0, 1, 1);

        nickname = new QLabel(centralwidget);
        nickname->setObjectName("nickname");
        nickname->setMaximumSize(QSize(134, 16777215));
        nickname->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(nickname, 0, 1, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        chatPage = new QWidget();
        chatPage->setObjectName("chatPage");
        verticalLayout_2 = new QVBoxLayout(chatPage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        roomTextEdit = new QTextEdit(chatPage);
        roomTextEdit->setObjectName("roomTextEdit");

        horizontalLayout->addWidget(roomTextEdit);

        userListWidget = new QListWidget(chatPage);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(userListWidget);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        sayLineEdit = new QLineEdit(chatPage);
        sayLineEdit->setObjectName("sayLineEdit");

        horizontalLayout_2->addWidget(sayLineEdit);

        sayBtn = new QPushButton(chatPage);
        sayBtn->setObjectName("sayBtn");

        horizontalLayout_2->addWidget(sayBtn);

        logoutBtn = new QPushButton(chatPage);
        logoutBtn->setObjectName("logoutBtn");

        horizontalLayout_2->addWidget(logoutBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(chatPage);
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        gridLayout_3 = new QGridLayout(loginPage);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalSpacer_2 = new QSpacerItem(20, 153, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(279, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        loginFrame = new QFrame(loginPage);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setMinimumSize(QSize(100, 100));
        loginFrame->setFrameShape(QFrame::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(loginFrame);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(loginFrame);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setPointSize(11);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        ServerEdit = new QLineEdit(loginFrame);
        ServerEdit->setObjectName("ServerEdit");

        gridLayout->addWidget(ServerEdit, 0, 1, 1, 1);

        label_3 = new QLabel(loginFrame);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        UserNameEdit = new QLineEdit(loginFrame);
        UserNameEdit->setObjectName("UserNameEdit");

        gridLayout->addWidget(UserNameEdit, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);

        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");

        gridLayout_2->addWidget(loginButton, 2, 0, 1, 1);


        gridLayout_3->addWidget(loginFrame, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(279, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 153, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 2, 1, 1, 1);

        stackedWidget->addWidget(loginPage);

        gridLayout_4->addWidget(stackedWidget, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\201\212\345\244\251\345\256\244\345\256\242\346\210\267\347\253\257", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "\346\235\216\345\256\235\350\276\211\347\232\204\350\201\212\345\244\251\345\256\2442023414300207", nullptr));
        nickname->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260", nullptr));
        sayBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        logoutBtn->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        ServerEdit->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260\357\274\232", nullptr));
        UserNameEdit->setText(QCoreApplication::translate("MainWindow", "zayu", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225\350\201\212\345\244\251\345\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
