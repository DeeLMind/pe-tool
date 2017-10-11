#include "pe_analysis_tool.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <QStatusBar>
#include <QPainter>
#include <QHBoxLayout>
#include <QTreeView>
#include <QTableView>

pe_analysis_tool::pe_analysis_tool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

  // ����ͼ��
  setWindowIcon(QIcon(":/img/Don_2.jpg"));
  // ���ñ���
  setWindowTitle(QString::fromLocal8Bit("PE��������"));
  // ���ô�С
  // resize(800, 600);

  // ����Ƥ��
  changeskin();

  // �����ָ��õ�Action
  sepAction = new QAction(this);
  sepAction->setEnabled(false);

  // ����������
  QToolBar* toolBar = new QToolBar(this);
  addToolBar(Qt::TopToolBarArea, toolBar);
  toolBar->setMovable(false);
  // toolBar->setStyleSheet(QString("QStatusBar::body{background-color:transparent}"));

  // ����һ�����ļ��Ŀؼ�
  openAction = new QAction(tr("Open"), this);
  openAction->setShortcut(QKeySequence::Open);
  openAction->setStatusTip(tr("Open a file."));
  openAction->setIcon(QIcon(":/img/open_file.png"));
  // �󶨸ÿؼ����źŲ�
  connect(openAction, &QAction::triggered, this, &pe_analysis_tool::open);
  // ���ؼ��󶨵��˵���
  file = menuBar()->addMenu(tr("&File"));
  file->addAction(openAction);
  // ���ؼ��󶨵�������
  toolBar->addAction(openAction);

  // ����һ����ȫ���ļ��Ŀؼ�
  opensafeAction = new QAction(tr("Open (Safe Mode)"), this);
  opensafeAction->setStatusTip(tr("Open (Safe Mode)."));
  // �󶨸ÿؼ����źŲ�
  connect(opensafeAction, &QAction::triggered, this, &pe_analysis_tool::opensafe);
  // ���ؼ��󶨵��˵���
  file->addAction(opensafeAction);

  // ����һ���ر��ļ��Ŀؼ�
  closeAction = new QAction(tr("Close"), this);
  closeAction->setShortcut(QKeySequence::Close);
  closeAction->setStatusTip(tr("Close file."));
  // �󶨸ÿؼ����źŲ�
  connect(closeAction, &QAction::triggered, this, &pe_analysis_tool::close);
  // ���ؼ��󶨵��˵���
  file->addAction(closeAction);

  // �˵��ָ���
  file->addSeparator();

  // ����һ�������ļ��Ŀؼ�
  saveAction = new QAction(tr("Save"), this);
  saveAction->setShortcut(QKeySequence::Save);
  saveAction->setStatusTip(tr("Save file."));
  saveAction->setIcon(QIcon(":/img/save_file.png"));
  // ��ʼ���øÿؼ�����ʹ��
  saveAction->setEnabled(false);
  // �󶨸ÿؼ����źŲ�
  connect(saveAction, &QAction::triggered, this, &pe_analysis_tool::save);
  // ���ؼ��󶨵��˵���
  file->addAction(saveAction);
  // ���ؼ��󶨵�������
  toolBar->addAction(saveAction);
  // toolBar->addSeparator();

  // ����һ������ļ��Ŀؼ�
  saveasAction = new QAction(tr("Save As..."), this);
  saveasAction->setShortcut(QKeySequence::SaveAs);
  saveasAction->setStatusTip(tr("Save As."));
  // �󶨸ÿؼ����źŲ�
  connect(saveasAction, &QAction::triggered, this, &pe_analysis_tool::saveas);
  // ���ؼ��󶨵��˵���
  file->addAction(saveasAction);

  // ����һ�����õĿؼ�
  preferenceAction = new QAction(tr("Preference"), this);
  preferenceAction->setStatusTip(tr("Preference."));
  preferenceAction->setIcon(QIcon(":/img/tool.png"));
  // �󶨸ÿؼ����źŲ�
  connect(preferenceAction, &QAction::triggered, this, &pe_analysis_tool::preference);
  // ���ؼ��󶨵��˵���
  settings = menuBar()->addMenu(tr("&Settings"));
  settings->addAction(preferenceAction);

  // ����һ���л�Ƥ���Ŀؼ�
  aboutAction = new QAction(tr("Change Skin"), this);
  aboutAction->setStatusTip(tr("Change Skin."));
  aboutAction->setIcon(QIcon(":/img/Don_2.jpg"));
  // �󶨸ÿؼ����źŲ�
  connect(aboutAction, &QAction::triggered, this, &pe_analysis_tool::changeskin);
  // �����ڿؼ��󶨵��˵���
  aboutmenu = menuBar()->addMenu(tr("&Help"));
  aboutmenu->addAction(aboutAction);
  // �ڹ���������һ���ָ�����
  toolBar->addAction(sepAction);
  // ���ؼ��󶨵�������
  toolBar->addAction(aboutAction);

  // ����һ�����ڵĿؼ�
  aboutAction = new QAction(tr("About"), this);
  aboutAction->setStatusTip(tr("About."));
  aboutAction->setIcon(QIcon(":/img/Don.png"));
  // �󶨸ÿؼ����źŲ�
  connect(aboutAction, &QAction::triggered, this, &pe_analysis_tool::aboutbox);
  // �����ڿؼ��󶨵��˵���
  // menuBar()->addMenu(QIcon(":/img/Don.png"), tr("About"));
  aboutmenu->addAction(aboutAction);
  // ���ؼ��󶨵�������
  toolBar->addAction(aboutAction);


  
  // ����״̬��
  msgLabel = new QLabel;
  msgLabel->setMinimumSize(msgLabel->sizeHint());
  msgLabel->setAlignment(Qt::AlignHCenter);
  statusBar()->addWidget(msgLabel);
  // ȥ��״̬����������ʾʱ��С��
  statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

}

