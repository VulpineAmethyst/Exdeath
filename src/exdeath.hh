#ifndef EXDEATH_HH_GUARD
#define EXDEATH_HH_GUARD

#include <random>

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
#include <QList>
#include <QPixmap>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QSpinBox>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QWidget>

#include "data.hh"
#include "randomizer.hh"
#if 0
#include "fiesta.hh"
#endif

class Exdeath : public QWidget {
public:
	Exdeath(QSettings *cfg, QList<QPair<QString,QString> > modes, QList<QPair<QString,QString> > NEDs, QWidget *parent = nullptr);
	~Exdeath();

private:
	QSettings *_cfg;
	QString filename;

	QErrorMessage *error;

	QVBoxLayout *layApp;
	QHBoxLayout *layColumns;
	QVBoxLayout *layLeft;
	QVBoxLayout *layRight;

	// Main settings
	QGridLayout *layMain;
	QGroupBox *grpMain;
	QLabel *txtROM;
	QLabel *txtMode;
	QLabel *txtUnlock;
	QLabel *txtPortraits;
	QLabel *txtSound;
	QPushButton *btnROM;
	QPushButton *btnApply;
	QPushButton *btnSave;
	QComboBox *selMode;
	QCheckBox *chkUnlock;
	QCheckBox *chkPortraits;
	QCheckBox *chkSound;

	// Randomized settings
	QGroupBox *grpRandom;
	QFormLayout *layRandom;
	QSpinBox *numSeed;
	QComboBox *selNED;
	QCheckBox *chkRandom;
#if 0
	QCheckBox *chkFiesta;
	QComboBox *selFiesta;
	QComboBox *selModifier;
	//QCheckBox *chkVoid;
#endif

	// Innate abilities
	QGroupBox *grpInnates;
	QVBoxLayout *layInnates;
	QCheckBox *chkPassages;
	QCheckBox *chkPitfalls;
	QCheckBox *chkLiteStep;
	QCheckBox *chkDash;
	QCheckBox *chkLearning;
	bool innates_enabled;

	// Multipliers
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

	// NED preview
	QGroupBox *grpPreview;
	QVBoxLayout *layPreview;
	QLabel *txtPreview;
	QPixmap *imgPreview;

	// Initialization
	void initMain(QList<QPair<QString,QString> > modes);
	void initInnates(void);
	void initRandom(QList<QPair<QString,QString> > NEDs);
	void initMulti(void);
	void initPreview(void);
	void initConfig(void);

	// Event handlers
	void btnROM_clicked(bool trigger);
	void btnApply_clicked(bool trigger);
	void btnSave_clicked(bool trigger);
	void selMode_index(int idx);
	void selNED_index(int idx);

	// Where the magic happens
	void applyPatch(QFile *file, QIODevice *Data);
	void applyInnates(QFile *file);
};

#endif
