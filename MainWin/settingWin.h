// author : keke
// date : 2023/02/18
#pragma once
#ifndef __SETTINGWIN__
#define __SETTINGWIN__

#include <QWidget>
#include <QStrNode.hpp>
QT_BEGIN_NAMESPACE
namespace Ui {
class setForm;
} // namespace Ui
QT_END_NAMESPACE
class SettingWin : public QWidget {
Q_OBJECT
public:
  SettingWin(QWidget *parent = nullptr);
  ~SettingWin();

signals:
  void buildTree(sbt::NodePtr headPtr);
public slots:
  void btnx_build_clicked();

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  Ui::setForm *ui;
};

#endif