#ifndef HINT_H
#define HINT_H

#include <QDialog>

namespace Ui {
class hint;
}

class hint : public QDialog
{
    Q_OBJECT

public:
    explicit hint(QWidget *parent = nullptr);
    ~hint();

private slots:

    void on_exit_clicked();

private:
    Ui::hint *ui;
};

#endif // HINT_H
