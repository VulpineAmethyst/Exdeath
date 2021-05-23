#ifndef EXDEATH_HH_GUARD
#define EXDEATH_HH_GUARD

#include <QCheckBox>
#include <QComboBox>
#include <QCryptographicHash>
#include <QErrorMessage>
#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QIODevice>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QWidget>

#include "data.hh"

class Exdeath : public QWidget {
public:
	Exdeath(QWidget *parent = nullptr);
	~Exdeath();

private:
	QString filename;

	QErrorMessage *error;

	QVBoxLayout *layApp;
	QVBoxLayout *layColumns;

	QGridLayout *layMain;
	QVBoxLayout *layMode;
	QGroupBox *grpMain;

	QLabel *txtROM;
	QLabel *txtMode;
	QLabel *txtPortraits;
	QLabel *txtAP;
	QLabel *txtSound;
	QLabel *txtNED;

	QPushButton *btnROM;
	QPushButton *btnApply;

	QRadioButton *radBase;
	QRadioButton *radFiesta;
	QRadioButton *radBalance;
	QRadioButton *radCClass;

	QCheckBox *chkPortraits;
	QCheckBox *chkAP;
	QCheckBox *chkSound;

	QComboBox *selNED;

	QGroupBox *grpInnates;
	QVBoxLayout *layInnates;
	
	QCheckBox *chkPassages;
	QCheckBox *chkPitfalls;
	QCheckBox *chkLiteStep;
	QCheckBox *chkDash;
	QCheckBox *chkLearning;

	void initMain(void);
	void initInnates(void);
	void btnROM_clicked(bool trigger);
	void btnApply_clicked(bool trigger);
	void applyPatch(QFile *file, QString patch);
	void applyDemi(QFile *file);
};

#endif