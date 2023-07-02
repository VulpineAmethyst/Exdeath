/*
 * Copyright (c) 2023, Síle Ekaterin Liszka.
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

#include "patch.hh"

QList<QPair<QString,QString> > getPatchList(QDir dir, PatchType type) {
	QList<QPair<QString,QString> > list;

	if (!dir.exists()) {
		return list;
	}
	if (type == PatchType::Mode) {
		dir.cd("modes");
		if (!dir.exists()) {
			return list;
		}
	} else if (type == PatchType::NED) {
		dir.cd("ned");
		if (!dir.exists()) {
			return list;
		}
	}
	dir.setFilter(QDir::Files | QDir::Readable);
	dir.setSorting(QDir::Name);

	QFileInfoList files = dir.entryInfoList();

	for (int i = 0; i < files.size(); i++) {
		QFileInfo file = files.at(i);

		if (file.suffix() == "ips") {
			QString filename = file.canonicalPath() + "/" + file.completeBaseName() + ".ips";
			QPair<QString,QString> pair = {file.completeBaseName(), filename};

			list.append(pair);
		}
	}

	return list;
}