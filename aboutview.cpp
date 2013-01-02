#include <QDesktopServices>
#include <QLayout>
#include <QUrl>
#include "aboutview.h"
#include "ui_aboutview.h"

AboutView::AboutView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutView)
{
    ui->setupUi(this);

    QString ver = QApplication::applicationVersion();

    QString s1 = tr("Печать бланков почтовых переводов (версия ") + ver + ")";
    QString s2 = "<a href='mailto:acotwin@gmail.com?subject=bpp.exe(" + ver + ")'>" + tr("Задать вопрос") + "</a>";

    ui->label_version->setText(s1);

    ui->labeltechsupport->setText(s2);

//    QLayout *layout = window()->layout();
//    layout->setSizeConstraint( QLayout::SetFixedSize );

    setFixedSize(width(), height());

    setWindowFlags(Qt::Tool);

    activateWindow();
}

AboutView::~AboutView()
{
    delete ui;
}

void AboutView::on_labeltechsupport_linkActivated(const QString &link)
{



}
