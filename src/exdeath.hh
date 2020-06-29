#ifndef EXDEATH_HH_GUARD
#define EXDEATH_HH_GUARD

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFile>
#include <QIODevice>
#include <QCryptographicHash>
#include <QErrorMessage>

class Exdeath : public QWidget {
public:
	Exdeath(QWidget *parent = nullptr);
	~Exdeath();

private:
	QString filename;

	QErrorMessage *error;

	QGridLayout *layMain;
	QVBoxLayout *layMode;

	QLabel *txtROM;
	QLabel *txtMode;
	QLabel *txtPortraits;
	QLabel *txtAP;
	QLabel *txtSound;

	QPushButton *btnROM;
	QPushButton *btnApply;

	QRadioButton *radBase;
	QRadioButton *radFiesta;
	QRadioButton *radBalance;
	QRadioButton *radCClass;

	QCheckBox *chkPortraits;
	QCheckBox *chkAP;
	QCheckBox *chkSound;

	void btnROM_clicked(bool trigger);
	void btnApply_clicked(bool trigger);
	void applyPatch(QFile *file, QString patch);
};

#endif