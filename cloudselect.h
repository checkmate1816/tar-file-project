#ifndef CLOUDSELECT_H
#define CLOUDSELECT_H

#include <QMainWindow>

namespace Ui {
class cloudselect;
}

class cloudselect : public QMainWindow
{
    Q_OBJECT

public:
    explicit cloudselect(QWidget *parent = nullptr);
    ~cloudselect();

private slots:
    void on_upload_clicked();

    void on_download_clicked();

private:
    Ui::cloudselect *ui;
};

#endif // CLOUDSELECT_H
