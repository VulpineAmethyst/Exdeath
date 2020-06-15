
#include "exdeath.hh"
#include <cstring>
#include <iostream>

Exdeath::Exdeath(QWidget *parent) : QWidget(parent) {
	error = new QErrorMessage();
	filename = nullptr;

	layMain = new QGridLayout(this);
	layMode = new QVBoxLayout(this);

	txtROM       = new QLabel("ROM:");
	txtMode      = new QLabel("Mode:");
	txtPortraits = new QLabel("FFT-style Portraits:");
	txtAP        = new QLabel("Double AP:");
	txtSound     = new QLabel("Sound Restoration:");
	txtSound->setToolTip("Requires GBA BIOS if using VisualBoyAdvance");

	btnROM   = new QPushButton("Select ROM");
	btnApply = new QPushButton("Apply");

	radBase    = new QRadioButton("Base");
	radFiesta  = new QRadioButton("Fiesta");
	radBalance = new QRadioButton("Balance");
	radBase->setChecked(true);
	layMode->addWidget(radBase);
	layMode->addWidget(radFiesta);
	layMode->addWidget(radBalance);

	chkPortraits = new QCheckBox("Yes");
	chkAP        = new QCheckBox("Yes");
	chkSound     = new QCheckBox("Yes");

	layMain->addWidget(txtROM, 0, 0);
	layMain->addWidget(btnROM, 0, 1);
	layMain->addWidget(txtMode, 1, 0);
	layMain->addLayout(layMode, 1, 1);
	layMain->addWidget(txtPortraits, 2, 0);
	layMain->addWidget(chkPortraits, 2, 1);
	layMain->addWidget(txtAP, 3, 0);
	layMain->addWidget(chkAP, 3, 1);
	layMain->addWidget(txtSound, 4, 0);
	layMain->addWidget(chkSound, 4, 1);
	layMain->addWidget(btnApply, 5, 1);

	connect(btnROM, &QPushButton::clicked, this, &Exdeath::btnROM_clicked);
	connect(btnApply, &QPushButton::clicked, this, &Exdeath::btnApply_clicked);
}

Exdeath::~Exdeath() {}

void Exdeath::btnROM_clicked(bool trigger) {
	filename = QFileDialog::getOpenFileName(
		this,
		"Select ROM image",
		QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0],
		"GBA ROM images (*.gba)"
	);
	QFile *target = new QFile(filename);
	QCryptographicHash *md5 = new QCryptographicHash(QCryptographicHash::Md5);
	target->open(QIODevice::ReadOnly);
	if (md5->addData(target)) {
		if (md5->result().toHex().compare("9ed82843cc54876362be56faccb15d75") != 0) {
			error->showMessage("You must provide a Final Fantasy V Advance US image.");
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

	if (radFiesta->isChecked()) {
		patches << ":/patches/fiesta.ips";
	} else if (radBalance->isChecked()) {
		patches << ":/patches/balance.ips";
	}
	if (chkPortraits->isChecked()) {
		patches << ":/patches/portraits.ips";
	}
	if (chkAP->isChecked()) {
		patches << ":/patches/double_ap.ips";
	}
	if (chkSound->isChecked()) {
		patches << ":/patches/sound_restoration.ips";
	}

	if (patches.size() == 0) {
		return;
	}

	target = new QFile(output);
	target->open(QIODevice::WriteOnly | QIODevice::Append);
	target->seek(0);

	std::cout << "Size of target is " << target->size() << std::endl;

	for (int i = 0; i < patches.size(); i++) {
		applyPatch(target, patches[i]);
	}

	target->close();
}

void Exdeath::applyPatch(QFile *file, QString patch) {
	QFile *data = new QFile(patch);
	data->open(QIODevice::ReadOnly);
	char *temp = nullptr;

	if (data->read(temp, 5) != 5) {
		std::cout << "what the fuck?" << std::endl;
		data->close();
		return;
	}

	std::cout << "Just read " << temp << std::endl;

	if (!strncmp(temp, "PATCH", 5)) {
		data->close();
		return;
	}

	std::cout << "Applying patch '" << patch.toStdString() << "'..." << std::endl;

	while (!data->atEnd()) {
		int seek = 0, length = 0;
		data->read(temp, 3);
		if (!strncmp(temp, "EOF", 3)) {
			break;
		}
		seek = (temp[0] << 16) + (temp[1] << 8) + temp[2];
		data->read(temp, 2);
		length = (temp[0] << 8) + temp[1];

		if (length == 0) {
			// RLE hunk
			data->read(temp, 2);
			length = (temp[0] << 8) + temp[1];
			data->read(temp, 1);

			std::cout << "Seeking to " << seek << " and writing " << length << " RLE bytes." << std::endl;
			file->seek(seek);
			for (int i = 0; i < length; i++) {
				file->write(temp, 1);
			}
		} else {
			std::cout << "Seeking to " << seek << " and writing " << length << " bytes";
			data->read(temp, length);
			file->seek(seek);
			file->write(temp, length);
		}
	}

	data->close();
}
