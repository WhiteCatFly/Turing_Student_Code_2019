#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include "score.h"

std::string score::PRO[31]={"北京","天津","重庆","河北","山西","辽宁","吉林","黑龙江","江苏","安徽",
    "福建","山东","河南","湖北","湖南","广东","海南","四川","贵州","云南",
    "陕西","青海","内蒙古","广西","宁夏","甘肃","江西","西藏","新疆","浙江","上海"};
std::string score::PRO_[31]={"beijing","tianjin","chongqing","hebei","shanxi_1","liaoning",
"jilin","heilongjiang","jiangsu","anhui","fujian","shandong","henan","hubei","hunan","guangdong",
"hainan","sichuan","guizhou","yunnan","shanxi_2","qinghai","neimenggu","guangxi",
"ningxia","gansu","jiangxi","xizang","xinjiang","zhejiang","shanghai"};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("麦芒高考志愿填报系统");
    w.show();

    return a.exec();
}
