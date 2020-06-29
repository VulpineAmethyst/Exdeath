/*
 * Copyright (c) 2020, Kiyoshi Aman.
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

#include "exdeath.hh"
#include <cstring>
#include <cstdlib>
#include <cstdio>

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
	radCClass  = new QRadioButton("Custom Classes");
	radBase->setChecked(true);
	layMode->addWidget(radBase);
	layMode->addWidget(radFiesta);
	layMode->addWidget(radBalance);
	layMode->addWidget(radCClass);

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
	} else if (radCClass->isChecked()) {
		patches << ":/patches/custom_classes.ips";
		patches << ":/patches/cc_spellblade.ips";
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
	target->open(QIODevice::ReadWrite);

	for (int i = 0; i < patches.size(); i++) {
		applyPatch(target, patches[i]);
	}

	target->close();
}

void Exdeath::applyPatch(QFile *file, QString patch) {
	QFile *data = new QFile(patch);
	data->open(QIODevice::ReadOnly);

	// skipping header
	data->seek(5);

	while (!data->atEnd()) {
		unsigned int seek = 0;
		unsigned short length = 0;
		char *temp = reinterpret_cast<char *>(malloc(65536));

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
