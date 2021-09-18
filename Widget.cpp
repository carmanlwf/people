#include "Widget.h"
#include "./ui_Widget.h"
#include "math.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButtonClear_clicked()
{
    ui->textBrowser->clear();

}


void Widget::on_pushButtonOK_clicked()
{

    auto  year = ui->spinBox_year->value();
    auto  total = ui->spinBox_Total->value() * 100 ; // 百万
    auto births = ui->spinBox_Births->value();
    auto  deaths = ui->spinBox_Deaths->value();

    auto birthRate = ui->spinBoxBirthRate->value();
    auto  deathRate = ui->spinBox_DeathRate->value();

    //  计算规则 ：  每年人口  =   总人口 + （出生人口 x (1-降低的出生率)^n）- (死亡人口 x (1+ 增加的死亡率)^n)

    auto  tmp  =  total;
    for (int var = 1; var <= year ; ++var) {
        //total + (births  * pow((1- birthRate/100.0),  var) )  - (deaths * pow((1+deathRate/100.0), var ));

        ui->textBrowser->append(QString("********************* year   %1  ***************").arg(var));
        //ui->textBrowser->append(QString(" "));
        auto  tmpBirth =  (births  * pow((1- birthRate/100.0),  qMin(var, 10)));
        ui->textBrowser->append(QString("Birth : %1").arg(tmpBirth));
       // ui->textBrowser->append(QString(" "));
        auto  tmpDeath = (deaths * pow((1+deathRate/100.0), qMin(var, 10) ));
        ui->textBrowser->append(QString("Death : %1").arg(tmpDeath));
        //ui->textBrowser->append(QString(" "));
        auto tmpToatl =  tmp + tmpBirth -tmpDeath;
        tmp  =  tmpToatl;
        ui->textBrowser->append(QString("Total : %1").arg(tmpToatl ));
        //ui->textBrowser->append(QString(" "));
        if(tmpToatl  < 0)
            return;
    }


}

