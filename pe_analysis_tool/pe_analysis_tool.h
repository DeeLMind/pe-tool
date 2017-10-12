#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include "ui_pe_analysis_tool.h"
#include <QFile>

class QAction;
class QLabel;
class QStatusBar;
class QDragEnterEvent;
class QDropEvent;
class QStandardItemModel;

extern QApplication* pApp;

class pe_analysis_tool : public QMainWindow
{
	Q_OBJECT

public:
	pe_analysis_tool(QWidget *parent = Q_NULLPTR);

// Qt4�б���Ҫ��slots��Qt5������
private:
  void open();
  void opensafe();
  void close();
  void save();
  void saveas();
  void preference();
  void aboutbox();
  void changeskin();
  // ���ļ���bMode = false Ϊֻ����
  bool openFile(const QString& strFile, bool bMode = true);
  void initTreeView();

protected:
  void dragEnterEvent(QDragEnterEvent* event);  // �϶������¼�
  void dropEvent(QDropEvent* event); // �϶������¼�


private:
	Ui::pe_analysis_toolClass ui;
  
  QAction* openAction;
  QAction* opensafeAction;
  QAction* closeAction;
  QAction* saveAction;
  QAction* saveasAction;
  QAction* preferenceAction;
  QAction* aboutAction;
  QAction* skinAction;
  QAction* sepAction; // ���ڷָ����

  QMenu* file;
  QMenu* settings;
  QMenu* aboutmenu;

  QLabel* msgLabel;

  QFile peFile;
  QString peName;

  QStandardItemModel* treeModel;
};
