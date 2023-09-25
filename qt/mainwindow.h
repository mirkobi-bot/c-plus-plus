#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double calcolaFunzione(std::vector<double> coeff, int n, double x);
    bool stringaCorretta(std::string s);
    std::vector<double> estraiCoeff(std::string s);
    void aggiungiGrafico();

private:
    Ui::MainWindow *ui;
    QChartView *chartView;
    QChart *chart;
    std::vector<double> intersezione_X;
    double intersezione_Y;
    bool viewIsEmpty;


private slots:
    void on_disegna_clicked();
    void on_zoomin_clicked();
    void on_zoomout_clicked();
    void on_intersezione_clicked();
    bool eventFilter(QObject *obj, QEvent *event);
};
#endif // MAINWINDOW_H
