#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <regex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->messaggio->setVisible(false);
    viewIsEmpty = true;

}
MainWindow::~MainWindow()
{
    delete ui;
}

/*
calcola y = f(x) a partire da un vettore di coefficienti reali,
il grado n della funzione e il valore della coordinata x
*/
double MainWindow::calcolaFunzione(std::vector<double> coeff, int n, double x)
{
    double risultato = coeff[0];
    for (int i=1; i<n; i++)
        risultato = risultato*x + coeff[i];

    return risultato;
}
/*
implementa uno zoom con un fattore 2x
*/
void MainWindow::on_zoomin_clicked(){
    chart->zoomIn();
}

void MainWindow::on_zoomout_clicked(){
    chart->zoomOut();
}

/*
disegna il grafico, se ne è già presente uno lo cancella
e ne disegna uno nuovo
*/
void MainWindow::on_disegna_clicked(){
    if(!viewIsEmpty){
        delete chart;
        delete chartView;
        intersezione_X.clear();
        aggiungiGrafico();
    }
    else
        aggiungiGrafico();
}

/*
elabora la funziona data in input,
disegnandone alcuni punti e gli assi x e y
*/

void MainWindow::aggiungiGrafico(){
    viewIsEmpty = false;
    //esempio di stringa valida = "2x^3-3x^2+1x^1-2";
    std::string polystr = ui->lineEdit->text().toStdString();
    bool stringaOk = stringaCorretta(polystr);

    if(stringaOk){
        ui->messaggio->setVisible(false);
        QSplineSeries *series = new QSplineSeries();
        series->setName("spline");
        std::vector<double> coeff = estraiCoeff(polystr);
        double y;
        int n = coeff.size();
        for(double x = -10; x <= 10; x+=0.5){
            y =  calcolaFunzione(coeff, n, x);
            if(x==0)
                intersezione_Y=y;
            series->append(x,y);
        }

        chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->setTitle("Grafico di una funzione polinomiale");

        chart->createDefaultAxes();
        //stabilisco un range per entrambi gli assi
        chart->axes(Qt::Vertical).first()->setRange(-100, 100);
        chart->axes(Qt::Horizontal).first()->setRange(-100, 100);

        //estraggo tutti i punti disegnati del grafico e trovo l'intersezione con l'asse y
        QList<QPointF> punti = series->points();
        for(int i = 0; i< punti.size();i++){
            if(punti[i].y()>=-0.5 && punti[i].y()<=0.5)
                intersezione_X.push_back(punti[i].x());;

        }
        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        ui->verticalLayout_2->addWidget(chartView);
        chartView->installEventFilter(this);
    }
    else{
        ui->messaggio->setVisible(true);
        ui->messaggio->setText("Formato della funzione non corretto. Deve essere della forma ax^n+..bx^1+c, con a,b..c numeri reali ed n numeri naturali");
    }
}
/*
funzione che stabilisce se la stringa è corretta formalmente
*/
bool MainWindow::stringaCorretta(std::string s){
    if(s.length()==0)
        return false;
    std::regex str_expr("^([-+]?([0-9]*\\.?[0-9]+)?(x(\\^[+-]?[0-9]+)?)?)+");
    return std::regex_match(s,str_expr);
}

/*
funzione che estrae i coefficenti dalla stringa
*/
std::vector<double> MainWindow::estraiCoeff(std::string s){
    //vanno inseriti i coefficenti di tutti i gradi e x va inserito come x^1
    std::regex rgx("x\\^\\d+\\+?");
    std::sregex_token_iterator iter(s.begin(), s.end(), rgx,-1);
    std::sregex_token_iterator end;
    std::vector<std::string> str_coeff;
    for ( ; iter != end; ++iter)
        str_coeff.push_back(*iter);
    std::vector<double> coeff;
    for(int i=0;i< str_coeff.size();i++)
        coeff.push_back(stoi(str_coeff[i]));
    return coeff;

}

/*
tiene traccia degli eventi sul grafico e trasla il grafico sulla base
dei tasti premuti sulla tastiera
*/
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        auto *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        if  (key == Qt::Key_Left)
        {
            chart->scroll(-10, 0);
            return true;
        }
        if  (key == Qt::Key_Right)
        {
            chart->scroll(10, 0);
            return true;
        }
        if  (key == Qt::Key_Up)
        {
            chart->scroll(0, 10);
            return true;
        }
        if  (key == Qt::Key_Down)
        {
            chart->scroll(0, -10);
            return true;
        }
    } else {
        return QMainWindow::eventFilter(obj, event);
    }
}
/*
mostra l'intersezione con gli assi x e y in una label
*/
void MainWindow::on_intersezione_clicked(){
    ui->messaggio->setVisible(true);

    QString str;
    for(int i=0;i<intersezione_X.size();i++)
        str+="("+QString::number(intersezione_X[i])+",0)";

    ui->messaggio->setText("Intersezione con asse X: Punti "+
                           str+
                           " Intersezione con asse Y: Punti (0,"+
                           QString::number(intersezione_Y)+")");
}

