#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QImage image("path");
    QImage image2(image.width(), image.height(), QImage::Format_Grayscale8);

    QFile file("data.txt");

    for (int i = 0; i < image.width(); i++)
    {
        QByteArray line;

        for (int j = 0; j < image.height(); j++)
        {
           auto qcolor = image.pixelColor(i, j);
           //line.append(QString::number(qcolor.red(), 10) + QString::number(qcolor.green(), 10) + QString::number(qcolor.blue(), 10) + " ");
           line.append(QString::number(qcolor.red(), 10) + " ");

        }


        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            QMessageBox::warning(this, "sdf", "can't open", QMessageBox::Yes);
        }

        QTextStream stream(&file);
        stream << line << "\n";
        file.close();

    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can't open the file!" << endl;
    }
    while (!file.atEnd()) {
        for (int i = 0; i < image.height(); i++)

        {
            QByteArray line = file.readLine();
            auto row = line.trimmed().split(' ');
            for (int j = 0; j < image.width(); j++)
            {
                //image2.setPixel(i, j, row[j].toUInt(NULL, 16));
                image2.setPixel(i, j, row[j].toUInt(nullptr, 10));
            }
        }

    }
    file.close();
    QPixmap pix = QPixmap::fromImage(image, Qt::AutoColor);
    ui->label->setPixmap(pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}

