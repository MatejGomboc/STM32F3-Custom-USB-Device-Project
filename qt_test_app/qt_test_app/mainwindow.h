#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_toggleLEDPushButton_clicked();
    void on_refreshPushButton_clicked();

private:
    Ui::MainWindow* ui;
    int selection;
};

#endif // MAINWINDOW_H
