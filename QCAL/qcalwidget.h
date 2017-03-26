#ifndef QCALWIDGET_H
#define QCALWIDGET_H

#include <QMainWindow>
#include <QDebug>
#include "ui_qcalwidget.h"
#include "visa/visa.h"


#define READ_BUFFER_SIZE 4096

namespace Ui {
class QCALWidget;
}

class QCALWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit QCALWidget(QWidget *parent = 0);
    ~QCALWidget();

private slots:
    void on_pushButtonQCALScan_released();

    void on_pushButtonQCALConnect_released();

private:
    Ui::QCALWidget *ui;
};

#endif // QCALWIDGET_H
