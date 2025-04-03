#include "MainWindow.hpp"

MainWindow::MainWindow(Carte& carte) : carte(carte) {

    // Init the general widget
    this->setWindowTitle("Route-Planner");
    this->mainWidget = new QWidget;
	QHBoxLayout* qbl_general = new QHBoxLayout;
	this->mainWidget->setLayout(qbl_general);
	this->setCentralWidget(this->mainWidget);
    
    // Init the windows size
    this->width= 700; 
	this->height = 500;
	setMinimumSize(this->width, this->height);
	
	this->sceneCarte = new SceneCarte(carte);
	this->mainView = new MainView(this->sceneCarte, this);

    qbl_general->addWidget(createGroupBoxInfos());
	qbl_general->addWidget(this->mainView);

	this->statusBar = new QStatusBar;
	this->setStatusBar(this->statusBar);
   
	
	connect(this->mainView, &MainView::coord_viewport, this->miniView, &MiniView::trace_viewport);
	connect(this->mainView, &MainView::position, this, &MainWindow::geoCoordsSlot);
}


QGroupBox* MainWindow::createGroupBoxInfos() {
	QGroupBox * gb = new QGroupBox;
	gb->setMaximumWidth(this->width/3);

	QVBoxLayout *vbox = new QVBoxLayout;
	gb->setLayout(vbox);
    
    QLabel* startLabel = new QLabel("Departure City");
	QLabel* arrivalLabel = new QLabel("Arrival City");
    QLabel* distanceLabel = new QLabel("Distance: " + QString::fromStdString(std::to_string(this->sceneCarte->getDistance())) + " km");

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
	vbox->addWidget(distanceLabel);
	vbox->addWidget(this->miniView);

	return gb;
}

// Function to convert decimal degrees to D°MM.M' format
std::string MainWindow::decimalToDMS(double decimal, char positive, char negative) {
    char direction = (decimal >= 0) ? positive : negative;
    decimal = std::fabs(decimal);  // Work with absolute value

    int degrees = (int)decimal;  // Extract degrees
    double minutes = (decimal - degrees) * 60;  // Convert remainder to minutes

    // Format as D°MM.M'
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d°%.2f'%c", degrees, minutes, direction);
    return std::string(buffer);
}

void MainWindow::xyToLatLon(double x, double y, float &lon, float &lat) {
    const double EARTH_RADIUS = 6378137.0; // Earth's radius in meters

    // Convert km back to meters
    x *= 1000;
    y *= 1000;

    // Compute longitude in degrees
    lon = (x / EARTH_RADIUS) * (180.0 / M_PI);

    // Compute latitude in degrees
    lat = (2 * atan(exp(y / EARTH_RADIUS)) - M_PI / 2) * (180.0 / M_PI);
}

/*============================= SLOTS ==============================*/
void MainWindow::geoCoordsSlot(QPointF p) {
	float lat, lon;
	this->xyToLatLon(p.x(), p.y(), lon, lat);
	std::string latStr = this->decimalToDMS(lat, 'N', 'S');
    std::string lonStr = this->decimalToDMS(lon, 'E', 'W');

	QString msg = "Stage coordinates: ("+ QString::fromStdString(latStr) + ", " + QString::fromStdString(lonStr) + ")";
	this->statusBar->showMessage(msg);

}