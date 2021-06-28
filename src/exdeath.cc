/*
 * Copyright (c) 2021, Sheila Aman.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the software nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <QApplication>

#include "exdeath.hh"

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <climits>

Exdeath::Exdeath(QSettings *cfg, QWidget *parent) : QWidget(parent) {
	error = new QErrorMessage();
	filename = nullptr;
	_cfg = cfg;

	setWindowTitle(QApplication::applicationDisplayName() + " " + QApplication::applicationVersion());

	layApp = new QVBoxLayout(this);
	layColumns = new QHBoxLayout(this);
	layApp->addLayout(layColumns);
	layLeft = new QVBoxLayout(this);
	layRight = new QVBoxLayout(this);
	layColumns->addLayout(layLeft);
	layColumns->addLayout(layRight);

	initMain();
	initRandom();
	initInnates();
	initMulti();
	initPreview();
	initConfig();

	connect(btnROM, &QPushButton::clicked, this, &Exdeath::btnROM_clicked);
	connect(selMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Exdeath::selMode_index);
	connect(selNED, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Exdeath::selNED_index);
	connect(btnApply, &QPushButton::clicked, this, &Exdeath::btnApply_clicked);
	connect(btnSave, &QPushButton::clicked, this, &Exdeath::btnSave_clicked);
}

Exdeath::~Exdeath() {}

void Exdeath::initMain(void) {
	layMain = new QGridLayout(this);
	grpMain = new QGroupBox("Main");
	grpMain->setLayout(layMain);
	layLeft->addWidget(grpMain);

	txtROM  = new QLabel("ROM:");
	btnROM  = new QPushButton("Select ROM");

	txtMode = new QLabel("Mode:");
	selMode = new QComboBox();
	selMode->addItem("Base");
	selMode->addItem("Waddler Rebalance", "waddle.ips");
	selMode->addItem("Balance", "balance.ips");
	selMode->addItem("Custom Classes", "custom_classes.ips");

	txtUnlock = new QLabel("Unlock Jobs:");
	chkUnlock = new QCheckBox("Yes");

	txtPortraits = new QLabel("FFT-style Portraits:");
	chkPortraits = new QCheckBox("Yes");

	txtSound     = new QLabel("Sound Restoration:");
	txtSound->setToolTip("Requires GBA BIOS if using VisualBoyAdvance");
	chkSound     = new QCheckBox("Yes");

	btnApply = new QPushButton("Apply");
	layApp->addWidget(btnApply);
	btnSave  = new QPushButton("Save Config");

	layMain->addWidget(txtROM, 0, 0);
	layMain->addWidget(btnROM, 0, 1);
	layMain->addWidget(txtMode, 1, 0);
	layMain->addWidget(selMode, 1, 1);
	layMain->addWidget(txtUnlock, 2, 0);
	layMain->addWidget(chkUnlock, 2, 1);
	layMain->addWidget(txtPortraits, 3, 0);
	layMain->addWidget(chkPortraits, 3, 1);
	layMain->addWidget(txtSound, 4, 0);
	layMain->addWidget(chkSound, 4, 1);
	layMain->addWidget(btnSave, 5, 1);
}

void Exdeath::initRandom(void) {
	layRandom = new QFormLayout(this);
	grpRandom = new QGroupBox("Randomization");
	grpRandom->setLayout(layRandom);
	layLeft->addWidget(grpRandom);

	numSeed = new QSpinBox();
	numSeed->setRange(0, INT_MAX);
	// provide a default value so it's not just 0 all the time
	numSeed->setValue(time(NULL) / 3600);
	layRandom->addRow("Seed:", numSeed);

	selNED = new QComboBox();
	selNED->addItem("Random", "random");
	selNED->addItem("Vanilla", "vanilla");
	selNED->setCurrentIndex(1);
	selNED->addItem("Absolute Virtue", "abs_vir");
	selNED->addItem("Barf", "barf");
	selNED->addItem("Biolizard", "biolizard");
	selNED->addItem("Cactuar", "cactuar");
	selNED->addItem("Chain Chomp", "chomp");
	//selNED->addItem("Classic", "classic");
	selNED->addItem("Chaos", "chaos");
	selNED->addItem("Cloud of Darkness", "cad");
	selNED->addItem("Doomtrain", "train");
	selNED->addItem("Emperor", "emperor");
	selNED->addItem("Fiends", "fiend_ned");
	selNED->addItem("Flammie (1)", "flammie1");
	selNED->addItem("Flammie (2)", "flammie2");
	selNED->addItem("Fly", "fly");
	selNED->addItem("Godzilla", "godzilla");
	selNED->addItem("Lavos Spawn", "lavos-spawn");
	selNED->addItem("Kefka", "kefka");
	selNED->addItem("MechaGodzilla", "mechagodzilla");
	selNED->addItem("Metroid", "metroid");
	selNED->addItem("Neo X Death", "neo-x-death");
	selNED->addItem("Neo ExDesert", "NeoExDesert");
	selNED->addItem("Neo ExDuck", "neoexduck");
	selNED->addItem("Neon ExDeath", "fancy");
	selNED->addItem("Nero Exdeath", "nero_exdeath");
	selNED->addItem("Omega Larboard Cannon", "omega_cannon");
	selNED->addItem("Puzzle & Dragon", "pad");
	selNED->addItem("Romancing SaGa 3 Boss", "rs3boss");
	selNED->addItem("Shaq", "shaq");
	selNED->addItem("Stupid Sexy Flanders", "flanders");
	selNED->addItem("TargetNED", "targetned");
	selNED->addItem("Territorial Oak", "tree");
	selNED->addItem("Thomas the Tank Engine", "thomas");
	selNED->addItem("Yiazmat", "yiazmat");
	layRandom->addRow("Neo ExDeath:", selNED);

	chkRandom = new QCheckBox("Yes");
	layRandom->addRow("Abilities:", chkRandom);

#if 0
	chkFiesta = new QCheckBox("Yes");
	layRandom->addRow("Fiesta:", chkFiesta);

	selFiesta = new QComboBox();
	selFiesta->addItem("Normal", RunNormal);
	selFiesta->setCurrentIndex(0);
	selFiesta->addItem("Normal 750", Run750);
	selFiesta->addItem("Normal No750", RunNo750);
	selFiesta->addItem("Random", RunRandom);
	selFiesta->addItem("Random 750", RunRandom750);
	selFiesta->addItem("Random No750", RunRandomNo750);
	selFiesta->addItem("Chaos", RunChaos);
	selFiesta->addItem("Chaos 750", RunChaos750);
	selFiesta->addItem("Chaos No750", RunChaosNo750);
	selFiesta->addItem("Pure Chaos", RunPure);
	selFiesta->addItem("Advance", RunAdvance);
	layRandom->addRow("Run:", selFiesta);

	selModifier = new QComboBox();
	selModifier->addItem("None", ModNone);
	selModifier->addItem("Fifth Job", ModFifth);
	//selModifier->addItem("Forbidden", ModVoid);
	layRandom->addRow("Modifier:", selModifier);
#endif
}

void Exdeath::initInnates(void) {
	layInnates = new QVBoxLayout(this);
	grpInnates = new QGroupBox("Innate abilities");
	grpInnates->setLayout(layInnates);
	layRight->addWidget(grpInnates);

	chkPassages = new QCheckBox("Innate Passages");
	chkPitfalls = new QCheckBox("Innate Pitfalls");
	chkLiteStep = new QCheckBox("Innate Light Step");
	chkDash     = new QCheckBox("Innate Dash");
	chkLearning = new QCheckBox("Innate Learning");
	layInnates->addWidget(chkPassages);
	layInnates->addWidget(chkPitfalls);
	layInnates->addWidget(chkLiteStep);
	layInnates->addWidget(chkDash);
	layInnates->addWidget(chkLearning);
}

void Exdeath::initMulti(void) {
	grpMulti = new QGroupBox("Multipliers");
	layMulti = new QFormLayout(this);
	grpMulti->setLayout(layMulti);
	layRight->addWidget(grpMulti);

	layXP = new QHBoxLayout(this);
	butsXP = new QButtonGroup();
	layAP = new QHBoxLayout(this);
	butsAP = new QButtonGroup();
	layGil = new QHBoxLayout(this);
	butsGil = new QButtonGroup();

	int i[4] = {1, 2, 4, 8};
	for (int j = 0; j < 4; j++) {
		char temp[2];
		snprintf(temp, 2, "%dx", i[j]);
		radXP[j] = new QRadioButton(temp);
		radAP[j] = new QRadioButton(temp);
		radGil[j] = new QRadioButton(temp);
		butsXP->addButton(radXP[j]);
		butsXP->setId(radXP[j], i[j]);
		butsAP->addButton(radAP[j]);
		butsAP->setId(radAP[j], i[j]);
		butsGil->addButton(radGil[j]);
		butsGil->setId(radGil[j], i[j]);
		layXP->addWidget(radXP[j]);
		layAP->addWidget(radAP[j]);
		layGil->addWidget(radGil[j]);
	}
	radXP[0]->setChecked(true);
	radAP[0]->setChecked(true);
	radGil[0]->setChecked(true);
	layMulti->addRow("XP:", layXP);
	layMulti->addRow("AP:", layAP);
	layMulti->addRow("Gil:", layGil);
}

void Exdeath::initPreview(void) {
	grpPreview = new QGroupBox("Neo Exdeath Preview");
	layPreview = new QVBoxLayout();
	txtPreview = new QLabel();
	imgPreview = new QPixmap(":/gallery/ned/vanilla.png");
	txtPreview->setPixmap(*imgPreview);
	grpPreview->setLayout(layPreview);
	layPreview->addWidget(txtPreview);
	layRight->addWidget(grpPreview);
}

void Exdeath::initConfig(void) {
	QString version = QApplication::applicationVersion();
	// don't load config from old versions.
	if (!version.compare(_cfg->value("main/version", version).toString())) {
		return;
	}
	QString temp = _cfg->value("rom/filename", "").toString();

	if (temp.length() != 0) {
		filename = temp;
	}
	selMode->setCurrentIndex(_cfg->value("main/mode", 0).toInt());
	selNED->setCurrentIndex(_cfg->value("main/ned", 1).toInt());
	chkPortraits->setChecked(_cfg->value("main/portraits", false).toBool());
	chkSound->setChecked(_cfg->value("main/sound_restore", false).toBool());

	innates_enabled = _cfg->value("innate/enabled", true).toBool();
	chkPassages->setChecked(_cfg->value("innate/passages", false).toBool());
	chkPitfalls->setChecked(_cfg->value("innate/pitfalls", false).toBool());
	chkLiteStep->setChecked(_cfg->value("innate/litestep", false).toBool());
	chkDash->setChecked(_cfg->value("innate/dash", false).toBool());
	chkLearning->setChecked(_cfg->value("innate/learning", false).toBool());
#if 0
	chkFiesta->setChecked(_cfg->value("fiesta/enable", false).toBool());
	selFiesta->setCurrentIndex(_cfg->value("fiesta/mode", 0).toInt());
#endif
	butsXP->button(_cfg->value("multi/xp", 1).toInt())->setChecked(true);
	butsAP->button(_cfg->value("multi/ap", 1).toInt())->setChecked(true);
	butsGil->button(_cfg->value("multi/gil", 1).toInt())->setChecked(true);
}

void Exdeath::selNED_index(int idx) {
	imgPreview = new QPixmap(":/gallery/ned/" + selNED->itemData(idx).toString() + ".png");
	txtPreview->setPixmap(*imgPreview);
}

void Exdeath::selMode_index(int idx) {
	bool random_ok = false;
	bool unlock_ok = false;
	bool innate_ok = false;
	bool sound_ok  = false;
	bool ned_ok    = false;

	if (idx < 2) {
		unlock_ok = true;
		innate_ok = true;
		sound_ok  = true;
		ned_ok    = true;
	}
	if (idx == 0) {
		random_ok = true;
	}

	chkRandom->setEnabled(random_ok);

	chkUnlock->setEnabled(unlock_ok);
	chkSound->setEnabled(sound_ok);

	selNED->setEnabled(ned_ok);

	chkPassages->setEnabled(innate_ok);
	chkPitfalls->setEnabled(innate_ok);
	chkLiteStep->setEnabled(innate_ok);
	chkDash->setEnabled(innate_ok);
	chkLearning->setEnabled(innate_ok);
	innates_enabled = innate_ok;
}

void Exdeath::btnSave_clicked(bool trigger) {
	_cfg->setValue("main/version", QApplication::applicationVersion());
	_cfg->setValue("rom/filename", filename);
	_cfg->setValue("main/mode", selMode->currentIndex());
	_cfg->setValue("main/ned", selNED->currentIndex());
	_cfg->setValue("main/portraits", chkPortraits->isChecked());
	_cfg->setValue("main/sound_restore", chkSound->isChecked());

	_cfg->setValue("innate/enabled", innates_enabled);
	_cfg->setValue("innate/passages", chkPassages->isChecked());
	_cfg->setValue("innate/pitfalls", chkPitfalls->isChecked());
	_cfg->setValue("innate/litestep", chkLiteStep->isChecked());
	_cfg->setValue("innate/dash", chkDash->isChecked());
	_cfg->setValue("innate/learning", chkLearning->isChecked());
#if 0
	_cfg->setValue("fiesta/enable", chkFiesta->isChecked());
	_cfg->setValue("fiesta/mode", selFiesta->currentIndex());
#endif
	_cfg->setValue("multi/xp", butsXP->checkedId());
	_cfg->setValue("multi/ap", butsAP->checkedId());
	_cfg->setValue("multi/gil", butsGil->checkedId());
	_cfg->sync();
}

void Exdeath::btnROM_clicked(bool trigger) {
	filename = QFileDialog::getOpenFileName(
		this,
		"Select ROM image",
		#ifdef __WIN32__
		QApplication::applicationDirPath(),
		#else
		QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0],
		#endif
		"GBA ROM images (*.gba)"
	);
	_cfg->setValue("rom/filename", filename);
	QFile *target = new QFile(filename);
	QCryptographicHash *md5 = new QCryptographicHash(QCryptographicHash::Md5);
	target->open(QIODevice::ReadOnly);
	if (md5->addData(target)) {
		if (md5->result().toHex().compare("9ed82843cc54876362be56faccb15d75") != 0) {
			error->showMessage("You must provide a Final Fantasy V Advance US image.");
			filename = nullptr;
		}
	}
	target->close();
}
void Exdeath::btnApply_clicked(bool trigger) {
	if (filename == nullptr) {
		error->showMessage("You can't apply patches without a ROM.");
		return;
	}
	QFile *target;
	QStringList patches;
	QString output = QFileDialog::getSaveFileName(
		this,
		"Select target ROM image",
		QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0],
		"GBA ROM images (*.gba)"
	);
	QFile::copy(filename, output);
	int mode = selMode->currentIndex();
	std::mt19937 rand(numSeed->value());
	std::uniform_int_distribution<> dist(1, selNED->count() - 1);

	// Unconditionally include this patch.
	patches << ":/patches/fixnames.ips";

	if (mode > 0) {
		patches << ":/patches/" + selMode->itemData(mode).toString();
	}
	if (chkUnlock->isChecked() && chkUnlock->isEnabled()) {
		patches << ":/patches/unlock.ips";
	}
	if (chkPortraits->isChecked()) {
		patches << ":/patches/portraits.ips";
	}
	if (chkSound->isEnabled() && chkSound->isChecked()) {
		patches << ":/patches/sound_restoration.ips";
	}
	int idx = selNED->currentIndex();
	if (idx == 0) {
		idx = dist(rand);
	}
	if (selNED->isEnabled() && (idx > 1)) {
		patches << ":/patches/ned/" + selNED->itemData(idx).toString() + ".ips";
	}
	char *XP = butsXP->checkedButton()->text().toLatin1().data();
	if (strncmp(XP, "1", 2)) {
		QString temp = ":/patches/xp/";
		temp.append(XP);
		temp.append("x.ips");
		patches << temp.toLatin1().data();
	}
	char *AP = butsAP->checkedButton()->text().toLatin1().data();
	if (strncmp(AP, "1", 2)) {
		QString temp = ":/patches/ap/";
		temp.append(AP);
		temp.append("x.ips");
		patches << temp.toLatin1().data();
	}
	char *Gil = butsGil->checkedButton()->text().toLatin1().data();
	if (strncmp(Gil, "1", 2)) {
		QString temp = ":/patches/gil/";
		temp.append(Gil);
		temp.append("x.ips");
		patches << temp.toLatin1().data();
	}

	target = new QFile(output);
	target->open(QIODevice::ReadWrite);
	if (patches.size() > 0) {
		for (int i = 0; i < patches.size(); i++) {
			QFile *patch = new QFile(patches[i]);
			patch->open(QIODevice::ReadOnly);
			applyPatch(target, patch);
		}
	}

	bool global_innates = innates_enabled && (chkPassages->isChecked() || chkPitfalls->isChecked() || chkLiteStep->isChecked() || chkDash->isChecked() || chkLearning->isChecked());
	if (chkRandom->isChecked() && chkRandom->isEnabled()) {
		Randomizer *rando = new Randomizer(rand);
		QFile *pfile = new QFile(output + ".random.ips");
		pfile->open(QIODevice::WriteOnly);
		QBuffer *patch = rando->makeRandom(global_innates);
		pfile->write(patch->readAll());
		patch->seek(0);
		pfile->close();
		applyPatch(target, patch);
	}
#if 0
	if (chkFiesta->isChecked()) {
		Fiesta *fiesta = new Fiesta(rand);
		QFile *pfile = new QFile(output + ".fiesta.ips");
		pfile->open(QIODevice::WriteOnly);
		QBuffer *patch = fiesta->makeRun((RunType)selFiesta->currentIndex(), ModNone);
		pfile->write(patch->readAll());
		patch->seek(0);
		pfile->close();
		applyPatch(target, patch);
	}
#endif
	if (global_innates) {
		applyInnates(target);
	}
	target->close();
}

void Exdeath::applyPatch(QFile *file, QIODevice *data) {
	// skipping header
	data->seek(5);

	while (!data->atEnd()) {
		unsigned int seek = 0;
		unsigned short length = 0;
		char temp[65536];

		data->read(temp, 3);
		if (!strncmp(temp, "EOF", 3)) {
			break;
		}

		seek = ((temp[0] & 0xff) << 16) + ((temp[1] & 0xff) << 8) + (temp[2] & 0xff);
		file->seek(seek);
		data->read(temp, 2);
		length = ((temp[0] & 0xff) << 8) + (temp[1] & 0xff);

		if (length == 0) {
			// RLE hunk
			data->read(temp, 2);
			length = ((temp[0] & 0xff) << 8) + (temp[1] & 0xff);
			data->read(temp, 1);

			for (unsigned int i = 0; i < length; i++) {
				file->write(temp, 1);
			}
		} else {
			data->read(temp, length);
			file->write(temp, length);
		}
	}

	file->flush();
	data->close();
}
void Exdeath::applyInnates(QFile *file) {
	unsigned char base = 0;

	if (chkPassages->isChecked()) base |= Innate::Passages;
	if (chkPitfalls->isChecked()) base |= Innate::Pitfalls;
	if (chkLiteStep->isChecked()) base |= Innate::LiteStep;
	if (chkDash->isChecked())     base |= Innate::Dash;
	if (chkLearning->isChecked()) base |= Innate::ILearning;

	for (int i = 0; i < 26; i++) {
		char temp[2];
		file->seek(job_innates + (i * 2));
		file->read(temp, 2);
		temp[0] |= base;
		file->seek(job_innates + (i * 2));
		file->write(temp, 2);
	}
}
