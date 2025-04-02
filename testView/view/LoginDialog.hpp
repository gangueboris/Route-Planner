#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QMessageBox>
using namespace std;

// Login Dialog Class definition
class LoginDialog : public QDialog {
    Q_OBJECT
    public:
        // Constructor
        LoginDialog(QWidget* parent = nullptr);

        // Destructor
        ~LoginDialog(){};

        // Getteurs

        //========= Get Data load by the user ========
        void getResult(string& host, string& database, string& username, string& password);

    public slots:
        void slotLogin();


    private:
       // QDialog (visual) attributes
       QLabel* hostLabel;
       QLabel* databaseLabel;
       QLabel* usernameLabel;
       QLabel* passwordLabel;
       QLineEdit* hostLineEdit;
       QLineEdit* usernameLineEdit;
       QLineEdit* databaseLineEdit;
       QLineEdit* passwordLineEdit;
       QPushButton* loginButton;
       QPushButton* cancelButton;

       // LoginDialog attributes
       QString host;
       QString database;
       QString username;
       QString password;
};



#endif