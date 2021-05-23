#ifndef EXDEATH_HH_GUARD
#define EXDEATH_HH_GUARD

#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QCryptographicHash>
#include <QErrorMessage>
#include <QFile>
#include <QFileDialog>
#include <QFormLayout>
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
	QHBoxLayout *layColumns;
	QVBoxLayout *layColumn2;

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

	QComboBox *selMode;

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

	QGroupBox *grpMulti;
	QFormLayout *layMulti;
	QHBoxLayout *layXP;
	QHBoxLayout *layAP;
	QHBoxLayout *layGil;
	QButtonGroup *butsXP;
	QButtonGroup *butsAP;
	QButtonGroup *butsGil;
	QRadioButton *radXP[4];
	QRadioButton *radAP[4];
	QRadioButton *radGil[4];

	void initMain(void);
	void initInnates(void);
	void initMulti(void);
	void btnROM_clicked(bool trigger);
	void btnApply_clicked(bool trigger);
	void applyPatch(QFile *file, QString patch);
	void applyInnates(QFile *file);
};

#endif