void pe_analysis_tool::open()
{
  // QMessageBox* msgBox;
  // msgBox = new QMessageBox;
  // msgBox->information(NULL, tr("Open"), tr("Open a file"));
  // ����һ�����ļ��ĶԻ���
  QString path = QFileDialog::getOpenFileName(this,                 // ������ָ��
                                              tr("Open File"),      // �������ڵ�����
                                              ".",                  // ���ļ���·��
                                              tr("All Files(*.*)")  // �ļ����ͣ������������ͨ��ͨ���ָ���ļ�����
                                              
                                             );
  // ��һ��д��
  // QFileDialog* fileDialog = new QFileDialog(this);
  // fileDialog->setWindowTitle(tr("Open Fise"));
  // fileDialog->setDirectory(".");
  // // fileDialog->setFilter(tr("All Files(*.*)")); // ����ʹ������ɸѡ��ʽ
  // fileDialog->setFilter(QDir::Filters::enum_type::AllDirs);
  // fileDialog->exec();
}

void pe_analysis_tool::opensafe()
{
  QString path = QFileDialog::getOpenFileName(this,                 // ������ָ��
                                              tr("Open File"),      // �������ڵ�����
                                              ".",                  // ���ļ���·��
                                              tr("All Files(*.*)")  // �ļ����ͣ������������ͨ��ͨ���ָ���ļ�����
                                             );
}

void pe_analysis_tool::close()
{
}

void pe_analysis_tool::save()
{
  QMessageBox* msgBox;
  msgBox = new QMessageBox;
  msgBox->information(NULL, tr("Save"), tr("Save a file"));
}

void pe_analysis_tool::saveas()
{
  QString path = QFileDialog::getOpenFileName(this,                 // ������ָ��
                                              tr("Open File"),      // �������ڵ�����
                                              ".",                  // ���ļ���·��
                                              tr("All Files(*.*)")  // �ļ����ͣ������������ͨ��ͨ���ָ���ļ�����
                                             );
}

void pe_analysis_tool::preference()
{
}

void pe_analysis_tool::aboutbox()
{
  QMessageBox aboutmsg(QMessageBox::NoIcon, tr("About"), QString::fromLocal8Bit("������ʹ�� <font color='blue'>Qt</font> ����<br><br>Դ�룺<a href='https://github.com/KevinsBobo/pe-tool'>https://github.com/KevinsBobo/pe-tool</a><br><br>���߲��ͣ�<a href='https://kevins.pro'>https://kevins.pro</a>"));
  QPixmap pic(":/img/Don.png");
  QSize size;
  size.setHeight(10);
  size.setWidth(10);
  pic.scaled(size, Qt::KeepAspectRatio);
  aboutmsg.setIconPixmap(pic);
  aboutmsg.exec();
}

void pe_analysis_tool::changeskin()
{
  static int nNum = 0;

  if (nNum == 0)
  {
    pApp->setStyleSheet("");
  }
  else if (nNum == 1)
  {
    QFile qss(":/skin/write.qss");
    qss.open(QFile::ReadOnly);
    pApp->setStyleSheet(qss.readAll());
    qss.close();
  }
  else
  {
    QFile qss(":/skin/black.qss");
    qss.open(QFile::ReadOnly);
    pApp->setStyleSheet(qss.readAll());
    qss.close();
  }

  nNum += 1;
  nNum %= 3;
}
