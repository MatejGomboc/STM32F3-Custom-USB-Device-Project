#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libusb.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    selection(0)
{
    ui->setupUi(this);

    int result = libusb_init(nullptr);
    if (result != LIBUSB_SUCCESS)
        std::exception(("Cannot init LibUSB. Error: " + std::to_string(result)).c_str());
}

MainWindow::~MainWindow()
{
    libusb_exit(nullptr);
    delete ui;
}

void MainWindow::on_toggleLEDPushButton_clicked()
{
    if (ui->devicesListWidget->selectionModel()->selectedRows().count() == 1)
    {
        libusb_device** devs;
        ssize_t cnt = libusb_get_device_list(nullptr, &devs);
        if (cnt < 1)
            return;

        libusb_device_handle* handle = nullptr;
        libusb_device* dev = devs[selection];

        int result = libusb_open(dev, &handle);
        if (result < 0)
            return;

        struct libusb_device_descriptor desc;
        result = libusb_get_device_descriptor(dev, &desc);
        if (result < 0)
            return;

        char data[255];
        result = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, (unsigned char*)data, sizeof(data));
        if (result < 1)
            return;

        volatile QString serial_num = QString(data).left(result);

        result = libusb_set_configuration(handle, 1);
        if (result < 0)
            return;

        result = libusb_claim_interface(handle, 0);
        if (result < 0)
            return;

        result = libusb_control_transfer(
            handle,
            LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_VENDOR|LIBUSB_RECIPIENT_INTERFACE,
            0x00,
            0x0000,
            0x0000,
            (unsigned char*)data,
            0x0000,
            1000
        );

        libusb_close(handle);
        libusb_free_device_list(devs, 1);
    }
    return;
}

void MainWindow::on_refreshPushButton_clicked()
{
    ui->devicesListWidget->clear();

    libusb_device** devs;
    ssize_t cnt = libusb_get_device_list(nullptr, &devs);
    if (cnt < 1)
        return;

    int i = 0;
    libusb_device* dev;
    while ((dev = devs[i++]) != nullptr)
    {
        struct libusb_device_descriptor desc;
        int result = libusb_get_device_descriptor(dev, &desc);
        if (result < 0)
            continue;

        libusb_device_handle* handle = nullptr;
        result = libusb_open(dev, &handle);
        if (result < 0)
            continue;

        char data[255];
        result = libusb_get_string_descriptor_ascii(handle, desc.iProduct, (unsigned char*)data, sizeof(data));
        if (result < 1)
            continue;

        QString product = QString(data).left(result);

        result = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, (unsigned char*)data, sizeof(data));
        if (result < 1)
            continue;

        QString serial_num = QString(data).left(result);

        libusb_close(handle);

        ui->devicesListWidget->addItem(
            product + ", " +
            "VID:" + QString::number(QString::number(desc.idVendor).toInt(), 16).toUpper().rightJustified(2, '0') + ", " +
            "PID:" + QString::number(QString::number(desc.idProduct).toInt(), 16).toUpper().rightJustified(2, '0') + ", " +
            "serial:0x" + serial_num
        );

        selection = i - 1;
    }

    libusb_free_device_list(devs, 1);
    return;
}
