#include "MainWindow.hpp"

MainWindow::MainWindow(Carte& carte) : carte(carte) {

    // Init the general widget
    this->setWindowTitle("Route-Planner");
    this->mainWidget = new QWidget;
	QHBoxLayout* qbl_general = new QHBoxLayout;
	this->mainWidget->setLayout(qbl_general);
	this->setCentralWidget(this->mainWidget);
    
    // Init the windows size
    this->width= 600; 
	this->height = 400;
	setMinimumSize(this->width, this->height);
	
	this->sceneCarte = new SceneCarte(carte);
	this->mainView = new MainView(this->sceneCarte, this);

    qbl_general->addWidget(createGroupBoxInfos());
	qbl_general->addWidget(this->mainView);

   
}


//===========================================================================================


/*FenetrePrincipale::FenetrePrincipale(Plan &plan_init) : plan(plan_init) {

	widget_general = new QWidget;
	QHBoxLayout * qbl_general = new QHBoxLayout;
	widget_general->setLayout(qbl_general);
	this->setCentralWidget(widget_general);

	largeur = 600; // qApp->desktop()->screenGeometry().width() / 2;
	hauteur = 400; // qApp->desktop()->screenGeometry().height() / 2;
	setMinimumSize(largeur,hauteur);

	myscene = new ScenePlan(plan);
	myview1 = new GrandeVue(myscene, this, plan.getOrientation());

	qbl_general->addWidget(creerGroupBoxInfos());

	qbl_general->addWidget(myview1);
	barre_statut = statusBar();
	
	connect( myview1, &GrandeVue::coord_viewport, myview2, &MiniVue::trace_viewport);
	connect( myview1, &GrandeVue::position, this, &FenetrePrincipale::affiche_pos_scene);
}

FenetrePrincipale::~FenetrePrincipale() {
}*/

QGroupBox* MainWindow::createGroupBoxInfos() {
	QGroupBox * gb = new QGroupBox;
	gb->setMaximumWidth(this->width/3);

	QVBoxLayout *vbox = new QVBoxLayout;
	gb->setLayout(vbox);
    
    QLabel* startLabel = new QLabel("Departure City");
	QLabel* arrivalLabel = new QLabel("Arrival City");
    // QLabel* distanceLabel = new QLabel("Distance: " + this->sceneCarte->getDistance());

    QLineEdit* startLineEdit = new QLineEdit;
    startLineEdit->setPlaceholderText("Departure...");
    QLineEdit* arrivalLineEdit = new QLineEdit;
    arrivalLineEdit->setPlaceholderText("Arrival...");
     
	QPushButton* compute = new QPushButton("Go");
	this->miniView = new MiniView(this->sceneCarte, this);

	vbox->addWidget(startLabel);
	vbox->addWidget(startLineEdit);
	vbox->addWidget(arrivalLabel);
	vbox->addWidget(arrivalLineEdit);
	vbox->addWidget(compute);
	vbox->addWidget(this->miniView);

	return gb;
}

/*============================= SLOTS ==============================*/
void MainWindow::geoCoordsSlot(QPointF p) {

}