#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow> // Already include QWidgets
#include <QGraphicsView>
#include <QApplication>

#include "MainView.hpp"
#include "MiniView.hpp"

#include "model/Carte.hpp"
#include "model/SceneCarte.hpp"

// For widget
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QGroupBox>
#include<QLabel>
#include <QStatusBar>
#include <QLineEdit>
#include <QPushButton>

class MainWindow: public QMainWindow {
    Q_OBJECT
    public:
        // Construtor
        MainWindow(Carte& carte);

        // Destructor
        virtual ~MainWindow(){}

    public slots:
        void geoCoordsSlot(QPointF p);

    private:
        QLabel* startTown;
        QLabel* destTown;
        QLabel* distance;
        QLabel* precision;
        QWidget* mainWidget;
        QStatusBar* statusBar;

        // Dimensions
        int width;
        int height;
        
        // Views
        MiniView* miniView;
        MainView* mainView;

        // Scene
        SceneCarte* sceneCarte;
        Carte& carte;

        // Methods
        QGroupBox* createGroupBoxInfos();
    
};

#endif